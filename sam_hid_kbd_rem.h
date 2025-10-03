/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2025 Evan Reichard. All Rights Reserved.
 */
#ifndef SAM_HID_KBD_REM_H
#define SAM_HID_KBD_REM_H

#include <hook.h>
#include <ksyms.h>
#include <ktypes.h>
#include <linux/printk.h>

#define BUS_BLUETOOTH 0x05
#define USB_VENDOR_ID_SAMSUNG_ELECTRONICS 0x04e8
#define USB_DEVICE_ID_SAMSUNG_WIRELESS_KBD 0x7021

struct device {};

struct device_driver {
  const char *name;
};

struct hid_driver {
  char *name;
};

struct hid_device_id {
  __u16 bus;
  __u16 group;
  __u32 vendor;
  __u32 product;
  unsigned long driver_data;
};

struct hid_device {
  __u16 bus;
  __u16 group;
  __u32 vendor;
  __u32 product;
  struct device dev;
};

#define HID_BLUETOOTH_DEVICE(ven, prod)                                        \
  .bus = BUS_BLUETOOTH, .vendor = (ven), .product = (prod)

#define to_hid_device(pdev) container_of(pdev, struct hid_device, dev);

#define lookup_name(func)                                                      \
  func = 0;                                                                    \
  func = (typeof(func))kallsyms_lookup_name(#func);                            \
  pr_info("kernel function %s addr: %llx\n", #func, func);                     \
  if (!func) {                                                                 \
    return -21;                                                                \
  }

#define hook_func(func, argv, before, after, udata)                            \
  if (!func) {                                                                 \
    return -22;                                                                \
  }                                                                            \
  hook_err_t hook_err_##func = hook_wrap(func, argv, before, after, udata);    \
  if (hook_err_##func) {                                                       \
    func = 0;                                                                  \
    pr_err("hook %s error: %d\n", #func, hook_err_##func);                     \
    return -23;                                                                \
  } else {                                                                     \
    pr_info("hook %s success\n", #func);                                       \
  }

#define unhook_func(func)                                                      \
  if (func && !is_bad_address(func)) {                                         \
    unhook(func);                                                              \
    func = 0;                                                                  \
  }

#endif
