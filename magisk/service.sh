#!/system/bin/sh

VENDOR_ID=04E8
DEVICE_ID=7021
DEV_DIR=/sys/bus/hid/devices/*:$VENDOR_ID:$DEVICE_ID*/
IGNORE_PARAM=/sys/module/hid/parameters/ignore_special_drivers
LOG="[samsung_kbd_override]"

# Wait Boot
while [ "$(getprop sys.boot_completed)" != "1" ]; do
  sleep 1
done

# Loop Service
while sleep 1; do
  if [ ! -d $DEV_DIR ]; then
    continue
  fi

  if [ ! -d $DEV_DIR/driver ]; then
    if [ "$(cat $IGNORE_PARAM)" = "0" ]; then
      echo "$LOG driver unbound -> ignoring special drivers"
      echo "1" > $IGNORE_PARAM
    fi
    else
    if [ "$(cat $IGNORE_PARAM)" = "1" ]; then
      echo "$LOG driver bound -> restoring special drivers"
      echo "0" > $IGNORE_PARAM
    fi
  fi
done

