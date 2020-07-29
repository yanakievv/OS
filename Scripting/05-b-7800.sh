#!/bin/bash

echo $PATH | sed "s/[:]/\n/g" | xargs -I{} find {} -type f -executable 2> /dev/null | wc -l
