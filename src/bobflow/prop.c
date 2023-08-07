#include "bobflow/prop.h"
#include <stdlib.h>


bf_prop_t *bf_prop_new(const char *name, double value) {
    bf_prop_t *prop = malloc(sizeof(bf_prop_t));
    if (prop == NULL) return NULL;

    prop->name = name;
    prop->value = value;

    prop->deps = NULL;
    prop->num_deps = 0;

    prop->on_compute = bf_event_new();
    prop->on_change = bf_event_new();
    if (prop->on_change == NULL) {
        free(prop);
        return NULL;
    }

    return prop;
}

static int bf_prop_dep_on_changed(void *context, void *data) {
    bf_prop_t *prop = context;
    bf_prop_t *dep = data;

    // recompute the value
    bf_event_emit(prop->on_compute, prop);

    return 0;
}

bf_prop_t *bf_prop_new_computed(const char *name, bf_prop_t **deps, int num_deps, bf_event_handler_cb_t on_compute, void *context) {
    bf_prop_t *prop = bf_prop_new(name, 0);
    if (prop == NULL) return NULL;

    // allocate the dependencies array
    prop->deps = malloc(sizeof(bf_prop_t *) * num_deps);
    if (prop->deps == NULL) {
        bf_prop_free(prop);
        return NULL;
    }

    // add event handlers for all dependencies
    prop->num_deps = num_deps;
    for (int i = 0; i < num_deps; i++) {
        prop->deps[i] = deps[i];
        bf_prop_add_changed_handler(deps[i], on_compute, context);
    }

    return prop;
}

void bf_prop_free(bf_prop_t *prop) {
    // unregister dependencie event handlers
    for (int i = 0; i < prop->num_deps; i++) {
        bf_prop_remove_changed_handler(prop->deps[i], prop->on_compute->handlers);
    }

    // free the dependencies array
    if (prop->num_deps > 0) free(prop->deps);

    // free events
    bf_event_free(prop->on_compute);
    bf_event_free(prop->on_change);

    free(prop);
}

void bf_prop_set_value(bf_prop_t *prop, double value) {
    prop->value = value;
    bf_event_emit(prop->on_change, prop);
}

double bf_prop_get_value(bf_prop_t *prop) {
    return prop->value;
}

void bf_prop_set_name(bf_prop_t *prop, const char *name) {
    prop->name = name;
}

const char *bf_prop_get_name(bf_prop_t *prop) {
    return prop->name;
}

bool bf_prop_is_computed(bf_prop_t *prop) {
    return prop->num_deps > 0;
}

bf_event_handler_t *bf_prop_add_changed_handler(bf_prop_t *prop, bf_event_handler_cb_t callback, void *context) {
    return bf_event_add_handler(prop->on_change, callback, context);
}

void bf_prop_remove_changed_handler(bf_prop_t *prop, bf_event_handler_t *handler) {
    bf_event_remove_handler(prop->on_change, handler);
}
