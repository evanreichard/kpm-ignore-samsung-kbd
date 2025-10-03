/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2025 Evan Reichard. All Rights Reserved.
 */
#include "sam_hid_kbd_rem.h"
#include <compiler.h>
#include <hook.h>
#include <kpmodule.h>
#include <linux/container_of.h>
#include <linux/string.h>
#include <log.h>

KPM_NAME("samsung-kbd-remove");
KPM_VERSION("1.0.0");
KPM_LICENSE("GPL v2");
KPM_AUTHOR("Evan Reichard");
KPM_DESCRIPTION(
    "Fix Generic Keyboards - Remove Samsung Wireless Keyboard Support");

// Ignored Devices
static const struct hid_device_id ignore_list[] = {
    {HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SAMSUNG_ELECTRONICS,
                          USB_DEVICE_ID_SAMSUNG_WIRELESS_KBD)},
    {}};

// Function Pointers
static unsigned long (*hid_lookup_quirk)(const struct hid_device *hdev);
static const struct hid_device_id *(*hid_match_device)(struct hid_device *hdev,
                                                       struct hid_driver *hdrv);
static const struct hid_device_id *(*hid_match_id)(
    const struct hid_device *hdev, const struct hid_device_id *id);

static void before_hid_lookup_quirk(hook_fargs1_t *args, void *udata) {
  const struct hid_device *hdev = (const struct hid_device *)args->arg0;
  if (hid_match_id(hdev, ignore_list)) {
    logkd("blocking samsung quirk\n");
    args->ret = 0;
    args->skip_origin = true;
  }
}

static void before_hid_match_device(hook_fargs2_t *args, void *udata) {
  struct hid_device *hdev = (struct hid_device *)args->arg0;
  struct hid_driver *hdrv = (struct hid_driver *)args->arg1;

  if (strcmp(hdrv->name, "samsung") == 0 && hid_match_id(hdev, ignore_list)) {
    logkd("blocking samsung driver match\n");
    args->ret = (unsigned long)NULL;
    args->skip_origin = true;
  }
}

static long inline_hook_hid_gets_squirk_init(const char *args,
                                             const char *event,
                                             void *__user reserved) {
  // Hook Quirk Lookup
  lookup_name(hid_match_id);
  lookup_name(hid_lookup_quirk);
  hook_func(hid_lookup_quirk, 1, before_hid_lookup_quirk, 0, 0);

  // Hook Device Match
  lookup_name(hid_match_device);
  hook_func(hid_match_device, 2, before_hid_match_device, 0, 0);

  return 0;
}

static long inline_hook_hid_gets_squirk_exit(void *__user reserved) {
  unhook_func(hid_match_device);
  unhook_func(hid_lookup_quirk);
  unhook_func(hid_match_id);

  return 0;
}

KPM_INIT(inline_hook_hid_gets_squirk_init);
KPM_EXIT(inline_hook_hid_gets_squirk_exit);
