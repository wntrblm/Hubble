/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/* Helpers for making sysex commands */

#include "teeth.h"
#include "wntr_assert.h"
#include "wntr_pack.h"
#include "wntr_serial_number.h"

#define _SYSEX_ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

#define SYSEX_COMMAND_FUNC_NAME(number, name) sysex_command_##number##_##name
#define SYSEX_COMMAND_DECL(number, name)                                                                               \
    static void SYSEX_COMMAND_FUNC_NAME(number, name)(const uint8_t* request_data, size_t request_len)
#define REGISTER_SYSEX_COMMAND(number, name)                                                                           \
    wntr_midi_register_sysex_command(number, SYSEX_COMMAND_FUNC_NAME(number, name));

#define SYSEX_DECODE_TEETH_REQUEST(size)                                                                               \
    WNTR_ASSERT(request_len == TEETH_ENCODED_LENGTH(size));                                                            \
    uint8_t request[size];                                                                                             \
    teeth_decode(request_data, TEETH_ENCODED_LENGTH(size), request);

#define SYSEX_RESPONSE_NULLARY(command) wntr_midi_send_sysex((uint8_t[2]){WNTR_MIDI_SYSEX_IDENTIFIER, command}, 2);
#define SYSEX_RESPONSE_UNARY(command, val1)                                                                            \
    wntr_midi_send_sysex((uint8_t[3]){WNTR_MIDI_SYSEX_IDENTIFIER, command, val1}, 3);

#define SYSEX_PREPARE_RESPONSE(command, size)                                                                          \
    uint8_t _full_response[2 + size];                                                                                  \
    uint8_t* response = _full_response + 2;                                                                            \
    const size_t response_len __attribute__((unused)) = size;                                                          \
    _full_response[0] = WNTR_MIDI_SYSEX_IDENTIFIER;                                                                    \
    _full_response[1] = command;

#define SYSEX_SEND_RESPONSE() wntr_midi_send_sysex(_full_response, _SYSEX_ARRAY_LEN(_full_response));
