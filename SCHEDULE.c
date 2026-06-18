#include <stdio.h>

void sjf();
void roundRobin();
void priorityScheduling();
void fcfs();

int main() {
    int choice;
    while (1) {
        printf("\nCPU Scheduling Algorithms:\n");
        printf("1. Shortest Job First (SJF)\n");
        printf("2. Round Robin\n");
        printf("3. Priority Scheduling\n");
        printf("4. First Come First Serve (FCFS)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: sjf(); break;
            case 2: roundRobin(); break;
            case 3: priorityScheduling(); break;
            case 4: fcfs(); break;
            case 5: return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// ------------------------- SJF -------------------------
void sjf() {
    int i, j, n;
    int at[10], bt[10], ct[10], wt[10], tt[10], completed[10] = {0};
    int pid[10];
    float avgwt = 0, avgtt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time of each process:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i);
        scanf("%d", &at[i]);
        pid[i] = i;
    }

    printf("Enter burst time of each process:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i);
        scanf("%d", &bt[i]);
    }

    int time = 0, count = 0, min, index;

    while(count < n) {
        min = 9999;
        index = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0 && bt[i] < min) {
                min = bt[i];
                index = i;
            }
        }

        if(index == -1) {
            time++;
        } else {
            wt[index] = time - at[index];
            if(wt[index] < 0) wt[index] = 0;
            ct[index] = time + bt[index];
            tt[index] = ct[index] - at[index];
            time += bt[index];
            completed[index] = 1;
            count++;
        }
    }

    printf("\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], wt[i], tt[i]);
        avgwt += wt[i];
        avgtt += tt[i];
    }

    avgwt /= n;
    avgtt /= n;

    printf("\nAverage Waiting Time: %.2f\n", avgwt);
    printf("Average Turnaround Time: %.2f\n", avgtt);
}

// ------------------------- Round Robin -------------------------
void roundRobin() {
    int n, quantum;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int r[n][6], rem_bt[n], i;

    for(i = 0; i < n; i++) {
        printf("Enter arrival time and burst time of process %d: ", i+1);
        r[i][0] = i + 1;
        scanf("%d%d", &r[i][1], &r[i][2]);
        rem_bt[i] = r[i][2];
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int done = 1;
        for(i = 0; i < n; i++) {
            if (rem_bt[i] > 0 && r[i][1] <= time) {
                done = 0;
                if (rem_bt[i] > quantum) {
                    time += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    time += rem_bt[i];
                    r[i][3] = time;
                    r[i][4] = r[i][3] - r[i][1];
                    r[i][5] = r[i][4] - r[i][2];
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }
        if (done) time++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        avg_tat += r[i][4];
        avg_wt += r[i][5];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", r[i][0], r[i][1], r[i][2], r[i][3], r[i][4], r[i][5]);
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("Average Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time = %.2f\n", avg_wt);
}

// ------------------------- Priority Scheduling -------------------------
void priorityScheduling() {
    int i, n, completed = 0, currentTime = 0;
    int ct[20], tat[20], wt[20];
    float avgwt = 0, avgtat = 0;
    int bt[20][5];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time, burst time, and priority of each process:\n");

    for (i = 0; i < n; i++) {
        printf("P[%d]: ", i);
        bt[i][0] = i;
        scanf("%d %d %d", &bt[i][3], &bt[i][1], &bt[i][2]);
        bt[i][4] = 0;
    }

    while (completed < n) {
        int idx = -1, highestPriority = 9999;

        for (i = 0; i < n; i++) {
            if (bt[i][3] <= currentTime && bt[i][4] == 0) {
                if (bt[i][2] < highestPriority) {
                    highestPriority = bt[i][2];
                    idx = i;
                } else if (bt[i][2] == highestPriority) {
                    if (bt[i][3] < bt[idx][3] || (bt[i][3] == bt[idx][3] && bt[i][0] < bt[idx][0])) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            currentTime += bt[idx][1];
            ct[idx] = currentTime;
            tat[idx] = ct[idx] - bt[idx][3];
            wt[idx] = tat[idx] - bt[idx][1];
            bt[idx][4] = 1;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               bt[i][0], bt[i][3], bt[i][1], bt[i][2], ct[i], tat[i], wt[i]);
        avgwt += wt[i];
        avgtat += tat[i];
    }

    avgwt /= n;
    avgtat /= n;

    printf("\nAverage Waiting Time: %.2f\n", avgwt);
    printf("Average Turnaround Time: %.2f\n", avgtat);
}

// ------------------------- FCFS -------------------------
void fcfs() {
    int i, n, wt[20] = {0}, tt[20] = {0}, ct[20] = {0};
    int bt[20][3], temp[20][2];
    float avgwt = 0, avgtt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter burst time and arrival time (in order) of each process:\n");

    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i);
        bt[i][0] = i;
        scanf("%d%d", &bt[i][1], &bt[i][2]);
        temp[i][1] = bt[i][1];
    }

    wt[0] = 0;
    ct[0] = bt[0][1];
    tt[0] = ct[0] - bt[0][2];

    for(i = 0; i < n-1; i++) {
        wt[i+1] = wt[i] + bt[i][1];
        ct[i+1] = wt[i+1] + bt[i+1][1];
        tt[i+1] = ct[i+1] - bt[i+1][2];
    }

    printf("\nProcess\tBT\tAT\tWT\tTAT\tCT\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t%d\t%d\n", bt[i][0], bt[i][1], bt[i][2], wt[i], tt[i], ct[i]);
        avgwt += wt[i];
        avgtt += tt[i];
    }

    avgwt /= n;
    avgtt /= n;

    printf("Average Waiting Time = %.2f\n", avgwt);
    printf("Average Turnaround Time = %.2f\n", avgtt);
}

