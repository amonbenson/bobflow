#pragma once


typedef int (*bf_event_handler_cb_t)(void *context, void *data);


typedef struct bf_event_handler_t bf_event_handler_t;
typedef struct bf_event_handler_t {
    bf_event_handler_cb_t callback;
    void *context;

    bf_event_handler_t *next;
} bf_event_handler_t;

typedef struct {
    bf_event_handler_t *handlers;
} bf_event_t;


bf_event_t *bf_event_new();
void bf_event_free(bf_event_t *event);

bf_event_handler_t *bf_event_add_handler(bf_event_t *event, bf_event_handler_cb_t callback, void *context);
void bf_event_remove_handler(bf_event_t *event, bf_event_handler_t *handler);

int bf_event_emit(bf_event_t *event, void *data);
