#include "camera.h"
#include "geometry.h"

void cam_update_projection(mesh_t* m, camera_t* cam)
{
    for (size_t i = 0; i < m->data.num_verts; i++) {
        vec3_t p = m->data._t_verts[i];

        // translate the point according to camera position
        p.x -= cam->pos.x;
        p.y -= cam->pos.y;
        p.z -= cam->pos.z;

        // TODO: rotate the point according to camera rotation

        // calculate ray intersection with camera plane
        p.x = (cam->depth * p.x) / (cam->depth + p.z);
        p.y = (cam->depth * p.y) / (cam->depth + p.z);

        m->data._t_verts[i] = p;
    }
}