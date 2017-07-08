/*
 * Functions.cpp

 *
 *  Created on: Jul 3, 2017
 *      Author: tourki
 */


#include "Functions.h"

inode_Class* touch(const char * filename,FAT_Class *FAT){
	FAT_Class::Link temp=FAT->CreateEntity(filename,'f');

	if(!temp){
		cout<<"touch: cannot create '"<<filename<<"' a file with the same name exists choose another name for the file"<<endl;
		return NULL;
		}
	else
	{
		return	&(temp->inode);
	}
}
inode_Class* mkdir(const char * filename,FAT_Class *FAT){
	inode_Class *node;
	node=&(FAT->CreateEntity(filename,'d'))->inode;
	if(!node){
		cout<<"mkdir: cannot create '"<<filename<<"' a directory with the same name exists choose another name for the directory"<<endl;
		return NULL;
		}
	else
	{
		return	node;
	}
}

void rm(const char * filename,FAT_Class *FAT){
	if(!FAT->DeleteWithName(filename,'f'))
		cout<<"rm: cannot remove ‘"<<filename<<"’: No such file"<<endl;
}

void rmdir(const char * filename,FAT_Class *FAT){
	if(!FAT->DeleteWithName(filename,'d'))
		cout<<"rmdir: cannot remove ‘"<<filename<<"’: No such directory"<<endl;
}
void ls(FAT_Class *FAT){
	FAT->List();
}
void cd(const char * filename,FAT_Class *FAT){
	FAT->Change_Directory(filename);
}
void cd_by_path(char *dir,FAT_Class *FAT){
	string sub,x=dir,token,delimiter = "/";;
	int pos = 0,count = 1;
	char *buffer;

	for (int i = 0; i < x.size(); i++)
		if (x[i] == '/') count++;

	string *cds=new string[count];
	if(x[0]=='/'){
		FAT->cd=FAT->root;
		x=x.substr(1);
//		cout<<"bade2 mn el root"<<endl;
	}
	count=0;
	while ((pos = x.find(delimiter)) != std::string::npos) {
	    token = x.substr(0, pos);
	    cds[count]=token;
	    x.erase(0, pos + delimiter.length());
	    count++;
	}
	bool flag;
	for (int i= 0;i  < count; i++) {
			buffer=new char[cds[i].length()+1];
			strcpy(buffer,cds[i].c_str());
			flag=FAT->Change_Directory(buffer);
			if(!flag){
				cout<<"No such a directory"<<endl;
			}
//			cout<<buffer<<endl;
		}
}
void copy_File(char*full_path,char*file_name,File *myfile,FAT_Class *fat){

	char *temp_path=new char[strlen(full_path)+1],*temp_name=new char[strlen(file_name)+1];

	strcpy(temp_path,full_path);
	strcpy(temp_name,file_name);

//	cout<<file_name<<endl;

	inode_Class *node=touch(file_name,fat);
	if(!node)
		return;
	strcat(temp_path,temp_name);
//	cout<<full_path<<endl;
	unsigned begin ,end;
	char* buffer;
	ifstream ifs(temp_path);

	begin=ifs.tellg();
	ifs.seekg(0,ios::end);
	end=ifs.tellg();
	ifs.seekg(0,ios::beg);
	buffer=new char[end];
	ifs.read(buffer,end);
//	fat->cd=fat->root;
	node->Number_Blocks=ceil((float)(end-begin)/myfile->SuperBlock->Data_blocksize);
	node->First_Block_Number=*myfile->FBL->get_blocks(node->Number_Blocks);

	node->write_inode(myfile,myfile->SuperBlock);
	myfile->as_write(node,buffer,end-begin);
	myfile->FIT->sync_FIT(myfile,myfile->SuperBlock);
	myfile->FBL->sync_FBL();

//	delete[] buffer;
	ifs.close();
}
void copy_DIR(char*full_path,char*DIR_name,File *myfile,FAT_Class *fat){
	char *temp_path=new char[strlen(full_path)+1],*temp_name=new char[strlen(DIR_name)+1];

	strcpy(temp_path,full_path);
	strcpy(temp_name,DIR_name);
	temp_name[strlen(temp_name)-1]='\0';
	if(!mkdir(temp_name,fat))
		return;
	cd(temp_name,fat);
	strcat(temp_path,DIR_name);//TEST THIS AS WE DIDN;T ALLOCATE ANY MEMORY
	DIR *dptr;
	struct dirent *dirp;
	string x;
	char* buffer;
	dptr = opendir(temp_path);

	while ((dirp = readdir(dptr)))
		{
			x=dirp->d_name;
			if(x[0]=='.') continue;
			buffer=new char[x.length()+1];
			strcpy(buffer,x.c_str());

			/*
			 * dirp->d_type==4 //folder
			 * dirp->d_type==8 //file
			 */

			if(dirp->d_type==4){
				strcat(buffer,"/");
				copy_DIR(temp_path,buffer,myfile,fat);
				cd("..",fat);
			}
			else if(dirp->d_type==8){
				copy_File(temp_path,buffer,myfile,fat);

			}
			delete[] buffer;
		}
//	cd("..",fat);

	closedir(dptr);
	myfile->FIT->sync_FIT(myfile,myfile->SuperBlock);
	myfile->FBL->sync_FBL();

}
char* get_paths_by_mode(char *dir,string &parent_path,int mode){

	string sub,x=dir,token,delimiter = "/";
	char*buffer;
	int pos = 0,count = 0;//file=0,dir=1

	  for (int i = 0; i < x.size(); i++)
	    if (x[i] == '/') count++;

	string cds[count];
	count=0;
	x=x.substr(1);
	while ((pos = x.find(delimiter)) != std::string::npos) {
	    token = x.substr(0, pos);
	    cds[count]=token;
	    count++;
//	    cout << token << endl;
	    x.erase(0, pos + delimiter.length());
	}
	cds[count]=x;
	int i;
	for(i = 0 ;i<count-mode ;i++){

		parent_path=parent_path+"/"+cds[i];
	}
	parent_path=parent_path+"/";

	if(mode==1)
	{
		cds[i]=cds[i]+"/";
	}
	buffer=new char[cds[i].length()+1];
	strcpy(buffer,cds[i].c_str());
//	cout<<parent_path<<"          "<<cds[i]<<endl;
	return buffer;
}
void COPY_F(char * PATH, File *myfile,FAT_Class *fat){
	string parent;
	char *filename,*parentPath;
	filename=get_paths_by_mode(PATH,parent,0);
	parentPath=new char[parent.length()+1];
	strcpy(parentPath,parent.c_str());
	copy_File(parentPath,filename,myfile,fat);
}
void COPY_D(char * PATH, File *myfile,FAT_Class *fat){
	string parent;char*x=new char[strlen(PATH)+1];
	strcpy(x,PATH);
	char *filename,*parentPath;
//	if(x[strlen(x)]!='/'){
//		strcat(PATH,"/");
//		}
	filename=get_paths_by_mode(PATH,parent,1);
	parentPath=new char[parent.length()+1];
	strcpy(parentPath,parent.c_str());
	copy_DIR(parentPath,filename,myfile,fat);
	cd("..",fat);

}


void copy_File_out(string distination,FAT_Class::Link target,File *myfile,FAT_Class *fat){
		string FullPathWithName=distination+"/"+(string)target->inode.FileName;
		int fd=open(FullPathWithName.c_str(),O_CREAT | O_RDWR ,0764);
		assert(fd);
		unsigned int actualSize=((target->inode.Number_Blocks?(target->inode.Number_Blocks==1?0:target->inode.Number_Blocks-1):0)*myfile->SuperBlock->Data_blocksize)+(target->inode.EndingOffset);
		void*buffer=new char[actualSize];
		myfile->as_read(&target->inode,buffer);
		write(fd,buffer,actualSize);
		delete[](char*)buffer;
		close(fd);
}

void copy_DIR_out(string distination,FAT_Class::Link target,File *myfile,FAT_Class *fat){
	string FullPathWithName=distination+"/"+(string)target->inode.FileName;
	if(mkdir(FullPathWithName.c_str(),0764)<0){
		cout<<"given destination doesn't exist"<<endl;
		return;
	}
	FAT_Class::Link temp;
	bool flag=target->childern.first(temp);
	while(flag){
		if(temp->inode.Mode=='f')
			copy_File_out(FullPathWithName,temp,myfile,fat);
		else
			copy_DIR_out(FullPathWithName,temp,myfile,fat);
		flag=target->childern.next(temp);
	}
}


