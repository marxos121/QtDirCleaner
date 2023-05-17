#include "DirCleaner.h"

int main()
{
	DirCleaner cln;
	cln.readInJobs();
	cln.executeAll();
	cln.saveLog();

	return 0;
}