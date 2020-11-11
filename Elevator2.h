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
public:
	ElevatorTwo(int __myNumber) { myNum = __myNumber; floor = 0; status = 1; };
};

#endif

