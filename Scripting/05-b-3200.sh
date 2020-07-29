#!/bin/bash

read -p "Enter directory: " dir

if [[ dir =~ '.' ]]; then
	dir=" "
fi

find "$(pwd)/${dir}"
