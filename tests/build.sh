#!/bin/bash
export CFLAGS="-I$HOME/.local/include"
export LDFLAGS="-L$HOME/.local/lib"
export LD_LIBRARY_PATH="$HOME/.local/lib:$LD_LIBRARY_PATH"

gcc test_check.c -o test_check $CFLAGS $LDFLAGS -lcheck

./test_check
