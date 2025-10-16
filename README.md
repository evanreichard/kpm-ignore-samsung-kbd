# Magisk / KernelPatch / APatch - Android Generic BT Keyboard Fix

## Description

The underlying issue is that some cheap keyboards report their USB Vendor ID as `0x04E8` and Product ID as `0x7021`, which is the
same as a Samsung Wireless Keyboard. This causes the Samsung HID driver to claim the device, which doesn't support the keyboard properly.

We implement both a KernelPatch / APatch module, as well as a Magisk module. The former is a more comprehensive fix that fully patches
out the driver inside the Linux Kernel. The latter is a Magisk module that ignores special drivers while connecting to the device.

NOTE: The KernelPatch / APatch module will only work with APatch. The Magisk module will work for both.

### APatch Installation

Install the patch by copying the `./build/sam_hid_kbd_rem.kpm` file to your device, opening APatch, and loading/installing the module.

### Magisk Installation

Install the patch by copying the `./build/MagiskSamsungKBDOverride.zip` file to your device, opening APatch or Magisk, and installing the module.

### Kernel Patch

You can also patch the kernel directly by applying the provided patch file `kernel.patch`. At the time of writing this, the patch was
applied to the [LineageOS/android_kernel_samsung_sm8250](https://github.com/LineageOS/android_kernel_samsung_sm8250/tree/8acbe9760ef02f0d044c0f0ec1bb469fa383fb07)
at hash `8acbe9760ef02f0d044c0f0ec1bb469fa383fb07`.
