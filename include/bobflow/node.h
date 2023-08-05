#pragma once


typedef unsigned int bf_node_id_t;

typedef struct bf_node bf_node_t;
typedef struct bf_node {
    bf_node_id_t id;
    const char *name;

    bf_node_t *next;
} bf_node_t;

bf_node_t *bf_node_new(const char *name);
void bf_node_free(bf_node_t *node);
