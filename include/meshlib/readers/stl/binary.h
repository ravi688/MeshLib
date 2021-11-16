
#pragma once


#include <calltrace/calltrace.h>
#include <meshlib/data_structures.h>

function_signature(mesh_t, stl_parse_binary, const char* bytes);
#define stl_parse_binary(...) define_alias_function_macro(stl_parse_binary, __VA_ARGS__)
