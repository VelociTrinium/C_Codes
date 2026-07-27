#include <stdio.h>

#define N 3 // Number of processes

int main() {
    // Process IDs (p), Arrival Time (at), Burst Time (bt)
    int p[] = {1, 2, 3};
    int at[] = {0, 1, 2};
    int bt[] = {5, 2, 3};
    
    // Completion Time (ct), Turnaround Time (tat), Waiting Time (wt)
    int ct[N], tat[N], wt[N];
    int current_time = 0;
    
    // Header for output table
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < N; i++) {
        // FCFS: Process execution starts when it arrives or when the CPU is free.
        // It must wait until current_time (CPU free) AND it has arrived (at[i]).
        
        // 1. Completion Time (CT)
        if (current_time < at[i]) {
            // CPU is idle until process arrives
            current_time = at[i]; 
        }
        ct[i] = current_time + bt[i];
        current_time = ct[i];
        
        // 2. Turnaround Time (TAT) = CT - AT
        tat[i] = ct[i] - at[i];
        
        // 3. Waiting Time (WT) = TAT - BT
        wt[i] = tat[i] - bt[i];

        // Print results for the current process
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    
    return 0;
}
