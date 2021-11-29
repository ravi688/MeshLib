
#pragma once

#include <calltrace/calltrace.h>
#include <meshlib/defines.h>

typedef struct obj_parse_callbacks_t obj_parse_callbacks_t;

function_signature(void, obj_parse_ascii, const char* text, u64 length, obj_parse_callbacks_t* parse_callbacks);
#define obj_parse_ascii(...) define_alias_function_macro(obj_parse_ascii, __VA_ARGS__)
