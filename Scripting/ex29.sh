#!/bin/bash

num=10
cur_arg=1

if [ "${1}" = '-n' ] && [ $# -gt 2 ] && [[ "$2" =~ ^[0-9]+$ ]];then
	num="${2}"
	cur_arg=3
fi

num_args="$#"


while [ "${cur_arg}" -le "${num_args}" ]; do

	idf="${!cur_arg::-4}"
	
	cat "${!cur_arg}" | sort -n | tail "-${num}" | awk -v "idf=${idf}" '{
									     	printf "%s %s %s ", $1, $2, idf;

									     	for (i = 3; i <= NF; ++i) 
											{ 
												printf "%s ", $i; 
											} 

										 printf "\n";
									    }'
	cur_arg="$(expr "${cur_arg}" + 1)"
done




