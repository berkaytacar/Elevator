#pragma once
#ifndef __Reader__
#define __Reader__


#include "C:\RTExamples\RTExamples\rt.h"

class Reader : public ActiveClass {
private:
	int main();
	int myNum;
public:
	Reader(int __myNumber) { myNum = __myNumber; };
	int floor1;
	int status1;

};


#endif

#ifndef __ReaderTwo__
#define __ReaderTwo__

#include "C:\RTExamples\RTExamples\rt.h"


class ReaderTwo : public ActiveClass {
private:
	int main();
	int myNum;

public:
	ReaderTwo(int __myNumber) { myNum = __myNumber; };
	int floor2;
	int status2;
};


#endif

