#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "io.h"
#include "updLink.h"
#include "inputKey.h"
#include "updLink2.h"
#include "Passenger.h"
#include "inputPassenger.h"
#include "floorChecker.h"

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
	int door;
};


int IO::main() {
	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
	CSemaphore P1("Elv", 0, 1);
	CSemaphore C1("ElvDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());
	CCondition   OpenTheGates("GateOpen");

	//thread to print to io


	//thread to recieve update from monitor
	UpdateLink u1(1);
	UpdateLinkTwo u2(2);


	mutex* m1 = new mutex();
	mutex* m2 = new mutex();



	floorChecker fc(5, m2);
	//InputPassenger ipsg1(5, m2);


	u1.Resume();
	u2.Resume();

	fc.Resume();

	InputKey ik1(1, m2);
	ik1.Resume();

	OpenTheGates.Wait();
	Passenger ps1(1, m1);
	Passenger ps2(2, m1);
	Passenger ps22(2, m1);
	/*Passenger ps23(2, m1);
	Passenger ps24(2, m1);*/

	Passenger ps3(3, m1);
	Passenger ps4(4, m1);
	ps1.Resume();
	ps2.Resume();
	ps22.Resume();
	/*ps23.Resume();
	ps24.Resume();*/
	ps3.Resume();
	ps4.Resume();


	//just recieve inputs from keyboard and send to dispatcher
	

	

	//while (1) { //SignalMail from Dispatcher when time to quit 
	//	// Get Current Floor + Direction
	//	int message = _getch(); // get the first message
	//	int message2;
	//	printf("%d", message);// print the up or down in integer
	//	if (message == 100 || message == 117) {
	//		p1.Write(&message);// send up and down to the dispatcher
	//		message2 = _getch();// get the floor info
	//		if (message2 > '0' && message2 <= '9') {
	//			p1.Write(&message2); //send to dispatcher
	//		}
	//	}
	//	else {
	//		continue;
	//	}
	//	int __myNum = 0;
	//	
	//	int destFloor = message2 - 48;
	//	int floor;
	//	// Wait For Eleavator to go to Destination Floor
	//	/*
	//	do {
	//		P1.Wait();
	//		floor = MyDataPool->floor;
	//		C1.Signal();

	//	} while (destFloor != floor);
	//	*/
	//	printf("\n ENTER DEST FLOOR : ");
	//	// INSIDE THE ELEVATOR
	//	//ignore first part
	//	//send floor you wanna go to
	//	message = _getch();
	//	printf("%d \n", message - 48);// print the floor we want to go to
	//	if (message > '0' && message <= '9') {
	//		string m1s = std::to_string(message);
	//		char b[100];
	//		strcpy_s(b, m1s.c_str());
	//		p1.Write(&message);
	//	}


	//	destFloor = message - 48;
	//	/*
	//	do {
	//		P1.Wait();
	//		floor = MyDataPool->floor;
	//		C1.Signal();
	//	} while (destFloor != floor);

	//	printf("\nIO DONE 1 ITER\n");
	//	*/
	//}
	ps1.WaitForThread();
	ps2.WaitForThread();
	ps22.WaitForThread();
	//ps23.WaitForThread();

	//ps24.WaitForThread();

	ps3.WaitForThread();
	ps4.WaitForThread();
	fc.WaitForThread();
	u1.WaitForThread();
	u2.WaitForThread();
	ik1.WaitForThread();
	return 0;
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