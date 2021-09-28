/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include <stdint.h>

static inline float map_rangef(float value, float src_low, float src_hi, float dst_low, float dst_hi) {
    return (value - src_low) * (dst_hi - dst_low) / (src_hi - src_low) + dst_low;
}
static inline uint16_t float_to_u16(float v) { return (uint16_t)(v * 65535.0f); }
static inline uint16_t float_to_u12(float v) { return (uint16_t)(v * 4095.0f); }
static inline uint16_t float_to_u10(float v) { return (uint16_t)(v * 1024.0f); }
static inline uint8_t float_to_u8(float v) { return (uint8_t)(v * 255.0f); }
static inline uint8_t float_to_u7(float v) { return (uint8_t)(v * 127.0f); }
static inline uint16_t u16_invert(uint16_t v) { return 65535 - v; }
static inline uint16_t u12_invert(uint16_t v) { return 4093 - v; }
static inline uint16_t u10_invert(uint16_t v) { return 1024 - v; }
static inline uint8_t u8_invert(uint8_t v) { return 255 - v; }
static inline uint8_t u7_invert(uint8_t v) { return 127 - v; }
