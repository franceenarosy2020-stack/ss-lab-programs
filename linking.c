#include <stdio.h>
#define MAX_BLOCKS 100
#define END -1  // End of chain marker

int main() {
    int blocks[MAX_BLOCKS] = {0};      // 0 = free, 1 = allocated
    int next[MAX_BLOCKS];              // next[i] points to next block in chain
    int startBlock, length, i, j, block, prevBlock;
    int usedBlocks[MAX_BLOCKS];        // to temporarily store allocated blocks

    for (i = 0; i < MAX_BLOCKS; i++) {
        next[i] = END;
    }

    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter starting block and length of file %d: ", i + 1);
        scanf("%d %d", &startBlock, &length);

        if (startBlock < 0 || startBlock >= MAX_BLOCKS || blocks[startBlock] == 1) {
            printf("Error: Starting block is invalid or already allocated.\n");
            continue;
        }

        int count = 0;
        blocks[startBlock] = 1;
        usedBlocks[count++] = startBlock;

        // Allocate remaining (length - 1) blocks
        for (j = 0; j < MAX_BLOCKS && count < length; j++) {
            if (blocks[j] == 0) {
                blocks[j] = 1;
                usedBlocks[count++] = j;
            }
        }

        if (count < length) {
            printf("Error: Not enough free blocks for file %d.\n", i + 1);
            // Rollback
            for (j = 0; j < count; j++) {
                blocks[usedBlocks[j]] = 0;
            }
            continue;
        }

        // Link the blocks
        for (j = 0; j < length - 1; j++) {
            next[usedBlocks[j]] = usedBlocks[j + 1];
        }
        next[usedBlocks[length - 1]] = END;

        printf("File %d allocated.\n", i + 1);
        printf("Block chain: ");
        block = startBlock;
        while (block != END) {
            printf("%d ", block);
            block = next[block];
        }
        printf("\n");
    }

    return 0;
}

