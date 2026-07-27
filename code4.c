#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt;
    int done;
};

int main() {
    int n, time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter PID, Arrival Time, Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
        p[i].done = 0;
    }

    while (completed < n) {
        int idx = -1, minBT = 1e9;


        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }


        p[idx].rt = time - p[idx].at;


        time += p[idx].bt;
        p[idx].ct = time;


        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        p[idx].done = 1;
        completed++;

        totalTAT += p[idx].tat;
        totalWT += p[idx].wt;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT = %.2f\n", totalWT / n);

    return 0;
}

