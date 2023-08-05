#pragma once

#include "bobflow/node.h"


typedef struct {
    const char *name;
    bf_node_t *nodes;
} bflow_t;

bflow_t *bflow_new(const char *name);
void bflow_free(bflow_t *bf);

void bflow_print(bflow_t *bf);

bf_node_t *bflow_add_node(bflow_t *bf, const char *name);
void bflow_remove_node(bflow_t *bf, bf_node_id_t node_id);
