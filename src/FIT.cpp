#include "FIT.h"

FIT_Class::FIT_Class(SuperBlock_Class *sb){
	FIT=new unsigned int [sb->inode_Numbers]();
	FIT[0]=1;//there is always a root at node 0;
}
bool FIT_Class::get_inode_number(unsigned int &num,SuperBlock_Class* sb){
	for(unsigned int i=0;i<sb->inode_Numbers;i++)
	{
		if(FIT[i]==0)
		{
			num=i;				// return the free node number

			sb->free_inode_Numbers--;
			FIT[i]=1;			// now the node is not free
			return true;
		}
	}
		return false;  // no sufficient nodes
	}

void FIT_Class::load_FIT(File* myfile,SuperBlock_Class* sb){
	assert(myfile);
	myfile->llseek(0,sb->FIT_Start);
	myfile->s_read(FIT,sizeof(unsigned int)*sb->inode_Numbers);
}

void FIT_Class::sync_FIT(File* myfile,SuperBlock_Class* sb){
	assert(myfile);
	myfile->llseek(0,sb->FIT_Start);
	myfile->s_write(FIT,sizeof(unsigned int)*sb->inode_Numbers);
}
