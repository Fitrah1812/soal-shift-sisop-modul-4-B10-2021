#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>
#include<stdbool.h>

static  const  char *dirpath = "/home/fitraharie/Downloads";

unsigned long int getExt(char * input){
    int i;
    if(strcmp(input,".")==0||strcmp(input,"..")==0||input[strlen(input)-1]=='.')return strlen(input);
    else{
        for(i=strlen(input);i>=0;i--){
            if(input[i]=='/'){
                return strlen(input);
            }
            if(input[i]=='.'){
                return i;
            }
        }
    }
    
    return strlen(input);
}
int isFileExistsStats(const char *pathku){
    struct stat stats;

    stat(pathku, &stats);
    if (stats.st_mode & __S_IFREG){
        return 1;
    }
    return 0;
}
int searchEncEnd(char * input){
    int i;
    char * p=strstr(input,"AtoZ_");
    int encidx=p-input;
    for(i=encidx;i<strlen(input);i++){
        if(input[i]=='/'){
            return i+1;
        }
    }
    return strlen(input);
}

int where(char charku){
    int i;
    for(i=0;i<strlen(customalpha);i++){
        if(charku==customalpha[i]){
            return i;
        }
    }
    return -1;
}

int searchName(char * input){
    int i;

    int limit=searchEncEnd(input)-1;
    for(i=strlen(input)-1;i>=limit;i--){
        if(input[i]=='/'&& i >= limit){
            return i;
        }
    }
    return strlen(input);
}

void encrpt(char * input){
    int i;
    for(i = 0; i < strlen(input); i++) {
        if(input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = 'Z' - (input[i] - 'A');
        }
        if(input[i] >= 'a' && input[i] <= 'z') {
            input[i] = 'z' - (input[i] - 'a');
        }
    }
}
void dencrpt(char * inputasli){
    int i;
    for(i = 0; i < strlen(input); i++) {
        if(input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = 'A' - (input[i] - 'Z');
        }
        if(input[i] >= 'a' && input[i] <= 'z') {
            input[i] = 'a' - (input[i] + 'z');
        }
    }
}


void writeInfo(char *text, char* path){
    char* info = "INFO";
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char log[1000];
    sprintf(log, "[%s]::[%04d][%02d][%02d]-[%02d]:[%02d]:[%02d]::[%s]::[%s]", info, tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, text, path);
    FILE *out = fopen("/home/fitraharie/SinSeiFS.log", "a");  
    fprintf(out, "%s\n", log);  
    fclose(out);  
    return;
    
}
void writeInfo2Param(char *text, char* path, char * path2){
    char* info = "INFO";
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char log[1000];
    sprintf(log, "[%s]::[%04d][%02d][%02d]-[%02d]:[%02d]:[%02d]::[%s]::[%s]::[%s]", info, tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, text, path,path2);
    FILE *out = fopen("/home/fitraharie/SinSeiFS.log", "a");  
    fprintf(out, "%s\n", log);  
    fclose(out);  
    return;
    
}
void writeWarning(char *text, char* path){
    char* info = "WARNING";
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char log[1000];
    sprintf(log, "[%s]::[%04d][%02d][%02d]-[%02d]:[%02d]:[%02d]::[%s]::[%s]", info, tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, text, path);
    FILE *out = fopen("/home/fitraharie/SinSeiFS.log", "a");  
    fprintf(out, "%s\n", log);  
    fclose(out);  
    return;
    
}
static  int  xmp_getattr(const char *path, struct stat *stbuf){
    int res;
    char fpath[1000];
	char spath[1000];
	sprintf(spath,"%s",path);
    if(strstr(spath,"AtoZ_")){
	    dencrpt(spath);
    }
    sprintf(fpath,"%s%s",dirpath,spath);
    res = lstat(fpath, stbuf);

    if (res == -1)
        return -errno;
    return 0;
}

  
//readdir
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi){
    char fpath[1000];
	char spath[1000];
    if(strcmp(path,"/") == 0)
    {
        path=dirpath;
        sprintf(fpath,"%s",path);

    }
    else {
        
        sprintf(spath,"%s",path);
        if(strstr(spath,"AtoZ_")){
            dencrpt(spath);
        }
        sprintf(fpath,"%s%s",dirpath,spath);
    }
    int res = 0;
    DIR *dp;
    struct dirent *de;
    (void) offset;
    (void) fi;
    dp = opendir(fpath);
    if (dp == NULL)
        return -errno;
    while ((de = readdir(dp)) != NULL) {
        struct stat st;

        memset(&st, 0, sizeof(st));

        st.st_ino = de->d_ino;

        st.st_mode = de->d_type << 12;
        char buff[1000];
		sprintf(buff, "%s/%s", path,de->d_name);
        char *p=strstr(buff,"AtoZ_");
        if(p){
		    encrpt(buff);
        }
        sprintf(buff, "%s", buff+strlen(path)+1);

        res = (filler(buf, buff, &st, 0));

        if(res!=0) break;
    }
    closedir(dp);
    return 0;

}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,struct fuse_file_info *fi){
    char fpath[1000];
	char spath[1000];
    if(strcmp(path,"/") == 0||strcmp(path,".") == 0||strcmp(path,"..") == 0)
    {
        path=dirpath;
        sprintf(fpath,"%s",path);
    }
    else {
        sprintf(spath,"%s",path);
        if(strstr(spath,"AtoZ_")){
		    dencrpt(spath);
        }
        sprintf(fpath,"%s%s",dirpath,spath);
    }
    int res = 0;
    int fd = 0 ;
    (void) fi;

    fd = open(fpath, O_RDONLY);

    if (fd == -1){
        return -errno;
    }else{
        writeInfo("CAT", (char*)fpath);
    }
    res = pread(fd, buf, size, offset);

    if (res == -1)
        res = -errno;
    close(fd);

    return res;
}
static int xmp_mkdir(const char *path, mode_t mode){
	int res;
    int i;
    char jalan[1024];
    char name[1024];
    char jalan2[1024];
    if(strstr(path,"AtoZ_")){
        for(i=strlen(path);i>=0;i--){
            if(path[i]=='/'){
                break;
            }
        }
        sprintf(name,"%s",path+i);
        strcpy(jalan,"");
        strncpy(jalan,path,strlen(path)-strlen(name));
        dencrpt(jalan);
        sprintf(jalan2,"%s%s%s",dirpath,jalan,name);
    }else{
        sprintf(jalan2,"%s%s",dirpath,path);
    }
	res = mkdir((const char*)jalan2, mode);
	if (res == -1){
		return -errno;
    }else
    {
        writeInfo("MKDIR", jalan2);
    }
    

	return 0;
}
static int xmp_open(const char *path, struct fuse_file_info *fi){
	char jalan[1024];
    char jalan2[1024];
    if(strstr(path,"AtoZ_")){   
        sprintf(jalan,"%s",path);
        dencrpt(jalan);
        sprintf(jalan2,"%s%s",dirpath,jalan);
    }else{
        sprintf(jalan2,"%s%s",dirpath,path);
    }
	int res;
	res = open(path, fi->flags);
	if (res == -1){
		return -errno;
    }else{
        writeInfo("OPEN", (char*)jalan2);
    }
	close(res);
	return 0;
}

static int xmp_truncate(const char *path, off_t size){
	char jalan[1024];
    char jalan2[1024];
    if(strstr(path,"AtoZ_")){
        
        sprintf(jalan,"%s",path);
        dencrpt(jalan);
        sprintf(jalan2,"%s%s",dirpath,jalan);
    }else{
        sprintf(jalan2,"%s%s",dirpath,path);
    }
    int res;

	res = truncate(path, size);
	if (res == -1){
		return -errno;
    }{
        writeInfo("TRUNCATE", jalan2);
    }

	return 0;
}


static int xmp_unlink(const char *path){

    char jalan[1024];
    char jalan2[1024];
    if(strstr(path,"AtoZ_")){
        
        sprintf(jalan,"%s",path);
        dencrpt(jalan);
        sprintf(jalan2,"%s%s",dirpath,jalan);
    }else{
        sprintf(jalan2,"%s%s",dirpath,path);
    }
	int res;

	res = unlink(path);
	if (res == -1){
		return -errno;
    }else{
        writeWarning("REMOVE", jalan2);

    }

	return 0;
}
static int xmp_rmdir(const char *path){
    char jalan[1024];
    char jalan2[1024];
    if(strstr(path,"AtoZ_")){
        
        sprintf(jalan,"%s",path);
        dencrpt(jalan);
        sprintf(jalan2,"%s%s",dirpath,jalan);
    }else{
        sprintf(jalan2,"%s%s",dirpath,path);
    }
	int res;
	res = rmdir(jalan2);
	if (res == -1){
		return -errno;
    }else{
        writeWarning("RMDIR", jalan2);
    }

	return 0;
}
static int xmp_rename(const char *from, const char *to){
    int res,i;
    char dari[1024],ke[1024],name[1024],jalan[1024];
    sprintf(dari,"%s%s",dirpath,from);
    sprintf(ke,"%s%s",dirpath,to);
    if(strstr(dari,"AtoZ_")){
        dencrpt(dari);
        for(i=strlen(dari);i>=0;i--){
            if(dari[i]=='/'){
                break;
            }
        }
        sprintf(name,"%s",dari+i);
        strcpy(jalan,"");
        strncpy(jalan,dari,strlen(dari)-strlen(name));
        sprintf(dari,"%s%s",jalan,name);
    }
    if(strstr(ke,"AtoZ_")){
        for(i=strlen(ke);i>=0;i--){
            if(ke[i]=='/'){
                break;
            }
        }
        sprintf(name,"%s",ke+i);
        dencrpt(ke);
        strcpy(jalan,"");
        strncpy(jalan,ke,strlen(ke)-strlen(name));
        sprintf(ke,"%s%s",jalan,name);
    }
 	res = rename(dari, ke);
	if (res == -1){
		return -errno;
    }else{
        writeInfo2Param("MOVE", (char*)from,(char*)to);
    }
	return 0;
}
static int xmp_write(const char *path, const char *buf, size_t size,off_t offset, struct fuse_file_info *fi){	
    char jalan[1024];
    char jalan2[1024];
    if(strstr(path,"AtoZ_")){
        sprintf(jalan,"%s",path);
        dencrpt(jalan);
        sprintf(jalan2,"%s%s",dirpath,jalan);
    }else{
        sprintf(jalan2,"%s%s",dirpath,path);
    }

    int fd;
	int res;

	(void) fi;
	fd = open(jalan2, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1){
		res = -errno;
    }else{
        writeInfo("WRITE", jalan2);

    }

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
.getattr = xmp_getattr,
.readdir = xmp_readdir,
.read = xmp_read,
.mkdir		= xmp_mkdir,
.rmdir = xmp_rmdir,
.open = xmp_open,
.rename		= xmp_rename,
.unlink = xmp_unlink,
.truncate = xmp_truncate,
.write = xmp_write
};

int  main(int  argc, char *argv[]){
    umask(0);
    return fuse_main(argc, argv, &xmp_oper, NULL);
}