
#include "Inode.h"
void inode_Class::delete_inode(FIT_Class* FitPtr,SuperBlock_Class* SuperPtr,FBL_Class * FBL){
	FitPtr->FIT[inode_number]=0;     //  now it's free and we can override it's data ;
	(SuperPtr->free_inode_Numbers)++;
	FBL->delete_file(this);
}

//-----------------------------------------------------------------------------------------------------
void inode_Class::New_inode(const char* NewFileName,char mode,FIT_Class* FitPtr,SuperBlock_Class* SuperPtr){
	strcpy(FileName,NewFileName);
	Mode=mode;
	get_inode_NUM(FitPtr,SuperPtr);
	// adjusting the creation time------------------------------------------------------------------------
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	strftime(CreationTime,sizeof(CreationTime),"%d-%m-%y %I:%M:%S",timeinfo);
}

 //-----------------------------------------------------------------------------------------------------
bool inode_Class::get_inode_NUM(FIT_Class* FitPtr,SuperBlock_Class* SuperPtr)   // momken tep2a  fe el constructor
{
	unsigned int num;
	bool flag=FitPtr->get_inode_number(num,SuperPtr); // ask the FIT for a node number
	if(flag){
		inode_number=num;	// give a number to the node
		return true;
	}
	return false;  // there're no free nodes in the FIT,we will need to extend the FIT
}
//------------------------------------------------------------------------------------------------------
void inode_Class::write_inode(File* myfile,SuperBlock_Class* sb){		// nodes num starts with 0	/// zapat el pointer dah 8alat
	assert(myfile);
	myfile->llseek(inode_number*sizeof(inode_Class),sb->FAT_Start); //  this would give error , sizeof(inode_class) contain other data because of string variables for example
	myfile->s_write(this,sizeof(inode_Class));
}
//-----------------------------------------------------------------------------------------------------
void inode_Class::get_inodeNumber_Data(File* myfile,SuperBlock_Class* sb,unsigned int inode_number){
	assert(myfile);
	myfile->llseek(inode_number*sizeof(inode_Class),sb->FAT_Start);
	myfile->s_read(this,sizeof(inode_Class));
}
//----------------------------------------------------------------------------------------------------------------------------------------------
inode_Class::inode_Class(){
	inode_number=0;  	// starts with (0) with max (inode_numbers)
	First_Block_Number=0;     	// get it from FBL
	Number_Blocks=0;				//number of blocks of this file
	EndingOffset=0;
	Mode=0;					    // 0 for file and 1 for directory
//	FileName[101]; 	// The name of the file (with 10 letters maximum)
//	CreationTime[18];
}
