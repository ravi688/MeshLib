
#include <meshlib/readers/stl/binary.h>
#include <meshlib/readers/stl/vertex.h>

function_signature(mesh_t, stl_parse_binary, const char* bytes)
{
	mesh_t mesh = mesh_new(stl_vertex_t); 
	return mesh;
}