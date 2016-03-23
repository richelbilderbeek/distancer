#!/bin/bash
cd cpp
qmake distancer_exe.pro
make release
./distancer_exe
