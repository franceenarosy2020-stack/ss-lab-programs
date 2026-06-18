#include <stdio.h>

#define MAX_BLOCKS 100  // Total number of disk blocks

int main() {
    int blocks[MAX_BLOCKS] = {0}; // 0 = free, 1 = allocated
    int start, length, i, j, flag;

    int n; // Number of files
    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter starting block and length of file %d: ", i + 1);
        scanf("%d %d", &start, &length);

        // Check if the file can fit
        flag = 0;
        if (start < 0 || start + length > MAX_BLOCKS) {
            printf("Error: File exceeds disk size!\n");
            continue;
        }

        // Check if blocks are free
        for (j = start; j < start + length; j++) {
            if (blocks[j] == 1) {
                flag = 1; // some block is already used
                break;
            }
        }

        if (flag == 1) {
            printf("Error: Blocks already allocated, file %d cannot be stored.\n", i + 1);
        } else {
            for (j = start; j < start + length; j++) {
                blocks[j] = 1; // Mark blocks as allocated
            }
            printf("File %d allocated from block %d to %d\n", i + 1, start, start + length - 1);
        }
    }

    return 0;
}

