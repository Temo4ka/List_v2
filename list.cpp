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


int listElemCtor(List *list, Elem_t val) {
    catchNullptr(list);

    list -> prev = list;
    list -> next = list;

    list -> data = val;

    return ListIsOk;
}

int listDtor(List *list) {
    catchNullptr(list);
    
    free(list);

    return ListIsOk;

}

List *listLogicInsert(List *listHead, size_t ind, Elem_t val) {
    if (listHead == nullptr) return nullptr;

    List *prevPos = listGetPos(listHead, ind);
    if (prevPos == nullptr) return nullptr;
    
    List *newPos = (List *) calloc(1, sizeof(List)); 
    if (listElemCtor(newPos, val)) return nullptr; 
    
    newPos -> next = prevPos -> next;
    newPos -> prev =     prevPos    ;

    (prevPos -> next) -> prev = newPos;
          prevPos -> next     = newPos;

    return newPos;
}

List *listPushBack(List *listHead, Elem_t val) {
    if (listHead == nullptr) return nullptr;

    List *prevPos = listHead -> prev;
    if (prevPos == nullptr) return nullptr;
    
    List *newPos = (List *) calloc(1, sizeof(List)); 
    if (listElemCtor(newPos, val)) return nullptr; 
    
    newPos -> next = prevPos -> next;
    newPos -> prev =     prevPos    ;

    (prevPos -> next) -> prev = newPos;
          prevPos -> next     = newPos;

    return newPos;
}

List *listPushFront(List *listHead, Elem_t val) {
    if (listHead == nullptr) return nullptr;

    List *prevPos = listHead;
    if (prevPos == nullptr) return nullptr;
    
    List *newPos = (List *) calloc(1, sizeof(List)); 
    if (listElemCtor(newPos, val)) return nullptr; 
    
    newPos -> next = prevPos -> next;
    newPos -> prev =     prevPos    ;

    (prevPos -> next) -> prev = newPos;
          prevPos -> next     = newPos;

    return newPos;
}

int listLogicErase (List *listHead, size_t ind) {
    catchNullptr(listHead);

    if (listHead -> next == listHead) return ListIsEmpty;

    List *curPos = listGetPos(listHead, ind);
    if (curPos == nullptr) return ListWrongIndex;
    
    (curPos -> prev) -> next = curPos -> next;
    (curPos -> next) -> prev = curPos -> prev;

    free(curPos);

    return ListIsOk;
}


List *listGetPos(List *listHead, size_t index) {
    if (listHead == nullptr) return nullptr;

    List *curElem = listHead;
    for (size_t pos = 0; pos < index; ++pos) {
        curElem = curElem -> next;
        if (curElem == listHead)
            return nullptr;
    }

    return curElem;
}

int listPrint(List *listHead, FILE* stream) {
    catchNullptr(listHead);

    fprintf(stream, "FictElem");
    for (List *curElem = listHead -> next; curElem != listHead; curElem = curElem -> next) {
        fprintf(stream, " -> %d", curElem -> data);
    }
    fprintf(stream, "\n");

    return ListIsOk;
}
