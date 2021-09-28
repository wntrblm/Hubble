/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/*
    Currents is a flow-based programming engine.

    A "flow" consists of multiple "nodes" connected by "links". Nodes can
    send and receive "messages" through one "ports". A link connects a single
    port on one node to a port on another node.

    Currents is *really* low-level!! It does *not* manage its own storage!
*/

#include "wntr_deque.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct CurrentsFlow;
struct CurrentsNode;

struct CurrentsMessage {
    /* TODO: make this a **tagged** union */
    union {
        float f;
        uint32_t u32;
        int32_t i32;
        bool b;
        void* v;
    };
};

#define CURRENTS_MESSAGE_EMPTY ((struct CurrentsMessage){})
#define CURRENTS_SEND(port, data) CurrentsFlow_send(f, node, port, (struct CurrentsMessage)data);
#define CURRENTS_SEND_EMPTY(port) CurrentsFlow_send(f, node, port, CURRENTS_MESSAGE_EMPTY);

typedef void (*currents_node_fn)(
    struct CurrentsFlow* f, struct CurrentsNode* node, uint8_t port, struct CurrentsMessage data);

#define CURRENTS_NODE_FN(name)                                                                                         \
    void name##_fn(struct CurrentsFlow* f, struct CurrentsNode* node, uint8_t port, struct CurrentsMessage data)

struct CurrentsNode {
    uint8_t id;
    currents_node_fn fn;
    bool on_start;
    bool on_step;
    size_t link_offsets[4];
};

struct CurrentsLink {
    uint8_t src_id;
    uint8_t src_port;
    uint8_t dst_id;
    uint8_t dst_port;
};

struct CurrentsEvent {
    bool valid;
    uint8_t src_id;
    uint8_t src_port;
    size_t link_offset;
    struct CurrentsMessage data;
};

struct CurrentsFlow {
    struct CurrentsNode* nodes;
    size_t nodes_capacity;
    struct CurrentsLink* links;
    size_t links_capacity;
    struct CurrentsEvent* events;
    size_t events_capacity;
    struct WntrDeque event_queue;
};

void CurrentsFlow_init(struct CurrentsFlow* flow);

void CurrentsFlow_send(
    struct CurrentsFlow* flow, const struct CurrentsNode* src, const uint8_t port, struct CurrentsMessage data);

void CurrentsFlow_start(struct CurrentsFlow* flow);

void CurrentsFlow_step(struct CurrentsFlow* flow);
