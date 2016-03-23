#!/bin/bash
cd cpp
qmake distancer_exe.pro
make debug
./distancer_exe

qmake distancer_exe.pro
make release
./distancer_exe

qmake distancer_test.pro
make debug
./distancer_test

qmake distancer_test.pro
make release
./distancer_test
