#!/bin/bash

if [ ! -f "${1}" ] || [ "$(find "${2}" -mindepth 1 -type f)" ]; then
	printf "Usage: bash ./ex26.sh <textfile> <empty dir>.\n"
	exit 1
fi

input="${1}"
dir="${2}"

names=$(mktemp)

cat "${input}" | sed -e 's/://g'  | awk  ' /^./ {print $1, $2}' | sort | uniq | awk -v "ctr=0" '{++ctr; print $1, $1";"ctr} END {print int(NR-1)}' > "${names}"

logfile="${dir}/logfile.txt"
touch "${logfile}"

cat "${names}" | tail +1  > "${logfile}"

cat "${logfile}" | cut -d ';' -f2 | xargs -I{} touch "${dir}"/{}.txt

i=1
while read first last; do
	cat "${input}" | egrep "${first}" | egrep "${last}" > "${dir}"/"${i}".txt 
	i="$(expr "${i}" + 1)"
done < <(cat "${names}" | cut -d ';' -f1)



