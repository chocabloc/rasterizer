#pragma once
#include "vector.h"
#include "geometry.h"

// a simple perspective camera
typedef struct {
    vec3_t pos;
    vec3_t rot;
    float depth;
} camera_t;

void cam_update_projection(mesh_t* m, camera_t* cam);