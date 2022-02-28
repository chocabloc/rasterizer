#include "geometry.h"
#include <math.h>

void geom_update_transform(mesh_t* m)
{
    geom_transform_t* t = &(m->transform);

    for (size_t i = 0; i < m->data.num_verts; i++) {
        vec3_t in = m->data.verts[i];

        // apply scaling
        in.x *= t->scale.x;
        in.y *= t->scale.y;
        in.z *= t->scale.z;

        // apply rotation, first about x axis
        vec3_t out = in;
        out.y = in.y * cosf(t->rot.x) + in.z * sinf(t->rot.x);
        out.z = in.z * cosf(t->rot.x) - in.y * sinf(t->rot.x);
        in = out;

        // then about y axis
        out.z = in.z * cosf(t->rot.y) + in.x * sinf(t->rot.y);
        out.x = in.x * cosf(t->rot.y) - in.z * sinf(t->rot.y);
        in = out;

        // then about z axis
        out.y = in.y * cosf(t->rot.z) + in.x * sinf(t->rot.z);
        out.x = in.x * cosf(t->rot.z) - in.y * sinf(t->rot.z);

        // finally, apply translation
        out.x += t->pos.x;
        out.y += t->pos.y;
        out.z += t->pos.z;

        // store transformed vertex
        m->data._t_verts[i] = out;
    }
}