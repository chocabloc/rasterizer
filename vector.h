#pragma once

typedef struct {
    float x;
    float y;
} vec2_t;
#define vec2_new(X, Y) ((vec2_t) { .x = (X), .y = (Y) })

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;
#define vec3_new(X, Y, Z) ((vec3_t) { .x = (X), .y = (Y), .z = (Z) })