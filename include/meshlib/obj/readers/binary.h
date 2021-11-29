
#pragma once

#include <calltrace/calltrace.h>
#include <meshlib/defines.h>

typedef struct obj_parse_callbacks_t obj_parse_callbacks_t;


function_signature(void, obj_parse_binary, const char* bytes, u64 length, obj_parse_callbacks_t* parse_callbacks);
#define obj_parse_binary(...) define_alias_function_macro(obj_parse_binary, __VA_ARGS__)
