#!/bin/bash
qmake distancer_exe.pro
make debug
./distancer_exe
if [ ! -f exe_debug.txt ]
then
  echo "ERROR: Cannot find exe_debug.txt"
  exit 1
fi

qmake distancer_exe.pro
make release
./distancer_exe
if [ ! -f exe_release.txt ]
then
  echo "ERROR: Cannot find exe_release.txt"
  exit 1
fi

qmake distancer_test.pro
make debug
./distancer_test
if [ ! -f test_debug.txt ]
then
  echo "ERROR: Cannot find test_debug.txt"
  exit 1
fi

qmake distancer_test.pro
make release
./distancer_test
if [ ! -f test_release.txt ]
then
  echo "ERROR: Cannot find test_release.txt"
  exit 1
fi

lyx --export pdf2 distancer.lyx