#!/bin/sh

INC_DIR=/usr/include
LIB_DIR=/usr/lib

cp -v bin/libmarray.so "${LIB_DIR}"
cp -v src/m_array.h "${INC_DIR}"

