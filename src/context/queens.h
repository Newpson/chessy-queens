#pragma once
#define QUEENS_MAX_BOARDSIZE 128

typedef struct Queens_Context Queens_Context;

Queens_Context *Queens_Create(int boardSize);
void Queens_Destroy(Queens_Context *context);
int Queens_Solve(Queens_Context *context);
