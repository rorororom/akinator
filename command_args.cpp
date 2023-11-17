#include <string.h>
#include <stdio.h>

#include "command_args.h"

extern char* FILENAME_FOR_WORK = "";
extern char* FILENAME_DATA_BASE = "";
extern int MODE_ARG = 0;

void CheckArgComStr(int argc, char* argv[])
{
    char* argModeFromComStr = "";
    if (argc > 1)
    {
        for (int i = 1; i < argc; i+=2)
        {
            if (strcmp(argv[i], "-b") == 0 && argv[i + 1] != NULL)
            {
                FILENAME_DATA_BASE = argv[i + 1];
            }
            else if (strcmp(argv[i], "-f") == 0 && argv[i + 1] != NULL)
            {
                FILENAME_FOR_WORK = argv[i + 1];
            }
            else if (strcmp(argv[i], "-m") == 0 && argv[i + 1] != NULL)
            {
                argModeFromComStr = argv[i + 1];
            }
            else
            {
                printf("с такими аргументами командной строки я пользоваться не умею\n");
            }
        }
    }

    if (FILENAME_DATA_BASE == NULL) strcpy(FILENAME_DATA_BASE, "DataBase.txt");
    if (FILENAME_FOR_WORK == NULL) strcpy(FILENAME_FOR_WORK, "DataBase.txt");

    printf("%s\n", FILENAME_DATA_BASE);
    MODE_ARG = CheckMode(argModeFromComStr);
}

int CheckMode(const char* argModeFromComStr)
{
    if (strcmp(argModeFromComStr, "0") == 0) return ARG_MARIIA;
    else if (strcmp(argModeFromComStr, "1") == 0) return ARG_DED;
    else return ARG_MARIIA;
}
