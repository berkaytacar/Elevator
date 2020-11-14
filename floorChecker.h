#pragma once
#ifndef __floorChecker__
#define __floorChecker__


#include "C:\RTExamples\RTExamples\rt.h"
#include <mutex>
#include "inputPassenger.h"

class floorChecker : public ActiveClass {
private:
	int main();
	int start;
	int finish;
	int dir;
	int myNum;
	mutex* m2;
	void sendPpl(int f,  InputPassenger& i, int e, int dir); //dir = 1 go up
	//void printScreen(int __myNum, int floor);

public:
	floorChecker(int __myNumber, mutex* m) {
		myNum = __myNumber;
		m2 = m;
	};
};


#endif