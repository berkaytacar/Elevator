#pragma once
#ifndef __Monitor__
#define __Monitor__


#include "C:\RTExamples\RTExamples\rt.h"

class Monitor : public ActiveClass {
private:
	int main();
	int myNum;
	CMutex* m1;

public:
	Monitor(int __myNumber, string Name) { myNum = __myNumber;
	m1 = new CMutex(string("__Mutex__") + string(Name)); };
	int getElevatorStatus();
	void updateStatus();
};

#endif


