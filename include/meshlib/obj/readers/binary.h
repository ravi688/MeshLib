
#pragma once

/* for stacktrace */
#include <calltrace/calltrace.h>
/* for u64 */
#include <meshlib/defines.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct obj_parse_callbacks_t obj_parse_callbacks_t;

/* obj_parse_binary(const char* bytes, u64 length, obj_parse_callbacks_t* parse_callbacks):
 * THIS METHOD ISN'T DEFINED, Calling this would produce the following fetal error:
 * obj_parse_binary isn't implemented because the standard binary version doesn't exists
 */
function_signature(void, obj_parse_binary, const char* bytes, u64 length, obj_parse_callbacks_t* parse_callbacks);
#define obj_parse_binary(...) define_alias_function_macro(obj_parse_binary, __VA_ARGS__)



#ifdef __cplusplus
}
#endif
