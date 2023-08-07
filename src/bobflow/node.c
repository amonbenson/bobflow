#include "bobflow/node.h"
#include <stdlib.h>
#include <stdio.h>

static unsigned int node_id = 0;


bf_node_t *bf_node_new(const char *name) {
    bf_node_t *node = malloc(sizeof(bf_node_t));
    if (node == NULL) return NULL;

    node->id = node_id++;
    node->name = name;
    node->x = bf_prop_new(0.0);
    node->y = bf_prop_new(0.0);
    node->next = NULL;

    return node;
}

void bf_node_free(bf_node_t *node) {
    bf_prop_free(node->x);
    bf_prop_free(node->y);
    free(node);
}

void bf_node_print(bf_node_t *node) {
    printf("node \"%s\" at (%.3f, %.3f)\n", node->name, bf_prop_get_value(node->x), bf_prop_get_value(node->y));
}
