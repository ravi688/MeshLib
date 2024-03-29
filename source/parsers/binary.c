
#include <meshlib/parsers/binary.h>
#include <meshlib/assert.h>
#include <memory.h>

static binary_parser_t* binded_parser = NULL;

#ifdef GLOBAL_DEBUG
#	define CHECK(ptr) (*check(&(ptr)))
#else
#	define CHECK(ptr) ptr
#endif

#define check(...) define_alias_function_macro(check, __VA_ARGS__)
static function_signature(const char**, check, const char** ptr)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	ASSERT(*ptr < (binded_parser->origin + binded_parser->length), "Out of bound memory access\n");
	CALLTRACE_RETURN(ptr);
}

MESHLIB_API function_signature(void, binary_parser_bind, binary_parser_t* parser) { CALLTRACE_BEGIN(); binded_parser = parser; CALLTRACE_END(); }
MESHLIB_API function_signature_void(void, binary_parser_unbind) { CALLTRACE_BEGIN(); binded_parser = NULL; CALLTRACE_END(); }

MESHLIB_API function_signature(binary_parser_t, binary_parser_new, const char* bytes, u64 length)
{
	CALLTRACE_BEGIN();
	CALLTRACE_RETURN((binary_parser_t)
	{
		.origin = bytes,
		.length = length, 
		.bytes = bytes
	});
}

MESHLIB_API function_signature_void(u64, binary_parser_count)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	CALLTRACE_RETURN(binded_parser->bytes - binded_parser->origin);
}

MESHLIB_API function_signature_void(void, binary_parser_rewind)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	binded_parser->bytes = binded_parser->origin;
	CALLTRACE_END();
}

MESHLIB_API function_signature(bool, binary_parser_cmp_float, float value)
{
	CALLTRACE_BEGIN();
	bool result = (*(float*)binded_parser->bytes) == value;
	if(result)
		CHECK(binded_parser->bytes) += sizeof(float);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(bool, binary_parser_cmp_s8, s8 value)
{
	CALLTRACE_BEGIN();
	bool result = (*(s8*)binded_parser->bytes) == value;
	if(result)
		CHECK(binded_parser->bytes) += sizeof(s8);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(bool, binary_parser_cmp_s16, s16 value)
{
	CALLTRACE_BEGIN();
	bool result = (*(s16*)binded_parser->bytes) == value;
	if(result)
		CHECK(binded_parser->bytes) += sizeof(s16);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(bool, binary_parser_cmp_s32, s32 value)
{
	CALLTRACE_BEGIN();
	bool result = (*(s32*)binded_parser->bytes) == value;
	if(result)
		CHECK(binded_parser->bytes) += sizeof(s32);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(bool, binary_parser_cmp_s64, s64 value)
{
	CALLTRACE_BEGIN();
	bool result = (*(s64*)binded_parser->bytes) == value;
	if(result)
		CHECK(binded_parser->bytes) += sizeof(s64);
	CALLTRACE_RETURN(result);
}


MESHLIB_API function_signature(bool, binary_parser_cmp_u8, u8 value)
{
	CALLTRACE_BEGIN();
	bool result = (*(u8*)binded_parser->bytes) == value;
	if(result)
		CHECK(binded_parser->bytes) += sizeof(u8);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(bool, binary_parser_cmp_u16, u16 value)
{
	CALLTRACE_BEGIN();
	bool result = (*(u16*)binded_parser->bytes) == value;
	if(result)
		CHECK(binded_parser->bytes) += sizeof(u16);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(bool, binary_parser_cmp_u32, u32 value)
{
	CALLTRACE_BEGIN();
	bool result = (*(u32*)binded_parser->bytes) == value;
	if(result)
		CHECK(binded_parser->bytes) += sizeof(u32);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(bool, binary_parser_cmp_u64, u64 value)
{
	CALLTRACE_BEGIN();
	bool result = (*(u64*)binded_parser->bytes) == value;
	if(result)
		CHECK(binded_parser->bytes) += sizeof(u64);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(bool, binary_parser_cmp_bytes, void* bytes, u32 count)
{
	CALLTRACE_BEGIN();
	bool result = memcmp(binded_parser->bytes, bytes, count) == 0;
	if(result)
		CHECK(binded_parser->bytes) += count;
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(void, binary_parser_skip_bytes, u64 count)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	CHECK(binded_parser->bytes) += count;
	CALLTRACE_END();
}

MESHLIB_API function_signature_void(float, binary_parser_float)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	float result = *(float*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(float);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature_void(u8, binary_parser_u8)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	u8 result = *(u8*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(u8);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature_void(u16, binary_parser_u16)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	u16 result = *(u16*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(u16);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature_void(u32, binary_parser_u32)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	u32 result = *(u32*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(u32);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature_void(u64, binary_parser_u64)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	u64 result = *(u64*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(u64);
	CALLTRACE_RETURN(result);
}
