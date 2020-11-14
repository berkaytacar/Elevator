#pragma once
#ifndef __InputKey__
#define __InputKey__


#include "C:\RTExamples\RTExamples\rt.h"
#include <mutex>

class InputKey : public ActiveClass {
private:
	int main();
	int myNum;
	int status;
	int floor;
	mutex* m2;

	void printScreen(int __myNum, int floor);

public:
	InputKey(int __myNumber, mutex* m) { myNum = __myNumber; m2 = m; };
	int sendUpd() { return floor; };
};


#endif

