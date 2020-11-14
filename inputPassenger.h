#pragma once
#pragma once
#ifndef __InputPassenger__
#define __InputPassenger__


#include "C:\RTExamples\RTExamples\rt.h"
#include <mutex>

class InputPassenger : public ActiveClass {
private:
	int main();
	int start;
	int finish;
	int dir;
	int myNum;
	mutex* m2;
	//void printScreen(int __myNum, int floor);

public:
	InputPassenger(int __myNumber, mutex* m) {
		myNum = __myNumber;
		m2 = m;
	};
	int upWait[10][20];
	int downWait[10][20];
	int upNum[10];
	int downNum[10];
};


#endif