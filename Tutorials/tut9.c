// q3

int update(int fd, int k, struct X new) {

	off_t offset = k*sizeof(struct X);
	if(lseek(fd, offset, SEEK_SET) != offset) return -1;

	size_t numBytes = sizeof(struct X);
	if(write(fd, &new, numBytes) != numBytes) return -1;
	return 0;

}


// q4


Physical memory
	Stored in computers RAM
	Fast access
	Is an absolute offset within memory from 0..sizeof(RAM)

Virtual memory
	Stored on a computers disk drive
	Slower access due to disk retrieve/load time
	Virtual memory is a mapping process which 
	allows for more processes/information to be stored because
	virtual memory has more space than physical memory
	Is an offset within the process address space from 
	0..end of stack

