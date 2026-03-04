/*
 * Copyright (C) 2026 Phosh.mobi e.V.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * Author: Guido Günther <agx@sigxcpu.org>
 */

#define G_LOG_DOMAIN "ms-main"

#include "ms-main.h"

#include "mobile-settings-config.h"

#include <glib/gi18n-lib.h>

/**
 * ms_init:
 *
 * Initialise the library.
 */
void
ms_init (void)
{
  static gsize initialised = FALSE;

  if (g_once_init_enter (&initialised)) {
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);

    g_once_init_leave (&initialised, TRUE);
  }
}
