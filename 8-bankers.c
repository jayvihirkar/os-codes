/* Banker's Algorithm
   Program to check whether the system is in SAFE or UNSAFE state */

#include <stdio.h>

int main()
{
    int n, m;   // n = number of processes, m = number of resources
    int i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix = Max - Allocation
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Display Need Matrix
    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int finish[n], safeSeq[n], work[m];
    int count = 0;

    // Initialize finish[] = 0 and work[] = avail[]
    for (i = 0; i < n; i++)
        finish[i] = 0;

    for (i = 0; i < m; i++)
        work[i] = avail[i];

    // Banker's Algorithm
    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                // Check if need <= work
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                // If all resources can be allocated
                if (j == m)
                {
                    // Release allocated resources after process finishes
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        // If no process could be allocated, system is unsafe
        if (found == 0)
        {
            printf("\nSystem is in UNSAFE state.\n");
            return 0;
        }
    }

    // If all processes are finished, system is safe
    printf("\nSystem is in SAFE state.\n");
    printf("Safe Sequence: ");

    for (i = 0; i < n; i++)
    {
        printf("P%d", safeSeq[i]);
        if (i != n - 1)
            printf(" -> ");
    }

    printf("\n");

    return 0;
}