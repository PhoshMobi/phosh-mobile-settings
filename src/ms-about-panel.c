/*
 * Copyright (C) 2026 Phosh.mobi e.V.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Author: Guido Günther <agx@sigxcpu.org>
 */

#include "mobile-settings-config.h"

#include "ms-about-panel.h"

#include "gmobile.h"

struct _MsAboutPanel {
  MsPanel parent;

  AdwActionRow *device_row;
  AdwActionRow *os_row;
  AdwActionRow *version_row;
  GtkPicture *logo;
};

G_DEFINE_TYPE (MsAboutPanel, ms_about_panel, MS_TYPE_PANEL)


static char *
ms_about_panel_get_os_info (void)
{
  g_autofree char *os_name = NULL;
  g_autofree char *os_version = NULL;
  g_autofree char *os_pretty = NULL;

  os_name = g_get_os_info (G_OS_INFO_KEY_NAME);
  os_version = g_get_os_info (G_OS_INFO_KEY_VERSION_ID);
  os_pretty = g_get_os_info (G_OS_INFO_KEY_PRETTY_NAME);

  if (os_pretty)
    return g_steal_pointer (&os_pretty);

  if (os_name && os_version)
    return g_strdup_printf ("%s %s", os_name, os_version);

  return NULL;
}


static char *
ms_about_panel_get_device_info (void)
{
  g_auto (GStrv) compatibles = gm_device_tree_get_compatibles (NULL, NULL);
  g_autoptr (GmDeviceInfo) info = NULL;
  const char *name;
  GmDisplayPanel *panel;

  if (gm_strv_is_null_or_empty (compatibles))
    return NULL;

  info = gm_device_info_new ((const char * const *)compatibles);
  panel = gm_device_info_get_display_panel (info);
  if (!panel)
    goto no_panel_info;

  name = gm_display_panel_get_name (panel);
  if (name)
    return g_strdup (name);

 no_panel_info:
  g_warning ("No info for '%s', please update info in gmobile", compatibles[0]);
  return g_strdup (compatibles[0]);
}


static void
ms_about_panel_class_init (MsAboutPanelClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class,
                                               "/mobi/phosh/MobileSettings/ui/ms-about-panel.ui");

  gtk_widget_class_bind_template_child (widget_class, MsAboutPanel, device_row);
  gtk_widget_class_bind_template_child (widget_class, MsAboutPanel, os_row);
  gtk_widget_class_bind_template_child (widget_class, MsAboutPanel, version_row);
  gtk_widget_class_bind_template_child (widget_class, MsAboutPanel, logo);
}


static void
ms_about_panel_init (MsAboutPanel *self)
{
  g_autofree char *os_info = NULL, *device_info = NULL;

  gtk_widget_init_template (GTK_WIDGET (self));
  gtk_picture_set_resource (self->logo, "/mobi/phosh/MobileSettings/phosh.mobi.svg");

  adw_action_row_set_subtitle (self->version_row, MOBILE_SETTINGS_VERSION);

  os_info = ms_about_panel_get_os_info ();
  if (os_info)
    adw_action_row_set_subtitle (self->os_row, os_info);
  else
    gtk_widget_set_visible (GTK_WIDGET (self->os_row), FALSE);

  device_info = ms_about_panel_get_device_info ();
  if (device_info)
    adw_action_row_set_subtitle (self->device_row, device_info);
  else
    gtk_widget_set_visible (GTK_WIDGET (self->device_row), FALSE);
}
