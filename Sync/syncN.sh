#!/usr/bin
# 用于与服务器的文件同步功能 server -> local

if [[ 4 -gt $# ]]; then
	echo usage: bash syncN.sh src_dir dest_dir host_name ip
	exit
else
	src_dir=$1
	dest_dir=$2
	host_name=$3
	ip=$4
fi

echo "Synchronizes ${host_name}@${ip}:${src_dir} -> ${dest_dir}."
echo -e "${host_name}@${ip}'s password: \c"
read -s $password
echo ""

function mkdirHelp(){
	# 递归创建文件夹
	local dir=$1 # bash 变量默认全局变量
	if [[ ! -e $dir ]]
	then
		mkdirHelp ${dir%/*}
		mkdir $dir
	fi
}

function deldirHelp() {
	# 递归删除空文件夹
	local dir=$1
	if [[ "`ls -A $dir`" = "" ]]
	then
		rm -r $dir
		echo "Dir ${dir} han been deleted."
		deldirHelp ${dir%/*}
	fi
}

if [[ ! -e $dest_dir ]]
then
	mkdir $dest_dir # 初始化文目标件夹
fi

cp record.sh ${dest_dir}/.record.sh
cp scpHelp.exp ${dest_dir}/.scpHelp.exp
cd $dest_dir # 把目标路径移入目标文件夹

if [[ ! -e .record_o.txt ]]
then
	touch .record_o.txt
fi

/usr/bin/expect << EOF # 启用 EXPECT 命令
set timeout 5
spawn scp .record.sh ${host_name}@${ip}:${src_dir}/.record.sh
	expect {
		"(yes/no)*" { send "yes\r"; exp_continue}
		"password" { send "${password}\r"; exp_continue}
		"No such file or directory" { send_user "error\n"; exit 1}
		 timeout { send_user "expect was timeout\n"; exit }

	}

spawn ssh -l ${host_name} ${ip}
	expect {
		"(yes/no)*" { send "yes\r"; exp_continue}
		"password" { send "${password}\r"}
		 timeout { puts "expect was timeout"; exit 2 }
	}

	expect "~$"
	send "cd ${src_dir}\r"

	expect "*${src_dir}$"
	send "bash .record.sh \r"
	# expect  {
	# 	"#$" { send "cd ${src_dir}\r"; exp_continue}
	# 	"*${src_dir}$" { send "bash .record.sh \r"}
	# }

	expect  {
		"done" { send "rm .record.sh\r"; send "exit\r"}
		timeout { send_user "error\n"; exit 2}
	}

	expect eof

spawn scp ${host_name}@${ip}:${src_dir}/.record.txt .record_n.txt
	expect {
		"(yes/no)*" { send "yes\r"; exp_continue}
		"password" { send "${password}\r"; exp_continue}
		"No such file or directory" { send_user "error"; exit 1}
		 timeout { send_user "expect was timeout\n"; exit 2 }
	}
	exit 0
EOF

while read line # 新添或更新文件
do
	file_n=$line
	read data_n
	
	if grep -q $file_n ".record_o.txt" # 查看源文件是否为新文件
	then
		raw=$(find ./ -name .record_o.txt -exec grep -n  $file_n {} \;)
		raw=${raw%:*}
		let "raw=$raw + 1 "
		data_o=$(sed -n ${raw}p .record_o.txt)

		if [[ $data_n > $data_o ]] # 比较文件修改日期判断是否要更新
		then
			# update
			expect .scpHelp.exp ${host_name}"@"${ip} $password ${file_n/./${src_dir}} $file_n
			echo "${file_n} has been updated."
		fi
	else
		# download
		mkdirHelp ${file_n%/*}
		expect .scpHelp.exp ${host_name}"@"${ip} $password ${file_n/./${src_dir}} $file_n
		echo "File ${file_n} has been created."
	fi
done < .record_n.txt

# check whether the old file should be deleted
while read line  # 删除目标文件中的旧文件
do
	file_o=$line
	read data_o
	if  [[ "`grep -o $file_o .record_n.txt`" = "" ]] # 记住等号空格
	then
		rm $file_o
		echo "File ${file_o} han been deleted."
		deldirHelp ${file_o%/*}
	fi
done < .record_o.txt

mv .record_n.txt .record_o.txt # 更新文件表
rm .record.sh .scpHelp.exp # 清尾工作
echo DONE!!!
