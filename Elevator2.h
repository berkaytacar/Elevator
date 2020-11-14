#pragma once
#ifndef __ElevatorTwo__
#define __ElevatorTwo__

#include "C:\RTExamples\RTExamples\rt.h"


class ElevatorTwo : public ActiveClass {
private:
	int main();
	void updateData();
	int myNum;
	int floor;
	int status;
	int door;
	int* sortQ(int[], int, int*, int);
	int* removeQ(int[], int);
	void raiseCond(int d, int floor);
	void readInTwo();



public:
	ElevatorTwo(int __myNumber) { myNum = __myNumber; floor = 0; status = 1; door = 1; };
	int q[10] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
	int qsize = 0;
	int* qpt = q;

	int destin;
	int d;

	int ppl2 = 0;
	int dppl2[4] = { -1, -1, -1, -1 };
	CMailbox myMail;
};

#endif

