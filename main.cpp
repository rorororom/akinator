#include <stdio.h>
#include <stdlib.h>

#include "akinator.h"

int main()
{
    TreeAkinator tree = {};
    NodeAkinator root = {};
    tree.RootTree = &root;
    FILE* file = fopen("printoutAK.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }

    tree.RootTree = buildTree(file);
    fclose(file);

    PRINT_COMMAND();
    char c;
    scanf(" %c", &c);
    int mode = CheckCommand(c);

    do {
        while(mode == -1)
        {
            printf("Некорректная команда. Пожалуйста, введите правильную команду.\n");
            PRINT_COMMAND();
            scanf(" %c", &c);
            mode = CheckCommand(c);
        }
        switch(mode)
        {
            case AKINATOR:
                Akinator(&tree.RootTree);
                break;
            case DELETE:
                TreeDtor(&tree);
                CtorInDelete(&tree);
                break;
            case DEFENITION:
                ObjectDefinition(&tree);
                break;
            case COMPARISON:
                CompareObjects(&tree);
                break;
            case SAVE:
                SaveTreeToFile(tree.RootTree);
                break;
        }
        printf("\n");
        PRINT_COMMAND();

        scanf(" %c", &c);
        mode = CheckCommand(c);
    } while (c != 'e');

    GenerateImage(&tree);
    CreateNewGraph();

    TreeDtor(&tree);
    return 0;
}
