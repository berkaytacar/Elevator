#pragma once
#ifndef __Passenger__
#define __Passenger__

#include "C:\RTExamples\RTExamples\rt.h"


class Passenger : public ActiveClass {
private:
	int main();
	int start;
	int finish;
	int dir;
	int myNum;
	CMutex* m2;// for the passengers
	
public:
	//Passenger(int __myNumber) { myNum = __myNumber; };
	Passenger(int __myNumber, string Name) {
		myNum = __myNumber;
		m2 = new CMutex(string("__Mutex__") + string(Name));
	};
};

#endif