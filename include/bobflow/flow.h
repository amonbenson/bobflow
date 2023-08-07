#pragma once

#include "bobflow/node.h"
#include "bobflow/constraint.h"


typedef struct {
    const char *name;
    bf_node_t *nodes;
    bf_constraint_t *constraints;
} bflow_t;

bflow_t *bflow_new(const char *name);
void bflow_free(bflow_t *bf);

bf_node_t *bflow_add_node(bflow_t *bf, const char *name, double x, double y);
void bflow_remove_node(bflow_t *bf, bf_node_t *node);

bf_constraint_t *bflow_add_distance_constraint(bflow_t *bf, bf_node_t *node_a, bf_node_t *node_b, double weight, double distance);
void bflow_remove_constraint(bflow_t *bf, bf_constraint_t *constraint);

void bflow_update(bflow_t *bf, double dt);
