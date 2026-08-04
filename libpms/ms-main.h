/*
 * Copyright (C) 2026 Phosh.mobi e.V.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#include "libpms-version.h"
#include "ms-os-updater.h"

#include <glib.h>

#if !defined(_LIBPMS_INSIDE) && !defined(LIBPMS_COMPILATION)
# error "Only <libpms.h> can be included directly."
#endif

G_BEGIN_DECLS

PMS_AVAILABLE_IN_ALL
void ms_init (void);

PMS_AVAILABLE_IN_ALL
MsOsUpdater *ms_get_default_os_updater_sync (void);

G_END_DECLS
