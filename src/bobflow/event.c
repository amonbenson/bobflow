#include "bobflow/event.h"
#include <stdlib.h>
#include "uthash/utlist.h"


bf_event_t *bf_event_new() {
    bf_event_t *event = malloc(sizeof(bf_event_t));
    if (event == NULL) return NULL;

    event->handlers = NULL;

    return event;
}

void bf_event_free(bf_event_t *event) {
    // remove all handlers
    bf_event_handler_t *el, *tmp;
    LL_FOREACH_SAFE(event->handlers, el, tmp) {
        bf_event_remove_handler(event, el);
    }

    free(event);
}

bf_event_handler_t *bf_event_add_handler(bf_event_t *event, bf_event_handler_cb_t callback, void *context) {
    bf_event_handler_t *handler = malloc(sizeof(bf_event_handler_t));
    if (handler == NULL) return NULL;

    handler->callback = callback;
    handler->context = context;

    LL_PREPEND(event->handlers, handler);

    return handler;
}

void bf_event_remove_handler(bf_event_t *event, bf_event_handler_t *handler) {
    LL_DELETE(event->handlers, handler);
    free(handler);
}

int bf_event_emit(bf_event_t *event, void *data) {
    bf_event_handler_t *el, *tmp;
    LL_FOREACH_SAFE(event->handlers, el, tmp) {
        int ret = el->callback(el->context, data);
        if (ret != 0) return ret;
    }

    return 0;
}
