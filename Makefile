build_magisk:
	rm -f ./build/MagiskSamsungKBDOverride.zip
	cd ./magisk && zip -r ../build/MagiskSamsungKBDOverride.zip *

build_apatch:
	$(MAKE) -C ./apatch sam_hid_kbd_rem.kpm
