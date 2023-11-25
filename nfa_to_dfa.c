#include <stdio.h>
#include <string.h>
#include <math.h>

int ninputs;
int dfa[100][10][100] = {0};  // Assuming a maximum of 10 input symbols
int state[1 << 15] = {0};
char ch[10], str[1000];
int go[1 << 15][10] = {0};  // Assuming a maximum of 10 input symbols
int arr[1 << 15] = {0};

int main() {
    int st, fin, in;
    int f[10];
    int i, j, s = 0, final = 0, flag = 0, curr1, l;
    int k;  // Number of input symbols
    int c;

    printf("\nFollow the one based indexing\n");

    printf("\nEnter the number of states::");
    scanf("%d", &st);

    printf("\nGive state numbers from 0 to %d", st - 1);

    for (i = 0; i < st; i++)
        state[(int)pow(2, i)] = 1;

    printf("\nEnter number of final states\t");
    scanf("%d", &fin);

    printf("\nEnter final states::");
    for (i = 0; i < fin; i++) {
        scanf("%d", &f[i]);
    }

    printf("\nEnter the number of input symbols (k): ");
    scanf("%d", &k);

    int p, q, r, rel;
    printf("\nEnter the number of rules according to NFA::");
    scanf("%d", &rel);

    printf("\nDefine transition rule as \"initial state input symbol final state\"\n");
    for (i = 0; i < rel; i++) {
        scanf("%d%d%d%d", &p, &q, &c, &r);  // Read the input symbol
        dfa[p][c][r] = 1;
    }

    printf("\nEnter initial state::");
    scanf("%d", &in);
    in = pow(2, in);

    printf("\nSolving according to DFA");
    int x = 0;

    for (i = 0; i < st; i++) {
        for (j = 0; j < k; j++) {
            int stf = 0;
            for (int kk = 0; kk < st; kk++) {
                if (dfa[i][j][kk] == 1)
                    stf = stf + pow(2, kk);
            }
            go[(int)pow(2, i)][j] = stf;
            printf("%d-%d-->%d\n", (int)pow(2, i), j, stf);
            if (state[stf] == 0)
                arr[x++] = stf;
            state[stf] = 1;
        }
    }

    for (i = 0; i < x; i++) {
        printf("for %d ---- ", arr[x]);
        for (j = 0; j < k; j++) {
            int new = 0;
            for (int kk = 0; kk < st; kk++) {
                if (arr[i] & (1 << kk)) {
                    int h = pow(2, kk);
                    if (new == 0)
                        new = go[h][j];
                    new = new | (go[h][j]);
                }
            }
            if (state[new] == 0) {
                arr[x++] = new;
                state[new] = 1;
            }
        }
    }

    printf("\nThe total number of distinct states are::\n");
    printf("STATE     ");
    for (int sym = 0; sym < k; sym++) {
        printf("%d   ", sym);
    }
    printf("\n");

    for (i = 0; i < 1 << 15; i++) {
        if (state[i] == 1) {
            int y = 0;
            if (i == 0)
                printf("q0 ");
            else
                for (j = 0; j < st; j++) {
                    int x = 1 << j;
                    if (x & i) {
                        printf("q%d ", j);
                        y = y + pow(2, j);
                    }
                }
            printf("       ");
            for (int sym = 0; sym < k; sym++) {
                printf("%d   ", go[y][sym]);
            }
            printf("\n");
        }
    }

    j = 3;
    while (j--) {
        printf("\nEnter string: ");
        scanf("%s", str);
        l = strlen(str);
        curr1 = in;
        flag = 0;
        printf("\n
