#pragma once
#ifndef __UpdateLinkTwo__
#define __UpdateLinkTwo__


#include "C:\RTExamples\RTExamples\rt.h"

class UpdateLinkTwo : public ActiveClass {
private:
	int main();
	int myNum;
	int status;
	int floor;
	void printScreen(int __myNum, int floor);

public:
	UpdateLinkTwo(int __myNumber) { myNum = __myNumber; };
	int sendUpd() { return floor; };
};


#endif

