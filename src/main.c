#include <stdio.h>
#include "bobflow/flow.h"


int main(int argc, char *argv[]) {
    (void)(argc);
    (void)(argv);

    bf_flow_t *bf = bflow_new("test");

    bflow_add_node(bf, "node1");
    bflow_print(bf);

    bflow_free(bf);
    return 0;
}
