#pragma once
#pragma once
#ifndef __InputPassenger__
#define __InputPassenger__


#include "C:\RTExamples\RTExamples\rt.h"

class InputPassenger : public ActiveClass {
private:
	int main();
	int start;
	int finish;
	int dir;
	int myNum;
	CMutex* m1;
	//void printScreen(int __myNum, int floor);

public:
	InputPassenger(int __myNumber, string Name) {
		myNum = __myNumber;
		m1 = new CMutex(string("__Mutex__") + string(Name));
	};
	int upWait[10][20];
	int downWait[10][20];
	int upNum[10];
	int downNum[10];
};


#endif