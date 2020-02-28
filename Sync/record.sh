#!/bin/bash

function getdir(){
	for element in `ls $1`
	do
		dir_or_file=$1"/"${element}
		if [[ -d $dir_or_file ]]
		then
			getdir $dir_or_file
		else
			echo $dir_or_file >> .record.txt
			stat  $dir_or_file | grep -i Modify | awk -F. '{print $1}' | awk '{print $2$3}'| awk -F- '{print $1$2$3}' | awk -F: '{print $1$2$3}' >>.record.txt
		fi
	done
}

dir='.'
if [[ -e .record.txt ]]; then
	rm .record.txt
fi
touch .record.txt
getdir $dir
echo done
