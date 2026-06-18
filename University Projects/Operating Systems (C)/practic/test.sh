#!/bin/bash

LINES=0
COUNT=0

find $1 -type f -name "*.c" | while read FILE
do
	LINES=$(wc -l $FILE | awk '{print $1}')
	if [ $LINES -gt 500 ]
	then
		echo "$FILE"
		COUNT=$((COUNT+1))
		if [ $COUNT -eq 2 ]
		then
			break
		fi
	fi
done
