#!/bin/bash

input=$(mktemp)
max=0
min=0
cat > "${input}"

while read line; do
	if [[ "${line}" =~ ^(-?)[0-9]+$ ]]; then
		if [ "${line}" -gt "${max}" ]; then
			max="${line}"
		fi
		if [ "${line}" -lt "${min}" ]; then
			min="${line}"
		fi
	fi	
done < <(cat "${input}")
	
if [ "${max}" -eq "${min:1}" ]; then
	echo "${min}"
	echo "${max}"
else
	echo "${max}"
fi

toprint=99999
curmax=0

while read line; do
	if [[ "${line}" =~ ^-?[0-9]+$ ]]; then
		temp="${line}"
		if [ "${temp}" -lt 0 ]; then
			temp="${temp:1}"
		fi
		tempcount=0
		while [ "${temp}" -gt 0 ]; do
			k="$(expr "${temp}" % 10)"
			tempcount="$(expr "${tempcount}" + "${k}")"
			temp="$(expr "${temp}" / 10)"
		done

		if [ "${tempcount}" -ge "${curmax}" ] && [ "${line}" -lt "${toprint}" ]; then
			curmax="${tempcount}"
			toprint="${line}"
		fi
	fi

done < <(cat "${input}")

echo "${toprint}"
