#pragma once
#ifndef __Dispatcher__
#define __Dispatcher__


#include "C:\RTExamples\RTExamples\rt.h"

class Dispatcher : public ActiveClass {
private:
	int main();
	int myNum;
	int status1 = 1;
	int floor1=0;
	int status2 = 1;
	int floor2=0;
	int inc(int dest, int curr);
	int inc2(int dest, int curr);
	void floor();
	//int checkMessage();
	int pipeEmpty();
	
public:
	Dispatcher(int __myNumber) { myNum = __myNumber; };

};


#endif

