/*
 * SuperBlock.cpp
 *
 *  Created on: May 5, 2017
 *      Author: tourki
 */

#include "SuperBlock.h"

void SuperBlock_Class::load_super(File *Myfile){
	assert(Myfile);//check the file pointer is not null
	Myfile->llseek(0,0);//as the super block at the beginning of the file
	Myfile->s_read(this,sizeof(SuperBlock_Class));//get the super block from the VFS
}

void SuperBlock_Class::sync_super(File *Myfile){
	assert(Myfile);//check the file pointer is not null
	Myfile->llseek(0,0);//as the super block at the beginning of the file
	Myfile->s_write(this,sizeof(SuperBlock_Class));//get the super block from the VFS
}
