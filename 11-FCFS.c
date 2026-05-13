// FCFS (First Come First Serve) CPU Scheduling
#include <stdio.h>

int main() {
    int n, i;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n];
    char p[n][10];

    // Input process names and burst times
    for (i = 0; i < n; i++) {
        printf("Enter Process Name and Burst Time for Process %d: ", i + 1);
        scanf("%s %d", p[i], &bt[i]);
    }

    // FCFS Scheduling
    wt[0] = 0;               // Waiting time of first process is 0
    tat[0] = bt[0];          // Turnaround time = Burst Time

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = wt[i] + bt[i];
    }

    // Calculate averages
    float avg_wt = 0, avg_tat = 0;

    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    // Display results
    printf("\nFCFS Scheduling Result:\n");
    printf("-------------------------------------------------\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\n",
               p[i], bt[i], wt[i], tat[i]);
    }

    printf("-------------------------------------------------\n");
    printf("Average Waiting Time    = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    return 0;
}