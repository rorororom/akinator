#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int main()
{
    Tree tree = {0};
    CtorTreeStruct(&tree);

//     Node Node3 = {0};
//     NodeAkinatorInit(&Node3, 3, NULL, NULL, &tree);
//
//     Node Node15 = {0};
//     NodeAkinatorInit(&Node15, 16, NULL, NULL, &tree);
//
//     Node Node19 = {0};
//     NodeAkinatorInit(&Node19, 19, NULL, NULL, &tree);
//
//     Node Node20 = {0};
//     NodeAkinatorInit(&Node20, 20, &Node15, &Node19, &tree);
//
//     Node Node10 = {0};
//     NodeAkinatorInit(&Node10, 10, &Node3, &Node20, &tree);
//
//     tree.RootTree = &Node10;
//
//     AddNewNodeIncreasing(tree.RootTree, 5, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 12, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 18, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 21, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 2, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 4, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 23, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 16, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 17, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 8, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 34, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 1, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 3, &tree);
//     AddNewNodeIncreasing(tree.RootTree, 100, &tree);

    //GenerateImage(&tree);

    Node* root = (struct Node*)malloc(sizeof(Node));
    FILE* inputFile = fopen("outputTextDump.txt", "r");
    if (inputFile) {
        root = read_data(inputFile);
        fclose(inputFile);
    }

    tree.RootTree = root;

    GenerateImage(&tree);

    inputFile = fopen("outputTextDumpAAAA.txt", "w");
    if (inputFile)
    {
        PrintNode(tree.RootTree, inputFile);
        fclose(inputFile);
    }
    else
    {
        printf("файл не открылся\n");
    }

    TreeDtor(&tree);
    return 0;
}

void CtorTreeStruct(struct Tree* tree)
{
    tree->RootTree = NULL;
    tree->size = 0;
}

void DestroyNode(Node* node)
{
    if (node == nullptr) {
        return;
    }

    DestroyNode(node->left);
    DestroyNode(node->right);
    free(node);
}

void TreeDtor(Tree* tree)
{
    DestroyNode(tree->RootTree);
    tree->RootTree = nullptr;
}

void NodeAkinatorInit(Node* node, int value, Node* left, Node* right, Tree* tree)
{
    assert(node);

    node->value = value;
    node->left = left;
    node->right = right;

    tree->size++;
}

void AddNewNodeIncreasing(Node* current, int value, Tree* tree)
{
    assert(current);

    if (current->value > value)
    {
        if (current->left != NULL)
        {
            AddNewNodeIncreasing(current->left, value, tree);
        }
        else
        {
            Node* newNode = (struct Node*)malloc(sizeof(Node));
            NodeAkinatorInit(newNode, value, NULL, NULL, tree);
            current->left = newNode;
        }
    }
    else
    {
        if (current->right != NULL)
        {
            AddNewNodeIncreasing(current->right, value, tree);
        }
        else
        {
            Node* newNode = (struct Node*)malloc(sizeof(Node));
            NodeAkinatorInit(newNode, value, NULL, NULL, tree);
            current->right = newNode;
        }
    }
}

void PrintNode(Node* node, FILE* file)
{
    if (node == NULL)
    {
        fprintf(file, "null ");
        fprintf(file, "\n");
        return;
    }
    fprintf(file, "(");
    fprintf(file, "\n");
    fprintf(file, "%d", node->value);
    fprintf(file, "\n");
    PrintNode(node->left, file);
    PrintNode(node->right, file);
    fprintf(file, ")");
    fprintf(file, "\n");
}

void PrintNodeConsol(Node* node)
{
    if (node == NULL)
    {
        printf("null ");
        printf("\n");
        return;
    }
    printf("(");
    printf("\n");
    printf("%d", node->value);
    printf("\n");
    PrintNodeConsol(node->left);
    PrintNodeConsol(node->right);
    printf(")");
    printf("\n");
}

void RecordingTextDump(Tree* tree)
{
    FILE *outputFile = fopen ("outputTextDump.txt", "w");
    if (! (outputFile))
    {
        printf ("File not found");
        return;
    }

    PrintNode(tree->RootTree, outputFile);

    fclose(outputFile);
}


void PrintNodeDump(FILE* dotFile, Node* node, const char* fillColor)
{
    if (node == NULL) {
        return;
    }

    fprintf(dotFile, "%d [shape=record, style=\"filled,rounded\", color=\"#552d7b\",\
                          fillcolor=\"%s\", fontsize=14, label=\" %d \"];\n",
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

void GenerateImage(Tree* tree)
{
    FILE* dotFile = fopen("graph.dot", "w");
    if (dotFile) {
        fprintf(dotFile, "digraph tree {\n");
        fprintf(dotFile, "\tnode [shape=Mrecord, style=filled, fillcolor=\"#bba6cd\", color=\"#552d7b\"];\n");

        PrintNodeDump(dotFile, tree->RootTree, "#d5a1a7");

        fprintf(dotFile, "}\n");
        fclose(dotFile);
    } else {
        fprintf(stderr, "Ошибка при открытии файла graph.dot\n");
    }
}

struct Node* RestoreTree(FILE* file)
{
    char c;
    fscanf(file, " %c", &c); // Считываем символ '('

    if (c == ')') {
        return NULL; // Встретили закрывающую скобку, возвращаем NULL
    }

    int value;
    fscanf(file, "%d", &value); // Считываем значение

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->left = RestoreTree(file); // Рекурсивно восстанавливаем левое поддерево
    newNode->right = RestoreTree(file); // Рекурсивно восстанавливаем правое поддерево

    fscanf(file, " %c", &c); // Считываем символ ')'

    return newNode;
}

Node* read_node(FILE* file) {

    int number = 0;
    char current[MAX_LEN] = "";

    Node* node = (Node*)calloc(1, sizeof(Node));

    fscanf(file, "%d", &number);
    node->value = number;

    fscanf(file, "%s", current);
    if (strcmp("(", current) == 0) {

        node->left = read_node(file);
    }

    else if (strcmp("null", current) == 0)
    {
        node->left = 0;
    }

    fscanf(file, "%s", current);
    if (strcmp("(", current) == 0) {
        node->right = read_node(file);
    }

    else if (strcmp("null", current) == 0)
    {
        node->right = 0;
    }


    fscanf(file, "%s", current); //закрывающая скобка

    return node;
}


Node* read_data(FILE* file)
{
    char current[MAX_LEN] = "";

    fscanf(file, "%s", current); //открывающая скобка

    Node* new_node = read_node(file);

    return new_node;
}


