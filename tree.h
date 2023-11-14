#include <stdio.h>

const int MAX_LEN = 100;
const int DTOR_ELEMENT = -1;

struct Node {
    int value;
    Node* left;
    Node* right;
    int FlagDirection;
};


struct Tree {
    Node* RootTree;
    int size;
};

void NodeAkinatorInit(Node* node, int value, Node* left, Node* right, Tree* tree);
void CtorTreeStruct(Tree* tree);
void AddNewNodeIncreasing(Node* current, int value, Tree* tree);
void RecordingTextDump(Tree* tree);
void PrintNodeDump(FILE* dotFile, Node* node, const char* fillColor);
void GenerateImage(Tree* tree);
struct Node* RestoreTree(FILE* file);
void PrintNode(Node* node, FILE* file);
void PrintNodeConsol(Node* node);
Node* read_node(FILE* file);
Node* read_data(FILE* file);

void DestroyNode(Node* node);
void TreeDtor(Tree* tree);
