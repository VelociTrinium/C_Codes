#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

#define LOGFILE "backup.log"
#define MAXPATH 4096
#define TIMEFMT "%Y-%m-%d_%H-%M-%S"

static void write_log(const char *dest_dir, const char *msg) {
    char logpath[MAXPATH];
    int fd;
    size_t w;
    size_t len;
    if (sprintf(logpath, "%s/%s", dest_dir, LOGFILE) >= (int)sizeof(logpath)) {
        strcpy(logpath, LOGFILE);
    }
    fd = open(logpath, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        fprintf(stderr, "Error: cannot open log file %s: %s\n", logpath, strerror(errno));
        return;
    }
    len = strlen(msg);
    w = write(fd, msg, len);
    if (w != (size_t)len) {
        fprintf(stderr, "Warning: cannot write complete log: %s\n", strerror(errno));
    }
    write(fd, "\n", 1);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s /path/to/source /path/to/destination\n", argv[0]);
        return 2;
    }
    const char *src = argv[1];
    const char *dest = argv[2];
    struct stat st;
    if (stat(src, &st) == -1) {
        fprintf(stderr, "Error: stat(%s) failed: %s\n", src, strerror(errno));
        return 3;
    }
    if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: source is not a directory: %s\n", src);
        return 4;
    }
    if (stat(dest, &st) == -1) {
        fprintf(stderr, "Error: stat(%s) failed: %s\n", dest, strerror(errno));
        return 5;
    }
    if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: destination is not a directory: %s\n", dest);
        return 6;
    }
    time_t t = time(NULL);
    if (t == (time_t)-1) {
        fprintf(stderr, "Error: time() failed: %s\n", strerror(errno));
        return 7;
    }
    struct tm tm;
    if (localtime_r(&t, &tm) == NULL) {
        fprintf(stderr, "Error: localtime_r failed: %s\n", strerror(errno));
        return 8;
    }
    char timestr[64];
    if (strftime(timestr, sizeof(timestr), TIMEFMT, &tm) == 0) {
        fprintf(stderr, "Error: strftime produced empty string\n");
        return 9;
    }
    char archive[MAXPATH];
    if (snprintf(archive, sizeof(archive), "%s/backup_%s.tar.gz", dest, timestr) >= (int)sizeof(archive)) {
        fprintf(stderr, "Error: destination path too long\n");
        return 10;
    }
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Error: fork failed: %s\n", strerror(errno));
        return 11;
    } else if (pid == 0) {
        execlp("tar", "tar", "-czf", archive, "-C", src, ".", (char *)NULL);
        fprintf(stderr, "Error: execlp(tar) failed: %s\n", strerror(errno));
        return 12;
    } else {
        int status;
        pid_t w = waitpid(pid, &status, 0);
        if (w == -1) {
            fprintf(stderr, "Error: waitpid failed: %s\n", strerror(errno));
            return 12;
        }

        char logbuf[1024];
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code == 0) {
                snprintf(logbuf, sizeof(logbuf),
                         "%s - Backup SUCCESS: %s (created by PID %d)",
                         timestr, archive, (int)pid);
                write_log(dest, logbuf);
                print("Backup successful: %s\n", archive);
                return 0;
            } else {
                snprintf(logbuf, sizeof(logbuf),
                         "%s - Backup FAILED (exit %d): %s (PID %d)",
                         timestr, code, archive, (int)pid);
                write_log(dest, logbuf);
                fprintf(stderr, "Backup process exited with code %d\n", code);
                return 13;
            }
        } else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            snprintf(logbuf, sizeof(logbuf),
                     "%s - Backup TERMINATED by signal %d: %s (PID %d)",
                     timestr, sig, archive, (int)pid);
            write_log(dest, logbuf);
            fprintf(stderr, "Backup process terminated by signal %d\n", sig);
            return 14;
        } else {
            snprintf(logbuf, sizeof(logbuf),
                     "%s - Backup FAILED (unknown reason): %s (PID %d)",
                     timestr, archive, (int)pid);
            write_log(dest, logbuf);
            fprintf(stderr, "Backup process failed for unknown reason\n");
            return 15;
        }
    }
}
