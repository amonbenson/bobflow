#include "bobflow/prop.h"
#include <stdlib.h>


bf_prop_t *bf_prop_new(double value) {
    bf_prop_t *prop = malloc(sizeof(bf_prop_t));
    if (prop == NULL) return NULL;

    prop->value = value;
    prop->on_change = bf_event_new();
    if (prop->on_change == NULL) {
        free(prop);
        return NULL;
    }

    return prop;
}

void bf_prop_free(bf_prop_t *prop) {
    bf_event_free(prop->on_change);
    free(prop);
}

void bf_prop_set(bf_prop_t *prop, double value) {
    prop->value = value;
    bf_event_emit(prop->on_change, prop);
}

double bf_prop_get(bf_prop_t *prop) {
    return prop->value;
}
