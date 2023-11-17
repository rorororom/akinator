#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>

#include "stack.h"
#include "akinator.h"
#include "command_args.h"

static void Akinator(NodeAkinator* nowNode);
static int GetValidAnswerAkinator(NodeAkinator* nowNode);
static int CheckAnswerAkinator(char answer);
static void AddNewObjectToAkinator(NodeAkinator* nowNode);
static int SearchingItemCharacteristics(Stack* myStack, NodeAkinator* node, const char* value);
static void CompareAndAsk(NodeAkinator* nowNode, char newObj[], char newStr[]);

static void PrintCommand();

static void CompareObjects(TreeAkinator* tree);
static void ProcessCompareSign(Stack* myStackComparison, Stack* myStackComp,
                               Stack* myStackComp2, NodeAkinator** nowNode);

static void DistinctiveFeatureSubject(Stack* myStackComparison, Stack* myStackComp, NodeAkinator* nowNode,
                                      const char request[], const char* conjunction);
static void ReadObject(char request[]);
static void ReadObjectUntilValid(char request[], TreeAkinator* tree, Stack* myStack);

static int GetMenuCommand(char command);

static void ObjectDefinition(TreeAkinator* tree);

static void CtorInDelete(TreeAkinator* tree);
static void InitializeAkinatorNode(NodeAkinator* node, const char value[],
                                   NodeAkinator* left, NodeAkinator* right);

static void DestroyNode(NodeAkinator* node);

static void PrintNodeAkinarot(NodeAkinator* node, FILE* file);
static void SaveTreeToFile(NodeAkinator* root);

static void PrintNodeAkinarotConsol(NodeAkinator* node);
static void PrintValue(const char* value, int i, int size, int negate);
static void PrintNodeDump(FILE* dotFile, NodeAkinator* node, const char* fillColor);

void AkinatorSayString(const char* format, ...);

void BuildTreeFromFile(const char* filename, TreeAkinator* tree)
{
    FILE* file = fopen(filename, "r");
    if (file == nullptr)
    {
        printf("Ошибка при открытии файла.\n");
    }

    tree->rootTree = BuildTree(file);

    if (tree->rootTree == NULL)
    {
        AKINATOR_PRINT_STRING("Файл пустой или содержит только пробелы. Дерево не заполнено.\n");
        CtorRoot(tree);
    }
}

void CtorRoot(TreeAkinator* tree)
{
    CREAT_NODE(newNode);

    strcpy(newNode->value, "неизвесто что");
    newNode->left = NULL;
    newNode->right = NULL;

    tree->rootTree = newNode;
}

static void PrintCommand()
{
    printf("Команды(английскими буквами):\n"
            "\t[a] - игра Акинатор,\n"
            "\t[d] - удаление базы данных,\n"
            "\t[b] - построение определения объекта\n"
            "\t[c] - сравнение объектов\n"
            "\t[p] - создание графического дерева\n"
            "\t[s] - сохранить изменения\n"
            "\t[e] - выйти из программы\n");
}

void RunAkinatorMenuLoop(TreeAkinator* tree)
{
    assert(tree);

    PrintCommand();
    char entered = 0;
    scanf(" %c", &entered);
    int mode = GetMenuCommand(entered);

    if(mode == EXIT) return;

    do {
        while(mode == INCORRECT)
        {
            AKINATOR_PRINT_STRING("Некорректная команда. Пожалуйста, введите правильную команду.\n");
            PrintCommand();
            scanf(" %c", &entered);
            mode = GetMenuCommand(entered);
        }
        switch(mode)
        {
            case AKINATOR:
                Akinator(tree->rootTree);
                break;
            case DELETE:
                TreeDtor(tree);
                BuildTreeFromFile(FILENAME_DATA_BASE, tree);
                SaveTreeToFile(tree->rootTree);
                break;
            case DEFENITION:
                ObjectDefinition(tree);
                break;
            case COMPARISON:
                CompareObjects(tree);
                break;
            case PICTURE:
                GenerateImage(tree);
                GenerateGraphImage();
            case SAVE:
                SaveTreeToFile(tree->rootTree);
                break;
        }
        printf("\n");
        PrintCommand();

        scanf(" %c", &entered);
        mode = GetMenuCommand(entered);
    } while (mode != EXIT);
}

static int GetMenuCommand(char command)
{
    switch (command) {
        case 'a':
            return AKINATOR;
        case 'd':
            return DELETE;
        case 'b':
            return DEFENITION;
        case 'c':
            return COMPARISON;
        case 's':
            return SAVE;
        case 'e':
            return EXIT;
        case 'p':
            return PICTURE;
        default:
            return INCORRECT;
    }
}

void GenerateGraphImage()
{
    char command[MAX_LEN] = "";
    sprintf(command, "dot -Tpng /Users/aleksandr/Desktop/akinator/grapth.dot -o /Users/aleksandr/Desktop/akinator/file.png");
    system(command);
}

static void DestroyNode(NodeAkinator* node)
{
    if (node->left != nullptr) {
        DestroyNode(node->left);
    }
    if (node->right != nullptr) {
        DestroyNode(node->right);
    }

    free(node);
}

static void InitializeAkinatorNode(NodeAkinator* node, const char value[], NodeAkinator* left, NodeAkinator* right)
{
    assert(node);

    strcpy(node->value, value);
    node->left = left;
    node->right = right;

}

void TreeDtor(TreeAkinator* tree)
{
    DestroyNode(tree->rootTree);
    tree->rootTree = nullptr;

    CtorRoot(tree);
}

static void CtorInDelete(TreeAkinator* tree)
{
    assert(tree);
    TreeDtor(tree);

    CREAT_NODE(newNode);
    CtorRoot(tree);
}

static void PrintNodeDump(FILE* dotFile, NodeAkinator* node, const char* fillColor)
{
    assert(dotFile);
    assert(node);

    if (node == NULL)
    {
        return;
    }

    fprintf(dotFile, "%d [shape=record, style=\"filled,rounded\", color=\"#552d7b\",\
                          fillcolor=\"%s\", fontsize=14, label=\" %s \"];\n",
                          node, fillColor, node->value);

    if (node->left != NULL)
    {
        fprintf(dotFile, "\t%d -> %d;\n", node, node->left);
        PrintNodeDump(dotFile, node->left, "#6495ed");
    }

    if (node->right != NULL)
    {
        fprintf(dotFile, "\t%d -> %d;\n", node, node->right);
        PrintNodeDump(dotFile, node->right, "#bba6cd");
    }
}

void AkinatorSayString(const char* format, ...)
{
    va_list argList;

    va_start(argList, format);

    static const size_t  maxStringLength  =    1024;
    static char  command[maxStringLength] =  "say ";
    static const size_t sayShift = 4;

    vsnprintf(command + sayShift, maxStringLength, format, argList);
    system(command);

    va_end(argList);
}


void GenerateImage(TreeAkinator* tree)
{
    assert(tree);

    FILE* dotFile = fopen("grapth.dot", "w");
    if (dotFile)
    {
        fprintf(dotFile, "digraph tree {\n");
        fprintf(dotFile, "\tnode [shape=Mrecord, style=filled, fillcolor=\"#bba6cd\", color=\"#552d7b\"];\n");

        PrintNodeDump(dotFile, tree->rootTree, "#d5a1a7");

        fprintf(dotFile, "}\n");
        fclose(dotFile);
    }
    else
    {
        AKINATOR_PRINT_STRING("Ошибка при открытии файла graph.dot\n");
    }
}

// static int Min()
// {
//
// }

static void Akinator(NodeAkinator* nowNode)
{
    assert(nowNode);

    if (nowNode == NULL)
    {
        return;
    }

    int mode = GetValidAnswerAkinator(nowNode);

    if (mode == YES)
    {
        if (nowNode->right == NULL)
        {
            AKINATOR_PRINT_STRING("УРА УРА\n");
        }
        else
        {
            Akinator(nowNode->right);
        }
    }
    else if (mode == NO)
    {
        AddNewObjectToAkinator(nowNode);
    }
}

static int GetValidAnswerAkinator(NodeAkinator* nowNode)
{
    printf("Введите [y] - да, [n] - нет\n");
    AKINATOR_PRINT_STRING("Это %s?\n", nowNode->value);

    char answer = 0;
    scanf(" %c", &answer);

    int entered = 0;
    while ((entered = getchar()) != '\n' && entered != EOF) { }
    int mode = CheckAnswerAkinator(answer);

    while(mode == INCORRECT)
    {
        AKINATOR_PRINT_STRING("Некорректный ответ, введите заново.\n");
        scanf(" %c", &answer);

        int entered = 0;
        while ((entered = getchar()) != '\n' && entered != EOF) { }
        mode = CheckAnswerAkinator(answer);
    }

    return mode;
}

static void AddNewObjectToAkinator(NodeAkinator* nowNode)
{
    if (nowNode->left == NULL)
    {
        char newObj[MAX_OBJECT_NAME_LENGTH] = "";
        char newStr[MAX_OBJECT_NAME_LENGTH] = "";

        CompareAndAsk(nowNode, newObj, newStr);

        ReadObject(newStr);
        CREAT_NODE(falseNode);
        InitializeAkinatorNode(falseNode, nowNode->value, nullptr, nullptr);

        CREAT_NODE(trueNode);
        InitializeAkinatorNode(trueNode, newObj, nullptr, nullptr);

        nowNode->right = trueNode;
        nowNode->left = falseNode;
        strcpy(nowNode->value, newStr);
    }
    else
    {
        if (nowNode->left != NULL)
        {
            Akinator(nowNode->left);
        }
    }
}

static void CompareAndAsk(NodeAkinator* nowNode, char newObj[], char newStr[])
{
    if (MODE_ARG == ARG_MARIIA)
    {
        AKINATOR_PRINT_STRING("Что или Кто это?\n");
        fgets(newObj, MAX_OBJECT_NAME_LENGTH, stdin);

        ReadObject(newObj);
        AKINATOR_PRINT_STRING("Не знаю, что это. Чем %s отличается от %s?\n", newObj, nowNode->value);
        fgets(newStr, MAX_OBJECT_NAME_LENGTH, stdin);
    }
    else if (MODE_ARG == ARG_DED)
    {
        AKINATOR_PRINT_STRING("Не знаю, что это. Чем твое загаданное отличается от %s?\n", nowNode->value);
        fgets(newStr, MAX_OBJECT_NAME_LENGTH, stdin);

        ReadObject(newObj);
        AKINATOR_PRINT_STRING("Что или Кто это?\n");
        fgets(newObj, MAX_OBJECT_NAME_LENGTH, stdin);
    }
}

static int CheckAnswerAkinator(char answer)
{
    if (answer == 'y') return YES;
    else if (answer == 'n') return NO;
    else return ERRROR_ANSWER;
}

static void PrintNodeAkinarot(NodeAkinator* node, FILE* file)
{
    assert(file);

    if (node == NULL)
    {
        fprintf(file, "<null> ");
        return;
    }

    fprintf(file, "( ");
    fprintf(file, "<%s> ", node->value);
    PrintNodeAkinarot(node->left, file);
    PrintNodeAkinarot(node->right, file);
    fprintf(file, ") ");
}

static void SaveTreeToFile(NodeAkinator* root)
{
    assert(root);

    FILE* file = fopen(FILENAME_FOR_WORK, "w");
    if (file == NULL)
    {
        AKINATOR_PRINT_STRING("Ошибка при открытии файла.\n");
        return;
    }

    PrintNodeAkinarot(root, file);
    fclose(file);
}

static void PrintNodeAkinarotConsol(NodeAkinator* node)
{
    assert(node);

    if (node == NULL)
    {
        printf("null\n");
        return;
    }

    printf("( ");
    printf("<%s> ", node->value);
    PrintNodeAkinarotConsol(node->left);
    PrintNodeAkinarotConsol(node->right);
    printf(") ");
}

NodeAkinator* BuildTree(FILE* file)
{
    assert(file);

    char token[MAX_OBJECT_NAME_LENGTH] = "";
    int i = 0;
    if (fscanf(file, "%s", token) == EOF) {
        return NULL;
    }

    if (strcmp(token, "(") == 0)
    {
        char c = 0;
        token[MAX_OBJECT_NAME_LENGTH];
        while ((c = fgetc(file)) != EOF && c != '>')
        {
            if (c == '<')
            {
                i--;
                continue;
            }

            if (i < MAX_OBJECT_NAME_LENGTH - 1)
            {
                token[i] = c;
                i++;
            }
        }

        token[i] = '\0';
        if (strcmp(token, "<null") == 0)
        {
            return NULL;
        }

        CREAT_NODE(newNode);
        InitializeAkinatorNode(newNode, token, NULL, NULL);

        newNode->left = BuildTree(file);
        newNode->right = BuildTree(file);
        fscanf(file, "%s", token);
        return newNode;
    }
    else
    {
        if (strcmp(token, "<null>") == 0)
        {
            return NULL;
        }

        CREAT_NODE(newNode);
        strcpy(newNode->value, token);
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }
}

static int SearchingItemCharacteristics(Stack* myStack, NodeAkinator* node, const char* value)
{
    assert(myStack);

    if (node == NULL)
    {
        return 0;
    }

    if (strcmp(node->value, value) == 0)
    {
        return 1;
    }

    StackPush(myStack, 0);
    int flagCharacteristics = SearchingItemCharacteristics(myStack, node->left, value);
    if (flagCharacteristics == 1)
    {
        return 1;
    }
    StackPop(myStack);

    StackPush(myStack, 1);
    flagCharacteristics = SearchingItemCharacteristics(myStack, node->right, value);
    if (flagCharacteristics == 0) StackPop(myStack);

    return flagCharacteristics;
}

static void ObjectDefinition(TreeAkinator* tree)
{
    assert(tree);

    Stack myStack = {};
    StackCtor(&myStack);

    char request[MAX_LEN] = "";

    AKINATOR_PRINT_STRING("Введите объект, определение которого вы хотите получить: ");
    scanf("%s", request);
    ReadObject(request);

    int flagCharacteristics = SearchingItemCharacteristics(&myStack, tree->rootTree, request);
    if (flagCharacteristics == 0)
    {
        AKINATOR_PRINT_STRING("Такого объекта нет\n");
    }

    AKINATOR_PRINT_STRING("%s: ", request);
    NodeAkinator* nowNode = tree->rootTree;

    for (int i = 0; i < myStack.size ; i++)
    {
        if (myStack.data[i] == 0)
        {
            //AKINATOR_PRINT_STRING("%s ", nowNode->value);
            PrintValue(nowNode->value, i, myStack.size, WITH_NEGATION);
            nowNode = nowNode->left;
        }
        else
        {
            //AKINATOR_PRINT_STRING("%s ", nowNode->value);
            PrintValue(nowNode->value, i, myStack.size, WITHOUT_NEGATION);
            nowNode = nowNode->right;
        }
    }
    printf("\n");
    StackDtor(&myStack);
}

static void PrintValue(const char* value, int i, int size, int negate)
{
    const char* prefix = (negate) ? "не " : "";
    const char* suffix = (i == size - 1) ? "." : ", ";
    AKINATOR_PRINT_STRING("%s%s%s", prefix, value, suffix);
}

static void CompareObjects(TreeAkinator* tree)
{
    assert(tree);

    Stack myStackComp = {};
    StackCtor(&myStackComp);

    Stack myStackComp2 = {};
    StackCtor(&myStackComp2);

    Stack myStackComparison = {};
    StackCtor(&myStackComparison);

    char request1[MAX_OBJECT_NAME_LENGTH] = "";
    char request2[MAX_OBJECT_NAME_LENGTH] = "";

    AKINATOR_PRINT_STRING("Введите объекты, сравнение которых хотите получить:\n");

    ReadObjectUntilValid(request1, tree, &myStackComp);
    ReadObjectUntilValid(request2, tree, &myStackComp2);

    AKINATOR_PRINT_STRING("%s и %s схожи тем, что они - ", request1, request2);
    NodeAkinator* nowNode = tree->rootTree;
    ProcessCompareSign(&myStackComparison, &myStackComp, &myStackComp2, &nowNode);

    NodeAkinator* newNode = nowNode;
    DistinctiveFeatureSubject(&myStackComparison, &myStackComp, newNode, request1, ", но");
    newNode = nowNode;
    DistinctiveFeatureSubject(&myStackComparison, &myStackComp2, newNode, request2, ", a");
}

static void DistinctiveFeatureSubject(Stack* myStackComparison, Stack* myStackComp, NodeAkinator* nowNode,
                               const char request[], const char* conjunction)
{
    assert(myStackComparison);
    assert(myStackComp);
    assert(nowNode);

    if (myStackComparison->size < myStackComp->size)
    {
        AKINATOR_PRINT_STRING("%s %s - ", conjunction, request);

        for (int i = myStackComparison->size; i < myStackComp->size; i++)
        {
            if (myStackComp->data[i] == 0)
            {
                PrintValue(nowNode->value, i, myStackComp->size, WITH_NEGATION);
                nowNode = nowNode->left;
            }
            else
            {
                PrintValue(nowNode->value, i, myStackComp->size, WITHOUT_NEGATION);
                nowNode = nowNode->right;
            }
        }
    }
}

static void ProcessCompareSign(Stack* myStackComparison, Stack* myStackComp,
                               Stack* myStackComp2, NodeAkinator** nowNode)
{
    assert(myStackComparison);
    assert(myStackComp);
    assert(myStackComp2);

    for (int i = 0; i < MIN(myStackComp2->size, myStackComp->size); i++)
    {
        if (myStackComp->data[i] == myStackComp2->data[i])
        {
            StackPush(myStackComparison, i);
            if (myStackComp->data[i] == 0)
            {
                AKINATOR_PRINT_STRING("\"не %s\" ", (*nowNode)->value);
                *nowNode = (*nowNode)->left;
            }
            else
            {
                AKINATOR_PRINT_STRING("\"%s\" ", (*nowNode)->value);
                *nowNode = (*nowNode)->right;
            }
        }
        else
        {
            break;
        }
    }
}

static void ReadObjectUntilValid(char request[], TreeAkinator* tree, Stack* myStack)
{
    assert(tree);
    assert(myStack);

    int flagCharacteristics = 0;
    do {
        AKINATOR_PRINT_STRING("\tВведите объект: ");
        scanf("%s", request);

        ReadObject(request);
        flagCharacteristics = SearchingItemCharacteristics(myStack, tree->rootTree, request);
        CHECKING_OBJECT(flagCharacteristics, request);
    } while (flagCharacteristics == 0);
}

static void ReadObject(char request[])
{
    size_t len = strlen(request);
    if (len > 0 && request[len - 1] == '\n')
    {
        request[len - 1] = '\0';
    }
}











