project('Mountain', ['cpp', 'c'], version: '0.0.1', default_options: ['cpp_std=c++20'])

sources = [
    
]

cfg = configuration_data()

cpp = meson.get_compiler('cpp')

cfg.set_quoted('mn_version', meson.project_version())
cfg.set_quoted('mn_platform', host_machine.system())
cfg.set_quoted('mn_compiler', cpp.get_id())
cfg.set_quoted('mn_linker', cpp.get_linker_id())
cfg.set('mn_alignment', cpp.alignment('int'))
cfg.set('mn_sizeInt', cpp.sizeof('int'))
cfg.set_quoted('mn_arch', host_machine.cpu_family())
cfg.set_quoted('mn_endian', host_machine.endian())

configure_file(configuration: cfg, output: 'MountainConfig.h', install: true, install_dir: 'share')

if get_option('debug')
    add_global_arguments(['-DDEBUG=1'], language : ['cpp', 'c'])
endif

add_global_arguments(['-DGR_GL_CHECK_ERROR=0', '-DGR_GL_LOG_CALLS=0', '-DSK_GL=1'], language : ['cpp', 'c'])

dependencies = [dependency('spdlog'), dependency('sdl2'), dependency('rang')]

inc_dirs = [ 'include' ]

mountain = library('mountain', sources: sources, dependencies: dependencies, include_directories: include_directories(inc_dirs), install: true)

mountain_dep = declare_dependency(link_with: mountain, dependencies: dependencies, include_directories: include_directories(inc_dirs))

executable('sandbox', sources: 'sandbox/main.cpp', dependencies: mountain_dep)