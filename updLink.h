#pragma once
#ifndef __UpdateLink__
#define __UpdateLink__


#include "C:\RTExamples\RTExamples\rt.h"

class UpdateLink : public ActiveClass {
private:
	int main();
	int myNum;
	int status;
	int floor;
	void printScreen(int __myNum, int floor);

public:
	UpdateLink(int __myNumber) { myNum = __myNumber; };
	int sendUpd() { return floor; };
};


#endif

