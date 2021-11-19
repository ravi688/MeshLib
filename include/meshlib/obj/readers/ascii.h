
#pragma once

#include <calltrace/calltrace.h>
#include <meshlib/defines.h>
#include <meshlib/data_structures.h>


function_signature(mesh_t, obj_parse_ascii, const char* text, u64 length);
#define obj_parse_ascii(...) define_alias_function_macro(obj_parse_ascii, __VA_ARGS__)
