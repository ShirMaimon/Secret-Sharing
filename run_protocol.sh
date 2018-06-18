#! /bin/bash
for i in `seq $1 1 $2`;
do
	./secret_sharing -partyID ${i} -partiesNumber ${3} -inputFile ${4} -partiesFile ${6} -fieldType ${7} &
	echo "Running $i"
done
