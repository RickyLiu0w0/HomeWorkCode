#!/usr/bin
# 用于与服务器的文件同步功能 server -> local

dest_dir="./test"
src_dir="~/test"
password="XXX"
host_name="root"
ip="XXX.XXX.XXX.XXX"

function mkdirHelp(){
	local dir=$1 # bash 变量默认全局变量
	if [[ ! -e $dir ]]
	then
		mkdirHelp ${dir%/*}
		echo "mkdir $dir"
		mkdir $dir
	else
		echo "$dir exists"
	fi
}

function deldirHelp() {
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
	mkdir $dest_dir
fi

cp record.sh ${dest_dir}/.record.sh
cp scpHelp.exp ${dest_dir}/.scpHelp.exp
cd $dest_dir

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

	expect  {
		"~#" { send "cd ${src_dir}\r"; exp_continue}
		"*${src_dir}#" { send "bash .record.sh \r"}
	}

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

while read line
do
	file_n=$line
	read data_n
	
	if grep -q $file_n ".record_o.txt"
	then
		raw=$(find ./ -name .record_o.txt -exec grep -n  $file_n {} \;)
		raw=${raw%:*}
		# echo $raw
		let "raw=$raw + 1 "
		# echo $raw
		data_o=$(sed -n ${raw}p .record_o.txt)
		# file_n=${file_n/./${src_dir}}

		if [[ $data_n > $data_o ]]
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
while read line 
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

mv .record_n.txt .record_o.txt
rm .record.sh .scpHelp.exp
echo DONE!!!
