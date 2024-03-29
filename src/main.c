#include "queens.h"
#include "log.h"
#include <stdlib.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
		ERRORF("Usage: queens <boardSize>");
		return EXIT_FAILURE;
    }

	DEBUGF("Creating ‘context’");
    Queens_Context *context = Queens_Create(strtol(argv[1], NULL, 10));
	if (context == NULL)
	{
		ERRORF("Context creation error");
		return EXIT_FAILURE;
	}

    printf("%d solutions found\n", Queens_Solve(context));

    Queens_Destroy(context);
    return EXIT_SUCCESS;
}
