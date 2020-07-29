#!/bin/bash

while read a; do
	echo $a
done < <(find . | grep test)
