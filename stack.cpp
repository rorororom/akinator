#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "log_funcs.h"
#include "stack.h"

#define CAPACITY 1000
#define UP_KOEF 2
#define DOWN_KOEF 0.5

void StackCtor(struct Stack* myStack) {
    myStack->capacity = CAPACITY;
    myStack->size = 0;
    myStack->data = (Elem_t*)calloc(myStack->capacity, sizeof(Elem_t));
    if (myStack->data == NULL) {
        printf("AAAAAA\n");
        fprintf(stderr, "Ошибка выделения памяти для стека\n");
        exit(EXIT_FAILURE);
    }
}

void StackPush(struct Stack* myStack, Elem_t value) {
    if (myStack->size >= myStack->capacity) {
        myStack->capacity *= UP_KOEF;
        myStack->data = (Elem_t*)realloc(myStack->data, sizeof(Elem_t) * myStack->capacity);
    }
    myStack->data[myStack->size++] = value;
}

Elem_t StackPop(struct Stack* myStack) {
    assert(myStack->size > 0);

    Elem_t value = myStack->data[--myStack->size];
    return value;
}

void StackDump (struct Stack* myStack, const char *file, int line, const char *function)
{
    fprintf (LOG_FILE, "\nTime is %s\n", __TIME__);
    fprintf (LOG_FILE, "I'm stackDump called from %s (%d) %s\n", function, line, file);
    fprintf (LOG_FILE, "Stack[%p] \"myStack\" from %s (%d) in function - %s.\n\n", myStack->data, FILEF, LINE, function);

    fprintf (LOG_FILE, "--------------------------------------------------------------------------\n");
    fprintf (LOG_FILE, "Struct:\n");
    fprintf (LOG_FILE, "\tsize = %d\n", myStack->size);
    fprintf (LOG_FILE, "\tcapacity = %d\n", myStack->capacity);
    fprintf (LOG_FILE, "\tадрес data[] = %p\n", myStack->data);

    int now_size = myStack->size;
    for (int i = 0; i < now_size; i++)
    {
        fprintf (LOG_FILE, "\tdata[%d] = %d\n", i, myStack->data[i]);
    }
    fprintf (LOG_FILE, "--------------------------------------------------------------------------\n");
}


void StackDtor(struct Stack* myStack) {
    free(myStack->data);
    myStack->data = NULL;
    myStack->capacity = 0;
    myStack->size = 0;
}

void StackRealloc(struct Stack* myStack, float koef_capacity) {
    if (myStack->size < (myStack->capacity) / DOWN_KOEF) {
        myStack->capacity *= DOWN_KOEF;
        myStack->data = (Elem_t*)realloc(myStack->data, sizeof(Elem_t) * myStack->capacity);
    }
}

int GetSizeStack (struct Stack* myStack)
{
    return myStack->size;
}

Elem_t StackTop(const struct Stack* myStack)
{
    if (myStack->size > 0)
    {
        return myStack->data[myStack->size - 1];
    }
    else
    {
        printf("Стек пуст. Невозможно получить верхний элемент.\n");
        exit(1);
    }
}
