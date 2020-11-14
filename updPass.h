#pragma once
#ifndef __UpdatePass__
#define __UpdatePass__


#include "C:\RTExamples\RTExamples\rt.h"

class UpdatePass : public ActiveClass {
private:
	int main();
	int myNum;
	int n;
	int curr;
	int dest;


public:
	UpdatePass(int __myNumber) { myNum = __myNumber; };
	void passData(int a, int b, int c);
};


#endif

