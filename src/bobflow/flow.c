#include "bobflow/flow.h"
#include <stdlib.h>
#include <stdio.h>
#include "uthash/utlist.h"


bflow_t *bflow_new(const char *name) {
    bflow_t *bf = malloc(sizeof(bflow_t));
    if (bf == NULL) return NULL;

    bf->name = name;

    return bf;
}

void bflow_free(bflow_t *bf) {
    // remove all nodes
    bf_node_t *node = bf->nodes;
    while (node != NULL) {
        bf_node_t *next = node->next;
        bf_node_free(node);
        node = next;
    }

    free(bf);
}

bf_node_t *bflow_add_node(bflow_t *bf, const char *name, double x, double y) {
    bf_node_t *node = bf_node_new(name);
    if (node == NULL) return NULL;

    node->x = x;
    node->y = y;

    // add node to the list
    LL_PREPEND(bf->nodes, node);

    return node;
}

void bflow_remove_node(bflow_t *bf, bf_node_id_t node_id) {
    bf_node_t *node, *tmp;

    // search and remove node
    LL_FOREACH_SAFE(bf->nodes, node, tmp) {
        if (node->id == node_id) {
            LL_DELETE(bf->nodes, node);
            bf_node_free(node);
            return;
        }
    }
}

void bflow_update(bflow_t *bf, double dt) {
    // TODO: update all constraints

    // update all nodes
    bf_node_t *node;
    LL_FOREACH(bf->nodes, node) {
        bf_node_update(node, dt);
    }
}
