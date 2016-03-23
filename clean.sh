#!/bin/bash
function clean {
  rm *.o
  rm Makefile
  rm Makefile.Debug
  rm Makefile.Release
  rm *.pro.user
  rm distancer_exe
  rm distancer_test
  rm exe_debug.txt
  rm exe_release.txt
  rm test_debug.txt
  rm test_release.txt
  rm -rf debug
  rm -rf release
}

clean
cd src; clean; cd ..
cd cpp; clean; cd ..