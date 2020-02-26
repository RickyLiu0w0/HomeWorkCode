#!/bin/bash
# test

# exec 2>&1-
# exec >output.log 2>&1 # exec 命令是全脚本有效

time=$(date "+%Y-%m-%d %H:%M:%S")
echo "************** ${time} *****************"

function update(){
	# echo $1
	# echo $2
	if [[ ! -e $2 ]]
	then
		`cp $1 $2`
		echo "${2} has been created."
	else
		if [[ $1 -nt $2 ]]
		then
			`cp $1 $2`
			echo "${2} has been updated."
		fi
	fi

}

function delete(){

	for element in `ls $2`
	do
		src_dir_or_file=$1"/"${element}
		dest_dir_or_file=$2"/"${element}
		if [[ -d $dest_dir_or_file ]]
		then
			# if [[ ! -s $dest_dir_or_file ]]
			if [[ "`ls -A $dest_dir_or_file`" = "" ]]
			then
				`rm -r $dest_dir_or_file`
				echo "Dir ${dest_dir_or_file} han been deleted."
			else
				delete $src_dir_or_file $dest_dir_or_file
			fi
		else
			if [[ ! -e $src_dir_or_file ]]
			then
				`rm $dest_dir_or_file`
				echo "File ${dest_dir_or_file} han been deleted."
			fi
		fi
	done
}

function getdir(){

	if [[ ! -e $2 ]]
	then
		echo "File not exits, I will create it"
		`mkdir $2`
	fi

	for element in `ls $1` 
	do 
		src_dir_or_file=$1"/"${element}
		dest_dir_or_file=$2"/"${element}
		if [[ -d $src_dir_or_file ]]
		then 
			if [[ ! -e $dest_dir_or_file ]]
			then
				`mkdir $dest_dir_or_file`
			fi
			getdir $src_dir_or_file $dest_dir_or_file
		else
			# $element 是单纯文件名
			# $dir_or_file 是相对路径
			# echo $src_dir_or_file
			update $src_dir_or_file $dest_dir_or_file
		fi
	done

	delete $1 $2
}



src_dir='../Algorithms'
dest_dir='/Users/rickyliu/Documents/Algorithms'

getdir $src_dir $dest_dir

echo -e "********************  E O F  ***********************\n"
exit 0