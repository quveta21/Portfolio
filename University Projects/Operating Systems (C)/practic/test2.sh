#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Error: not enough arguments."
	exit 1
fi

if [ ! -d $1 ]
then
	echo "$1 is not a directory."
	exit 1
fi

find $1 -type f -name "*.log" | while read FILE
do
	SORTED_FILE=$(mktemp)
	if sort $FILE -o $SORTED_FILE
	then
		if mv $SORTED_FILE $FILE
		then
			echo "Successfully sorted: $FILE"
		else
			echo "Error replacing: $FILE"
			rm $SORTED_FILE
		fi
	else
		echo "Error sorting: $FILE"
		rm $SORTED_FILE
	fi
done
