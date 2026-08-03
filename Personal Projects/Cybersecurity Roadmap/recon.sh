#!/bin/bash

# ca prima sarcina, am explorat cum functioneaza dig si l-am folosit 
# sa fac o recunoastere DNS, afisand name serverele, serverele de mail, inregistrarile TXT
# si o tentativa de Zone Transfer pe fiecare NS gasit

if [ "$#" -ne 1 ]; then
    echo "Utilizare: $0 <nume_domeniu>"
    exit 1
fi

# afisam name serverele
echo -e "Name serverele:\n"
dig -t ns $1 +short

# afisam serverele de mail
echo -e "\nServerele de mail:\n"
dig -t mx $1 +short

# afisam inregistrarile txt
echo -e "\nInregistrarile TXT:\n"
dig -t txt $1 +short

# tentativa de zone transfer
echo -e "\nZone Transfer:\n"
ALL_NS=$(dig -t ns $1 +short)

for NS in $ALL_NS
do
	echo -e "\nIncercam pe $NS:\n"
	dig axfr $1 @$NS
done
