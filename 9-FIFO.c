// C program to calculate the number of page faults using FIFO Page Replacement

#include <stdio.h>

int main() {
    int pages[100], frames[10];
    int n, m;
    int i, j, k;
    int page_faults = 0;
    int index = 0;
    int found;

    // Input number of pages in reference string
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    // Input reference string
    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &m);

    // Initialize frames to -1 (empty)
    for (i = 0; i < m; i++) {
        frames[i] = -1;
    }

    // FIFO Page Replacement Algorithm
    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in any frame
        for (j = 0; j < m; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If page not found, page fault occurs
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % m;   // Move to next frame in circular order
            page_faults++;
        }

        // Display current frame status
        printf("After page %d: ", pages[i]);
        for (k = 0; k < m; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }

        if (!found)
            printf("-> Page Fault");
        else
            printf("-> No Page Fault");

        printf("\n");
    }

    // Display total page faults
    printf("\nTotal Number of Page Faults = %d\n", page_faults);

    return 0;
}