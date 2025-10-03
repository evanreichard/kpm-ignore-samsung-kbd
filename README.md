# KernelPatch / APatch - Android Generic BT Keyboard Fix

### Description

This is a [KernelPatch](https://github.com/bmax121/KernelPatch) / [APatch](https://github.com/bmax121/APatch) module used to fix an
issue with the Samsung Galaxy Tab S7 on some kernels where a Bluetooth keyboard connects but fails to work.

The underlying issue is that some cheap keyboards report their USB Vendor ID as `0x04E8` and Product ID as `0x7021`, which is the
same as a Samsung Wireless Keyboard. This causes the Samsung HID driver to claim the device, which doesn't support the keyboard properly.

This patch blocks the Samsung driver from matching these devices and prevents custom quirks from being applied, allowing the generic HID driver to handle them instead.

### Installation

Install the patch by copying the `sam_hid_kbd_rem.kpm` file to your device, opening APatch, and loading/installing the module.

### Kernel Patch

You can also patch the kernel directly by applying the provided patch file `sam_hid_kbd_rem.patch`. At the time of writing this, the patch was
applied to the [LineageOS/android_kernel_samsung_sm8250](https://github.com/LineageOS/android_kernel_samsung_sm8250/tree/8acbe9760ef02f0d044c0f0ec1bb469fa383fb07)
at hash `8acbe9760ef02f0d044c0f0ec1bb469fa383fb07`.
