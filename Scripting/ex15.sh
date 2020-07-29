#!/bin/bash

if [ $(id -u) -eq 0 ]; then
	exit 0
fi

while read usr home; do
	if [ ! -d "${home}" ] || sudo -u "${usr}" [ ! -w "${home}" ]; then
		echo "${usr}"
	fi
done < <(cat /etc/passwd | awk -F : '{print $1,$6}')

