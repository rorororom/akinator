#ifndef STACK_H
#define STACK_H

typedef int Elem_t;
typedef int Canary_t;

const int SIZE = 10;
const int CAPACITY = SIZE + 5;
const int HASH_CONST = 234;
const int XOR_CONST = 3;
const int MOD_FOR_HASH = 107;
const Elem_t POISONELEMENT = -1;
const int DOP_RIGHT = 1;
const int DOP_LEFT = 1;
const int UP_KOEF = 2;
const float DOWN_KOEF = 0.5;

const Canary_t BUF_CANARY =  0xDEDEEDED;

#define LINE __LINE__
#define FILEF __FILE__

#define STACK_DUMP(myStack) StackDump (myStack, FILEF, LINE, __func__);

#define STACK_VERIFY(myStack) {         \
    if (StackVerify (myStack) > 0) {    \
        STACK_DUMP (myStack);           \
    }                                   \
}

struct Stack{
    Elem_t* data;
    int capacity;
    int size;
};

enum StackErrors {
    ERROR_SIZE_BIT          = 1,
    ERROR_CAPACITY_BIT      = 1 << 2,
    ERROR_DATA_BIT          = 1 << 3,
    ERROR_PUSH_BIT          = 1 << 4,
    ERROR_HASH_BIT          = 1 << 5,
    ERROR_CANARY_START_BIT  = 1 << 6,
    ERROR_CANARY_END_BIT    = 1 << 7,
    ERROR_DATA_END_BIT      = 1 << 8,
    ERROR_DATA_START_BIT    = 1 << 9
};

//
//! @brief creator of all data on the stack
//! @param [in] myStack all structure data
//!
//!
//! sets initial parameters for the structure and allocates memory for the initial stack size
void StackCtor (struct Stack* myStack);

//
//! @brief destroys all stack data
//! @param [in] myStack all structure data
//!
//!
//! resets all data and stack pointers
void StackDtor (struct Stack* myStack);

//
//! @brief adding elements to the stack
//! @param [in] myStack all structure data
//!
//!
//! adds elements to the stack and increases the stack size
void StackPush (struct Stack* myStack, Elem_t value);

//
//! @brief deletes elements to the stack
//! @param [in]  myStack all structure data
//! @param [out] ans stack element that is removed and returned
//!
//!
//! returns and removes elements from the stack
Elem_t StackPop (struct Stack* myStack);

//
//! @brief prints all stack data
//! @param [in]  myStack all structure data
//! @param [in]  file the file from which it was called
//! @param [in]  line the line from which it was called
//! @param [in]  function the function from which it was called
//!
//!
//! makes a complete printout of the stack and its data
void StackDump (struct Stack* myStack, const char *file, int line, const char *function);

int GetSizeStack (struct Stack* myStack);

Elem_t StackTop(const struct Stack* myStack);

#endif

