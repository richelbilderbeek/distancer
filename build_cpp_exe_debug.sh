#!/bin/bash
cd cpp
qmake distancer_exe.pro
make debug
./distancer_exe
