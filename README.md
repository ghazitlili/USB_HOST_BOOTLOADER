# USB_HOST_BOOTLOADER


hexdump led_blink.bin

printf '\xae\x69\x0f\x75' | dd of=led_blink.bin bs=1 seek=3092 count=4 conv=notrunc
