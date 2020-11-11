#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
atomic_flag flag;

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
};



int Monitor::main() {
	CSemaphore P1("Elv", 0, 1);
	CSemaphore C1("ElvDone", 1, 1);
	CSemaphore P2("Status", 0, 1);
	CSemaphore C2("StatusDone", 1, 1);

	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());

	CEvent   ElevatorUpdate("E1UPD");
	
	int floor;
	int __myNum = 0;

	while (1) {
		ElevatorUpdate.Wait();
		C1.Wait();
		C2.Wait(); //Both IO and Dispatcher have read that Data
		//while (flag.test_and_set() == true)
		//	;
		//MOVE_CURSOR(30, __myNum +19);
		//printf("\r ELEVATOR 1		|		ELEVATOR 2");
		//MOVE_CURSOR(30, __myNum + 20);
		//printf("\r			0				  ");
		//MOVE_CURSOR(30, __myNum + 21);
		//printf("\r			1				  ");
		//MOVE_CURSOR(30, __myNum + 22);
		//printf("\r			2				  ");
		//MOVE_CURSOR(30, __myNum + 23);
		//printf("\r			3				  ");
		//MOVE_CURSOR(30, __myNum + 24);
		//printf("\r			4				  ");
		//MOVE_CURSOR(30, __myNum + 25);
		//printf("\r			5				  ");
		//MOVE_CURSOR(30, __myNum + 26);
		//printf("\r			6				  ");
		//MOVE_CURSOR(30, __myNum + 27);
		//printf("\r			7				  ");
		//MOVE_CURSOR(30, __myNum + 28);
		//printf("\r			8				  ");
		//MOVE_CURSOR(30, __myNum + 29);
		//printf("\r			9				  ");
		//fflush(stdout); // force output to be written to screen now
		//flag.clear();
		//floor = MyDataPool->floor;
		//printScreen(0, floor);
		//printf("\nMonitor Reads Floor = %d", MyDataPool->floor);// print the elevator floor
		//printScreen(0);
		P1.Signal();
		P2.Signal(); //Tell IO and Dispatcher that new Data is available
	}

	return 0;
}

int Monitor::getElevatorStatus() {
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());
	return MyDataPool->floor;
}

void Monitor::updateStatus() {
	return;
}

void Monitor::printScreen(int __myNum, int floor) {
	//while (flag.test_and_set() == true)
	//	;
	//MOVE_CURSOR(30, __myNum + 19);
	//printf("\r ELEVATOR 1		|		ELEVATOR 2");
	//printf("\x1b[A"); // you can add the number of lines: "\x1b[7A"

	//while (1) {
	while (flag.test_and_set() == true)
		;
	MOVE_CURSOR(30, __myNum + 20 + floor - 1);
	printf("\r                       ");
	//printf("%d				  ", floor - 1);
	MOVE_CURSOR(30, __myNum + 20 + floor);
	printf("\r	#		%d				  ", floor);
	MOVE_CURSOR(30, __myNum + 20 + floor + 1);
	printf("\r                       ");
	fflush(stdout); // force output to be written to screen now
	flag.clear();

	//while (flag.test_and_set() == true)
	//	;
	//MOVE_CURSOR(30, __myNum + 20 + floor-1);
	//printf("\r			%d				  ", floor-1);
	//fflush(stdout); // force output to be written to screen now
	//flag.clear();

	//while (flag.test_and_set() == true)
	//	;
	//MOVE_CURSOR(30, __myNum + 20+floor);
	//printf("\r	#		%d				  ", floor);
	//fflush(stdout); // force output to be written to screen now
	//flag.clear();

	//while (flag.test_and_set() == true)
	//	;
	//MOVE_CURSOR(30, __myNum + 20 + floor+1);
	//printf("\r			%d				  ", floor+1);
	//fflush(stdout); // force output to be written to screen now
	//flag.clear();
	


	
		//if (floor == 1) {
		//	while (flag.test_and_set() == true)
		//		;

		//	MOVE_CURSOR(30, __myNum + 21);
		//	printf("\r	#		1				  ");
		//	fflush(stdout); // force output to be written to screen now
		//	flag.clear();
		//
		//}
		//else if (floor == 2) {
		//	while (flag.test_and_set() == true)
		//		;

		//	MOVE_CURSOR(30, __myNum + 22);
		//	printf("\r	#		2				  ");
		//	fflush(stdout); // force output to be written to screen now
		//	flag.clear();
		//}
		//else if (floor == 3) {
		//	while (flag.test_and_set() == true)
		//		;

		//	MOVE_CURSOR(30, __myNum + 23);
		//	printf("\r	#		3				  ");
		//	fflush(stdout); // force output to be written to screen now
		//	flag.clear();
		//}

	//}
	
	
	
	//if (floor == 0) {
	//	while (flag.test_and_set() == true)
	//		;
	//	MOVE_CURSOR(30, __myNum + 19);
	//	printf("\r ELEVATOR 1		|		ELEVATOR 2");
	//	MOVE_CURSOR(30, __myNum + 20);
	//	printf("\r	#		0				  ");
	//	MOVE_CURSOR(30, __myNum + 21);
	//	printf("\r			1				  ");
	//	MOVE_CURSOR(30, __myNum + 22);
	//	printf("\r			2				  ");
	//	MOVE_CURSOR(30, __myNum + 23);
	//	printf("\r			3				  ");
	//	MOVE_CURSOR(30, __myNum + 24);
	//	printf("\r			4				  ");
	//	MOVE_CURSOR(30, __myNum + 25);
	//	printf("\r			5				  ");
	//	MOVE_CURSOR(30, __myNum + 26);
	//	printf("\r			6				  ");
	//	MOVE_CURSOR(30, __myNum + 27);
	//	printf("\r			7				  ");
	//	MOVE_CURSOR(30, __myNum + 28);
	//	printf("\r			8				  ");
	//	MOVE_CURSOR(30, __myNum + 29);
	//	printf("\r			9				  ");
	//	fflush(stdout); // force output to be written to screen now
	//	flag.clear();
	//}
	//if (floor == 1) {
	//	while (flag.test_and_set() == true)
	//		;
	//	MOVE_CURSOR(30, __myNum + 19);
	//	printf("\r ELEVATOR 1		|		ELEVATOR 2");
	//	MOVE_CURSOR(30, __myNum + 20);
	//	printf("\r	0		0				  ");
	//	/*MOVE_CURSOR(30, __myNum + 21);
	//	printf("\r	#		1				  ");
	//	MOVE_CURSOR(30, __myNum + 22);
	//	printf("\r			2				  ");*/
	//	fflush(stdout); // force output to be written to screen now
	//	flag.clear();
	//}
	//else if (floor == 2) {
	//	while (flag.test_and_set() == true)
	//		;
	//	MOVE_CURSOR(30, __myNum + 19);
	//	printf("\r ELEVATOR 1		|		ELEVATOR 2");
	//	MOVE_CURSOR(30, __myNum + 21);
	//	printf("\r			1				  ");
	//	/*MOVE_CURSOR(30, __myNum + 22);
	//	printf("\r	#		2				  ");
	//	MOVE_CURSOR(30, __myNum + 23);
	//	printf("\r			3				  ");*/
	//	fflush(stdout); // force output to be written to screen now
	//	flag.clear();
	//}
	//else if (floor == 3) {
	//	while (flag.test_and_set() == true)
	//		;
	//	MOVE_CURSOR(30, __myNum + 19);
	//	printf("\r ELEVATOR 1		|		ELEVATOR 2");
	//	MOVE_CURSOR(30, __myNum + 22);
	//	printf("\r			2				  ");
	//	/*MOVE_CURSOR(30, __myNum + 23);
	//	printf("\r	#		3				  ");
	//	MOVE_CURSOR(30, __myNum + 24);
	//	printf("\r			4				  ");*/
	//	fflush(stdout); // force output to be written to screen now
	//	flag.clear();
	//}
	return;
}