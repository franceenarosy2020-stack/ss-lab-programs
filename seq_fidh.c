#include<stdio.h>
void main() {
    int f[50], i, st, len, j, c, k, count = 0;

    // Initialize disk blocks to 0 (free)
    for (i = 0; i < 50; i++)
        f[i] = 0;

    printf("Files Allocated are : \n");

x:  // Label for goto
    count = 0;

    // Input start block and length of file
    printf("Enter starting block and length of files: ");
    scanf("%d%d", &st, &len);

    // Count free blocks from start to end
    for (k = st; k < (st + len); k++) {
        if (f[k] == 0)
            count++;
    }

    // If enough free blocks available
    if (len == count) {
        for (j = st; j < (st + len); j++) {
            if (f[j] == 0) {
                f[j] = 1;
                printf("%d\t%d\n", j, f[j]);
            }
        }
        printf("The file is allocated to disk\n");
    } else {
        printf("The file is not allocated\n");
    }

    // Ask to continue
    printf("Do you want to enter more file(Yes - 1 / No - 0): ");
    scanf("%d", &c);
    if (c == 1)
        goto x;
        }


