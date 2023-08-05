#pragma once


typedef struct bf_unit bf_unit_t;
typedef struct bf_unit {
    const char *tag;
    const char *name;
    double scale;

    bf_unit_t *next;
} bf_unit_t;

typedef struct {
    bf_unit_t *unit;
    double value;
} bf_value_t;
