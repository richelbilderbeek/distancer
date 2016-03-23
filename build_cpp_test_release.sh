#!/bin/bash
cd cpp
qmake distancer_test.pro
make debug
./distancer_test
