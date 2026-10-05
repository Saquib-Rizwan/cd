#include <stdio.h>

int n;

int eps[10][10];
int moveA[10][10], moveB[10][10];

int closure[10][10];
int isFinal[10], newFinal[10];
int visited[10];

void dfs(int start, int state)
{
    visited[state] = 1;
    closure[start][state] = 1;

    for (int j = 0; j < n; j++)
    {
        if (eps[state][j] && !visited[j])
            dfs(start, j);
    }
}

int main()
{
    int i, j;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter epsilon transition matrix (%d x %d):\n", n, n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &eps[i][j]);

    printf("Enter transition matrix for symbol 'a':\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &moveA[i][j]);

    printf("Enter transition matrix for symbol 'b':\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &moveB[i][j]);

    printf("Enter final states (1 = final, 0 = not final):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &isFinal[i]);

    /* Step 1: Find epsilon closure of every state */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            visited[j] = 0;

        dfs(i, i);
    }

    /* Step 2: Find new final states */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (closure[i][j] && isFinal[j])
            {
                newFinal[i] = 1;
                break;
            }
        }
    }

    int newA[10][10] = {0};
    int newB[10][10] = {0};

    /* Step 3: Construct new transitions */
    for (i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            if (closure[i][k])
            {
                /* For 'a' transitions */
                for (j = 0; j < n; j++)
                {
                    if (moveA[k][j])
                    {
                        /* Add epsilon closure of destination */
                        for (int p = 0; p < n; p++)
                        {
                            if (closure[j][p])
                                newA[i][p] = 1;
                        }
                    }
                }

                /* For 'b' transitions */
                for (j = 0; j < n; j++)
                {
                    if (moveB[k][j])
                    {
                        /* Add epsilon closure of destination */
                        for (int p = 0; p < n; p++)
                        {
                            if (closure[j][p])
                                newB[i][p] = 1;
                        }
                    }
                }
            }
        }
    }

    /* Step 4: Print new NFA */
    printf("\n--- NFA without epsilon transitions ---\n");

    printf("\nNew Transition Table:\n");
    printf("State\ta\tb\n");

    for (i = 0; i < n; i++)
    {
        printf("q%d\t{ ", i);

        for (j = 0; j < n; j++)
            if (newA[i][j])
                printf("q%d ", j);

        printf("}\t{ ");

        for (j = 0; j < n; j++)
            if (newB[i][j])
                printf("q%d ", j);

        printf("}\n");
    }

    printf("\nNew Final States: { ");

    for (i = 0; i < n; i++)
        if (newFinal[i])
            printf("q%d ", i);

    printf("}\n");

    return 0;
}
