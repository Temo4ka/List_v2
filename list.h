#include "listType.h"
#include <cstdio>
#include <string.h>

const int MAX_LIST_SIZE = 20;

enum ListErrors {
            ListIsOk          =       0,
           ListIsNull         = 1 <<  0,
           ListIsFull         = 1 <<  1, 
           ListIsEmpty        = 1 <<  2,
          ListHeadErase       = 1 <<  3,
          ListDataIsNull      = 1 <<  4,
          ListNextIsNull      = 1 <<  5,
          ListWrongIndex      = 1 <<  6,
          ListPrevIsNull      = 1 <<  7,
          ListIsInActive      = 1 <<  8,
         ListPoisonInData     = 1 <<  9,
         ListFreeBlocksErr    = 1 << 10,
       ListDoubleDestruction  = 1 << 11,
      ListDoubleConstruction  = 1 << 12,
     ListGraphVizExecutionErr = 1 << 13,
};

enum Status {
     Active = 0,
    InActive = 1
};

enum Life {
    Bitter = 0,  
    Sweet  = 1
};

struct List {
    List  *next   = nullptr;
    List  *prev   = nullptr;

    Elem_t data   = POISON ;
};

#define catchNullptr(POINTER) {                                                                                    \
    if ((POINTER) == nullptr) {                                                                                     \
        fprintf(stderr, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __PRETTY_FUNCTION__, __FILE__, __LINE__);  \
        return EXIT_FAILURE;                                                                                          \
    }                                                                                                                  \
}

int listElemCtor(List *list, Elem_t val = POISON);

List *listLogicInsert(List *listHead, size_t ind, Elem_t val);

List *listPushBack(List *listHead, Elem_t val);

List *listPushFront(List *listHead, Elem_t val);

int listLogicErase (List *listHead, size_t ind);

List *listGetPos(List *listHead, size_t index);

int listPrint(List *listHead, FILE* stream = stdout);

int listDtor(List *list);