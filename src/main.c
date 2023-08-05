#include <stdio.h>
#include "bobflow/flow.h"


static int test_cb(void *context, void *data) {
    (void)(context);
    bf_prop_t *x = data;

    printf("cb x = %f\n", bf_prop_get(x));
    return 0;
}

int main(int argc, char *argv[]) {
    (void)(argc);
    (void)(argv);

    bflow_t *bf = bflow_new("test");

    bflow_add_node(bf, "node1");
    bflow_print(bf);

    bf_event_add_handler(bf->nodes->x->on_change, test_cb, NULL);
    bf_prop_set(bf->nodes->x, 1.0);

    bflow_free(bf);
    return 0;
}
