#!/usr/bin

# dir=$1
dest_dir="."
src_dir="~/test"
password="XXX"
host_name="root"
ip="XXX.XXX.XXX.XXX"

if [[ ! -e $dest_dir ]]
then
	mkdir $dest_dir
	touch record_old.txt
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

fi


