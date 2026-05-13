// C program to calculate the number of page faults using LRU Page Replacement

#include <stdio.h>

int main() {
    int pages[100], frames[10];
    int n, f, i, j, k;
    int pageFaults = 0;
    int found, lruIndex;
    int leastRecent, counter = 0;
    int time[10];   // Stores the last used time of each frame

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &n);

    // Input reference string
    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames as empty
    for (i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = -1;
    }

    // LRU Page Replacement Algorithm
    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in frame (Page Hit)
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                counter++;
                time[j] = counter;   // Update recent usage
                break;
            }
        }

        // Page Fault occurs
        if (!found) {
            // Find empty frame first
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    counter++;
                    time[j] = counter;
                    pageFaults++;
                    found = 1;
                    break;
                }
            }

            // If no empty frame, replace Least Recently Used page
            if (!found) {
                leastRecent = time[0];
                lruIndex = 0;

                for (j = 1; j < f; j++) {
                    if (time[j] < leastRecent) {
                        leastRecent = time[j];
                        lruIndex = j;
                    }
                }

                frames[lruIndex] = pages[i];
                counter++;
                time[lruIndex] = counter;
                pageFaults++;
            }
        }

        // Display current frame contents
        printf("After page %d -> ", pages[i]);
        for (k = 0; k < f; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }
        printf("\n");
    }

    // Output total page faults
    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}