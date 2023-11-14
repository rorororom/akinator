#ifndef AKINATOR_H
#define AKINATOR_H

#include "stack.h"

const int MAX_LEN = 100;

struct NodeAkinator {
    char value[MAX_LEN];
    NodeAkinator* left;
    NodeAkinator* right;
};


struct TreeAkinator {
    NodeAkinator* RootTree;
    int size;
};

enum Register
{
    INCORECT = -1,
    AKINATOR,
    DELETE,
    DEFENITION,
    COMPARISON,
    SAVE,
    EXIT,
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CHECKING_OBJECT(cnt, request) if (cnt == 0) printf("Такого объекта нет: %s\n", request)

#define PRINT_COMMAND()                                 \
    printf("Команды(английскими буквами):\n"            \
            "\t[a] - игра Акинатор,\n"                  \
            "\t[d] - удаление базы данных,\n"           \
            "\t[b] - построение определения объекта\n"  \
            "\t[c] - сравнение объектов\n"              \
            "\t[s] - сохранить изменения\n"             \
            "\t[e] - выйти из программы\n")

void Akinator(NodeAkinator** nowNode);
void PrintNodeAkinarot(NodeAkinator* node, FILE* file);
void SaveTreeToFile(NodeAkinator* root);

void PrintNodeAkinarotConsol(NodeAkinator* node);
void PrintNodeDump(FILE* dotFile, NodeAkinator* node, const char* fillColor);
void GenerateImage(TreeAkinator* tree);

NodeAkinator* buildTree(FILE* file);

int CheckCommand(char c);

void ObjectDefinition(TreeAkinator* tree);

void CtorInDelete(TreeAkinator* tree);
void DestroyNode(NodeAkinator* node);
void TreeDtor(TreeAkinator* tree);

int SearchingItemCharacteristics(Stack* myStack, NodeAkinator* node, const char* value);

void CompareObjects(TreeAkinator* tree);
void ProcessCompareSign(Stack* myStackComparison, Stack* myStackComp,
                        Stack* myStackComp2, NodeAkinator** nowNode);

void DistinctiveFeatureSubject(Stack* myStackComparison, Stack* myStackComp, NodeAkinator* nowNode,
                               const char request[], const char* conjunction);
void ReadObject(char request[]);
void ReadObjectUntilValid(char request[], TreeAkinator* tree, Stack* myStack);

void CreateNewGraph();
#endif
