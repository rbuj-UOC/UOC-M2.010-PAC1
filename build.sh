#!/bin/bash
./autogen.sh && CFLAGS="-g -O -D_FORTIFY_SOURCE=2 -Wall -Wextra -Wconversion -Wunused-parameter -Wendif-labels -Wformat=2 -Winit-self -Wswitch-enum -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes -Wredundant-decls -Wnested-externs -Wundef -Wformat-security" ./configure && make V=1
