#include <stdio.h>

int main() {
    int n, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    char p[n][10];
    int at[n], bt[n], wt[n], tat[n];

    // Input
    for (i = 0; i < n; i++) {
        printf("Enter Process Name, Arrival Time and Burst Time: ");
        scanf("%s %d %d", p[i], &at[i], &bt[i]);
    }

    // Sort by Arrival Time (FCFS rule)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                // Swap arrival time
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap burst time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap process name
                char tempName[10];
                int k;
                for (k = 0; k < 10; k++) {
                    tempName[k] = p[j][k];
                    p[j][k] = p[j + 1][k];
                    p[j + 1][k] = tempName[k];
                }
            }
        }
    }

    // Calculate Waiting Time and Turnaround Time
    int current_time = 0;

    for (i = 0; i < n; i++) {
        // CPU may be idle until process arrives
        if (current_time < at[i])
            current_time = at[i];

        wt[i] = current_time - at[i];
        tat[i] = wt[i] + bt[i];

        current_time += bt[i];
    }

    // Calculate averages
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    // Output
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}