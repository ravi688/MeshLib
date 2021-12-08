
#include <meshlib/parsers/binary.h>
#include <meshlib/assert.h>

static binary_parser_t* binded_parser = NULL;

#ifdef GLOBAL_DEBUG
#	define CHECK(ptr) (*check(&(ptr)))
#else
#	define CHECK(ptr) ptr
#endif

#define check(...) define_alias_function_macro(check, __VA_ARGS__)
function_signature(static const char**, check, const char** ptr)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	ASSERT(*ptr < (binded_parser->origin + binded_parser->length), "Out of bound memory access\n");
	CALLTRACE_RETURN(ptr);
}

function_signature(void, binary_parser_bind, binary_parser_t* parser) { CALLTRACE_BEGIN(); binded_parser = parser; CALLTRACE_END(); }
function_signature_void(void, binary_parser_unbind) { CALLTRACE_BEGIN(); binded_parser = NULL; CALLTRACE_END(); }

function_signature(binary_parser_t, binary_parser_new, const char* bytes, u64 length)
{
	CALLTRACE_BEGIN();
	CALLTRACE_RETURN((binary_parser_t)
	{
		.origin = bytes,
		.length = length, 
		.bytes = bytes
	});
}

function_signature_void(u64, binary_parser_count)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	CALLTRACE_RETURN(binded_parser->bytes - binded_parser->origin);
}

function_signature(void, binary_parser_skip_bytes, u64 count)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	CHECK(binded_parser->bytes) += count;
	CALLTRACE_END();
}

function_signature_void(float, binary_parser_float)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	float result = *(float*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(float);
	CALLTRACE_RETURN(result);
}

function_signature_void(u8, binary_parser_u8)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	u8 result = *(u8*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(u8);
	CALLTRACE_RETURN(result);
}

function_signature_void(u16, binary_parser_u16)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	u16 result = *(u16*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(u16);
	CALLTRACE_RETURN(result);
}

function_signature_void(u32, binary_parser_u32)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	u32 result = *(u32*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(u32);
	CALLTRACE_RETURN(result);
}

function_signature_void(u64, binary_parser_u64)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	u64 result = *(u64*)binded_parser->bytes;
	CHECK(binded_parser->bytes) += sizeof(u64);
	CALLTRACE_RETURN(result);
}
