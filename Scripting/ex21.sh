#!/bin/bash

function get_user_RSS {
	ps -u "${1}" -o rss= | awk '{cnt+=$1} END {print cnt}'

}

function get_user_AVG_RSS {
	ps -u "${1}" -o rss= | awk '{avg+=$1} END {print int(avg/NR)}'
}


if [ $(id -u) -ne 0 ]; then
	printf "Must be root.\n"
	exit 1
fi

users=$(mktemp)

ps -e -o user= | sort | uniq > "${users}"

while read user; do
	echo $(get_user_RSS "${user}")
	avg=$(get_user_AVG_RSS "${user}")
	ps -u "${user}" -o pid=,rss= | awk -v "foo=${avg}" '{ if ($2 > 2*foo) {print "PID:", $1, $2, foo} }'
done < "${users}"
	
