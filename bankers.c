#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n, i, j, k;
    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &m, &n);

    int allocation[m][n], max[m][n], need[m][n], available[n];

    printf("Enter the Allocation matrix:\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter the Maximum matrix:\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the Available resources:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &available[i]);

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Display Need Matrix
    printf("Need Matrix:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int work[n], finish[m], safeSequence[m], count = 0;

    for (i = 0; i < n; i++)
        work[i] = available[i];

    for (i = 0; i < m; i++)
        finish[i] = 0;

    while (count < m) {
        int found = 0;
        for (i = 0; i < m; i++) {
            if (!finish[i]) {
                for (j = 0; j < n; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == n) {
                    for (k = 0; k < n; k++)
                        work[k] += allocation[i][k];
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("The system is in an UNSAFE state.\n");
            return 0;
        }
    }
    printf("The system is in a SAFE state.\nSafe sequence: ");
    for (i = 0; i < m; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");
    return 0;
}
