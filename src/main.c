#include <stdio.h>
#include "bobflow/flow.h"


int main(int argc, char *argv[]) {
    (void)(argc);
    (void)(argv);

    bf_flow_t *bf = bflow_new();

    printf("Hello World!\n");

    bflow_free(bf);
    return 0;
}
