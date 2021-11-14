
#include <meshlib/data_structures.h>
#include <calltrace/calltrace.h>

function_signature(mesh_t, __mesh_new, u64 vertexStride)
{
	CALLTRACE_BEGIN();
	CALLTRACE_RETURN((mesh_t) 
	{
		.user_data = NULL,
		.vertices = BUFcreate(NULL, vertexStride, 0, 0)
	});
}

function_signature(void, mesh_destroy, mesh_t mesh)
{
	CALLTRACE_BEGIN();
	if(mesh.user_data != NULL)
		free(mesh.user_data);
	if(mesh.vertices != BUF_INVALID)
		buf_free(mesh.vertices);
	CALLTRACE_END();
}