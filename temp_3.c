#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCS 30
#define MAX_RES 10
#define INF 1000000
#define MAX_SIM_TIME 1000

typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int priority; 
    int resource_list[MAX_RES];
    int allocated; 
    int start_time; 
    int completion_time;
    int is_completed;
} Process;

Process P[MAX_PROCS];
int n, m;
int avail[MAX_RES];
int total_resources[MAX_RES];
int allocation[MAX_PROCS][MAX_RES];
int cpu_owner[MAX_SIM_TIME];

int resource_holders[MAX_RES][MAX_PROCS][MAX_SIM_TIME];
int resource_alloc_count[MAX_RES][MAX_SIM_TIME];


void init_globals() {
    int t;
    for (t = 0; t < MAX_SIM_TIME; t++) {
        cpu_owner[t] = 0;
        for (int r = 0; r < m; r++) resource_alloc_count[r][t] = 0;
    }
    for (int i = 0; i < MAX_PROCS; i++) {
        for (int r = 0; r < MAX_RES; r++) allocation[i][r] = 0;
    }
    memset(resource_holders, 0, sizeof(resource_holders));
}

int all_completed() {
    for (int i = 0; i < n; i++) if (!P[i].is_completed) return 0;
    return 1;
}


int is_safe_if_allocate(int pid) {
	// bankers algo.
    int work[MAX_RES];
    int finish[MAX_PROCS];
    int need[MAX_PROCS][MAX_RES];
    int i, r;

    for (i = 0; i < n; i++) {
        for (r = 0; r < m; r++) {
            need[i][r] = P[i].resource_list[r] - allocation[i][r];
            if (need[i][r] < 0) need[i][r] = 0;
        }
    }

    for (r = 0; r < m; r++) work[r] = avail[r];

    for (r = 0; r < m; r++) {
        if (need[pid][r] > 0) {
            if (work[r] < need[pid][r]) return 0; 
            work[r] -= need[pid][r];
        }
    }

    int sim_alloc[MAX_PROCS][MAX_RES];
    for (i = 0; i < n; i++)
        for (r = 0; r < m; r++)
            sim_alloc[i][r] = allocation[i][r];

    for (r = 0; r < m; r++) {
        sim_alloc[pid][r] = P[pid].resource_list[r];
    }
    
    for (i = 0; i < n; i++) finish[i] = (P[i].is_completed ? 1 : 0);

    int changed;
    do {
        changed = 0;
        for (i = 0; i < n; i++) {
            if (finish[i]) continue;

            int can = 1;
            for (r = 0; r < m; r++) {
                int needed = P[i].resource_list[r] - sim_alloc[i][r];
                if (needed < 0) needed = 0;
                
                if (needed > work[r]) {
                    can = 0;
                    break;
                }
            }

            if (can) {
                for (r = 0; r < m; r++) {
                    work[r] += sim_alloc[i][r];
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
        int needed = P[pid].resource_list[r];
        if (needed > 0 && avail[r] < needed) {
            return 0;
        }
    }

    if (!is_safe_if_allocate(pid)) return 0;

    for (int r = 0; r < m; r++) {
        int needed = P[pid].resource_list[r];
        if (needed > 0) {
            allocation[pid][r] = needed;
            avail[r] -= needed;
        }
    }
    P[pid].allocated = 1;
    return 1;
}

void release_resources(int pid) {
    for (int r = 0; r < m; r++) {
        if (allocation[pid][r] > 0) {
            avail[r] += allocation[pid][r];
            allocation[pid][r] = 0;
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
           "PID", "AT", "BT", "Pri", "MaxRequest", "Start", "CT", "TAT", "WT");
    printf("--------------------------------------------------------------------------------\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        int tat = P[i].completion_time - P[i].arrival;
        int wt = tat - P[i].burst;
        total_wt += wt; total_tat += tat;
        printf("%-5d\t%-5d\t%-5d\t%-5d\t", P[i].pid, P[i].arrival, P[i].burst, P[i].priority);

        char res_str[MAX_RES * 8 + 2] = "{"; 
        int first = 1;
        char temp_str[20];
        int has_res = 0;
        for (int r = 0; r < m; r++) {
            if (P[i].resource_list[r] > 0) { 
                has_res = 1;
                if (!first) strcat(res_str, ",");
                sprintf(temp_str, "R%d:%d", r, P[i].resource_list[r]); 
                strcat(res_str, temp_str);
                first = 0;
            }
        }
        if (!has_res) strcat(res_str, "none");
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
        printf("Resource R%d (Total: %d):\n", r, total_resources[r]);
        int tt = 0;
        while (tt < final_time) {
            int alloc_count = resource_alloc_count[r][tt];

            int t2 = tt + 1;
            while (t2 < final_time) {
                if (resource_alloc_count[r][t2] != alloc_count) break;

                int holders_same = 1;
                for (int i = 0; i < n; i++) {
                    if (resource_holders[r][i][tt] != resource_holders[r][i][t2]) {
                        holders_same = 0;
                        break;
                    }
                }
                if (!holders_same) break;
                t2++;
            }

            printf("  (%d->%d) [Alloc: %d/%d] Held by: ", tt, t2, alloc_count, total_resources[r]);
            if (alloc_count == 0) {
                printf("none");
            } else {
                int first_holder = 1;
                for (int i = 0; i < n; i++) {
                    if (resource_holders[r][i][tt]) { 
                        if (!first_holder) printf(", ");
                        printf("P%d (%d)", P[i].pid, allocation[i][r]);
                        first_holder = 0;
                    }
                }
            }
            printf("\n");
            tt = t2;
        }
    }
}

int main() {
    init_globals();
    printf("Multilevel Queue Scheduling Simulator with Banker's Deadlock Avoidance\n");
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
        total_resources[r] = avail[r];
    }

    printf("\nEnter processes details:\n");
    for (int i = 0; i < n; i++) {
        P[i].allocated = 0;
        P[i].start_time = -1;
        P[i].is_completed = 0;
        for (int r = 0; r < m; r++) P[i].resource_list[r] = 0;
        printf("\nProcess %d:\n", i + 1);
        printf(" PID (integer): "); scanf("%d", &P[i].pid);
        printf(" Arrival time (AT): "); scanf("%d", &P[i].arrival);
        printf(" Burst time (BT): "); scanf("%d", &P[i].burst);
        printf(" Priority (1=High,2=Medium,3=Low): "); scanf("%d", &P[i].priority);

        if (m > 0) {
            printf(" Enter MAX instance count for each resource (R0 to R%d):\n", m - 1);
            for (int r = 0; r < m; r++) {
                printf("  Instances for R%d: ", r);
                scanf("%d", &P[i].resource_list[r]);
                if (P[i].resource_list[r] < 0) P[i].resource_list[r] = 0;
                
                if (P[i].resource_list[r] > total_resources[r]) {
                    printf("  Error: Request %d for R%d exceeds total %d. Setting to %d.\n",
                           P[i].resource_list[r], r, total_resources[r], total_resources[r]);
                    P[i].resource_list[r] = total_resources[r];
                }
            }
        }
        P[i].remaining = P[i].burst;
    }

    int time_quantum;
    printf("\nEnter time quantum for High-priority RR queue (suggested 2-5): ");
    scanf("%d", &time_quantum);
    if (time_quantum <= 0) time_quantum = 2;
	
	// working part
	
    int time = 0;
    int final_time = 0;
    int rr_pointer = 0;
    int rr_used[MAX_PROCS];
    for (int i = 0; i < n; i++) rr_used[i] = 0;

    while (!all_completed() && time < MAX_SIM_TIME) {
        int high[MAX_PROCS], med[MAX_PROCS], low[MAX_PROCS];
        int hcount = 0, mcount = 0, lcount = 0;
        collect_ready_lists(time, high, &hcount, med, &mcount, low, &lcount);

        int chosen = -1;
        int chosen_queue = 0;

        // 1-rr (High)
        if (hcount > 0) {
            int found = 0;
            int tries = 0;
            if (rr_pointer >= hcount) rr_pointer = 0;
            int idx = rr_pointer;

            while (tries < hcount) {
                int pidx = high[idx];
                if (!P[pidx].is_completed && P[pidx].arrival <= time) {
                    if (P[pidx].allocated || try_allocate(pidx)) {
                        chosen = pidx;
                        chosen_queue = 1;
                        rr_pointer = (idx + 1) % hcount;
                        found = 1;
                        break;
                    }
                }
                idx = (idx + 1) % hcount;
                tries++;
            }
            if (!found) chosen = -1;
        }

        // 2-srtf (Medium)
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

        // 3-fcfs (Low)
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

        // execution
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

        for (int r = 0; r < m; r++) {
            resource_alloc_count[r][time] = total_resources[r] - avail[r];
            for (int i = 0; i < n; i++) {
                if (allocation[i][r] > 0) {
                    resource_holders[r][i][time] = 1;
                } else {
                    resource_holders[r][i][time] = 0;
                }
            }
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
