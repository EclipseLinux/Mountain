project('Skia', ['cpp', 'c'], version: '1.20')

path = meson.project_source_root() + '/out/' + build_machine.system() + '/' + build_machine.cpu_family()

compiler = [meson.get_compiler('cpp'), meson.get_compiler('c')]

fs = import('fs')

if not fs.is_dir(path)
    error('Skia build files not found, run "' + meson.project_source_root() + '/gen_gn_and_build.sh ' + build_machine.system() + ' ' + build_machine.cpu_family() + ' ' + compiler[0].get_id() + ' ' + compiler[1].get_id() + '"')
endif

skia_lib = compiler[0].find_library('skia', dirs: path)
skottie_lib = compiler[0].find_library('skottie', dirs: path)
sksg_lib = compiler[0].find_library('sksg', dirs: path)
bentley_lib = compiler[0].find_library('bentleyottmann', dirs: path)

include_dirs = ['.', 'include', 'modules', 'src']

dependencies = [
    dependency('fontconfig'),
    dependency('freetype2'),
    dependency('threads'),
    dependency('libturbojpeg'),
    dependency('libpng'),
    dependency('libwebp'),
    dependency('libwebpdemux'),
    skia_lib, skottie_lib, sksg_lib, bentley_lib
]

skia = declare_dependency(
    dependencies: dependencies,
    include_directories: include_directories(include_dirs)
)

meson.override_dependency('skia', skia)