#include "bobflow/flow.h"
#include <stdlib.h>


bf_flow_t *bflow_new(void) {
    bf_flow_t *bf = malloc(sizeof(bf_flow_t));
    if (bf == NULL) return NULL;

    return bf;
}

void bflow_free(bf_flow_t *bf) {
    free(bf);
}

bf_node_t *bflow_add_node(bf_flow_t *bf, const char *name) {
    bf_node_t *node = bf_node_new(name);
    if (node == NULL) return NULL;

    node->next = bf->nodes;
    bf->nodes = node;

    return node;
}

void bflow_remove_node(bf_flow_t *bf, bf_node_id_t node_id) {
    bf_node_t *node = bf->nodes;
    bf_node_t *prev = NULL;

    while (node != NULL) {
        if (node->id == node_id) {
            if (prev == NULL) {
                bf->nodes = node->next;
            } else {
                prev->next = node->next;
            }

            bf_node_free(node);
            return;
        }

        prev = node;
        node = node->next;
    }
}
