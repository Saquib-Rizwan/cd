#include <stdio.h>
#define MAX 10

int n, t;
int trans[3][MAX][MAX];   /* trans[0] = a, trans[1] = b, trans[2] = epsilon */
int visited[MAX];

void dfs(int state)
{
    int j;
    visited[state] = 1;

    for (j = 0; j < n; j++)
    {
        if (trans[2][state][j] == 1 && visited[j] == 0)
        {
            dfs(j);
        }
    }
}

int main()
{
    int i, j;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of transition symbols: ");
    scanf("%d", &t);

    printf("\nEnter matrix for a:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &trans[0][i][j]);

    printf("\nEnter matrix for b:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &trans[1][i][j]);

    printf("\nEnter matrix for epsilon:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &trans[2][i][j]);

    printf("\nEpsilon Closures:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            visited[j] = 0;

        dfs(i);

        printf("Epsilon-Closure(q%d) = { ", i);
        for (j = 0; j < n; j++)
            if (visited[j])
                printf("q%d ", j);
        printf("}\n");
    }

    return 0;
}