#!/bin/bash

[ $(id -u) -eq 0 ] || exit 0

ps=$(mktemp)
users=$(mktemp)
foo="${1}"

ps -e -o user=,pid=,etimes= | grep -v '^_' | sort -t' ' -k1 > "${ps}"
ps -e -o user= | grep -v '^_' | uniq  > "${users}"

foo_ps_count=$(awk -v "var=${foo}" '{ if ($1 == var) ++cnt } END {print cnt}' "${ps}")

while read i; do
	user_ps_count=$(awk -v "var=${i}" '{ if ($1 == var) ++cnt} END {print cnt}' "${ps}")
	if $(expr "${user_ps_count}" >  "${foo_ps_count}"); then
		echo "${i}"
	fi
done < "${users}"

AVG=$(awk '{total += $3} END {print int(total/NR)}' "${ps}")

echo "${AVG}"

while read usr pid etimes; do
	if [ "${etimes}" -gt $( echo "${AVG} * 2" | bc )  ]; then
		echo "${pid}"
	fi
done < "${ps}"
