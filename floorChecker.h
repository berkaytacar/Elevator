#pragma once
#ifndef __floorChecker__
#define __floorChecker__


#include "C:\RTExamples\RTExamples\rt.h"

class floorChecker : public ActiveClass {
private:
	int main();
	int start;
	int finish;
	int dir;
	int myNum;
	CMutex* m3;
	//void printScreen(int __myNum, int floor);

public:
	floorChecker(int __myNumber, string Name) {
		myNum = __myNumber;
		m3 = new CMutex(string("__Mutex__") + string(Name));
	};
	int upWait[10][20];
	int downWait[10][20];
	int upNum[10];
	int downNum[10];
};


#endif