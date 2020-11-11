#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "io.h"

atomic_flag flag1;

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
};


int IO::main() {
	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
	CSemaphore P1("Elv", 0, 1);
	CSemaphore C1("ElvDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());



	while (1) { //SignalMail from Dispatcher when time to quit 
		// Get Current Floor + Direction
		int message = _getch(); // get the first message
		int message2;
		printf("%d", message);// print the up or down in integer
		if (message == 100 || message == 117) {
			p1.Write(&message);// send up and down to the dispatcher
			message2 = _getch();// get the floor info
			if (message2 > '0' && message2 <= '9') {
				p1.Write(&message2); //send to dispatcher
			}
		}
		else {
			continue;
		}
		int __myNum = 0;
		
		int destFloor = message2 - 48;
		int floor;
		// Wait For Eleavator to go to Destination Floor
		do {
			P1.Wait();
			floor = MyDataPool->floor;
			while (flag1.test_and_set() == true)
				;
			MOVE_CURSOR(30, __myNum + 19);
			printf("\r ELEVATOR 1		|		ELEVATOR 2");
			MOVE_CURSOR(30, __myNum + 20);
			printf("\r			0				  ");
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
			printScreen(0, floor);
			C1.Signal();

		} while (destFloor != floor);

		printf("\n ENTER DEST FLOOR : ");
		// INSIDE THE ELEVATOR
		//ignore first part
		//send floor you wanna go to
		message = _getch();
		printf("%d \n", message - 48);// print the floor we want to go to
		if (message > '0' && message <= '9') {
			string m1s = std::to_string(message);
			char b[100];
			strcpy_s(b, m1s.c_str());
			p1.Write(&message);
		}

		destFloor = message - 48;
		do {
			P1.Wait();
			floor = MyDataPool->floor;
			while (flag1.test_and_set() == true)
				;
			MOVE_CURSOR(30, __myNum + 19);
			printf("\r ELEVATOR 1		|		ELEVATOR 2");
			MOVE_CURSOR(30, __myNum + 20);
			printf("\r			0				  ");
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
			printScreen(0, floor);
			C1.Signal();
		} while (destFloor != floor);
		printf("\nIO DONE 1 ITER\n");

	}

	return 0;
}

void IO::printScreen(int __myNum, int floor) {
	//while (flag.test_and_set() == true)
	//	;
	//MOVE_CURSOR(30, __myNum + 19);
	//printf("\r ELEVATOR 1		|		ELEVATOR 2");
	//printf("\x1b[A"); // you can add the number of lines: "\x1b[7A"

	//while (1) {
	while (flag1.test_and_set() == true)
		;
	MOVE_CURSOR(30, __myNum + 20 + floor - 1);
	printf("\r                       ");
	//printf("%d				  ", floor - 1);
	MOVE_CURSOR(30, __myNum + 20 + floor);
	printf("\r	#		%d				  ", floor);
	MOVE_CURSOR(30, __myNum + 20 + floor + 1);
	printf("\r                       ");
	fflush(stdout); // force output to be written to screen now
	flag1.clear();
	return;
}
//elevator 1   | elevator 2
//			1
//			2
//			3
//			4
//			5
//			6
//			7
//			8
//			9
//			10
//Busy			Free
//Door 

//while (flag.test_and_set() == true)
//;
//MOVE_CURSOR(30, myNum + 20);
//printf("\r Car # %d, Entering Pit", myNum);
////printf("\x1b[A"); // you can add the number of lines: "\x1b[7A"
//fflush(stdout); // force output to be written to screen now
//flag.clear();