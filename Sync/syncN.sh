#!/usr/bin

# dir=$1
dest_dir="./test"
src_dir="~/test"
password="XXX"
host_name="root"
ip="XXX.XXX.XXX.XXX"

if [[ ! -e $dest_dir ]]
then
	mkdir $dest_dir
fi

cp record.sh ${dest_dir}/record.sh
cd $dest_dir

if [[ ! -e record_o.txt ]]; then
	touch record_o.txt
fi

/usr/bin/expect << EOF # 启用 EXPECT 命令
set timeout 5
spawn scp record.sh ${host_name}@${ip}:${src_dir}/record.sh
	expect {
		"(yes/no)*" { send "yes\r"; exp_continue}
		"password" { send "${password}\r"; exp_continue}
		"No such file or directory" { send_user "error\n"; exit 1}
		 timeout { send_user "expect was timeout\n"; return }

	}
	# expect eof

spawn ssh -l ${host_name} ${ip}
	expect {
		"(yes/no)*" { send "yes\r"; exp_continue}
		"password" { send "${password}\r"}
		 timeout { puts "expect was timeout"; exit 2 }
	}

	expect  {
		"~#" { send "cd ${src_dir}\r"; exp_continue}
		"*${src_dir}#" { send "bash record.sh \r"}
	}

	expect  {
		"done" { send "exit\r"}
		timeout { send_user "error\n"; exit 2}
	}

spawn scp ${host_name}@${ip}:${src_dir}/record.txt record_n.txt
	expect {
		"(yes/no)*" { send "yes\r"; exp_continue}
		"password" { send "${password}\r"; exp_continue}
		"No such file or directory" { send_user "error"; exit 1}
		 timeout { send_user "expect was timeout\n"; exit 2 }
	}
	# expect eof
EOF

if [[ ! -e record_o.txt ]]
then
	mv record_n.txt record_o.txt
	while read line
	do
		file_o=$line
		file_o=${file_o/./${src_dir}}
		read data_o
		# echo $file_n $data_n
		/usr/bin/expect << EOF
		send_user ${file_o}
EOF

	done < record_o.txt
fi

while read line
do
	file_n=$line
	read data_n
	echo $file_n
	# echo $data_n
	
	if grep -q $file_n "record_o.txt"
	then
		raw=$(find ./ -name record_o.txt -exec grep -c  $file_n {} \;)
		echo $raw
		let "raw=$raw +1 "
		echo $raw
		data_o=$(sed -n ${raw}p record_o.txt)
		if [[ $data_n > $data_o ]]
		then
			echo new
			# update
		else
			echo same
			# do nothing
		fi
	else
		# this is a new file, update
	fi
done < record_n.txt

# check whether the old file should be deleted
