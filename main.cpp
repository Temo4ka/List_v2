#include "list.h"
#include <stdlib.h>

int main (int argc, const char* argv[]) {
    int  n  = 0;
    int cmd = 0;
    int pos = 0;
    int val = 0;

    List head = {};
    listCtor(&head);

    // listDump(&list);

    FILE* f = (argc > 1? fopen (argv[1], "r") : stdin);

    fscanf(f, "%d", &n);
    for (size_t i = 0; i < n; i++) {
        fscanf(f, "%d %d", &cmd, &pos);
        if (cmd) {
            fscanf(f, "%d", &val);
            listLogicInsert(&head, pos, val);
        } else {
            listLogicErase(&head, pos);
        }
        //fprintf(stderr, "--- %d ---\n", list.prev[list.head]);
        // fprintf(logStream, "Command number %zu\n", i);
        listPrint(&(head.list));
    }

    if (f != stdin) fclose (f);

    return EXIT_SUCCESS;
}
