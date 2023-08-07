#include "bobflow/constraint.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define LERP(a, b, t) ((a) + ((b) - (a)) * (t))


bf_constraint_t *bf_constraint_new(bf_node_t *node_a, bf_node_t *node_b, double weight, bf_constraint_update_cb_t update_cb, bf_constraint_free_cb_t free_cb) {
    bf_constraint_t *constraint = malloc(sizeof(bf_constraint_t));
    if (constraint == NULL) return NULL;

    constraint->node_a = node_a;
    constraint->node_b = node_b;
    constraint->weight = weight;

    constraint->next = NULL;

    constraint->update_cb = update_cb;
    constraint->free_cb = free_cb;

    return constraint;
}

void bf_constraint_free(bf_constraint_t *constraint) {
    // invoke the free callback
    constraint->free_cb(constraint);
}


void bf_constraint_update(bf_constraint_t *constraint, double dt) {
    // run the update callback
    bf_constraint_result_t result = constraint->update_cb(constraint);

    // apply the weighted forces
    double w = (1 - exp(-dt * constraint->weight));
    bf_node_apply_force(constraint->node_a, -result.dx / 2.0 * w, -result.dy / 2.0 * w);
    bf_node_apply_force(constraint->node_b, result.dx / 2.0 * w, result.dy / 2.0 * w);
}


static bf_constraint_result_t _bf_distance_constraint_update_cb(bf_constraint_t *constraint) {
    bf_distance_constraint_t *distance_constraint = (bf_distance_constraint_t *) constraint;

    double actual_dx = constraint->node_b->x - constraint->node_a->x;
    double actual_dy = constraint->node_b->y - constraint->node_a->y;
    double actual_d = hypot(actual_dx, actual_dy);

    double desired_d = distance_constraint->distance;
    double desired_dx = actual_dx / actual_d * desired_d;
    double desired_dy = actual_dy / actual_d * desired_d;

    // return the difference between the desired and actual relative positions
    return (bf_constraint_result_t) {
        .dx = desired_dx - actual_dx,
        .dy = desired_dy - actual_dy
    };
}

static void _bf_distance_constraint_free_cb(bf_constraint_t *constraint) {
    free(constraint);
}

bf_distance_constraint_t *bf_distance_constraint_new(bf_node_t *node_a, bf_node_t *node_b, double weight, double distance) {
    bf_distance_constraint_t *constraint = (bf_distance_constraint_t *) bf_constraint_new(node_a, node_b, weight, _bf_distance_constraint_update_cb, _bf_distance_constraint_free_cb);
    if (constraint == NULL) return NULL;

    constraint->distance = distance;

    return constraint;
}
