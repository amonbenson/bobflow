#include "bobflow/node.h"
#include <stdlib.h>

static unsigned int node_id = 0;


bf_node_t *bf_node_new(const char *name) {
    bf_node_t *node = malloc(sizeof(bf_node_t));
    if (node == NULL) return NULL;

    node->id = node_id++;
    node->name = name;
    node->next = NULL;

    return node;
}

void bf_node_free(bf_node_t *node) {
    free(node);
}
