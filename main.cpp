#include "DirCleaner.h"

int main()
{
	DirCleaner cln;
	cln.readInJobs();
	cln.executeAL();
	cln.saveLog();

	return 0;
}