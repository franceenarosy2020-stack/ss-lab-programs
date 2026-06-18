#include <stdio.h>

int main() {
    int n, i, j;
    int blocks[100] = {0};

    printf("Enter total number of blocks on disk: ");
    scanf("%d", &n);
printf("\n--- Linked Allocation ---\n");
    int lcount;
    printf("Enter number of blocks to allocate: ");
    scanf("%d", &lcount);

    int chain[100], valid = 1;

    for (i = 0; i < lcount; i++) {
        printf("Enter block %d: ", i + 1);
        scanf("%d", &chain[i]);
        if (blocks[chain[i]] == 1) {
            printf("Block %d already allocated.\n", chain[i]);
            valid = 0;
            break;
        }
    }

    if (valid) {
        for (i = 0; i < lcount; i++)
            blocks[chain[i]] = 1;

        printf("File allocated using linked allocation.\n");
        printf("Block chain: ");
        for (i = 0; i < lcount; i++)
            printf("%d -> ", chain[i]);
        printf("NULL\n");
    }

    return 0;
}
