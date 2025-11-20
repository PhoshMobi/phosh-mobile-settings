/*
 * Copyright (C) 2025 Stefan Hansson
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Author: Stefan Hansson <newbyte@postmarketos.org>
 */

#include "ms-tweaks-backend-interface.h"


enum {
  SIGNAL_SAVE_AS_ADMINISTRATOR,
  SIGNAL_LAST,
};
guint signals[SIGNAL_LAST];


G_DEFINE_INTERFACE (MsTweaksBackend, ms_tweaks_backend, G_TYPE_OBJECT)


static void
ms_tweaks_backend_default_init (MsTweaksBackendInterface *iface)
{
  signals[SIGNAL_SAVE_AS_ADMINISTRATOR] =
    g_signal_new ("save-as-administrator",
                  MS_TYPE_TWEAKS_BACKEND,
                  G_SIGNAL_RUN_LAST,
                  0,
                  NULL, NULL, NULL,
                  G_TYPE_NONE,
                  2,
                  G_TYPE_STRING, /* From. */
                  G_TYPE_STRING); /* To. */
}
