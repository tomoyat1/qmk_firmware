#!/bin/sh
docker run -e keymap=tomoyat1 -e keyboard=ergodox_ez --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware
