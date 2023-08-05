#pragma once

#include "bobflow/event.h"


typedef struct {
    double value;
    bf_event_t *on_change;
} bf_prop_t;


bf_prop_t *bf_prop_new(double value);
void bf_prop_free(bf_prop_t *prop);

void bf_prop_set(bf_prop_t *prop, double value);
double bf_prop_get(bf_prop_t *prop);
