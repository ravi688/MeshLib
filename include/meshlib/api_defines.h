#pragma once

#if (defined _WIN32 || defined __CYGWIN__) && defined(__GNUC__)
#	define MESHLIB_IMPORT_API __declspec(dllimport)
#	define MESHLIB_EXPORT_API __declspec(dllexport)
#else
#	define MESHLIB_IMPORT_API __attribute__((visibility("default")))
#	define MESHLIB_EXPORT_API __attribute__((visibility("default")))
#endif

#ifdef MESHLIB_BUILD_STATIC_LIBRARY
#	define MESHLIB_API
#elif defined(MESHLIB_BUILD_DYNAMIC_LIBRARY)
#	define MESHLIB_API MESHLIB_EXPORT_API
#elif defined(MESHLIB_USE_DYNAMIC_LIBRARY)
#	define MESHLIB_API MESHLIB_IMPORT_API
#elif defined(MESHLIB_USE_STATIC_LIBRARY)
#	define MESHLIB_API
#else
#	define MESHLIB_API
#endif
