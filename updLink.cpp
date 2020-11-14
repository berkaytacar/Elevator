#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "updLink.h"
#include "updLink2.h"

atomic_flag flag1;

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
	int door;
};



int UpdateLink::main() {
	CSemaphore P1("Elv", 0, 1);
	CSemaphore C1("ElvDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());

	floor = 0;
	int __myNum = 0;
	while (flag1.test_and_set() == true)
		;
	printStatus(door, status, dir);
	MOVE_CURSOR(30, __myNum + 18);
	printf("\r ELEVATOR 1		|		ELEVATOR 2");
	MOVE_CURSOR(30, __myNum + 20);
	printf("\r	#	        B1");
	fflush(stdout); // force output to be written to screen now
	flag1.clear();
	while (1) {
		P1.Wait();
		floor = MyDataPool->floor;
		door = MyDataPool->door;
		status = MyDataPool->status;
		dir = MyDataPool->dir;
		printStatus(door, status, dir);
		printScreen(0, floor);
		C1.Signal();

	}
	return 0;
}

void UpdateLink::printStatus(int door, int status, int dir) {
	MOVE_CURSOR(0,  14);
	(door) ? printf("Door : Open    ") : printf("Door : Closed");
	MOVE_CURSOR(0, 15);
	(status) ? printf("Status : In Service         ") : printf("Status : Out of Service");
	MOVE_CURSOR(0, 16);
	(dir) ? printf("Going Up     ") : printf("Going Down");
}

void UpdateLink::printScreen(int __myNum, int floor) {
	while (flag1.test_and_set() == true)
		;
	MOVE_CURSOR(30, __myNum + 20 + floor - 1);
	printf("\r                       ");
	MOVE_CURSOR(30, __myNum + 20 + floor);
	printf("\r	#		%d				  ", floor);
	MOVE_CURSOR(30, __myNum + 20 + floor + 1);
	printf("\r                       ");
	fflush(stdout); // force output to be written to screen now
	flag1.clear();
	return;
}



int UpdateLinkTwo::main() {
	CSemaphore P3("Elv2", 0, 1);
	CSemaphore C3("ElvDone2", 1, 1);
	CDataPool 		dp2("Elevator2", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp2.LinkDataPool());

	floor = 0;
	int __myNum = 0;
	while (flag1.test_and_set() == true)
		;
	printStatus(door, status, dir);
	MOVE_CURSOR(30, __myNum + 18);
	printf("\r ELEVATOR 1		|		ELEVATOR 2");
	MOVE_CURSOR(40, __myNum + 20);
	printf("#			  ");
	MOVE_CURSOR(30, __myNum + 21);
	printf("\r			1				  ");
	MOVE_CURSOR(30, __myNum + 22);
	printf("\r			2				  ");
	MOVE_CURSOR(30, __myNum + 23);
	printf("\r			3				  ");
	MOVE_CURSOR(30, __myNum + 24);
	printf("\r			4				  ");
	MOVE_CURSOR(30, __myNum + 25);
	printf("\r			5				  ");
	MOVE_CURSOR(30, __myNum + 26);
	printf("\r			6				  ");
	MOVE_CURSOR(30, __myNum + 27);
	printf("\r			7				  ");
	MOVE_CURSOR(30, __myNum + 28);
	printf("\r			8				  ");
	MOVE_CURSOR(30, __myNum + 29);
	printf("\r			9				  ");
	fflush(stdout); // force output to be written to screen now
	flag1.clear();

	while (1) {
		P3.Wait();
		floor = MyDataPool->floor;
		door = MyDataPool->door;
		status = MyDataPool->status;
		dir = MyDataPool->dir;
		printStatus(door, status, dir);
		printScreen(0, floor);
		C3.Signal();
	}
	return 0;
}

void UpdateLinkTwo::printStatus(int door, int status, int dir) {
	MOVE_CURSOR(40, 14);
	(door) ? printf("Door : Open    ") : printf("Door : Closed");
	MOVE_CURSOR(40, 15);
	(status) ? printf("Status : In Service      ") : printf("Status : Out of Service");
	MOVE_CURSOR(40, 16);
	(dir) ? printf("Going Up    ") : printf("Going Down");
}


void UpdateLinkTwo::printScreen(int __myNum, int floor) {

	while (flag1.test_and_set() == true)
		;
	MOVE_CURSOR(40, __myNum + 20 + floor - 1);
	printf("                           ");
	//printf("%d				  ", floor - 1);
	MOVE_CURSOR(40, __myNum + 20 + floor);
	printf("#			  ", floor);
	MOVE_CURSOR(40, __myNum + 20 + floor + 1);
	printf("                            ");
	fflush(stdout); // force output to be written to screen now
	flag1.clear();
	return;
}
