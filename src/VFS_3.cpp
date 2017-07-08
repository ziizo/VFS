//============================================================================
// Name        : 1.cpp
// Author      : Zizo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include "FBL.h"
#include "File.h"
#include "Inode.h"
#include "FAT.h"
#include "SuperBlock.h"
#include "Functions.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;




int main(int argc,char**argv) {

	/********************copy code******************/
	/*
	 * dir
	 * dir in dir
	 * file
	 *
	 * check if the file is already exist in the same directory
	 * if not
	 * create inode
	 * check file or directory
	 * set all its variables
	 * allocate the required blocks
	 * get all it's data into a buffferwrite the buffer into the data blocks allocated
	 *
	 *for files "from my system to VFS	"
	 *		cp Source Directory
	 *
	 */

	File myfile(argv[1]);
	FAT_Class fat(&myfile);
	FAT_Class::Link current;
	char*SOURCE,*DISTENATION;
	string input,sub,token,delimiter=" ",*argu_values;
	int argu_num;
	while(1){
		argu_num=0;
		getline(cin,input);
		stringstream ss(input);
		stringstream qq(input);
		while(ss>>sub)
			argu_num++;
		argu_values=new string[argu_num];
		argu_num=0;
		while(qq>>argu_values[argu_num])
			argu_num++;

		if(argu_values[0]=="cpin"){
			/*
			 *
			 * handle errors here
			 * copy multiple files in one command
			 * cpin /home/muhammad/h /
			 * cpin /home/muhammad/trial /
			 * cpin /home/muhammad/trial/file3 /
			 * cpin /home/muhammad/h/ /home/muhammad/trial /home/muhammad/trial/file3 /
			 *
			 */
			if(argu_num < 3){
				cout<<"missing argument..!"<<endl;
				continue;
			}
			else {
			for (int i = 1; i < argu_num-1; i++) {
				current=fat.cd;
				SOURCE=new char[argu_values[i].length()+1];
				strcpy(SOURCE,argu_values[i].c_str());
				struct stat path_stat;
				stat(SOURCE, &path_stat);

				DISTENATION=new char[argu_values[argu_num-1].length()+1];
				strcpy(DISTENATION,argu_values[argu_num-1].c_str());
				cd_by_path(DISTENATION,&fat);

				if(S_ISREG(path_stat.st_mode))//0 Dir 1 File
					COPY_F(SOURCE,&myfile,&fat);
				else
					COPY_D(SOURCE,&myfile,&fat);
				fat.cd=current;
			}
			}
		}
		else if(argu_values[0]=="ls"){
			if(argu_num==1){
				fat.List();
			}else{
				/*
				 * error list even if the path is wrong
				 */
				current=fat.cd;
				DISTENATION=new char[argu_values[1].length()+1];
				strcpy(DISTENATION,argu_values[1].c_str());
				cd_by_path(DISTENATION,&fat);
				fat.List();
				fat.cd=current;
//				delete[]DISTENATION;
			}
		}
		else if(input=="unmount"){
			break;
		}else{
			cout<<argu_values[0]<<" :commant not found"<<endl;
			continue;
		}
	myfile.FBL->sync_FBL();
	myfile.FIT->sync_FIT(&myfile,myfile.SuperBlock);
	}
//	cd_by_path("/",&fat);
//	COPY_D(argv[2],&myfile,&fat);
//fat.List();
//	COPY_F(argv[2],&myfile,&fat);
//	COPY_D(argv[3],&myfile,&fat);
//	fat.List();
//	myfile.FBL->sync_FBL();
//	myfile.FIT->sync_FIT(&myfile,myfile.SuperBlock);

return 0;































//
//	File myfile(argv[1]);
////	SuperBlock_Class sb;
////	FBL_Class fbl(&sb,&myfile);
////	FIT_Class fit(&sb);
//	FAT_Class fat(&myfile);
////	fat.cd=fat.root;
////	fat.CreateEntity("home",'d');
////	fat.List();
////	cout<<endl;
//
////	fat.Change_Directory("tourki1/");
//
////	cout<<argv[3]<<endl;
////	fat.DeleteWithName("ile.txt",'f');
////	fat.DeleteWithName("file.txt",'f');
////	copy_File(argv[2],argv[3],&myfile,&fat);
////	copy_File(argv[2],argv[3],&myfile,&fat);
////	fat.List();
////	fat.DeleteWithName("tourki1/",'d');
////	copy_DIR(argv[2],argv[3],&myfile,&fat);
////	COPY_D(argv[2],&myfile,&fat);
//	fat.List();
//	fat.Change_Directory("tourki1");
//	fat.List();
//	fat.Change_Directory("hamadffa");
//	fat.List();
//
////	FAT_Class::Link temp;
////	fat.cd->childern.first(temp);
////	copy_DIR_out("/home/tourki/OUT",temp,&myfile,&fat);
////	myfile.FBL->sync_FBL();
//	myfile.FIT->sync_FIT(&myfile,myfile.SuperBlock);
//	return 0;
}
