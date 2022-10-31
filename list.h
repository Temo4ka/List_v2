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

struct ListElem {
    ListElem *next = nullptr;
    ListElem *prev = nullptr;

     Elem_t   data = POISON ;
};

struct List {
    ListElem list = {};

     size_t  size =  0;
};

#define catchNullptr(POINTER) {                                                                                    \
    if ((POINTER) == nullptr) {                                                                                     \
        fprintf(stderr, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __PRETTY_FUNCTION__, __FILE__, __LINE__);  \
        return EXIT_FAILURE;                                                                                          \
    }                                                                                                                  \
}

int listCtor(List *head);

int listElemCtor(ListElem *elem, ListElem *prev, ListElem *next, Elem_t val = POISON); 

ListElem *listLogicInsert(List *head, size_t ind, Elem_t val);

ListElem *listPushBack(List *head, Elem_t val);

ListElem *listPushFront(List *head, Elem_t val);

int listLogicErase (List *head, size_t ind);

ListElem *listGetPos(ListElem *listHead, size_t index);

int listPrint(ListElem *listHead, FILE* stream = stdout);

int listElemDtor(ListElem *list);