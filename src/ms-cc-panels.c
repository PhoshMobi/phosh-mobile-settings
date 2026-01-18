/*
 * Copyright (C) 2026 Phosh.mobi e.V.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Author: Guido Günther <agx@sigxcpu.org>
 */

#define G_LOG_DOMAIN "ms-cc-panels"

#include "mobile-settings-config.h"

#include "ms-cc-panels.h"
#include "ms-panel.h"
#include "ms-window.h"

#include <NetworkManager.h>
#include <adwaita.h>

#include <glib/gi18n.h>

#define MAX_KEYWORDS 4

#ifdef MOBILE_SETTINGS_HAVE_GCC_PANELS

/**
 * MsCcpaneldata:
 *
 * Hold the data of the panels we import from g-c-c via the g-c-c/ subproject
 */
typedef struct _MsCcPanelData {
  const char *name;
  GType (*get_type) (void);
  void (*init_func) (void);
} MsCcPanelData;


static AdwHeaderBar *
cc_panel_find_header_bar (GtkWidget *root)
{
  if (root == NULL)
    return NULL;

  if (ADW_IS_HEADER_BAR (root))
    return ADW_HEADER_BAR (root);

  for (GtkWidget *child = gtk_widget_get_first_child (root);
       child != NULL;
       child = gtk_widget_get_next_sibling (child)) {
    AdwHeaderBar *headerbar = cc_panel_find_header_bar (child);
    if (headerbar)
      return ADW_HEADER_BAR (headerbar);
  }

  return NULL;
}

/* From CcObjectStore */

#define CC_OBJECT_NMCLIENT     "CcObjectStorage::nm-client"
gboolean     cc_object_storage_has_object (const char *key);
void         cc_object_storage_add_object (const char *key, gpointer object);

/* See CcPanelLoader */

extern GType cc_wifi_panel_get_type (void);
extern GType cc_wwan_panel_get_type (void);
extern GType cc_bluetooth_panel_get_type (void);
extern GType cc_online_accounts_panel_get_type (void);
extern GType cc_sound_panel_get_type (void);

void         cc_wwan_panel_static_init_func (void);
void         cc_wifi_panel_static_init_func (void);

/* Keep this order in sync with CcPanelLoader as otherwise loading might fail due
 * to different object initialization order */

static const MsCcPanelData panel_data[] = {
  {
    "bluetooth",
    cc_bluetooth_panel_get_type,
    NULL,
  },
  {
    "sound",
    cc_sound_panel_get_type,
    NULL,
  },
  {
    "online-accounts",
    cc_online_accounts_panel_get_type,
    NULL,
  },
  {
    "wifi",
    cc_wifi_panel_get_type,
    cc_wifi_panel_static_init_func,
  },
  {
    "wwan",
    cc_wwan_panel_get_type,
    cc_wwan_panel_static_init_func,
  },
};


void
ms_cc_panels_add_all (MsWindow *window)
{
  GtkWidget *cc_panel;

  /* For icons in the Wi-Fi and sound panels */
  gtk_icon_theme_add_resource_path (gtk_icon_theme_get_for_display (gdk_display_get_default ()),
                                    "/org/gnome/Settings/icons");

  /* Create panels in CC compatible ordering */
  for (gsize i = 0; i < G_N_ELEMENTS (panel_data); i++) {
    const MsCcPanelData *data = &panel_data[i];
    AdwHeaderBar *headerbar;

    if (data->init_func)
      (*data->init_func)();

    cc_panel = g_object_new ((*data->get_type)(),
                             "title", "doesnotmatter",
                             "can-pop", FALSE,
                             NULL);

    /* Disable headerbar as one is enough */
    headerbar = cc_panel_find_header_bar (cc_panel);
    if (headerbar) {
      gtk_widget_set_visible (GTK_WIDGET (headerbar), FALSE);
    } else {
      g_critical ("No header bar found for panel %s", data->name);
      return;
    }

    ms_window_insert_cc_panel (window, data->name, cc_panel);
  }
}

#else

void
ms_cc_panels_add_all (MsWindow *window)
{
}

#endif
