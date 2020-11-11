#pragma once
#ifndef __Dispatcher__
#define __Dispatcher__


#include "C:\RTExamples\RTExamples\rt.h"

class Dispatcher : public ActiveClass {
private:
	int main();
	int myNum;
	int status1;
	int floor1=1;
	int status2;
	int floor2=1;
	void inc(int dest, int curr);
	void inc2(int dest, int curr);

public:
	Dispatcher(int __myNumber) { myNum = __myNumber; };
};


#endif

