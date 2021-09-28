#include "generated_flow.h"
void generated_flow_init(struct CurrentsFlow* flow, struct FlowNodeState* states) {
    /* midi_in */
    flow->nodes[0] = (struct CurrentsNode){
        .id = 0,
        .fn = midi_in_fn,
        .link_offsets = {
            0,
            0,
            0,
            0,
        }};

    states[0].midi_in.channel = 1;

    /* pitch_cv */
    flow->nodes[1] = (struct CurrentsNode){
        .id = 1,
        .fn = midi_to_cv_fn,
        .link_offsets = {
            3,
            4,
            0,
            0,
        }};

    /* out1 */
    flow->nodes[2] = (struct CurrentsNode){
        .id = 2,
        .fn = output_one_fn,
        .link_offsets = {
            0,
            0,
            0,
            0,
        }};

    /* gate */
    flow->nodes[3] = (struct CurrentsNode){
        .id = 3,
        .fn = midi_to_gate_fn,
        .link_offsets = {
            5,
            0,
            0,
            0,
        }};

    /* out2 */
    flow->nodes[4] = (struct CurrentsNode){
        .id = 4,
        .fn = output_two_fn,
        .link_offsets = {
            0,
            0,
            0,
            0,
        }};

    /* velocity_scaler */
    flow->nodes[5] = (struct CurrentsNode){
        .id = 5,
        .fn = multiply_fn,
        .link_offsets = {
            6,
            0,
            0,
            0,
        }};

    states[5].multiply.by = 8.0;

    /* out3 */
    flow->nodes[6] = (struct CurrentsNode){
        .id = 6,
        .fn = output_three_fn,
        .link_offsets = {
            0,
            0,
            0,
            0,
        }};

    /* mod_wheel */
    flow->nodes[7] = (struct CurrentsNode){
        .id = 7,
        .fn = midi_cc_fn,
        .link_offsets = {
            7,
            0,
            0,
            0,
        }};

    states[7].midi_cc.number = 1;

    /* mod_wheel_scaler */
    flow->nodes[8] = (struct CurrentsNode){
        .id = 8,
        .fn = multiply_fn,
        .link_offsets = {
            8,
            0,
            0,
            0,
        }};

    states[8].multiply.by = 8.0;

    /* out4 */
    flow->nodes[9] = (struct CurrentsNode){
        .id = 9,
        .fn = output_four_fn,
        .link_offsets = {
            0,
            0,
            0,
            0,
        }};

    /* in1 */
    flow->nodes[10] = (struct CurrentsNode){
        .id = 10,
        .fn = input_a_fn,
        .link_offsets = {
            9,
            0,
            0,
            0,
        }};

    /* in1_inverter */
    flow->nodes[11] = (struct CurrentsNode){
        .id = 11,
        .fn = multiply_fn,
        .link_offsets = {
            10,
            0,
            0,
            0,
        }};

    states[11].multiply.by = -1.0;

    /* outd */
    flow->nodes[12] = (struct CurrentsNode){
        .id = 12,
        .fn = output_delta_fn,
        .link_offsets = {
            0,
            0,
            0,
            0,
        }};

    flow->links[0] = (struct CurrentsLink){.src_id = 0, .src_port = 0, .dst_id = 1, .dst_port = 0};
    flow->links[1] = (struct CurrentsLink){.src_id = 0, .src_port = 0, .dst_id = 3, .dst_port = 0};
    flow->links[2] = (struct CurrentsLink){.src_id = 0, .src_port = 0, .dst_id = 7, .dst_port = 0};
    flow->links[3] = (struct CurrentsLink){.src_id = 1, .src_port = 0, .dst_id = 2, .dst_port = 0};
    flow->links[4] = (struct CurrentsLink){.src_id = 1, .src_port = 1, .dst_id = 5, .dst_port = 0};
    flow->links[5] = (struct CurrentsLink){.src_id = 3, .src_port = 0, .dst_id = 4, .dst_port = 0};
    flow->links[6] = (struct CurrentsLink){.src_id = 5, .src_port = 0, .dst_id = 6, .dst_port = 0};
    flow->links[7] = (struct CurrentsLink){.src_id = 7, .src_port = 0, .dst_id = 8, .dst_port = 0};
    flow->links[8] = (struct CurrentsLink){.src_id = 8, .src_port = 0, .dst_id = 9, .dst_port = 0};
    flow->links[9] = (struct CurrentsLink){.src_id = 10, .src_port = 0, .dst_id = 11, .dst_port = 0};
    flow->links[10] = (struct CurrentsLink){.src_id = 11, .src_port = 0, .dst_id = 12, .dst_port = 0};
}
