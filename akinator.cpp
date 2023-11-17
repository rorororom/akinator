#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "stack.h"
#include "akinator.h"

int CheckCommand(char c)
{
    switch (c) {
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
        default:
            return -1;
    }
}

void CreateNewGraph()
{
    char command[1000];
    sprintf(command, "dot -Tpng /Users/aleksandr/Desktop/akinator/grapth.dot -o /Users/aleksandr/Desktop/akinator/file.png");
    system(command);
}

void DestroyNode(NodeAkinator* node)
{
    assert(node);

    if (node == nullptr) {
        return;
    }

    if (node->left != nullptr) {
        DestroyNode(node->left);
    }
    if (node->right != nullptr) {
        DestroyNode(node->right);
    }

    free(node);
}

void TreeDtor(TreeAkinator* tree)
{
    DestroyNode(tree->RootTree);
    tree->RootTree = nullptr;
}

void CtorInDelete(TreeAkinator* tree)
{
    assert(tree);
    TreeDtor(tree);

    NodeAkinator* newNode = (NodeAkinator*)malloc(sizeof(NodeAkinator));
    if (newNode == nullptr) {
        printf("не выделилась память для структуры\n");
    }

    strcpy(newNode->value, "неизвестно что");

    newNode->left = nullptr;
    newNode->right = nullptr;
    tree->RootTree = newNode;
}

void PrintNodeDump(FILE* dotFile, NodeAkinator* node, const char* fillColor)
{
    assert(dotFile);
    assert(node);

    if (node == NULL) {
        return;
    }

    fprintf(dotFile, "%d [shape=record, style=\"filled,rounded\", color=\"#552d7b\",\
                          fillcolor=\"%s\", fontsize=14, label=\" %s \"];\n",
                          node, fillColor, node->value);

    if (node->left != NULL) {
        fprintf(dotFile, "\t%d -> %d;\n", node, node->left);
        PrintNodeDump(dotFile, node->left, "#6495ed");
    }

    if (node->right != NULL) {
        fprintf(dotFile, "\t%d -> %d;\n", node, node->right);
        PrintNodeDump(dotFile, node->right, "#bba6cd");
    }
}



void GenerateImage(TreeAkinator* tree)
{
    assert(tree);

    FILE* dotFile = fopen("grapth.dot", "w");
    if (dotFile)
    {
        fprintf(dotFile, "digraph tree {\n");
        fprintf(dotFile, "\tnode [shape=Mrecord, style=filled, fillcolor=\"#bba6cd\", color=\"#552d7b\"];\n");

        PrintNodeDump(dotFile, tree->RootTree, "#d5a1a7");

        fprintf(dotFile, "}\n");
        fclose(dotFile);
    }
    else
    {
        fprintf(stderr, "Ошибка при открытии файла graph.dot\n");
    }
}

void Akinator(NodeAkinator** nowNode)
{
    assert(nowNode);

    if (*nowNode == NULL)
    {
        return;
    }
    printf("\n\nВведите [y] - да, [n] - нет\n\n");

    printf("Это %s?\n", (*nowNode)->value);
    char s;
    scanf(" %c", &s);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    if (s == 'y')
    {
        if ((*nowNode)->right == NULL)
        {
            printf("СЮДАААА\n");
        }
        else
        {
            Akinator(&((*nowNode)->right));
        }
    }
    else if (s == 'n')
    {
        if ((*nowNode)->left == NULL)
        {
            printf("Что или Кто это?\n");
            char newObj[MAX_LEN];
            fgets(newObj, MAX_LEN, stdin);

            char newStr[MAX_LEN];
            printf("Не знаю, что это. Чем %s отличается от твоего загаданного?\n", (*nowNode)->value);
            fgets(newStr, MAX_LEN, stdin);

            size_t len = strlen(newStr);
            if (len > 0 && newStr[len - 1] == '\n')
            {
                newStr[len - 1] = '\0';
            }

            NodeAkinator* newRoot = (NodeAkinator*)malloc(sizeof(NodeAkinator));
            strcpy(newRoot->value, newStr);
            newRoot->left = *nowNode;
            newRoot->right = NULL;

            len = strlen(newObj);
            if (len > 0 && newObj[len - 1] == '\n')
            {
                newObj[len - 1] = '\0';
            }

            NodeAkinator* newObject = (NodeAkinator*)malloc(sizeof(NodeAkinator));
            strcpy(newObject->value, newObj);
            newObject->left = NULL;
            newObject->right = NULL;

            newRoot->right = newObject;
            *nowNode = newRoot;
        }
        else
        {
            if ((*nowNode)->left != NULL)
            {
                Akinator(&((*nowNode)->left));
            }
        }
    }
}

void PrintNodeAkinarot(NodeAkinator* node, FILE* file)
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

void SaveTreeToFile(NodeAkinator* root)
{
    assert(root);

    FILE* file = fopen("printoutAK.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return;
    }

    PrintNodeAkinarot(root, file);
    fclose(file);
}

void PrintNodeAkinarotConsol(NodeAkinator* node)
{
    assert(node);

    if (node == NULL) {
        printf("null\n");
        return;
    }

    printf("( ");
    printf("<%s> ", node->value);
    PrintNodeAkinarotConsol(node->left);
    PrintNodeAkinarotConsol(node->right);
    printf(") ");
}

NodeAkinator* buildTree(FILE* file)
{
    assert(file);

    char token[MAX_LEN];
    int i = 0;
    fscanf(file, "%s", token);

    if (strcmp(token, "(") == 0)
    {
        char c;
        token[MAX_LEN];
        while ((c = fgetc(file)) != EOF && c != '>')
        {
            if (c == '<')
            {
                i--;
                continue;
            }

            if (i < MAX_LEN - 1)
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

        NodeAkinator* newNode = (NodeAkinator*)malloc(sizeof(NodeAkinator));
        strcpy(newNode->value, token);
        newNode->left = buildTree(file);
        newNode->right = buildTree(file);
        fscanf(file, "%s", token);
        return newNode;
    }
    else
    {
        if (strcmp(token, "<null>") == 0)
        {
            return NULL;
        }

        NodeAkinator* newNode = (NodeAkinator*)malloc(sizeof(NodeAkinator));
        strcpy(newNode->value, token);
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }
}

int SearchingItemCharacteristics(Stack* myStack, NodeAkinator* node, const char* value)
{
    assert(myStack);
    assert(node);

    if (node == NULL)
    {
        return 0;
    }

    if (strcmp(node->value, value) == 0)
    {
        return 1;
    }

    StackPush(myStack, 0);
    int k = SearchingItemCharacteristics(myStack, node->left, value);
    if (k == 1)
    {
        return 1;
    }
    StackPop(myStack);

    StackPush(myStack, 1);
    k = SearchingItemCharacteristics(myStack, node->right, value);
    if (k == 0) StackPop(myStack);

    return k;
}

void ObjectDefinition(TreeAkinator* tree)
{
    assert(tree);

    Stack myStack = {};
    StackCtor(&myStack);

    char request[100];
    printf("Введите объект, определение которого вы хотите получить: ");
    scanf("%s", request);
    size_t len = strlen(request);
    if (len > 0 && request[len - 1] == '\n')
    {
        request[len - 1] = '\0';
    }

    int k = SearchingItemCharacteristics(&myStack, tree->RootTree, request);
    if (k == 0)
    {
        printf("Такого объекта нет\n");
    }

    printf("%s: ", request);
    NodeAkinator* nowNode = tree->RootTree;

    for (int i = 0; i < myStack.size ; i++)
    {
        if (myStack.data[i] == 0)
        {
            if (i ==  myStack.size - 1)
            {
                printf("не %s.", nowNode->value);
            }
            else
            {
                printf("не %s, ", nowNode->value);
            }
            nowNode = nowNode->left;
        }
        else
        {
            if (i ==  myStack.size - 1)
            {
                printf("%s.", nowNode->value);
            }
            else
            {
                printf("%s, ", nowNode->value);
            }
            nowNode = nowNode->right;
        }
    }
    printf("\n");
    StackDtor(&myStack);
}

void CompareObjects(TreeAkinator* tree)
{
    assert(tree);

    Stack myStackComp = {};
    StackCtor(&myStackComp);

    Stack myStackComp2 = {};
    StackCtor(&myStackComp2);

    Stack myStackComparison = {};
    StackCtor(&myStackComparison);

    char request1[MAX_LEN];
    char request2[MAX_LEN];
    printf("Введите объекты, сравнение которых хотите получить:\n");
    ReadObjectUntilValid(request1, tree, &myStackComp);
    ReadObjectUntilValid(request2, tree, &myStackComp2);

    printf("%s\n", request1);
    printf("%s\n", request2);
    printf("%s и %s схожи тем, что они - ", request1, request2);
    NodeAkinator* nowNode = tree->RootTree;
    ProcessCompareSign(&myStackComparison, &myStackComp, &myStackComp2, &nowNode);

    DistinctiveFeatureSubject(&myStackComparison, &myStackComp, nowNode, request1, "но");
    DistinctiveFeatureSubject(&myStackComparison, &myStackComp2, nowNode, request2, "a");
}

void DistinctiveFeatureSubject(Stack* myStackComparison, Stack* myStackComp, NodeAkinator* nowNode,
                               const char request[], const char* conjunction)
{
    assert(myStackComparison);
    assert(myStackComp);
    assert(nowNode);

    NodeAkinator* newNode = nowNode;
    if (myStackComparison->size < myStackComp->size) {
        printf("\n\n%s %s - ", conjunction, request);

        for (int i = myStackComparison->size; i < myStackComp->size; i++)
        {
            if (myStackComp->data[i] == 0)
            {
                printf("\"не %s\" ", newNode->value);
                newNode = newNode->left;
            }
            else
            {
                printf("\"%s\" ", newNode->value);
                newNode = newNode->right;
            }
        }
    }
}

void ProcessCompareSign(Stack* myStackComparison, Stack* myStackComp,
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
                printf("\"не %s\" ", (*nowNode)->value);
                *nowNode = (*nowNode)->left;
            }
            else
            {
                printf("\"%s\" ", (*nowNode)->value);
                *nowNode = (*nowNode)->right;
            }
        }
    }
}

void ReadObjectUntilValid(char request[], TreeAkinator* tree, Stack* myStack)
{
    assert(tree);
    assert(myStack);

    int cnt = 0;
    do{
        ReadObject(request);
        cnt = SearchingItemCharacteristics(myStack, tree->RootTree, request);
        CHECKING_OBJECT(cnt, request);
    } while (cnt == 0);
}

void ReadObject(char request[])
{
    printf("\tВведите объект: ");
    scanf("%s", request);

    size_t len = strlen(request);
    if (len > 0 && request[len - 1] == '\n')
    {
        request[len - 1] = '\0';
    }
}











