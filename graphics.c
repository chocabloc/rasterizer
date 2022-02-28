#include "graphics.h"
#include "camera.h"
#include "geometry.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>

static void drawline(vec3_t a, vec3_t b)
{
    scr_line((vec2_t){ a.x, a.y } , (vec2_t){ b.x, b.y });
}

static void drawpoint(vec3_t v)
{
    scr_point((vec2_t){ v.x, v.y });
}

void gfx_drawmesh(camera_t* cam, mesh_t* mesh)
{
    geom_update_transform(mesh);
    cam_update_projection(mesh, cam);

    int* inds = mesh->data.inds;
    vec3_t* verts = mesh->data._t_verts;
    switch (mesh->drawtype) {
        case DRAW_WIREFRAME: {
            for (size_t i = 0; i < mesh->data.num_inds; i += 3) {
                int i1 = inds[i], i2 = inds[i + 1], i3 = inds[i + 2];

                // skip triangles which are wholly or partially behind camera
                // TODO: clip them instead
                if (verts[i1].z < 0 || verts[i2].z < 0 || verts[i3].z < 0)
                    continue;
                    
                drawline(verts[i1], verts[i2]);
                drawline(verts[i2], verts[i3]);
                drawline(verts[i3], verts[i1]);
            }
        } break;

        case DRAW_VERTICES: {
            for (size_t i = 0; i < mesh->data.num_verts; i++)
                drawpoint(verts[i]);
        } break;

        case DRAW_FILLED: {
            printf("error: DRAW_FILLED not implemented\n");
            exit(-1);
        } break;

        default: {
            printf("invalid draw type: %d\n", mesh->drawtype);
            exit(-1);
        }
    }
}