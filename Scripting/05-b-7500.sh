#!/bin/bash

if [ $# -ne 2 ] || [[ ! "${1}" =~ ^[0-9]+$ ]] || [[ ! "${2}" =~ ^[0-9]+$ ]]; then
	printf "The two arguments must be positive integers!\n"
	exit 1
fi	

lower="${1}"
upper=$(expr ${2} - ${1})

counter=1

number=$(( (RANDOM % ${upper}) + ${lower} ))

echo $number

while true; do
	read -p "Guess? " ans
	if [ "${ans}" -eq "${number}" ]; then
		printf "RIGHT! Guessed in ${counter} tries!\n"
		exit 0
	elif [ "${ans}" -gt "${number}" ]; then
		printf "... smaller!\n"
	else
		printf "... bigger!\n"
	fi
	counter=$(expr $counter + 1)
done

