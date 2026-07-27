#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCS 30
#define MAX_RES 10
#define INF 1000000

typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int priority; // 1=High(RR),2=Medium(SRTF),3=Low(FCFS)
    int resource_list[MAX_RES]; // 1 if needs resource r, else 0
    int resource_count;
    int allocated; // 1 if resources allocated, else 0
    int start_time; // first time it got CPU (-1 if never)
    int completion_time;
    int is_completed;
} Process;

Process P[MAX_PROCS];
int n, m;
int avail[MAX_RES];
int allocation[MAX_PROCS][MAX_RES];
int cpu_owner[10000];
int resource_owner[MAX_RES][10000];
int MAX_TIME_RECORD = 10000;

void init_globals() {
    int t;
    for (t = 0; t < MAX_TIME_RECORD; t++) {
        cpu_owner[t] = 0;
        for (int r = 0; r < m; r++) resource_owner[r][t] = 0;
    }
    for (int i=0;i<MAX_PROCS;i++){
        for (int r=0;r<MAX_RES;r++) allocation[i][r]=0;
    }
}

int all_completed() {
    for (int i = 0; i < n; i++) if (!P[i].is_completed) return 0;
    return 1;
}

int is_safe_if_allocate(int pid) {
    int work[MAX_RES];
    int finish[MAX_PROCS];
    int need[MAX_PROCS][MAX_RES];
    int i, r;
    for (i = 0; i < n; i++) {
        for (r = 0; r < m; r++) {
            need[i][r] = 0;
            if (!P[i].is_completed) {
                if (P[i].resource_list[r] && !allocation[i][r]) need[i][r] = 1;
            }
        }
    }
    for (r = 0; r < m; r++) work[r] = avail[r];
    for (r = 0; r < m; r++) {
        if (P[pid].resource_list[r] && !allocation[pid][r]) {
            if (work[r] <= 0) return 0;
            work[r] -= 1; 
        }
    }
    for (i = 0; i < n; i++) finish[i] = (P[i].is_completed ? 1 : 0);
    int sim_alloc[MAX_PROCS][MAX_RES];
    for (i = 0; i < n; i++)
        for (r = 0; r < m; r++)
            sim_alloc[i][r] = allocation[i][r];
    for (r = 0; r < m; r++)
        if (P[pid].resource_list[r]) sim_alloc[pid][r] = 1;
    int changed;
    do {
        changed = 0;
        for (i = 0; i < n; i++) {
            if (finish[i]) continue;
            int can = 1;
            for (r = 0; r < m; r++) {
                int needed = (P[i].resource_list[r] && !sim_alloc[i][r]) ? 1 : 0;
                if (needed > work[r]) { can = 0; break; }
            }
            if (can) {
                for (r = 0; r < m; r++) {
                    if (sim_alloc[i][r]) work[r] += 1;
                }
                finish[i] = 1;
                changed = 1;
            }
        }
    } while (changed);
    for (i = 0; i < n; i++) if (!finish[i]) return 0;
    return 1;
}

int try_allocate(int pid) {
    if (P[pid].allocated) return 1;
    for (int r = 0; r < m; r++) {
        if (P[pid].resource_list[r] && !allocation[pid][r]) {
            if (avail[r] <= 0) return 0;
        }
    }
    if (!is_safe_if_allocate(pid)) return 0;

    for (int r = 0; r < m; r++) {
        if (P[pid].resource_list[r] && !allocation[pid][r]) {
            allocation[pid][r] = 1;
            avail[r] -= 1;
        }
    }
    P[pid].allocated = 1;
    return 1;
}

void release_resources(int pid) {
    for (int r = 0; r < m; r++) {
        if (allocation[pid][r]) {
            allocation[pid][r] = 0;
            avail[r] += 1;
        }
    }
    P[pid].allocated = 0;
}

void collect_ready_lists(int time, int high[], int *hn, int med[], int *mn, int low[], int *ln) {
    *hn = *mn = *ln = 0;
    for (int i = 0; i < n; i++) {
        if (P[i].is_completed) continue;
        if (P[i].arrival <= time) {
            if (P[i].priority == 1) high[(*hn)++] = i;
            else if (P[i].priority == 2) med[(*mn)++] = i;
            else low[(*ln)++] = i;
        }
    }
}

void print_results(int final_time) {
    printf("\n--- PROCESS TABLE ---\n");
    printf("%-5s\t%-5s\t%-5s\t%-5s\t%-15s\t%-5s\t%-5s\t%-5s\t%-5s\n",
           "PID", "AT", "BT", "Pri", "AllocatedRes", "Start", "CT", "TAT", "WT");
    printf("--------------------------------------------------------------------------------\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        int tat = P[i].completion_time - P[i].arrival;
        int wt = tat - P[i].burst;
        total_wt += wt; total_tat += tat;
        printf("%-5d\t%-5d\t%-5d\t%-5d\t", P[i].pid, P[i].arrival, P[i].burst, P[i].priority);
        char res_str[MAX_RES * 4 + 2] = "{";
        int first = 1;
        char temp_str[10];
        for (int r = 0; r < m; r++) {
            if (P[i].resource_list[r]) {
                if (!first) strcat(res_str, ",");
                sprintf(temp_str, "R%d", r);
                strcat(res_str, temp_str);
                first = 0;
            }
        }
        strcat(res_str, "}");
        printf("%-15s\t", res_str);
        if (P[i].start_time >= 0) printf("%-5d\t", P[i].start_time);
        else printf("%-5s\t", "-");
        printf("%-5d\t%-5d\t%-5d\n", P[i].completion_time, tat, wt);
    }
    
    double avg_wt = (double)total_wt / n;
    double avg_tat = (double)total_tat / n;
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);
    printf("\n--- CPU GANTT CHART (time units horizontally) ---\n");
    int t0 = 0;
    while (t0 < final_time) {
        int pid = cpu_owner[t0];
        int t1 = t0 + 1;
        while (t1 < final_time && cpu_owner[t1] == pid) t1++;
        if (pid == 0) printf("| idle (%d->%d) ", t0, t1);
        else printf("| P%d (%d->%d) ", pid, t0, t1);
        t0 = t1;
    }
    printf("|\n");
    printf("\n--- RESOURCE TIMELINES ---\n");
    for (int r = 0; r < m; r++) {
        printf("Resource R%d: ", r);
        int tt = 0;
        while (tt < final_time) {
            int pid = resource_owner[r][tt];
            int t2 = tt + 1;
            while (t2 < final_time && resource_owner[r][t2] == pid) t2++;
            if (pid == 0) printf("[free %d->%d] ", tt, t2);
            else printf("[P%d %d->%d] ", pid, tt, t2);
            tt = t2;
        }
        printf("\n");
    }
}

int main() {
    init_globals();
    printf("Multilevel Queue Scheduling Simulator with Banker-like Deadlock Avoidance\n");
    printf("Enter number of processes (max %d): ", MAX_PROCS);
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PROCS) { printf("Invalid n\n"); return 0; }
    printf("Enter number of resource types (max %d): ", MAX_RES);
    scanf("%d", &m);
    if (m < 0 || m > MAX_RES) { printf("Invalid m\n"); return 0; }

    for (int r = 0; r < m; r++) {
        printf("Enter total available instances of resource R%d: ", r);
        scanf("%d", &avail[r]);
        if (avail[r] < 0) avail[r] = 0;
    }

    printf("\nEnter processes details:\n");
    for (int i = 0; i < n; i++) {
        P[i].allocated = 0;
        P[i].start_time = -1;
        P[i].is_completed = 0;
        P[i].resource_count = 0;
        for (int r = 0; r < m; r++) P[i].resource_list[r] = 0;
        printf("\nProcess %d:\n", i+1);
        printf(" PID (integer): "); scanf("%d", &P[i].pid);
        printf(" Arrival time (AT): "); scanf("%d", &P[i].arrival);
        printf(" Burst time (BT): "); scanf("%d", &P[i].burst);
        printf(" Priority (1=High,2=Medium,3=Low): "); scanf("%d", &P[i].priority);
        printf(" Number of distinct resources required (0-%d): ", m); scanf("%d", &P[i].resource_count);
        if (P[i].resource_count > 0) {
            printf(" Enter resource indices (space-separated, each 0..%d): ", m-1);
            for (int k = 0; k < P[i].resource_count; k++) {
                int rid; scanf("%d", &rid);
                if (rid >= 0 && rid < m) P[i].resource_list[rid] = 1;
            }
        }
        P[i].remaining = P[i].burst;
    }

    int time_quantum;
    printf("\nEnter time quantum for High-priority RR queue (suggested 2-5): ");
    scanf("%d", &time_quantum);
    if (time_quantum <= 0) time_quantum = 2;
    int time = 0;
    int final_time = 0;
    int high_order[MAX_PROCS]; int hn=0; 
    int rr_pointer = 0; 
    int rr_used[MAX_PROCS]; 
    for (int i=0;i<n;i++) rr_used[i]=0;
    int MAX_SIM_TIME = 10000;

    while (!all_completed() && time < MAX_SIM_TIME) {
        int high[MAX_PROCS], med[MAX_PROCS], low[MAX_PROCS];
        int hcount=0,mcount=0,lcount=0;
        collect_ready_lists(time, high, &hcount, med, &mcount, low, &lcount);
        int new_high_order[MAX_PROCS], new_hn = 0;
        for (int i = 0; i < hcount; i++) {
            new_high_order[new_hn++] = high[i];
        }
        hn = new_hn;
        for (int i=0;i<hn;i++) high_order[i]=new_high_order[i];
        int chosen = -1;
        int chosen_queue = 0; 

        if (hn > 0) {
            int found = 0;
            int tries = 0;
            if (rr_pointer >= hn) rr_pointer = 0;
            int idx = rr_pointer;

            while (tries < hn) {
                int pidx = high_order[idx];
                if (!P[pidx].is_completed && P[pidx].arrival <= time) {
                    if (P[pidx].allocated || try_allocate(pidx)) {
                        chosen = pidx;
                        chosen_queue = 1;
                        rr_pointer = (idx + 1) % hn;
                        found = 1;
                        break;
                    }
                }
                idx = (idx + 1) % hn;
                tries++;
            }
            if (!found) chosen = -1;
        }

        if (chosen == -1 && mcount > 0) {
            int best = -1;
            int best_rem = INF;
            for (int i = 0; i < mcount; i++) {
                int p = med[i];
                if (P[p].is_completed || P[p].arrival > time) continue;
                if (!P[p].allocated) {
                    if (!try_allocate(p)) continue; 
                }
                if (P[p].remaining < best_rem) { best_rem = P[p].remaining; best = p; }
            }
            if (best != -1) { chosen = best; chosen_queue = 2; }
        }

        if (chosen == -1 && lcount > 0) {
            int earliest = -1;
            int earliest_at = INF;
            for (int i = 0; i < lcount; i++) {
                int p = low[i];
                if (P[p].is_completed || P[p].arrival > time) continue;
                if (!P[p].allocated) {
                    if (!try_allocate(p)) continue;
                }
                if (P[p].arrival < earliest_at) { earliest_at = P[p].arrival; earliest = p; }
            }
            if (earliest != -1) { chosen = earliest; chosen_queue = 3; }
        }

        for (int r = 0; r < m; r++) {
            int holder_pid = 0;
            for (int p_idx = 0; p_idx < n; p_idx++) {
                if (allocation[p_idx][r]) {
                    holder_pid = P[p_idx].pid;
                    break;
                }
            }
            resource_owner[r][time] = holder_pid;
        }
        if (chosen != -1) {
            cpu_owner[time] = P[chosen].pid;
            if (P[chosen].start_time == -1) P[chosen].start_time = time;
            P[chosen].remaining -= 1;
            if (chosen_queue == 1) {
                rr_used[chosen] += 1;
            }
            if (P[chosen].remaining <= 0) {
                P[chosen].is_completed = 1;
                P[chosen].completion_time = time + 1;
                release_resources(chosen);
                rr_used[chosen] = 0;
            } else {
                if (chosen_queue == 1 && rr_used[chosen] >= time_quantum) {
                    rr_used[chosen] = 0;
                }
            }
        } else {
            cpu_owner[time] = 0;
        }
        time++;
        final_time = time;
    }

    for (int i = 0; i < n; i++) {
        if (!P[i].is_completed) {
            P[i].completion_time = final_time;
            if (P[i].allocated) release_resources(i);
            P[i].is_completed = 1; 
        }
    }
    print_results(final_time);

    return 0;
}
