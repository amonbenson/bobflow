#include "bobflow/node.h"
#include <stdlib.h>
#include <stdio.h>


bf_node_t *bf_node_new(const char *name) {
    bf_node_t *node = malloc(sizeof(bf_node_t));
    if (node == NULL) return NULL;

    node->name = name;

    node->x = 0.0;
    node->y = 0.0;

    node->next = NULL;

    return node;
}

void bf_node_free(bf_node_t *node) {
    free(node);
}

void bf_node_update(bf_node_t *node, double dt) {
    // apply all forces (assume mass = 1, therefore velocity = force)
    node->x += node->fx * dt;
    node->y += node->fy * dt;

    // reset forces
    node->fx = 0.0;
    node->fy = 0.0;
}

void bf_node_apply_force(bf_node_t *node, double fx, double fy) {
    // apply force
    node->fx += fx;
    node->fy += fy;
}
