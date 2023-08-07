#include "bobflow/flow.h"
#include <stdlib.h>
#include <stdio.h>
#include "uthash/utlist.h"


bflow_t *bflow_new(const char *name) {
    bflow_t *bf = malloc(sizeof(bflow_t));
    if (bf == NULL) return NULL;

    bf->name = name;
    bf->nodes = NULL;
    bf->constraints = NULL;

    return bf;
}

void bflow_free(bflow_t *bf) {
    // remove all constraints
    bf_constraint_t *constraint, *tmp;
    LL_FOREACH_SAFE(bf->constraints, constraint, tmp) {
        bf_constraint_free(constraint);
    }

    // remove all nodes
    bf_node_t *node, *tmp2;
    LL_FOREACH_SAFE(bf->nodes, node, tmp2) {
        bf_node_free(node);
    }

    // free the flow itself
    free(bf);
}

bf_node_t *bflow_add_node(bflow_t *bf, const char *name, double x, double y) {
    bf_node_t *node = bf_node_new(name);
    if (node == NULL) return NULL;

    // set node position
    node->x = x;
    node->y = y;

    // add node to the list
    LL_PREPEND(bf->nodes, node);

    return node;
}

void bflow_remove_node(bflow_t *bf, bf_node_t *node) {
    LL_DELETE(bf->nodes, node);
    bf_node_free(node);
}

bf_constraint_t *bflow_add_distance_constraint(bflow_t *bf, bf_node_t *node_a, bf_node_t *node_b, double weight, double distance) {
    bf_constraint_t *constraint = (bf_constraint_t *) bf_distance_constraint_new(node_a, node_b, weight, distance);
    if (constraint == NULL) return NULL;

    LL_PREPEND(bf->constraints, constraint);

    return constraint;
}

void bflow_remove_constraint(bflow_t *bf, bf_constraint_t *constraint) {
    LL_DELETE(bf->constraints, constraint);
    bf_constraint_free(constraint);
}

void bflow_update(bflow_t *bf, double dt) {
    // update all constraints
    bf_constraint_t *constraint;
    LL_FOREACH(bf->constraints, constraint) {
        bf_constraint_update(constraint, dt);
    }

    // update all nodes
    bf_node_t *node;
    LL_FOREACH(bf->nodes, node) {
        bf_node_update(node, dt);
    }
}
