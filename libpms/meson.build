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

if get_option('introspection')
  libpms_gir_extra_args = [
    '--quiet',
    '-DLIBPMS_COMPILATION',
    '-DLIBPMS_USE_UNSTABLE_API',
    '--doc-format=gi-docgen',
  ]

  libpms_gir = gnome.generate_gir(
    libpms_lib,
    header: 'libpms.h',
    sources: libpms_public_sources + libpms_public_headers,
    nsversion: api_version,
    namespace: 'Pms',
    symbol_prefix: 'ms',
    identifier_prefix: 'Ms',
    includes: ['Gio-2.0', 'Gtk-4.0', 'Adw-1'],
    install: true,
    extra_args: libpms_gir_extra_args,
    fatal_warnings: true,
  )
endif
