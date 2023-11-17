#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "akinator.h"
#include "command_args.h"

int main(int argc, char* argv[])
{
    CheckArgComStr(argc, argv);

    TreeAkinator tree = {};
    CtorRoot(&tree);

    BuildTreeFromFile(FILENAME_FOR_WORK, &tree);

    RunAkinatorMenuLoop(&tree);

    TreeDtor(&tree);
    return 0;
}
