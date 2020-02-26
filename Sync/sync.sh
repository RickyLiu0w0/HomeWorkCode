#!/bin/bash
# 本地同步文件脚本(空文件夹不会被同步)

# exec 2>&1-
# exec >output.log 2>&1 # exec 命令是全脚本有效

time=$(date "+%Y-%m-%d %H:%M:%S")
echo "************** ${time} *****************"

function update(){
	# 根更新文件的函数
	# echo $1
	# echo $2
	if [[ ! -e $2 ]]
	then
		`cp $1 $2` # 文件为新添加，直接复制过来
		echo "${2} has been created."
	else
		if [[ $1 -nt $2 ]]
		then
			`cp $1 $2` # 文件陈旧，需要更新
			echo "${2} has been updated."
		fi
	fi

}

function delete(){
	# 由于本脚本没有类似于git的跟踪功能，所以源目标发生删除操作的时候，需要反向检查
	for element in `ls $2`
	do
		src_dir_or_file=$1"/"${element}
		dest_dir_or_file=$2"/"${element}
		if [[ -d $dest_dir_or_file ]]
		then # 此时 $dest_dir_or_file 为文件夹
			# if [[ ! -s $dest_dir_or_file ]]
			if [[ "`ls -A $dest_dir_or_file`" = "" ]] # 目标文件夹为空，直接删掉
			then
				`rm -r $dest_dir_or_file`
				echo "Dir ${dest_dir_or_file} han been deleted."
			else # 否则查看里面的文件在源目标是否还存在
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

	if [[ ! -e $2 ]] # 初始化同步文件夹
	then
		echo "File ${2} not exits, I will create it"
		`mkdir $2`
	fi

	for element in `ls $1` 
	do 
		src_dir_or_file=$1"/"${element}
		dest_dir_or_file=$2"/"${element}
		if [[ -d $src_dir_or_file ]]
		then  # 此时 $src_dir_or_file 为文件夹
			# if [[ ! -e $dest_dir_or_file  ]]
			# then
			# 	`mkdir $dest_dir_or_file`
			# fi
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



src_dir=$1
dest_dir=$2

if [[ -z $src_dir || -z $dest_dir ]]
then
	echo "usage: bash sync.sh src_path dest_path"
else
	# echo $src_dir $dest_dir
	getdir $src_dir $dest_dir
	echo "Finished!"
fi

echo -e "********************  E O F  ***********************\n"
exit 0