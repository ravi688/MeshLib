#------------- Generated By Build Master 1.0.0 ------------------

# ------------------------------ DOCUMENTATION ---------------------------------
# Release build
# -------------------------
# $ meson setup --wipe <builddir> # wipe the build artifacts (like object files)
# $ meson setup <builddir> --reconfigure --buildtype=release # reconfigure the build directory for release build
# $ meson compile -C <builddir> # compile the project
#
# Debug build
# -------------------------
# $ meson setup --wipe <buildir> # wipe the build artifacts (like object files)
# $ meson setup <builddir> --reconfigure --buildtype=release # reconfigure the build directory for debug build
# $ meson compile -C <builddir> # compile the project
#
# Static Library
# -------------------------
# $ meson setup --wipe <buildir> # wipe the build artifacts (like object files)
# # NOTE: --buildtype=release or --buildtype=debug options can be added here  
# $ meson setup -C <builddir> --reconfigure --default-library=static # reconfigure the build directory for static library
# $ meson compile -C <builddir> # compile the project
# $ meson install -C <builddir> # install the static library
#
# Shared Library
# -------------------------
# $ meson setup --wipe <buildir> # whipe the build artifacts (like object files)
# # NOTE: --buildtype=release or --buildtype=debug options can be added here
# $ meson setup -C <builddir> --reconfigure --default-library=shared # reconfigure the build directory for shared library
# $ meson compile -C <builddir> # compile the project
# $ meson install -C <builddir> # install the shared library
#
# Artifact Installation Directories
# ---------------------------------
# Headers: /include/<ProjectNameInSmallCase>
# Static Libraries: /lib/lib<ProjectNameInSmallCase>.a-
# Shared Libraries: /bin/lib<ProjectNameInSmallCase>.dll
# PkgConfig (.pc) for static library: $PKG_CONFIG_PATH/<ProjectNameInSmallCase>_static.pc
# PkgConfig (.pc) for shared library: $PKG_CONFIG_PATH/<ProjectNameInSmallCase>_shared.pc
#
# -------------------------------- PROJECT CONFIGS -----------------------------

project('MeshLib', 'c', 'cpp',
  version : '1.0.0',
  meson_version: '>=1.1',
  default_options : [
    'warning_level=3',
    'buildtype=debug',
    'c_std=c17',
    'cpp_std=c++20'
  ]
)

# Variables


# Defines
defines_bm_internal__ = [

]

# Release Build Defines
release_defines_bm_internal__ = [
'-DMESHLIB_RELEASE', '-DGLOBAL_RELEASE', '-DRELEASE', '-DLOG_RELEASE'
] 

# Debug Build Defines
debug_defines_bm_internal__ = [
'-DMESHLIB_DEBUG', '-DGLOBAL_DEBUG', '-DDEBUG', '-DLOG_DEBUG'
]

# Source files (common to all targets)
sources_bm_internal__ = files(
'source/obj/ascii.c', 'source/obj/binary.c', 'source/obj/parse_error.c', 'source/parsers/binary.c', 'source/parsers/string.c', 'source/stl/ascii.c', 'source/stl/binary.c', 'source/stl/parse_error.c'
)

# Include directories
inc_bm_internal__ = include_directories(
'include'
)

# Library Install Directory
lib_install_dir_bm_internal__ = get_option('libdir')/'meshlib'

# Dependencies
dependencies_bm_internal__ = [
dependency('bufferlib'),
dependency('calltrace'),
dependency('diskmanager'),
dependency('hpml'),
dependency('safemem'),
dependency('tempsys')
]

# Linker Arguments
windows_link_args_bm_internal__ = [ 

]
linux_link_args_bm_internal__ = [

]
darwin_link_args_bm_internal__ = [

]

# -------------------------------------------------------------------------------
# ------------------------------ FIXTURE ----------------------------------------

# Compiler configuration
add_project_arguments('-m64', language : 'c')
add_project_arguments('-m64', language : 'cpp')
# Linker configuration
link_args_bm_internal__ = []
os_name_bm_internal__ = host_machine.system()
if os_name_bm_internal__ == 'windows'
  link_args_bm_internal__ += windows_link_args_bm_internal__
elif os_name_bm_internal__ == 'linux'
  link_args_bm_internal__ += linux_link_args_bm_internal__
elif os_name_bm_internal__ == 'darwin'
  link_args_bm_internal__ += darwin_link_args_bm_internal__
endif
add_project_link_arguments('-m64', link_args_bm_internal__, language : 'c')
add_project_link_arguments('-m64', link_args_bm_internal__, language : 'cpp')

# Build type specific defines
build_mode_defines_bm_internal__ = defines_bm_internal__
if get_option('buildtype') == 'release'
  add_project_arguments(release_defines_bm_internal__, language : 'c')
  add_project_arguments(release_defines_bm_internal__, language : 'cpp')
  build_mode_defines_bm_internal__ += release_defines_bm_internal__
else
  add_project_arguments(debug_defines_bm_internal__, language : 'c')
  add_project_arguments(debug_defines_bm_internal__, language : 'cpp')
  build_mode_defines_bm_internal__ += debug_defines_bm_internal__
endif

# pkg-config package installation
# Try PKG_CONFIG_PATH first, typicallly it succeeds on MINGW64 (MSYS2)
python_pkg_config_path_result_bm_internal__ = run_command(find_program('python'), '-c', 'import os; print(os.environ["PKG_CONFIG_PATH"])', check : false)
pkgconfig_install_path_bm_internal__ = ''
if python_pkg_config_path_result_bm_internal__.returncode() == 0
  str = python_pkg_config_path_result_bm_internal__.stdout()
  # Unix
  if str.startswith('/')
    pkgconfig_install_path_bm_internal__ = str.replace(';', ':').split(':')[0]
  # Windows
  else
    pkgconfig_install_path_bm_internal__ = str.split(';')[0]
  endif
endif
if pkgconfig_install_path_bm_internal__ == ''
  # Otherwise use pkg-config to query its lookup directories
  message('PKG_CONFIG_PATH seems to be empty, trying another method')
  python_pkg_config_path_result_bm_internal__ = run_command('pkg-config', '--variable', 'pc_path', 'pkg-config', check : false)
  if python_pkg_config_path_result_bm_internal__.returncode() == 0
    str = python_pkg_config_path_result_bm_internal__.stdout()
    if str.startswith('/')
      pkgconfig_install_path_bm_internal__ = str.replace(';', ':').split(':')[0]
    else
      pkgconfig_install_path_bm_internal__ = str.split(';')[0]
    endif
  # Finally if the above attempts fail, use 'libdir' value
  else
    pkgconfig_install_path_bm_internal__ = get_option('libdir')
  endif
endif
message('pkg config path: ' + pkgconfig_install_path_bm_internal__)

#-------------------------------------------------------------------------------
#--------------------------------BUILD TARGETS----------------------------------
pkgmod = import('pkgconfig')

# -------------- Target: meshlib ------------------
meshlib_sources_bm_internal__ = [
'source/main.c'
]
meshlib_include_dirs_bm_internal__ = [

]
meshlib_dependencies_bm_internal__ = [

]
meshlib_link_args_bm_internal__ = {
'windows' : [],
'linux' : [],
'darwin' : []
}
meshlib_defines_bm_internal__ = [

]
meshlib = executable('meshlib',
	meshlib_sources_bm_internal__ + sources_bm_internal__,
	dependencies: dependencies_bm_internal__ + meshlib_dependencies_bm_internal__,
	include_directories: [inc_bm_internal__, meshlib_include_dirs_bm_internal__],
	install: false,
	c_args: meshlib_defines_bm_internal__,
	cpp_args: meshlib_defines_bm_internal__, 
	link_args: meshlib_link_args_bm_internal__[host_machine.system()],
	gnu_symbol_visibility: 'hidden'
)

# -------------- Target: meshlib_static ------------------
meshlib_static_sources_bm_internal__ = [

]
meshlib_static_include_dirs_bm_internal__ = [

]
meshlib_static_dependencies_bm_internal__ = [

]
meshlib_static_link_args_bm_internal__ = {
'windows' : [],
'linux' : [],
'darwin' : []
}
meshlib_static_build_defines_bm_internal__ = [

]
meshlib_static_use_defines_bm_internal__ = [

]
meshlib_static = static_library('meshlib_static',
	meshlib_static_sources_bm_internal__ + sources_bm_internal__,
	dependencies: dependencies_bm_internal__ + meshlib_static_dependencies_bm_internal__,
	include_directories: [inc_bm_internal__, meshlib_static_include_dirs_bm_internal__],
	install: true,
	install_dir: lib_install_dir_bm_internal__,
	c_args: meshlib_static_build_defines_bm_internal__,
	cpp_args: meshlib_static_build_defines_bm_internal__, 
	link_args: meshlib_static_link_args_bm_internal__[host_machine.system()],
	gnu_symbol_visibility: 'hidden'
)
meshlib_static_dep = declare_dependency(
	link_with: meshlib_static,
	include_directories: [inc_bm_internal__, meshlib_static_include_dirs_bm_internal__],
	compile_args: meshlib_static_use_defines_bm_internal__ + build_mode_defines_bm_internal__
)
pkgmod.generate(meshlib_static,
	name: 'MeshLib',
	description: 'Static library for MeshLib',
	filebase: 'meshlib_static',
	install_dir: pkgconfig_install_path_bm_internal__,
	extra_cflags: meshlib_static_use_defines_bm_internal__ + build_mode_defines_bm_internal__
)

# -------------- Target: meshlib_shared ------------------
meshlib_shared_sources_bm_internal__ = [

]
meshlib_shared_include_dirs_bm_internal__ = [

]
meshlib_shared_dependencies_bm_internal__ = [

]
meshlib_shared_link_args_bm_internal__ = {
'windows' : [],
'linux' : [],
'darwin' : []
}
meshlib_shared_build_defines_bm_internal__ = [

]
meshlib_shared_use_defines_bm_internal__ = [

]
meshlib_shared = shared_library('meshlib_shared',
	meshlib_shared_sources_bm_internal__ + sources_bm_internal__,
	dependencies: dependencies_bm_internal__ + meshlib_shared_dependencies_bm_internal__,
	include_directories: [inc_bm_internal__, meshlib_shared_include_dirs_bm_internal__],
	install: true,
	install_dir: lib_install_dir_bm_internal__,
	c_args: meshlib_shared_build_defines_bm_internal__,
	cpp_args: meshlib_shared_build_defines_bm_internal__, 
	link_args: meshlib_shared_link_args_bm_internal__[host_machine.system()],
	gnu_symbol_visibility: 'hidden'
)
meshlib_shared_dep = declare_dependency(
	link_with: meshlib_shared,
	include_directories: [inc_bm_internal__, meshlib_shared_include_dirs_bm_internal__],
	compile_args: meshlib_shared_use_defines_bm_internal__ + build_mode_defines_bm_internal__
)
pkgmod.generate(meshlib_shared,
	name: 'MeshLib',
	description: 'Shared Library for MeshLib',
	filebase: 'meshlib_shared',
	install_dir: pkgconfig_install_path_bm_internal__,
	extra_cflags: meshlib_shared_use_defines_bm_internal__ + build_mode_defines_bm_internal__
)


#-------------------------------------------------------------------------------
#--------------------------------Header Intallation----------------------------------
# Header installation
install_subdir('include/meshlib', install_dir : get_option('includedir'))


