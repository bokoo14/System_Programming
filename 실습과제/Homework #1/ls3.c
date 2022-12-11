#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

void do_ls(char[]);
void dostat(char*);
void show_file_info(char*, struct stat*);
void mode_to_letters(int, char[]);
char* uid_to_name(uid_t);
char* gid_to_name(gid_t);
void dostat2(char *dirname, char *filename);

void do_time(char[]);
void do_size(char[]);

//전체 파일의 개수 출력, 전체 파일의 크기의 합 출력
int FileNum=0;
long  FileVolume=0;



int main(int argc, char* argv[]){
	int i=0;
	int n=0;
	struct dirent** name_list = NULL;
	
	if (argc==1){
		do_ls(".");
	}
	else if (!strcmp(argv[1], "-t")){
		printf("option: -t\n");
		for (i = 2; i < argc; i++) {
			//printf("%s: /n", *++argv);
			do_time(argv[i]);
		}
	}
	else if (!strcmp(argv[1], "-b")){
		printf("option: -b\n");
		for (i = 2; i < argc; i++) {
			//printf("%s: /n", *++argv);
			do_size(argv[i]);
		}
	}
	else {
		for (i = 1; i < argc; i++)
			do_ls (argv[i]);
	}
	//---------------------------------------------------
	
	printf("\n");
	printf("total file num is.. %d\n", FileNum);
	printf("total file volume is.. %ld\n", FileVolume);
	
	
    return 0;

}

void do_ls(char dirname[]){
	DIR * dir_ptr;
	struct dirent* direntp;
	if((dir_ptr=opendir(dirname))==NULL){
		fprintf(stderr, "ls3: cannot open %s \n", dirname);
	}
	else{
		
		while((direntp=readdir(dir_ptr))!=NULL){
			//printf("%s\n", direntp->d_name);
			//dostat(direntp->d_name);
			dostat2 (dirname, direntp->d_name);
			FileNum++; //파일 수
		}

		closedir(dir_ptr);
	}
}

//-----------------------------------------
void do_time(char dirname[]){
	DIR * dir_ptr;
	struct dirent* direntp;
	
	
	if((dir_ptr=opendir(dirname))==NULL){
		fprintf(stderr, "ls3: cannot open %s \n", dirname);
	}
	else{

		struct stat tmpstat[100]; //stat구조체 (마지막 수정시간, 바이트 수 ... 담겨있음)
		struct dirent* tmpdirentp[100]; //파일 이름 저장
		struct stat tt; //임시 구조체
		int kk=0;
		// 모든 
		while((direntp=readdir(dir_ptr))!=NULL){
			stat(direntp->d_name, &tmpstat[kk]); //stat함수로 stat구조체에 담기
			tmpdirentp[kk]=direntp; //dirent구조체 저장
			kk++;
			FileNum++; //파일 수 세주기
		}
		
		//시간순 정렬하기
		for (int i=0; i<FileNum-1; i++){
			for (int j=i+1; j<FileNum; j++)
			{
				if(tmpstat[i].st_mtime < tmpstat[j].st_mtime){
					tt=tmpstat[i];
					tmpstat[i]=tmpstat[j];
					tmpstat[j]=tt;
				}
			}
		}
		
		//정렬된 구조체를 출력해주기
		for (int p=0; p<FileNum; p++){
			show_file_info(tmpdirentp[p]->d_name, &tmpstat[p]); //디렉토리명
		}

		closedir(dir_ptr);
	}
}

//디렉토리 크기별 정렬 후 출력
void do_size(char dirname[]){
	DIR * dir_ptr;
	struct dirent* direntp;
	
	
	if((dir_ptr=opendir(dirname))==NULL){
		fprintf(stderr, "ls3: cannot open %s \n", dirname);
	}
	else{

		struct stat tmpstat[100]; //stat구조체 (마지막 수정시간, 바이트 수 ... 담겨있음)
		struct dirent* tmpdirentp[100]; //파일 이름 저장
		struct stat tt; //임시 구조체
		int kk=0;
		// 모든 
		while((direntp=readdir(dir_ptr))!=NULL){
			stat(direntp->d_name, &tmpstat[kk]); //stat함수로 stat구조체에 담기
			tmpdirentp[kk]=direntp; //dirent구조체 저장
			kk++;
			FileNum++; //파일 수 세주기
		}
		
		//시간순 정렬하기
		for (int i=0; i<FileNum-1; i++){
			for (int j=i+1; j<FileNum; j++)
			{
				if(tmpstat[i].st_size < tmpstat[j].st_size){
					tt=tmpstat[i];
					tmpstat[i]=tmpstat[j];
					tmpstat[j]=tt;
				}
			}
		}
		
		//정렬된 구조체를 출력해주기
		for (int p=0; p<FileNum; p++){
			show_file_info(tmpdirentp[p]->d_name, &tmpstat[p]); //디렉토리명
		}

		closedir(dir_ptr);
	}
}


//-----------------------------------------
void dostat(char *filename){
	struct stat info;
	if(stat(filename, &info)==-1)
		perror(filename);
	else
		show_file_info(filename, &info);
}

void dostat2(char *dirname, char *filename){
	struct stat info;
	char fname[256];
	strcpy (fname, dirname);
	strcat (fname, "/");
	strcat (fname, filename);
	
	if(stat(fname, &info)==-1)
		perror(fname);
	else
		show_file_info(filename, &info);
}


void show_file_info(char* filename,  struct stat* info_p){
	char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void mode_to_letters();
	char modestr[20];

	mode_to_letters(info_p->st_mode, modestr);
	printf("%s", modestr);
	printf("%4d", (int)info_p->st_nlink);
	printf("%-8s", uid_to_name(info_p->st_uid));
	printf("%-8s", gid_to_name(info_p->st_gid));
	printf("%-8ld", (long)info_p->st_size); //크기
	printf("%.12s", 4+ctime(&info_p->st_mtime)); //시간
	printf("%s \n", filename);

	FileVolume+=info_p->st_size;
}

void mode_to_letters(int mode, char str[]){
	strcpy(str, "-------------");

	if(S_ISDIR(mode)) str[0] ='d';
	if(S_ISCHR(mode)) str[0] ='c';
	if(S_ISBLK(mode)) str[0] ='b';
	
	if(mode&S_IRUSR) str[1] ='r';
	if(mode&S_IWUSR) str[2] ='w';
	if(mode&S_IXUSR) str[3] ='x';

	if(mode&S_IRGRP) str[4] ='r';
	if(mode&S_IWGRP) str[5] ='w';
       	if(mode&S_IXGRP) str[6] ='x';
       
	if(mode & S_IROTH) str[7] ='r';
	if(mode & S_IWOTH) str[8] ='w';
	if(mode & S_IXOTH) str[9] ='x';
}

char * uid_to_name(uid_t uid){
	struct passwd * getpwuid(), *pw_ptr;
	static char numstr[10];

	if((pw_ptr=getpwuid(uid))==NULL){
		sprintf(numstr, "%d", uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

char* gid_to_name (gid_t gid){
	struct group *getrid(), *grp_ptr;
	static char numstr[10];
	if((grp_ptr = getgrgid(gid))==NULL){
		sprintf(numstr, "%d", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}


