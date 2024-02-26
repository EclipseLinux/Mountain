project('Mountain', ['cpp', 'c'], version: '0.0.1', default_options: ['cpp_std=c++20'])

sources = [
    
]

dependencies = [dependency('spdlog'), dependency('sdl2')]

inc_dirs = [ 'include' ]

mountain = library('mountain', sources: sources, dependencies: dependencies, include_directories: include_directories(inc_dirs), install: true)

mountain_dep = declare_dependency(link_with: mountain, dependencies: dependencies, include_directories: include_directories(inc_dirs))

executable('sandbox', sources: 'sandbox/main.cpp', dependencies: mountain_dep)