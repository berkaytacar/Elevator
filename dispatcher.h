#pragma once
#ifndef __Dispatcher__
#define __Dispatcher__


#include "C:\RTExamples\RTExamples\rt.h"

class Dispatcher : public ActiveClass {
private:
	int main();
	int myNum;
	int status1;
	int floor1;
	int status2;
	int floor2;
public:
	Dispatcher(int __myNumber) { myNum = __myNumber; };
};


#endif

