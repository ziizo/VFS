/*
 * Functions.h
 *
 *  Created on: Jul 3, 2017
 *      Author: tourki
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <stdio.h>
#include "FBL.h"
#include "File.h"
#include "Inode.h"
#include "FAT.h"
#include "SuperBlock.h"

#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <fstream>
inode_Class* touch(const char * filename,FAT_Class *FAT);
inode_Class* mkdir(const char * filename,FAT_Class *FAT);
void rm(const char * filename,FAT_Class *FAT);
void rmdir(const char * filename,FAT_Class *FAT);
void ls(FAT_Class *FAT);
void cd(const char * filename,FAT_Class *FAT);
void cd_by_path(char *dir,FAT_Class *FAT);
void COPY_F(char * PATH, File *myfile,FAT_Class *fat);
void COPY_D(char * PATH, File *myfile,FAT_Class *fat);
char* get_paths_by_mode(char *dir,string &parent_path,int mode);
void copy_File(char*full_path,char*file_name,File *myfile,FAT_Class *fat);
void copy_DIR(char*full_path,char*DIR_name,File *myfile,FAT_Class *fat);
void copy_File_out(string distination,FAT_Class::Link target,File *myfile,FAT_Class *fat);
void copy_DIR_out(string distination,FAT_Class::Link target,File *myfile,FAT_Class *fat);




#endif /* FUNCTIONS_H_ */
