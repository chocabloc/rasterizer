#include "camera.h"
#include "geometry.h"
#include "graphics.h"
#include "window.h"
#include "objfile.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <complex.h>

int main(void)
{
    camera_t camera = (camera_t) {
        .depth = 2,
        .pos = { 0, 0, -5 },
        .rot = { 0, 0, 0 }
    };

    win_init();
    mesh_t* m = obj_mesh_from_file("./test/teapot.obj");
    while(true) {
        win_clear();

        m->transform.rot.y += 0.01;
        gfx_drawmesh(&camera, m);

        win_mainloop();
    }
}
