
#pragma once


#include <calltrace/calltrace.h>
#include <meshlib/data_structures.h>

function_signature(mesh_t, stl_parse_ascii, const char* text);
#define stl_parse_ascii(...) define_alias_function_macro(stl_parse_ascii, __VA_ARGS__)
