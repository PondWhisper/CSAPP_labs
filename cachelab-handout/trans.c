/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32)
    {
        for (int i = 0; i < 32; i += 8)
        {
            for (int j = 0; j < 32; j += 8)
            {
                for (int m = 0; m < 8; m++)
                {
                    int s1 = A[i + m][j + 1];
                    int s2 = A[i + m][j + 2];
                    int s3 = A[i + m][j + 3];
                    int s4 = A[i + m][j + 4];
                    int s5 = A[i + m][j + 5];
                    int s6 = A[i + m][j + 6];
                    int s7 = A[i + m][j + 7];
                    int s8 = A[i + m][j + 8];

                    B[j + 1][i + m] = s1;
                    B[j + 2][i + m] = s2;
                    B[j + 3][i + m] = s3;
                    B[j + 4][i + m] = s4;
                    B[j + 5][i + m] = s5;
                    B[j + 6][i + m] = s6;
                    B[j + 7][i + m] = s7;
                    B[j + 8][i + m] = s8;
                }
            }
        }
    }
    else if (M == 64 && N == 64)
    {
        int i, j, k;
        int v1, v2, v3, v4, v5, v6, v7, v8;

        if (M == 32)
        {
            for (i = 0; i < 32; i += 8)
            {
                for (j = 0; j < 32; j += 8)
                {
                    for (k = i; k < i + 8; k++)
                    {
                        v1 = A[k][j];
                        v2 = A[k][j + 1];
                        v3 = A[k][j + 2];
                        v4 = A[k][j + 3];
                        v5 = A[k][j + 4];
                        v6 = A[k][j + 5];
                        v7 = A[k][j + 6];
                        v8 = A[k][j + 7];

                        B[j][k] = v1;
                        B[j + 1][k] = v2;
                        B[j + 2][k] = v3;
                        B[j + 3][k] = v4;
                        B[j + 4][k] = v5;
                        B[j + 5][k] = v6;
                        B[j + 6][k] = v7;
                        B[j + 7][k] = v8;
                    }
                }
            }
        }
        else if (M == 64)
        {
            for (i = 0; i < 64; i += 8)
            {
                for (j = 0; j < 64; j += 8)
                {
                    for (k = i; k < i + 4; k++)
                    {
                        v1 = A[k][j];
                        v2 = A[k][j + 1];
                        v3 = A[k][j + 2];
                        v4 = A[k][j + 3];
                        v5 = A[k][j + 4];
                        v6 = A[k][j + 5];
                        v7 = A[k][j + 6];
                        v8 = A[k][j + 7];

                        B[j][k] = v1;
                        B[j + 1][k] = v2;
                        B[j + 2][k] = v3;
                        B[j + 3][k] = v4;
                        B[j][k + 4] = v5;
                        B[j + 1][k + 4] = v6;
                        B[j + 2][k + 4] = v7;
                        B[j + 3][k + 4] = v8;
                    }
                    for (k = j; k < j + 4; k++)
                    {
                        v1 = A[i + 4][k];
                        v2 = A[i + 5][k];
                        v3 = A[i + 6][k];
                        v4 = A[i + 7][k];
                        v5 = B[k][i + 4];
                        v6 = B[k][i + 5];
                        v7 = B[k][i + 6];
                        v8 = B[k][i + 7];

                        B[k][i + 4] = v1;
                        B[k][i + 5] = v2;
                        B[k][i + 6] = v3;
                        B[k][i + 7] = v4;
                        B[k + 4][i] = v5;
                        B[k + 4][i + 1] = v6;
                        B[k + 4][i + 2] = v7;
                        B[k + 4][i + 3] = v8;
                    }
                    for (k = i + 4; k < i + 8; k++)
                    {
                        v1 = A[k][j + 4];
                        v2 = A[k][j + 5];
                        v3 = A[k][j + 6];
                        v4 = A[k][j + 7];
                        B[j + 4][k] = v1;
                        B[j + 5][k] = v2;
                        B[j + 6][k] = v3;
                        B[j + 7][k] = v4;
                    }
                }
            }
        }
        else
        {
            for (i = 0; i < N; i += 16)
            {
                for (j = 0; j < M; j += 16)
                {
                    for (v1 = i; v1 < i + 16 && v1 < N; v1++)
                    {
                        for (v2 = j; v2 < j + 16 && v2 < M; v2++)
                        {
                            B[v2][v1] = A[v1][v2];
                        }
                    }
                }
            }
        }
    }
    if (M == 61 && N == 67)
    {
        for (int i = 0; i < N; i += 16)
        {
            for (int j = 0; j < M; j += 16)
            {
                for (int v1 = i; v1 < i + 16 && v1 < N; v1++)
                {
                    for (int v2 = j; v2 < j + 16 && v2 < M; v2++)
                    {
                        B[v2][v1] = A[v1][v2];
                    }
                }
            }
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
