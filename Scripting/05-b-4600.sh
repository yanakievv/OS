#!/bin/bash
if ! [[ "${1}" =~ ^[-0-9]+$ ]]; then
	exit 3
elif [ "${2}" -ge "${3}" ]; then
	exit 2
elif [ "${1}" -le "${2}" ] || [ "${1}" -ge "${3}" ]; then
	exit 1
else
	exit 0
fi
