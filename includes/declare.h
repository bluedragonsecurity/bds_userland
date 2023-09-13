static FILE *(*orig_fopen)(const char *pathname, const char *mode);
static int (*orig_unlink)(const char *pathname);
static int (*orig_unlinkat) (int dirfd, const char *pathname, int flags);
static struct dirent *(*orig_readdir)(DIR *dir);
static struct dirent64 *(*orig_readdir64) (DIR * dir);
static FILE *(*orig_fopen64) (const char *filename, const char *mode);
static int (*orig_rmdir)(const char *pathname);

