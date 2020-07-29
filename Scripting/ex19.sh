#!/bin/bash
if [ $# -eq 2 ]; then
	find "${1}" -type f -printf "%n %f\n" | awk -v "var=${2}" '{ if ($1 >= var) {print $2}}'
fi
if [ $# -eq 1 ]; then
	find "${1}" -type l | xargs -I{} file {} | grep 'broken' 
fi
