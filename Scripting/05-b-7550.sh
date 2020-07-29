#!/bin/bash

if [ $# -ne 1 ]; then
	printf "Invalid number of arguments, valid is 1.\n"
	exit 1
fi

ps -u "${1}" -o %p | sed "s/[ ]//g" | xargs -I{} kill {}

