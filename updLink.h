#pragma once
#ifndef __UpdateLink__
#define __UpdateLink__


#include "C:\RTExamples\RTExamples\rt.h"

class UpdateLink : public ActiveClass {
private:
	int main();
	int myNum;
	int status =1 ;
	int dir = 1;
	int door = 1;
	int floor;
	void printScreen(int __myNum, int floor);
	void printStatus(int door, int status, int dir);

public:
	UpdateLink(int __myNumber) { myNum = __myNumber; };
	int sendUpd() { return floor; };
};


#endif

