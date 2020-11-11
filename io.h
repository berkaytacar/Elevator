#pragma once
#ifndef __IO__
#define __IO__

#include "C:\RTExamples\RTExamples\rt.h"

class IO : public ActiveClass {
private:
	int main();
	int myNum;

public:
	IO(int __myNumber) { myNum = __myNumber; };
	void printScreen(int __myNum, int floor);
};

#endif

