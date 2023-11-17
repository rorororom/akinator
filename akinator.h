#ifndef AKINATOR_H
#define AKINATOR_H

#include "stack.h"

const int MAX_OBJECT_NAME_LENGTH = 100;
const int MAX_LEN = 256;

struct NodeAkinator {
    char value[MAX_OBJECT_NAME_LENGTH];
    NodeAkinator* left;
    NodeAkinator* right;
};


struct TreeAkinator {
    NodeAkinator* rootTree;
    int size;
};

enum PrintMode {
    WITHOUT_NEGATION = 0,
    WITH_NEGATION
};

enum AnswerAkinator{
    YES,
    NO,
    ERRROR_ANSWER
};

enum Register{
    INCORRECT = -1,
    AKINATOR,
    DELETE,
    DEFENITION,
    COMPARISON,
    SAVE,
    EXIT,
    PICTURE
};

#define MIN(a, b) a < b ? a : b
#define CHECKING_OBJECT(cnt, request) if (cnt == 0) printf("Такого объекта нет: %s\n", request)
#define CREAT_NODE(node) NodeAkinator* node = (NodeAkinator*)malloc(sizeof(NodeAkinator))

#define AKINATOR_PRINT_STRING(...)                      \
    do{                                                 \
        printf(__VA_ARGS__);                            \
        AkinatorSayString(__VA_ARGS__);                 \
    } while (0)

void RunAkinatorMenuLoop(TreeAkinator* tree);
void BuildTreeFromFile(const char* filename, TreeAkinator* tree);

NodeAkinator* BuildTree(FILE* file);
void TreeDtor(TreeAkinator* tree);
void CtorRoot(TreeAkinator* tree);

void GenerateImage(TreeAkinator* tree);
void GenerateGraphImage();

void AkinatorSayString(const char* format, ...);
#endif

