#!/bin/bash
#./autogen.sh && ./configure CFLAGS="-g -fsanitize=address -static-libasan -Wall"
 ./autogen.sh && CFLAGS="-g -O0 -fsanitize=address,leak,undefined -fno-omit-frame-pointer -fno-common -Wformat -Werror=format-security -Werror=array-bounds" LDFLAGS="-fsanitize=address,undefined,leak -fno-omit-frame-pointer -fno-common" ./configure && make V=1
