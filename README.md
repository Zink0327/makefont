# makefont
A simple tool to DIY your own font for EOS

## What can it do?
It can convert a txt file with '.' and '*' into a C array. It'll be very convienient because you don't need to calculate the hex number by yourself.

## How to use it?
Just type this following command:
makefont example.txt font.h

NOTICE:The font structure in text MUST be continuous.

## Changelog
Feb 5 2023 v1.0 first published

Feb 7 2023 v1.1 use the 'fprintf' instead of 'hextoascii' so that it can be compiled in either c or c++



By the way, if you find that something goes wrong, please report the issue, or edit the source code by yourself and republish it, thanks.
