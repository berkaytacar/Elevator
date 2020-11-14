#pragma once
#ifndef __Passenger__
#define __Passenger__

#include "C:\RTExamples\RTExamples\rt.h"
#include <mutex>


class Passenger : public ActiveClass {
private:
	int main();
	int start;
	int finish;
	int dir;
	int myNum;
	mutex* m1;
	
public:
	//Passenger(int __myNumber) { myNum = __myNumber; };
	Passenger(int __myNumber, mutex* m ) {
		myNum = __myNumber;
		m1 = m;
	};
};

#endif