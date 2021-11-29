
#pragma once


#include <calltrace/calltrace.h>

typedef struct stl_parse_callbacks_t stl_parse_callbacks_t;

function_signature(void, stl_parse_ascii, const char* text, stl_parse_callbacks_t* parse_callbacks);
#define stl_parse_ascii(...) define_alias_function_macro(stl_parse_ascii, __VA_ARGS__)
