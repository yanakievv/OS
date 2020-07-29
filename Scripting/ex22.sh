#!/bin/bash


find "${1}" -type l | xargs -I{} file {} | grep -v 'broken' | awk '{print $1, "->", $5}'
find "${1}" -type l | xargs -I{} file {} | grep 'broken' | awk 'END {print "Broken symlinks:", NR}'
