#pragma once
#ifndef __Algo__
#define __Algo__


#include "C:\RTExamples\RTExamples\rt.h"

class Algo : public ActiveClass {
private:
	int main();
	int myNum;
	int status;
	int floor;

public:
	Algo(int __myNumber) { myNum = __myNumber; };
	int sendUpd() { return floor; };
};


#endif
