/*
 * Copyright (C) 2026 Phosh.mobi e.V.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Author: Rudra Pratap Singh <rudrasingh900@gmail.com>
 */

#include "libpms.h"

static void
on_app_activated (GApplication *app)
{
  MsOskLayoutPrefs *prefs = ms_osk_layout_prefs_new ();

  ms_osk_layout_prefs_load_osk_layouts (prefs);
}


int
main (int argc, char **argv)
{
  int status;
  GtkApplication *app = gtk_application_new ("mobi.phosh.MobileSettings.LibmsExampleC",
                                             G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect_object (G_APPLICATION (app),
                           "activate",
                           G_CALLBACK (on_app_activated),
                           NULL,
                           G_CONNECT_DEFAULT);

  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
