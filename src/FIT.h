#ifndef FIT_H_
#define FIT_H_

#include "SuperBlock.h"
#include "File.h"

class FIT_Class{
public:
	unsigned int *FIT; 			//pointer to dynamically allocated array with numbers of nodes and it's state

	FIT_Class(SuperBlock_Class *sb);
	bool  get_inode_number(unsigned int &num,SuperBlock_Class* sb);
	void load_FIT(File* myfile,SuperBlock_Class* sb);	// read FIT from file
	void sync_FIT(File* myfile,SuperBlock_Class* sb);    // update the file with the new FIT
};
#endif /* FIT_H_ */
