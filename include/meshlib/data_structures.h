/*
1. Create from existing array vertices
2. 
*/


#pragma once

#include <meshlib/defines.h>
#include <buffer.h>
#include <safe_memory/safe_memory.h>

typedef struct 
{
	void* user_data;
	BUFFER* vertices;
} mesh_t;


//TODO: convert it to a template<Type>
#define mesh_new(type) __mesh_new(sizeof(type))
function_signature(mesh_t, __mesh_new, u64 vertexStride);
#define __mesh_new(...) define_alias_function_macro(__mesh_new, __VA_ARGS__)

function_signature(void, mesh_destroy, mesh_t mesh);
#define mesh_destroy(...) define_alias_function_macro(mesh_destroy, __VA_ARGS__)

#define mesh_vertex_add(mesh, ptr) buf_push(mesh.vertices, ptr)
#define mesh_vertex_addv(mesh, ptr, count) buf_pushv(mesh.vertices, ptr, count)

//TODO: convert it to a template<Type>
#define mesh_vertex(type, mesh, index) (*(type*)buf_getptr_at(mesh.vertices, index)) 

//TODO: convert it to a template<Type>
//TODO: when SafeMemory's issue https://github.com/ravi688/SafeMemory/issues/4 gets solved
// #define mesh_vertices(type, mesh) ((type*)checked(buf_get_ptr(mesh.vertices), buf_get_element_count(mesh.vertices)))
#define mesh_vertices(type, mesh) ((type*)buf_get_ptr(mesh.vertices))

#define mesh_vertices_clear(mesh) buf_clear(mesh.vertices, NULL)