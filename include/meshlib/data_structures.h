/*
1. create from existing array vertices
2. 
*/


#pragma once

#include <meshlib/defines.h>
#include <buffer.h>

typedef struct 
{	
	void* metaData;
	/*TODO: Expose __BUFFER struct definition in the header buffer.h*/
	BUFFER* vertices;
} mesh_t;


#define mesh_new(type) __mesh_new(sizeof(type))
mesh_t __mesh_new(u64 vertexStride);
void mesh_destroy(mesh_t mesh);

#define mesh_vertex_add(mesh, ptr) buf_push(mesh.vertices, ptr)
#define mesh_vertex_addv(mesh, ptr, count) buf_pushv(mesh.vertices, ptr, count)
#define mesh_vertices(mesh, type) ((type*)buf_get_ptr(mesh.vertices))