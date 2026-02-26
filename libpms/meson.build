api_version = '1.0'

libpms_private_sources = [
  'ms-osk-layout-row.c',
]

libpms_public_sources = [
  'ms-osk-add-layout-dialog.c',
  'ms-osk-layout-prefs.c',
  'ms-osk-layout.c',
]

libpms_public_headers = [
  'ms-osk-add-layout-dialog.h',
  'ms-osk-layout-prefs.h',
  'ms-osk-layout.h',
  'libpms.h',
]

libpms_deps = [
  adwaita_dep,
  gio_dep,
  gio_unix_dep,
  glib_dep,
  gnome_desktop_dep,
  gtk_dep,
  json_glib_dep,
  cc.find_library('m', required: false),
]

gnome = import('gnome')

libpms_resources = gnome.compile_resources(
  'libpms-resources',
  'libpms.gresource.xml',
)

libpms_generated_sources = [
  libpms_resources,
]

libpms_lib = shared_library(
  f'pms-@api_version@',
  libpms_public_sources + libpms_public_headers + libpms_private_sources,
  libpms_generated_sources,
  dependencies: libpms_deps,
  soversion: '0',
  install: true,
  c_args: '-D_LIBPMS_INSIDE',
)

install_headers(
  libpms_public_headers,
  subdir: f'pms-@api_version@',
)

libpms_dep = declare_dependency(
  sources: libpms_generated_sources,
  link_with: libpms_lib,
  include_directories: [include_directories('.')],
  dependencies: libpms_deps,
)
