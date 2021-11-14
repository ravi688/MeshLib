
#include <meshlib/data_structures.h>


mesh_t __mesh_new(u64 vertexStride)
{
	return (mesh_t) 
	{
		.metaData = NULL,
		.vertices = BUFcreate(NULL, vertexStride, 0, 0)
	};
}

void mesh_destroy(mesh_t mesh)
{
	// if(metaData != NULL)
	// 	free(metaData);
	// if(mesh.vertices != BUF_INVALID)
	// 	BUFfree(mesh.vertices);
}