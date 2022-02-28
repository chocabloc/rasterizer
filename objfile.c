/*
 * Wavefront .OBJ file loader
 *
 * does not yet support textures,
 * materials, or vertex normals
 * 
 */

#include "objfile.h"
#include "geometry.h"
#include <malloc.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// custom version of fgetc converting dos line endings
// to unix, as glibc on Ubuntu doesn't seem to do that
static int fgetc_ng(FILE* stream) {
    int c = fgetc(stream);
    if (c == '\r')
        return fgetc(stream);
    return c;
}

mesh_t* obj_mesh_from_file(char* file) {
    // open the file
    FILE* objfile = fopen(file, "rt");
    if (objfile == NULL) {
        fprintf(stderr, "error: file %s not found\n", file);
        exit(-1);
    }

    // to store vertices
    vec3_t* vbuff = (vec3_t*)malloc(sizeof(vec3_t));
    size_t vbuff_size = sizeof(vec3_t), vbuff_i = 0;

    // to store indices
    int* ibuff = (int*)malloc(sizeof(int));
    size_t ibuff_size = sizeof(int), ibuff_i = 0;

    // create mesh structure
    mesh_t* mesh = malloc(sizeof(mesh_t));
    mesh->drawtype = DRAW_WIREFRAME;
    mesh->transform = (geom_transform_t) {
        .pos = {0, -1.5, 1.5},
        .rot = {0, 0, 0},
        .scale = {1, 1, 1}
    };

    // parse the file
    bool eof = false;
    while (!eof) {
        switch (fgetc_ng(objfile)) {
            // comments
            case '#': {
                while (fgetc_ng(objfile) != '\n');
            } break;

            // vertices
            case 'v': {
                switch (fgetc_ng(objfile)) {
                    // texture vertices (unimplemented)
                    case 't': {
                        while (fgetc_ng(objfile) != '\n');
                    } break;

                    // vertex normals (unimplemented)
                    case 'n': {
                        while (fgetc_ng(objfile) != '\n');
                    } break;

                    // regular vertices
                    default: {
                        // make sure we have enough allocated memory
                        if (vbuff_size < (vbuff_i + 1) * sizeof(vec3_t)) {
                            size_t newsize = (vbuff_i + 1) * sizeof(vec3_t) * 2;
                            vbuff = realloc(vbuff, newsize);
                            vbuff_size = newsize;
                        }

                        // read the vertex data
                        int nmt = fscanf(objfile, " %f %f %f", &(vbuff[vbuff_i].x),
                                         &(vbuff[vbuff_i].y), &(vbuff[vbuff_i].z));
                        if (nmt != 3) {
                            fprintf(stderr, "error: parse error reading vertex data in file %s\n", file);
                            exit(-1);
                        }
                        vbuff_i += 1;
                        while (fgetc_ng(objfile) != '\n');
                    }
                }
            } break;

            // face
            case 'f': {
                /*
                    all other consecutive pairs of indices are
                    connected to the first, effectively converting
                    the polygon into a triangle fan
                */
                bool is_first = true;
                int first_i = 0, prev_i = 0,
                    index_no = 0;

                // parse the line
                while (true) {
                    // eat up spaces
                    char c;
                    while((c = fgetc_ng(objfile)) == ' ');
                    ungetc(c, objfile);

                    // stop at newline
                    if (c == '\n')
                        break;

                    // read the index
                    int i;
                    int nmt = fscanf(objfile, "%d", &i);
                    if (nmt != 1) {
                        fprintf(stderr, "error: parse error reading index data in file %s\n", file);
                        exit(-1);
                    }

                    if (is_first) {
                        first_i = i;
                        is_first = false;
                    } 
                    // create next triangle
                    else if (index_no >= 2) {
                        // check if enough space is allocated
                        if (ibuff_size < (ibuff_i + 3) * sizeof(int)) {
                            size_t newsize = 2 * (ibuff_i + 3) * sizeof(int);
                            ibuff = realloc(ibuff, newsize);
                            ibuff_size = newsize;
                        }

                        ibuff[ibuff_i] = first_i - 1;
                        ibuff[ibuff_i + 1] = prev_i - 1;
                        ibuff[ibuff_i + 2] = i - 1;
                        ibuff_i += 3;
                    }
                    prev_i = i;
                    index_no++;

                    // eat up any subsequent characters
                    c = fgetc_ng(objfile);
                    while (c != ' ' && c != '\n')
                        c = fgetc_ng(objfile);
                    ungetc(c, objfile);
                }
            } break;

            // end of file
            case EOF: {
                eof = true;
            } break;
        }
    }
    fclose(objfile);

    // initialize mesh data
    mesh->data.verts = vbuff;
    mesh->data.inds = ibuff;
    mesh->data.num_verts = vbuff_i;
    mesh->data.num_inds = ibuff_i;
    mesh->data._t_verts = (vec3_t*)malloc(sizeof(vec3_t) * vbuff_i);

    printf("mesh \"%s\" loaded\n", file);
    printf("vertices: %ld, indices: %ld, triangles: %ld\n", vbuff_i, ibuff_i, ibuff_i / 3);
    return mesh;
}