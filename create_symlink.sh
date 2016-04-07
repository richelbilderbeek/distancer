#!/bin/bash
cd src
for filename in `ls ../../BoostGraphTutorial/BoostGraphTutorial/*`
do
  ln -s $filename
done