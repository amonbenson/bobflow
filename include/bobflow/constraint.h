#pragma once

#include "bobflow/node.h"


#define BF_CONSTRAINT_WEIGHT_LIGHT 0.01
#define BF_CONSTRAINT_WEIGHT_DEFAULT 0.1
#define BF_CONSTRAINT_WEIGHT_HEAVY 1.0


typedef struct {
    double dx;
    double dy;
} bf_constraint_result_t;

typedef struct bf_constraint_t bf_constraint_t;
typedef bf_constraint_result_t (*bf_constraint_update_cb_t)(bf_constraint_t *constraint);
typedef void (*bf_constraint_free_cb_t)(bf_constraint_t *constraint);

typedef struct bf_constraint_t {
    bf_node_t *node_a;
    bf_node_t *node_b;
    double weight;

    bf_constraint_t *next;

    bf_constraint_update_cb_t update_cb;
    bf_constraint_free_cb_t free_cb;
} bf_constraint_t;

typedef struct {
    bf_constraint_t constraint;
    double distance;
} bf_distance_constraint_t;


bf_constraint_t *bf_constraint_new(bf_node_t *node_a, bf_node_t *node_b, double weight, bf_constraint_update_cb_t update_cb, bf_constraint_free_cb_t free_cb);
void bf_constraint_free(bf_constraint_t *constraint);

void bf_constraint_update(bf_constraint_t *constraint, double dt);


bf_distance_constraint_t *bf_distance_constraint_new(bf_node_t *node_a, bf_node_t *node_b, double weight, double distance);
