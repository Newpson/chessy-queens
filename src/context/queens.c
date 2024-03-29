#include "queens.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

struct Queens_Context
{
    int boardSize;
    int **board;
    int solutionsCount;
};

static int Queens_BoardCreate(Queens_Context *context);
static void Queens_BoardPut(Queens_Context *context, int qy, int qx, int value);
static void Queens_BoardDestroy(Queens_Context *context);

static int Queens_SolveRecursive(Queens_Context *context, int y);
static void Queens_Print(Queens_Context *context);
static void Queens_PrintQueens(Queens_Context *context);

Queens_Context *Queens_Create(int boardSize)
{
    if (boardSize < 1 || boardSize > QUEENS_MAX_BOARDSIZE)
    {
        ERRORF("‘boardSize’ must be in range [1, %d]", QUEENS_MAX_BOARDSIZE);
        return NULL;
    }

    DEBUGF("Allocating ‘context’");
    Queens_Context *context = calloc(1, sizeof(Queens_Context));
    if (context == NULL)
    {
        ERRORF("Context allocation error");
        return NULL;
    }

    context->boardSize = boardSize;
    DEBUGF("‘context->boardSize’ set to %d", boardSize);

    DEBUGF("Creating ‘context->board’");
    if (Queens_BoardCreate(context) < boardSize)
    {
        ERRORF("Board creation error");
        return NULL;
    }

    return context;
}

    static
int Queens_BoardCreate(Queens_Context *context)
{
    assert(context != NULL);
    assert(context->boardSize > 0);
    int allocated = 0;

    DEBUGF("Allocating ‘context->board’");
    context->board = calloc(context->boardSize, sizeof(int *));
    if (context->board == NULL)
    {
        ERRORF("Board allocation error");
        return allocated;
    }

    for (; allocated < context->boardSize; ++allocated)
    {
        DEBUGF("Allocating ‘context->board[%d]’", allocated);
        context->board[allocated] = calloc(context->boardSize, sizeof(int));
        if (context->board[allocated] == NULL)
        {
            ERRORF("Board allocation error");
            break;
        }
    }

    return allocated;
}

    static
void Queens_BoardDestroy(Queens_Context *context)
{
    assert(context != NULL);

    if (context->board)
    {
        for (int i = 0; i < context->boardSize; ++i)
        {
            DEBUGF("Freeing (if needed) ‘context->board[%d]’", i);
            free(context->board[i]);
        }
    }

    DEBUGF("Freeing (if needed) ‘context->board’");
    free(context->board);
}

    static
void Queens_BoardPut(Queens_Context *context, int qy, int qx, int value)
{
    assert(context != NULL);
    assert(context->board != NULL);

    for (int y = 0; y < context->boardSize; ++y)
    {
        for (int x = 0; x < context->boardSize; ++x)
        {
            if (x == qx && y == qy)
            {
                context->board[y][x] += QUEENS_MAX_BOARDSIZE*value;
            }
            if (x == qx || y == qy || y == x + (qy-qx) || y == -x + (qy+qx))
            {
                context->board[y][x] += value;
            }
        }
    }
}

    static
void Queens_Print(Queens_Context *context)
{
    for (int y = 0; y < context->boardSize; ++y)
    {
        for (int x = 0; x < context->boardSize; ++x)
        {
            printf("%03d", context->board[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

    static
void Queens_PrintQueens(Queens_Context *context)
{
    for (int y = 0; y < context->boardSize; ++y)
    {
        for (int x = 0; x < context->boardSize; ++x)
        {
            printf("%s ",
                    context->board[y][x] >= QUEENS_MAX_BOARDSIZE ? "♛" :
                    context->board[y][x] > 0 ? "." : "-");
        }
        printf("\n");
    }
    printf("\n");
}

int Queens_Solve(Queens_Context *context)
{
    assert(context != NULL);
    context->solutionsCount = 0;
    DEBUGF("Starting recursive solving");
    Queens_SolveRecursive(context, 0);

    return context->solutionsCount;
}

    static
int Queens_SolveRecursive(Queens_Context *context, int y)
{
    assert(context != NULL);

    if (y == context->boardSize)
    {
        context->solutionsCount += 1;
        DEBUGF("Solution #%d found", context->solutionsCount);
        Queens_PrintQueens(context);
        return y;
    }

    int attacked = 0;
    for (int x = 0; x < context->boardSize; ++x)
    {
        if (context->board[y][x] > 0)
        {
            ++attacked;
            continue;
        }
        Queens_BoardPut(context, y, x, 1);

        if (Queens_SolveRecursive(context, y+1) == context->boardSize)
        {
            ++attacked;
            Queens_BoardPut(context, y, x, -1);
        }
    }

    return attacked;
}

void Queens_Destroy(Queens_Context *context)
{
    if (context)
    {
        DEBUGF("Destroying (if needed) ‘context->board’");
        Queens_BoardDestroy(context);

        DEBUGF("Freeing (if needed) ‘context’");
        free(context);
    }
}
