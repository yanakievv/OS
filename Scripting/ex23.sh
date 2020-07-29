#!/bin/bash
find "${1}" -maxdepth 1 -type f -printf "%f\n" | grep -E  "^vmlinuz-[0-9]+\.[0-9]+\.[0-9]+-${2}$" | sort -rn | head -1
