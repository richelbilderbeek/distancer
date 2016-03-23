#!/bin/bash
for filename in `find . -name *.cpp`; do gcov-5 $filename; done

# Display gcov files
for filename in `find . -name *.gcov`; do cat $filename; done