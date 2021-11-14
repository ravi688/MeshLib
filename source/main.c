/*
TODO: 
1. Make buf_free() more secure
2. 
*/



#include <stdio.h>
#include <meshlib/data_structures.h>

#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>

#include <hpml/vec4/header_config.h>
#include <hpml/vec4/vec4.h>

#include <hpml/vec2/header_config.h>
#include <hpml/vec2/vec2.h>

typedef struct 
{
	vec4_t(float) color;
	vec3_t(float) position;
	vec3_t(float) normal;
	vec2_t(float) uv;
} vertex3d_t;

int main(int argc, char** argv)
{
	safe_memory_init();
	mesh_t mesh = mesh_new(vertex3d_t);
	vertex3d_t vertices[2] = 
	{
		{ { 1, 1, 1, 1 }, { 0, 0, 0 }, { 0, 1, 0 }, { 1, 0 } },
		{ { 1, 1, 1, 1 }, { 0, 0, 0 }, { 0, 1, 0 }, { 1, 0 } }
	};
	mesh_vertex_add(mesh, &vertices[0]);
	// mesh_vertex_addv(mesh, vertices, 2);
	// mesh_vertices_clear(mesh);
	mesh_vertices(vertex3d_t, mesh)[0] = (vertex3d_t) { };
	mesh_destroy(mesh);
	safe_memory_terminate();
	return 0;
}