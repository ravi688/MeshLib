
#pragma once

#include <calltrace/calltrace.h>
#include <meshlib/defines.h>
#include <meshlib/data_structures.h>


function_signature(mesh_t, obj_parse_binary, const char* text);
#define obj_parse_binary(...) define_alias_function_macro(obj_parse_binary, __VA_ARGS__)
