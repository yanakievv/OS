#!/bin/bash

printf "<table>\n"

usernames=($(cat /etc/passwd))

length="${#usernames[@]}"

i=0

while [ $i -lt $length ]; 
do
	username=$(echo "${usernames[${i}]}" | cut -d':' -f1)
	group=$(echo "${usernames[${i}]}" | cut -d':' -f4)
	shell=$(echo "${usernames[${i}]}" | cut -d':' -f7)
	gecko=$(echo "${usernames[${i}]}" | cut -d':' -f6)
	
	printf "\t<tr>\n"
	printf "\t\t<th>%s</th>\n" "${username}"
	printf "\t\t<th>%s</th>\n" "${group}"
	printf "\t\t<th>%s</th>\n" "${shell}"
	printf "\t\t<th>%s</th>\n" "${gecko}"
	printf "\t</tr>\n"

	i=$(expr ${i} + 1)
done

printf "</table>\n"
