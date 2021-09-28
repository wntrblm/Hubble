/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "currents.h"

void CurrentsFlow_init(struct CurrentsFlow* flow) {
    flow->event_queue.capacity = flow->events_capacity;
    flow->event_queue.item_size = sizeof(struct CurrentsEvent);
    flow->event_queue.data = (uint8_t*)flow->events;
    WntrDeque_init(&flow->event_queue);
}

void CurrentsFlow_send(
    struct CurrentsFlow* flow, const struct CurrentsNode* src, const uint8_t port, struct CurrentsMessage data) {
    struct CurrentsEvent e = {
        .valid = true, .src_id = src->id, .src_port = port, .link_offset = src->link_offsets[port], .data = data};
    WntrDeque_push(&flow->event_queue, (uint8_t*)&e);
}

void CurrentsFlow_start(struct CurrentsFlow* flow) {
    for (uint8_t i = 0; i < flow->nodes_capacity; i++) {
        struct CurrentsNode* node = &flow->nodes[i];
        if (node->id != i) {
            break;
        }

        if (node->on_start) {
            node->fn(flow, node, 0, CURRENTS_MESSAGE_EMPTY);
        }
    }
}

static void CurrentsFlow_step_nodes(struct CurrentsFlow* flow) {
    for (uint8_t i = 0; i < flow->nodes_capacity; i++) {
        struct CurrentsNode* node = &flow->nodes[i];
        if (node->id != i) {
            break;
        }

        if (node->on_step) {
            node->fn(flow, node, 0, CURRENTS_MESSAGE_EMPTY);
        }
    }
}

void CurrentsFlow_step(struct CurrentsFlow* flow) {
    CurrentsFlow_step_nodes(flow);

    while (!WntrDeque_is_empty(&flow->event_queue)) {
        struct CurrentsEvent event;
        WntrDeque_pop(&flow->event_queue, (uint8_t*)&event);

        size_t link_idx = event.link_offset;
        while (true) {
            const struct CurrentsLink link = flow->links[link_idx];
            if (link.src_id != event.src_id || link.src_port != event.src_port) {
                break;
            }

            struct CurrentsNode* dst = &flow->nodes[link.dst_id];
            dst->fn(flow, dst, link.dst_port, event.data);

            link_idx++;
        }
    }
}
