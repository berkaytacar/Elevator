#pragma once
#ifndef __UpdateLinkTwo__
#define __UpdateLinkTwo__


#include "C:\RTExamples\RTExamples\rt.h"

class UpdateLinkTwo : public ActiveClass {
private:
	int main();
	int myNum;
	int status = 1;
	int dir = 1;
	int door = 1;
	int floor;
	void printScreen(int __myNum, int floor);
	void printStatus(int door, int status, int dir);


public:
	UpdateLinkTwo(int __myNumber) { myNum = __myNumber; };
	int sendUpd() { return floor; };
};


#endif

