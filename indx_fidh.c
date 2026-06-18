#include <stdio.h>

int main() {
    int n, i, j;
    int blocks[100] = {0};

    printf("Enter total number of blocks on disk: ");
    scanf("%d", &n);

 int indexBlock;
    printf("\n--- Indexed Allocation ---\n");
    printf("Enter the index block: ");
    scanf("%d", &indexBlock);

    if (blocks[indexBlock] == 1) {
        printf("Index block already allocated.\n");
    } else {
        int count;
        printf("Enter number of blocks to allocate: ");
        scanf("%d", &count);

        int data[100], success = 1;

        for (i = 0; i < count; i++) {
            printf("Enter block %d: ", i + 1);
            scanf("%d", &data[i]);
            if (blocks[data[i]] == 1) {
                printf("Block %d already allocated.\n", data[i]);
                success = 0;
                break;
            }
        }

        if (success) {
            blocks[indexBlock] = 1;
            for (i = 0; i < count; i++)
                blocks[data[i]] = 1;

            printf("File allocated using indexed allocation.\n");
           
            for (i = 0; i < count; i++)
           
                printf("%d->%d\n ",indexBlock,data[i]);
            printf("\n");
        }
        }
        }
