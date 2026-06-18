#include <stdio.h>
#define MAX_BLOCKS 100

int main() {
    int blocks[MAX_BLOCKS] = {0}; // 0 = free, 1 = allocated
    int indexBlock, fileBlocks[20], n, i, blockNum, flag, j;

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter index block for file %d: ", i + 1);
        scanf("%d", &indexBlock);

        if (blocks[indexBlock] == 1) {
            printf("Error: Index block already allocated.\n");
            continue;
        }

        printf("Enter number of blocks needed for file %d (excluding index block): ", i + 1);
        scanf("%d", &blockNum);

        printf("Enter %d block numbers: ", blockNum);
        flag = 0;

        for (j = 0; j < blockNum; j++) {
            scanf("%d", &fileBlocks[j]);
            if (fileBlocks[j] < 0 || fileBlocks[j] >= MAX_BLOCKS || blocks[fileBlocks[j]] == 1) {
                flag = 1;
            }
        }

        if (flag == 1) {
            printf("Error: Some blocks are already allocated or invalid. File %d cannot be stored.\n", i + 1);
        } else {
            blocks[indexBlock] = 1;
            for (j = 0; j < blockNum; j++) {
                blocks[fileBlocks[j]] = 1;
            }

            printf("File %d stored successfully.\n", i + 1);
            printf("Index Block: %d -> ", indexBlock);
            for (j = 0; j < blockNum; j++) {
                printf("%d ", fileBlocks[j]);
            }
            printf("\n");
        }
    }

    return 0;
}

