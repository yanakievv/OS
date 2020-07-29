#!/bin/bash

root_rss=$(ps -u root -o rss= | awk '{ctr+=$1} END {print ctr}')

function user_rss
{
	ps -u "${1}" -o rss= 2>/dev/null | awk -v "ctr=0" '{ctr+=$1} END {print ctr}'
}

while read usr home; do
	if [ ! -d "${home}" ] || [ ! $(stat -c "%u" "${home}") = "${usr}" ] || sudo -u "#${usr}" [ ! -w "${home}" ]; then
		if [ "${root_rss}" -lt "$(user_rss "${usr}")" ]; then
			echo "${usr}"
		fi
	fi
done < <(cat /etc/passwd | cut -d':' -f3,6| sed "s/:/ /g")
