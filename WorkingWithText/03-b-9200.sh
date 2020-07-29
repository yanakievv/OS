#!/bin/bash

sizeNfile=($(du /etc 2>/dev/null | sort -n | tail -2 | head -1 ))
perm=$(stat "${sizeNfile[1]}" -c %a)

find . -mindepth 1 -perm "${perm}" 



