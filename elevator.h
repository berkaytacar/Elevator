#pragma once
#ifndef __Elevator__
#define __Elevator__

#include "C:\RTExamples\RTExamples\rt.h"


class Elevator : public ActiveClass {
private:
	int main();
	void updateData();
	int myNum;
	int floor;
	int status;
	int door;
	int* sortQ(int[], int, int*, int);
	int* removeQ(int[], int);

public:
	Elevator(int __myNumber) { myNum = __myNumber; floor = 0; status = 1; door = 1; };
};

#endif

