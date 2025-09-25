/*
 * Copyright (C) 2025 Stefan Hansson
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Author: Stefan Hansson <newbyte@postmarketos.org>
 */

#pragma once

#include "ms-tweaks-backend-interface.h"
#include "ms-tweaks-parser.h"

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MS_TYPE_TWEAKS_BACKEND_XRESOURCES ms_tweaks_backend_xresources_get_type ()
G_DECLARE_FINAL_TYPE (MsTweaksBackendXresources, ms_tweaks_backend_xresources, MS, TWEAKS_BACKEND_XRESOURCES, GObject)

MsTweaksBackend *ms_tweaks_backend_xresources_new (const MsTweaksSetting *setting_data);

void ms_tweaks_backend_xresources_set_xresources_path (MsTweaksBackend *backend,
                                                       char *xresources_path);

G_END_DECLS
