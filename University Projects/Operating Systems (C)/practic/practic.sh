#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar incorect de argumente."
	echo "Utilizare: $0 file1 file2 ..."
	exit 1
fi

while true
do
	echo -n "Litera: "
	read LITERA
	if [ "$LITERA" == "$" ]
	then
		break
	fi
	for FILE in $@
	do
		if file $FILE | grep -E -q "ASCII text"
		then
			NR_LINII=$(wc -l $FILE | awk '{print $1}')
			echo "Fisier: $FILE"
			echo "Linii: $NR_LINII"
			i=0
			while read LINE
			do
				i=$((i+1))
				NR_LITERE=$(echo $LINE | grep -E '[a-zA-Z]' -o | wc -l)
				echo "- linia $i: $NR_LITERE litere"
				if [ $((NR_LITERE%2)) -eq 1 ]
				then
					NR_CUV=$(echo $LINE | wc -w | awk '{print $1}')
					for j in $(seq 1 $NR_CUV)
					do
						CUV=$(echo $LINE | awk -v j="$j" '{print $j}')
						if echo $CUV | grep -E -q '[aeiouAEIOU]$'
						then
							echo $LINE | sed 's/$CUV/$CUV$LITERA/'
							break
						fi
					done
				fi
			done < $FILE
		fi
	done
done

exit 0
