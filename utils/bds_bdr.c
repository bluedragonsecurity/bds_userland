#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "bds_userspace_functions.h"

int main() {
	int ret = 0;

	system("kill -9 31335");
	system("killall -9 bds_daemon");
	system("/opt/bds_elf/bds_daemon");
	
	return 0;
}
