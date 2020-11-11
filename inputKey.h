#pragma once
#ifndef __InputKey__
#define __InputKey__


#include "C:\RTExamples\RTExamples\rt.h"

class InputKey : public ActiveClass {
private:
	int main();
	int myNum;
	int status;
	int floor;
	void printScreen(int __myNum, int floor);

public:
	InputKey(int __myNumber) { myNum = __myNumber; };
	int sendUpd() { return floor; };
};


#endif

