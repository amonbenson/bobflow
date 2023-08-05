#pragma once

#include "bobflow/node.h"


typedef struct {
    const char *name;
    bf_node_t *nodes;
} bf_flow_t;

bf_flow_t *bflow_new(const char *name);
void bflow_free(bf_flow_t *bf);

void bflow_print(bf_flow_t *bf);

bf_node_t *bflow_add_node(bf_flow_t *bf, const char *name);
void bflow_remove_node(bf_flow_t *bf, bf_node_id_t node_id);
