#pragma once

#include <stdbool.h>
#include "bobflow/event.h"


typedef struct bf_prop_t bf_prop_t;
typedef struct bf_prop_t {
    const char *name;
    double value;

    bf_prop_t **deps;
    int num_deps;

    bf_event_t *on_compute;
    bf_event_t *on_change;
} bf_prop_t;


bf_prop_t *bf_prop_new(const char *name, double value);
bf_prop_t *bf_prop_new_computed(const char *name, bf_prop_t **deps, int num_deps, bf_event_handler_cb_t on_compute, void *context);
void bf_prop_free(bf_prop_t *prop);

void bf_prop_set_value(bf_prop_t *prop, double value);
double bf_prop_get_value(bf_prop_t *prop);

void bf_prop_set_name(bf_prop_t *prop, const char *name);
const char *bf_prop_get_name(bf_prop_t *prop);

bool bf_prop_is_computed(bf_prop_t *prop);

bf_event_handler_t *bf_prop_add_changed_handler(bf_prop_t *prop, bf_event_handler_cb_t callback, void *context);
void bf_prop_remove_changed_handler(bf_prop_t *prop, bf_event_handler_t *handler);
