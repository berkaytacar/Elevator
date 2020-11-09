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
public:
	Elevator(int __myNumber) { myNum = __myNumber; floor = 0; status = 1; };
};

#endif

