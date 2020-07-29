#!/bin/bash

while read a; do
	if [[ "${a}" =~ ^[A-Za-z0-9_]((\.?)[A-Za-z0-9_-]+)*@[A-Za-z0-9]((\.?)[A-Za-z0-9-]+)*[A-Za-z0-9]$  ]]; then
		printf "Email "${a}" is correct.\n"
	else
		printf "Email "${a}" is incorrect!\n"
	fi
done <<<$(cat "${1}")
