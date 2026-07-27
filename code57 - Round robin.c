#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int rem_bt;     // Remaining Burst Time
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rem_bt = p[i].bt; 
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    int flag = 0; 
    float total_tat = 0, total_wt = 0;

    while (completed != n) {
        flag = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rem_bt > 0) {
                flag = 1;
                if (p[i].rem_bt > tq) {
                    time += tq;
                    p[i].rem_bt -= tq;
                } else {
                    time += p[i].rem_bt;
                    p[i].rem_bt = 0;
                    p[i].ct = time;
                    completed++;
                    p[i].tat = p[i].ct - p[i].at;
					p[i].wt = p[i].tat - p[i].bt;
					total_tat += p[i].tat;
					total_wt += p[i].wt;
                }
            }
        }

        if (flag == 0) time++;
    }


    printf("\n---------------------------------------------\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("---------------------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
