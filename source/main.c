
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
	vec3_t(float) position;
	vec4_t(float) color;
	vec2_t(float) uv;
	vec3_t(float) normal;
} vertex3d_t;

int main(int argc, char** argv)
{
	// mesh_t m = mesh_new(vertex3d_t);
	// vertex3d_t vertices[2] =  
	// {
	// 	{ { 0, 0, 0 }, { 1, 1, 1, 1 }, { 0, 1 }, { 1.2f, 2.3f, 0.1f } },
	// 	{ { 0, 0, 0 }, { 1, 1, 1, 1 }, { 0, 1 }, { 1.2f, 2.3f, 0.1f } }
	// };
	// mesh_vertex_add(mesh, &vertices[0]);
	// mesh_vertex_addv(mesh, vertices, 2);
	// mesh_vertex_clear_all(mesh);
	// mesh_vertices(mesh, vertex3d_t)[1] = (vertex3d_t) { };
	// mesh_destroy(m);
	return 0;
}