
#pragma once

/* for stacktrace */
#include <calltrace/calltrace.h>
/* for u64 */
#include <meshlib/defines.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct obj_parse_callbacks_t obj_parse_callbacks_t;

/* obj_parse_ascii(const char* text, u64 length, obj_parse_clallbacks_t* parse_callbacks):
 * DESCRIPTION:
 *		Parses a string containg ASCII obj data, and calls appropriate functions using parse_callbacks foreach parsed vertex and normal
 * PARAMS:
 * 		1. text: ASCII obj text/string in memory, note: this is not the file path
 * 		2. length: length of the text
 *		3. parse_callbacks: contains pointers to functions to be called foreach parsed vertex and normal, and a pointer to user_data
 * RETURNS:
 *		Nothing
 * ERROR DESCRIPTIONS:
 *		1. OBJ_PARSE_ERROR_VERTEX_NOT_FOUND, if the obj file doesn't contain valid obj ASCII data
 *		2. OBJ_PARSE_ERROR_UNRECOGNIZED_KEYWORD, if the obj file doesn't contain valid obj ASCII data
 *		3. OBJ_PARSE_ERROR_TEXCOORD_NOT_FOUND, if the obj file doesn't contain valid obj ASCII data
 *		4. OBJ_PARSE_ERROR_NORMAL_NOT_FOUND, if the obj file doesn't contain valid obj ASCII data
 *		5. OBJ_PARSE_ERROR_FACET_NOT_FOUND, if the obj file doesn't contain valid obj ASCII data
 *		7. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 *		8. binded_parser == NULL, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * MEMORY OPERATION DESCRIPTIONS:
 * 		1. No heap memory allocations, nor freed.
 * NOTE:
 * 		1. This function doesn't check for precondition, such as text shouldn't be NULL or length shouldn't be zero
 * 		2. text must be a valid string containing a valid ASCII obj data
 * 		3. length must be the length of the passed text inclusive of the null character
 * 		4. function pointers in parse_callbacks could be NULL, this function checks for NULL before calling them.
 *		5. THIS FUNCTION IS A PARTICULAR IMPLEMENTATION FOR ONLY A PARTICULAR KIND ASCII OBJ FILE
 * 			1. Facets must be of the format {vertexID}/{texcoordID}/{normalID}
 * 			2. Positions must be present in the OBJ file (v)
 * 			3. Texture coordinates must be present in the OBJ file (vt)
 * 			4. Normals must be present in the OBJ file (vn)
 *			5. Only a single mesh/model must be present, no hierarchies should be there in the OBJ file
 *		6. If the above conditions are not met then the behaviour of this function is undefined!
 * EXAMPLES:
 * 		#include <disk_manager/file_reader.h>
 *      #include <meslib/obj/readers/ascii.h>
 * 		static void print_position(vec3_t(float) position, void* user_data) { printf("POSITION: %f, %f, %f\n", position.x, position.y, position.z); }
 *      static void print_normal(vec3_t(float) normal, void* user_data) { printf("NORMAL: %f, %f, %f\n", normal.x, normal.y, normal.z); }
 *      static void print_texcoord(vec2_t(float) texcoord, void* user_data) { printf("texcoord: %f, %f\n", texcoord.x, texcoord.y); }
 *		static void print_facet(vec4_t(vec3_t(int)) facet, void* ptr)
 *		{
 *			printf("FACET -> (%d, %d, %d) (%d, %d, %d) (%d, %d, %d) (%d, %d, %d)\n",
 *				facet.x.x, facet.x.y, facet.x.z,
 *				facet.y.x, facet.y.y, facet.y.z,
 *				facet.z.x, facet.z.y, facet.z.z,
 *				facet.w.x, facet.w.y, facet.w.z);
 *		}
 * 		//some scope
 * 		BUFFER* obj_file_data = load_text_from_file("resource/ASCII-box.obj");
 *      obj_parse_callbacks_t callbacks = 
 *		{ 
 *			.user_data = NULL, 
 *			.vertex_position_callback = print_position, 
 *			.vertex_normal_callback = print_normal,
 *			.vertex_texcoord_callback = print_texcoord,
 *			.facet_callback = print_facet
 *		};
 *      obj_parse_ascii(obj_file_data->bytes, obj_file_data->element_count, &callbacks);
 *		buf_free(obj_file_data);
 */
MESHLIB_API function_signature(void, obj_parse_ascii, const char* text, u64 length, obj_parse_callbacks_t* parse_callbacks);
#define obj_parse_ascii(...) define_alias_function_macro(obj_parse_ascii, __VA_ARGS__)


#ifdef __cplusplus
}
#endif
