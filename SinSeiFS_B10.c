#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdbool.h>



#define MKDIR_STATUS 1

#define cak 0.5
#define MKNOD_STATUS 2
#define wenak 21
#define RMDIR_STATUS 3
#define wokek 39
#define REMOVE_STATUS 4
#define READDR_STATUS 5
#define RENAME_STATUS 6
#define TRUNCATE_STATUS 7
#define WRITE_STATUS 8
#define READ_STATUS 9
#define OPEN_STATUS 10



static  const  char * dirpath = "/home/fitraharie/Downloads";

char AtoZ[10] = "AtoZ_";

char encv2[10] = "RX_";

static int lastCommand = 0;

char *atbash(char* str)
{
	int i;
	for(i=0; i<strlen(str); i++) {
		if(str[i] >= 'A' && str[i] <= 'Z') str[i] = 'Z' + 'A' - str[i];
		if(str[i] >= 'a' && str[i] <= 'z') str[i] = 'z' + 'a' - str[i];
	}
	return str;
}
void writeWarning(char * str)
{
	FILE * logFile = fopen("/home/fitraharie/SinSei.log", "a");

	time_t rawtime;

	struct tm * timeinfo;

	time ( &rawtime );

	timeinfo = localtime (&rawtime);

	fprintf(logFile, "WARNING::%d%d%d-%d:%d:%d::%s\n", timeinfo->tm_year+1900, timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, str);
	fclose(logFile);
}
void rot13(char *start){
    int i, len = strlen(start);
    for (i=0; i<len; i++)
    {
        if( (*(start+i)>='a' && *(start+i)<'n') || (*(start+i)>='A' && *(start+i)<'N') )
            *(start + i) += 13;
        else if ( (*(start+i)>'m' && *(start+i)<'z') || (*(start+i)>'M' && *(start+i)<'Z') )
            *(start +i) -= 13;
    }
}
void writeInfo(char * str)
{
	FILE * logFile = fopen("/home/fitraharie/SinSei.log", "a");

	time_t rawtime;

	struct tm * timeinfo;

	time ( &rawtime );

	timeinfo = localtime (&rawtime);

	fprintf(logFile, "INFO::%d%d%d-%d:%d:%d::%s\n", timeinfo->tm_year+1900, timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, str);

	fclose(logFile);
}

int encrFull(char *str)
{
	int ans;
	char *fi = strtok(str, "/");

	char *sc = strtok(NULL, "/");

	ans = 0;

	while(sc)

	{
		char sub[1024];

		substring(fi, sub, 0, 5);

		if(!strcmp(sub, "AtoZ_")) ans=1;

		fi = sc;

		sc = strtok(NULL, "/");
		
	}
	return ans;
}


void hasilenkripWithLength(char* enc, int length) {

	if(strcmp(enc, ".") == 0 || strcmp(enc, "..") == 0)return;

	for(int i = length; i >= 0; i--)
	{
		if(enc[i]=='/')break;

		if(enc[i]=='.')
		{
			length = i;
			break;
		}
	}

	int start = 0;

	for(int i = 0; i < length; i++)
	{
		if(enc[i] == '/')
		{
			start = i+1;
			break;
		}
	}

    for ( int i = start; i < length; i++) 
	{
		if(enc[i]=='/')continue;
		for(i=0; i<strlen(enc); i++) 
		{
			if(enc[i] >= 'A' && enc[i] <= 'Z') enc[i] = 'Z' + 'A' - enc[i];
			if(enc[i] >= 'a' && enc[i] <= 'z') enc[i] = 'z' + 'a' - enc[i];
		}
        
    }
}

void decription1WithLength(char * enc, int length){
	if(strcmp(enc, ".") == 0 || strcmp(enc, "..") == 0)return;
	if(strstr(enc, "/") == NULL)return;
	for(int i = length; i >= 0; i--){
		if(enc[i]=='/')break;
		if(enc[i]=='.'){
			length = i;
			break;
		}
	}
	int start = length;
	for(int i = 0; i < length; i++){
		if(enc[i] == '/'){
			start = i+1;
			break;
		}
	}
    for ( int i = start; i < length; i++) {
		if(enc[i]=='/')continue;
		for(i=0; i<strlen(enc); i++) 
		{
			if(enc[i] >= 'A' && enc[i] <= 'Z') enc[i] = 'Z' + 'A' - enc[i];
			if(enc[i] >= 'a' && enc[i] <= 'z') enc[i] = 'z' + 'a' - enc[i];
		}
    }
}

void encription2(char * path){
	FILE * file = fopen(path, "rb");
	int count = 0;
	char topath[1000];
	sprintf(topath, "%s.%03d", path, count);
	void * buffer = malloc(1024);
	while(1){
		size_t readSize = fread(buffer, 1, 1024, file);
		if(readSize == 0)break;
		FILE * op = fopen(topath, "w");
		fwrite(buffer, 1, readSize, op);
		fclose(op);
		count++;
		sprintf(topath, "%s.%03d", path, count);
	}
	free(buffer);
	fclose(file);
	remove(path);
}

void decription2(char * path){
	FILE * check = fopen(path, "r");
	if(check != NULL)return;
	FILE * file = fopen(path, "w");
	int count = 0;
	char topath[1000];
	sprintf(topath, "%s.%03d", path, count);
	void * buffer = malloc(1024);
	while(1){
		FILE * op = fopen(topath, "rb");
		if(op == NULL)break;
		size_t readSize = fread(buffer, 1, 1024, op);
		fwrite(buffer, 1, readSize, file);
		fclose(op);
		remove(topath);
		count++;
		sprintf(topath, "%s.%03d", path, count);
	}
	free(buffer);
	fclose(file);
}
//rekursif
void encrypt2Directory(char * dir)
{
	DIR *dp;

	struct dirent *de;

	dp = opendir(dir);

	if (dp == NULL)
		return;
	char dirPath[1000];

	char filePath[1000];

	while ((de = readdir(dp)) != NULL) 
	{
		if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)continue;
		if(de->d_type == DT_DIR){
			sprintf(dirPath, "%s/%s", dir, de->d_name);
			encrypt2Directory(dirPath);
		}else if(de->d_type == DT_REG){
			sprintf(filePath, "%s/%s", dir, de->d_name);
			encription2(filePath);
		}
	}
	closedir(dp);
}

void decrypt2Directory(char * dir){
	DIR *dp;
	struct dirent *de;
	dp = opendir(dir);
	if (dp == NULL)
		return;
	char dirPath[1000];
	char filePath[1000];
	while ((de = readdir(dp)) != NULL) 
	{
		if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)continue;

		if(de->d_type == DT_DIR)
		{
			sprintf(dirPath, "%s/%s", dir, de->d_name);
			decrypt2Directory(dirPath);
		}
		else if(de->d_type == DT_REG)
		{
			sprintf(filePath, "%s/%s", dir, de->d_name);
			filePath[strlen(filePath)-4] = '\0';
			decription2(filePath);
		}
	}
	closedir(dp);
}

void hasilenkrip(char* enc) 
{
	hasilenkripWithLength(enc, strlen(enc));
}


void decription1(char* enc)
{
	decription1WithLength(enc, strlen(enc));
}

static  int  xmp_getattr(const char *path, struct stat *stbuf)
{

	char * AtoZPtr = strstr(path, AtoZ);

	if(lastCommand == MKNOD_STATUS || lastCommand == MKDIR_STATUS)
	{

	}
	else
	{
		if(AtoZPtr != NULL)
			decription1(AtoZPtr);
	}

	printf("DEBUG getattr %d %s\n", lastCommand, path);

	char * enc2Ptr = strstr(path, encv2);

	int woke;

	char fpath[1000];

	sprintf(fpath,"%s%s", dirpath, path);

	printf("%s\n", fpath);

	woke = lstat(fpath, stbuf);
	if (woke == -1)
	{
		if(enc2Ptr == NULL)
		{
			return -errno;
		}
		else
		{
			if(strstr(enc2Ptr, "/") == NULL)
			{
				return -errno;
			}
			else
			{
				sprintf(fpath,"%s%s.000", dirpath, path);

				lstat(fpath, stbuf);

				int count = 0;

				struct stat st;

				int sizeCount = 0;

				while(1)
				{
					if(stat(fpath, &st) < 0)
					{
						break;
					}
					count++;

					sprintf(fpath, "%s%s.%03d", dirpath, path, count);

					sizeCount += st.st_size;
				}

				stbuf->st_size = sizeCount;

				return 0;
			}
		}
	}
	printf("%d\n", woke);
	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{

	printf("DEBUGGING %s\n", path);

	char * AtoZPtr = strstr(path, AtoZ);

	if(AtoZPtr != NULL){
		decription1(AtoZPtr);
	}
		
	char * enc2Ptr = strstr(path, encv2);

	printf("\n\nDEBUG readdir\n\n");

	char fpath[1000];

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	} 
	else
	{
		sprintf(fpath, "%s%s", dirpath, path);
	} 

	int woke = 0;

	DIR *dp;

	struct dirent *de;

	(void) offset;

	(void) fi;

	dp = opendir(fpath);

	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) 
	{
		struct stat st;

		memset(&st, 0, sizeof(st));

		st.st_ino = de->d_ino;

		st.st_mode = de->d_type << 12;

		if(enc2Ptr != NULL)
		{

			if(de->d_type == DT_REG )
			{
				if(strcmp(de->d_name+(strlen(de->d_name)-4), ".000") == 0)
				{
					de->d_name[strlen(de->d_name)-4] = '\0';

					woke = (filler(buf, de->d_name, &st, 0));
				}
			}
			else
			{
				woke = (filler(buf, de->d_name, &st, 0));
			}
		}
		else
		{
			if(AtoZPtr != NULL)
				hasilenkrip(de->d_name);

			woke = (filler(buf, de->d_name, &st, 0));
		}

		if(woke!=0) break;
	}

	closedir(dp);

	lastCommand = READDR_STATUS;

	return 0;
}

static int xmp_mkdir(const char *path, mode_t mode){

	lastCommand = MKDIR_STATUS;

	printf("\n\nDEBUG mkdir %s\n\n", path);

	char * AtoZPtr = strstr(path, AtoZ);

	if(AtoZPtr != NULL)
	{
		int length = strlen(AtoZPtr);

		for(int i = length; i >= 0; i--)
		{
			if(AtoZPtr[i] == '/')
			{
				length = i;
				break;
			}
		}

		decription1WithLength(AtoZPtr, length);
	}

	char fpath[1000];

	sprintf(fpath, "%s%s",dirpath,path);

	printf("%s\n", fpath);

	int woke;

	woke = mkdir(fpath, mode);

	char str[100];

	sprintf(str, "MKDIR::%s", path);

	writeInfo(str);

	if (woke == -1)
		return -errno;
	return 0;
}

static int xmp_mknod(const char *path, mode_t mode, dev_t rdev){

	lastCommand = MKNOD_STATUS;

	char * AtoZPtr = strstr(path, AtoZ);

	if(AtoZPtr != NULL)
	{
		int length = strlen(AtoZPtr);

		printf("%d\n", length);

		for(int i = length; i >= 0; i--)
		{
			if(AtoZPtr[i] == '/')
			{
				length = i;
				break;
			}
		}

		printf("%d\n", length);

		decription1WithLength(AtoZPtr, length);
	}

	printf("\n\nDEBUG mknod %s\n\n", path);

	char fpath[1000];
	
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else 
	{
		sprintf(fpath, "%s%s",dirpath,path);
	}
	int woke;

	if (S_ISREG(mode)) 
	{
		woke = open(fpath, O_CREAT | O_EXCL | O_WRONLY, mode);
		if (woke >= 0)
			woke = close(woke);
	} 
	else if (S_ISFIFO(mode))
		woke = mkfifo(fpath, mode);
	else
		woke = mknod(fpath, mode, rdev);

	char str[100];

	sprintf(str, "CREATE::%s", path);
	writeInfo(str);

	if (woke == -1)
		return -errno;

	return 0;
}

static int xmp_unlink(const char *path) 
{

	char * AtoZPtr = strstr(path, AtoZ);

	if(AtoZPtr != NULL)
	{
		decription1(AtoZPtr);
	}

	printf("\n\nDEBUG unlink\n\n");

	char fpath[1000];

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;

		sprintf(fpath,"%s",path);
	} 
	else
	{
		sprintf(fpath, "%s%s",dirpath,path);
	}

	int woke;

	char str[100];

	sprintf(str, "REMOVE::%s", path);

	writeWarning(str);

	woke = unlink(fpath);

	if (woke == -1)
		return -errno;
	lastCommand = REMOVE_STATUS;
	return 0;
}

static int xmp_rmdir(const char *path) 
{
	lastCommand = RMDIR_STATUS;

	char * AtoZPtr = strstr(path, AtoZ);

	if(AtoZPtr != NULL)
		decription1(AtoZPtr);

	printf("\n\nDEBUG rmdir\n\n");

	char fpath[1000];

	sprintf(fpath, "%s%s",dirpath,path);

	int woke;

	woke = rmdir(fpath);

	char str[100];

	sprintf(str, "RMDIR::%s", path);

	writeWarning(str);

	if (woke == -1)
		return -errno;
	return 0;
}

static int xmp_rename(const char * from, const char * to) 
{
	lastCommand = RENAME_STATUS;

	char * encrFrom = strstr(from, encv2);

	char * encrTo = strstr(to, encv2);

	char * encrFrom1 = strstr(from, AtoZ);

	char * encrTo1 = strstr(to, AtoZ);

	printf("\n\nDEBUG rename\n\n");

	char ffrom[1000];

	char fto[1000];

	char ffrom1[1000];

	char fto1[1000];

	sprintf(ffrom, "%s%s",dirpath, from);

	sprintf(fto, "%s%s",dirpath, to);

	int woke;

	int dirIndex = 0;

	int flag = 0;

	int length = strlen(fto);

	for(int i = length; i >= 0; i--)
	{

		if(fto[i] == '/')
		{
			dirIndex = i;
			flag= i;
			break;
		}
	}

	char dir[1000];

	char dir1[1000];

	strncpy(dir, fto, dirIndex);

	strncpy(dir1, fto1, flag);

	pid_t id = fork();

	if(id)
	{
		wait(NULL);
	}
	else
	{
		mkdir(dir,0777);
		mkdir(dir1,0777);
	}

	woke = rename(ffrom, fto);

	char str[100];

	sprintf(str, "RENAME::%s::%s", from, to);

	writeInfo(str);

	if (woke == -1)
		return -errno;
	else
	{
		if(encrFrom == NULL && encrTo != NULL)
		{
			encrypt2Directory(fto);
		}
		else if(encrFrom1 == NULL && encrTo1 != NULL)
		{
			encrypt2Directory(fto1);
		}
		else if(encrFrom != NULL && encrTo == NULL)
		{
			decrypt2Directory(fto);
		}
		else if(encrFrom1 != NULL && encrTo1 == NULL)
		{
			decrypt2Directory(fto1);
		}
	}

	return 0;
}

static int xmp_truncate(const char *path, off_t size) 
{
	lastCommand = TRUNCATE_STATUS;

	printf("\n\nDEBUG truncate\n\n");

	char * AtoZPtr = strstr(path, AtoZ);

	if(AtoZPtr != NULL)
		decription1(AtoZPtr);

	char fpath[1000];

	sprintf(fpath, "%s%s",dirpath,path);

	int woke;

	woke = truncate(fpath, size);

	if (woke == -1)
		return -errno;
	return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{

	char * AtoZPtr = strstr(path, AtoZ);

	char * enc2Ptr = strstr(path, encv2);

	if(lastCommand == MKNOD_STATUS)
	{
		if(AtoZPtr != NULL)
		{
			int length = strlen(AtoZPtr);

			for(int i = length; i >= 0; i--)
			{
				if(AtoZPtr[i] == '/')
				{
					length = i;
					break;
				}
			}
			decription1WithLength(AtoZPtr, length);
		}
	}else
	{

		if(AtoZPtr != NULL)
			decription1(AtoZPtr);
	}
	printf("\n\nDEBUG open %d %s\n\n", lastCommand, path);

	char fpath[1000];

	if(enc2Ptr != NULL)
	{
		sprintf(fpath, "%s%s.000",dirpath,path);
	}
	else
	{
		sprintf(fpath, "%s%s",dirpath,path);
	}

	printf("%s\n", fpath);

	int woke;

	woke = open(fpath, fi->flags);

	if (woke == -1)
		return -errno;
	close(woke);
	return 0;
}

static int xmp_read(const char * path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	
	char * AtoZPtr = strstr(path, AtoZ);

	if(lastCommand == MKNOD_STATUS)
	{
		if(AtoZPtr != NULL)
		{
			int length = strlen(AtoZPtr);

			for(int i = length; i >= 0; i--)
			{
				if(AtoZPtr[i] == '/')
				{
					length = i;
					break;
				}
			}

			decription1WithLength(AtoZPtr, length);
		}
	}
	else
	{
		if(AtoZPtr != NULL)
			decription1(AtoZPtr);
	}

	lastCommand = READ_STATUS;

	printf("\n\nDEBUG read %s\n\n", path);

	char fpath[1000];

	int fd;

	int woke = 0;

	(void) fi;

	sprintf(fpath, "%s%s",dirpath,path);
	
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	woke = pread(fd, buf, size, offset);

	if (woke == -1)
		woke = -errno;
	close(fd);
	return woke;
}

static int xmp_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) 
{
	
	char * AtoZPtr = strstr(path, AtoZ);
	
	if(lastCommand == MKNOD_STATUS)
	{
		if(AtoZPtr != NULL)
		{
			int length = strlen(AtoZPtr);

			for(int i = length; i >= 0; i--)
			{
				if(AtoZPtr[i] == '/')
				{
					length = i;
					break;
				}
			}
			decription1WithLength(AtoZPtr, length);
		}
	}else
	{
		if(AtoZPtr != NULL)
			decription1(AtoZPtr);
	}

	lastCommand = WRITE_STATUS;

	printf("\n\nDEBUG write %s\n\n", path);
	
	char fpath[1000];

	sprintf(fpath, "%s%s", dirpath, path);

	int fd;

	int woke;

	(void) fi;

	fd = open(fpath, O_WRONLY);
	
	if (fd == -1)
		return -errno;

	char str[100];

	sprintf(str, "WRITE::%s", path);

	writeInfo(str);

	woke = pwrite(fd, buf, size, offset);

	if (woke == -1)
		woke = -errno;
	close(fd);
	return woke;
}


static struct fuse_operations xmp_oper = 
{

	.rmdir = xmp_rmdir,
	.rename = xmp_rename,
	.truncate = xmp_truncate,
	.mkdir = xmp_mkdir,
	.mknod = xmp_mknod,
	.open = xmp_open,
	.read = xmp_read,
	.write = xmp_write,
	.getattr = xmp_getattr,
	.readdir = xmp_readdir,
	.read = xmp_read,
	.unlink = xmp_unlink,
	

};

int  main(int  argc, char *argv[])
{
	umask(0);

	return fuse_main(argc, argv, &xmp_oper, NULL);
}
