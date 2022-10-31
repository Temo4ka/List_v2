#include "list.h"
#include <cstdlib>
#include <cstdarg>

//TODO: new List with struct

#define TAIL list -> prev[0]
#define HEAD list -> next[0]

const size_t   DUMP_SIZE  = 20;
const size_t   FictElem   =  0;
const size_t   DataFree   = -1;
const size_t MAX_CMD_SIZE = 40;

static FILE *LogGraph = fopen("logs/HtmlLog.html", "w");
static FILE *LogFile  = LogGraph;


int listCtor(List *head) {
    catchNullptr(head);

    (head -> list).next = &(head -> list);
    (head -> list).prev = &(head -> list);

    head -> size = 0;

    return ListIsOk;
}

int listElemCtor(ListElem *elem, ListElem *prev, ListElem *next, Elem_t val) {
    catchNullptr(elem);

    elem -> next = next;
    elem -> prev = prev;
    elem -> data = val ;

    return ListIsOk;
}

int listElemDtor(ListElem *list) {
    catchNullptr(list);
    
    free(list);

    return ListIsOk;

}

ListElem *listLogicInsert(List *head, size_t ind, Elem_t val) {
    if (head == nullptr) return nullptr;

    ListElem *prevPos = listGetPos(&(head -> list), ind);
    if (prevPos == nullptr) return nullptr;
    
    ListElem *newPos = (ListElem *) calloc(1, sizeof(ListElem));  
    if (listElemCtor(newPos, prevPos, prevPos -> next, val)) return nullptr;

    (prevPos -> next) -> prev = newPos;
          prevPos -> next     = newPos;

    head -> size++;

    return newPos;
}

ListElem *listPushBack(List *head, Elem_t val) {
    if (head == nullptr) return nullptr;

    ListElem *prevPos = (head -> list).prev;
    if (prevPos == nullptr) return nullptr;
    
    ListElem *newPos = (ListElem *) calloc(1, sizeof(ListElem));  
    if (listElemCtor(newPos, prevPos, prevPos -> next, val)) return nullptr;

    (prevPos -> next) -> prev = newPos;
          prevPos -> next     = newPos;

    head -> size++;

    return newPos;
}

ListElem *listPushFront(List *head, Elem_t val) {
    if (head == nullptr) return nullptr;

    ListElem *prevPos = &(head -> list);
    if (prevPos == nullptr) return nullptr;
    
    ListElem *newPos = (ListElem *) calloc(1, sizeof(ListElem));  
    if (listElemCtor(newPos, prevPos, prevPos -> next, val)) return nullptr;

    (prevPos -> next) -> prev = newPos;
          prevPos -> next     = newPos;

    head -> size++;

    return newPos;
}

int listLogicErase (List *head, size_t ind) {
    catchNullptr(head);

    if (!head -> size) return ListIsEmpty;

    ListElem *curPos = listGetPos(&(head -> list), ind);
    if (curPos == nullptr) return ListWrongIndex;
    
    (curPos -> prev) -> next = curPos -> next;
    (curPos -> next) -> prev = curPos -> prev;

    free(curPos);

    head -> size--;

    return ListIsOk;
}


ListElem *listGetPos(ListElem *listHead, size_t index) {
    if (listHead == nullptr) return nullptr;

    ListElem *curElem = listHead;
    for (size_t pos = 0; pos < index; ++pos) {
        curElem = curElem -> next;
        if (curElem == listHead)
            return nullptr;
    }

    return curElem;
}

int listPrint(ListElem *listHead, FILE* stream) {
    catchNullptr(listHead);

    fprintf(stream, "FictElem");
    for (ListElem *curElem = listHead -> next; curElem != listHead; curElem = curElem -> next) {
        fprintf(stream, " -> %d", curElem -> data);
    }
    fprintf(stream, "\n");

    return ListIsOk;
}
