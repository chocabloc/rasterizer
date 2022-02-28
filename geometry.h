#pragma once

#include "vector.h"
#include <stdint.h>
#include <stddef.h>

// vertex data for a mesh
typedef struct {
    size_t num_verts;
    size_t num_inds;
    vec3_t* verts;
    int* inds;

    // stores vertices after transformation
    vec3_t* _t_verts;
} meshdata_t;

// stores transformation
typedef struct {
    vec3_t pos, rot, scale;
} geom_transform_t;

// 3d mesh composed of triangles
typedef struct {
    // draw method
    enum {
        DRAW_WIREFRAME, // draw a wireframe
        DRAW_VERTICES,  // draw only the vertices
        DRAW_FILLED     // fill the triangles too
    } drawtype;

    // transformation data
    geom_transform_t transform;

    // vertex data
    meshdata_t data;
} mesh_t;

void geom_update_transform(mesh_t* m);
