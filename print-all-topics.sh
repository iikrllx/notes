#!/bin/sh
#
# Show all topics from all *.txt files
# Documentation files have for example:
# Темы:
# * [a-z]
# * [a-z]
# ...
#

for f in $(find . -type f -name "*.txt" -not -empty); do
	if grep 'Темы:' $f >/dev/null; then
		echo "\e[96m*** ----- $f ----- ***\e[0m"
		grep -Pzo 'Темы:\n\K\*.*\n(?:\*.*\n)*' --color $f
	fi
done
