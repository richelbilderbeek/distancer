#!/bin/bash
base_filename=distancer
lyx_filename=$base_filename.lyx
pdf_filename=$base_filename.pdf

echo $base_filename
echo $pdf_filename
echo $lyx_filename

if [ -f $pdf_filename ]
then
  rm $pdf_filename
fi

lyx --export pdf2 $lyx_filename

if [ ! -f $pdf_filename ]
then
  echo "ERROR: Cannot find "$pdf_filename
  exit 1
fi
