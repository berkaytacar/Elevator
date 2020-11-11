#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "Elevator2.h"

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
};


CEvent   ElevatorUpdate("E1UPD");

int Dispatcher::main() {
	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
	



	//Initialize Elevator and Monitors

	//Elevator e2(3);
	Monitor m1(4, "Bob");
	MonitorTwo m2(5, "Jim");
	Elevator e1(2);
	ElevatorTwo e2(2);
	e1.Resume();
	e2.Resume();
	m1.Resume();
	m2.Resume();

	while (1) {


		//////////////////////////////////////////////////////////////////////////////////////////////
		// Read Floor and Dir Passenger Wants to go
		int d;
		int s;
		int dest;
		int err = 0;

		//RECIEVE UP OR DOWN (U= 117 / D = 100)
		p1.Read(&s);

		if (s == '+') {
			p1.Read(&s);
			int faultCode = s - 48; //FIX TO READ PROPER NUMBER
			if (faultCode == 11) { // elv 1
				dest = floor1; // stay at the same flr
				e1.Post(dest);

			}
			else {// 12 // elv 2
				dest = floor2; // stay at the same flr
				e2.Post(dest);
			}
		}
		else if (s == '-') {
			p1.Read(&s);
			int faultCode = s - 48; //FIX TO READ PROPER NUMBER
			if (faultCode == 13) {// elv 1
				dest = floor1; // stay at the same flr
				e1.Post(dest);
			}
			else {// 14 // elv 2

			}
		}
		else if (s == 'e') {
			p1.Read(&s);
			if (s == 'e') {
				floor1 = 0;
				floor2 = 0;
				e1.Post(floor1);// send elv1 and 2 to GROUND floor
				e2.Post(floor2);

			}
		}
		else {// here is dir and the floor stuff
			d = s;// direction here 
			p1.Read(&s); // read it for the second time for the floor 
			int flr = s - 48;
			if (abs(flr - floor1) >= abs(flr - floor2)) {
				e2.Post(d);
				e2.Post(flr);
				inc2(flr, floor2);
			}
			else {
				e1.Post(d);
				e1.Post(flr);
				inc(flr, floor1);

			}
			p1.Read(&s);

			if (s == '1') { //elevator 1 
				p1.Read(&s);
				flr = s - 48;
				e1.Post(flr);
				inc(flr, floor1);

			}
			else {
				p1.Read(&s);
				flr = s - 48;
				MOVE_CURSOR(50, 0);
				printf("halfway point for dispatcher");
				e2.Post(flr);
				inc2(flr, floor2);
			}
			
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
		//d = s; //direction
		//p1.Read(&s);		

		//// Determine which elevator to send to that passenger
		//// Send Elevator to Pick up Passenger
		//int flr = s - 48; //FIX TO READ PROPER NUMBER
		//if (abs(flr - floor1) >= abs(flr - floor2)) {
		//	e2.Post(d);
		//	e2.Post(flr);
		//	inc2(flr, floor2);
		//}
		//else {
		//	e1.Post(d);
		//	e1.Post(flr);
		//	inc(flr, floor1);

		//}
		//

	

		//p1.Read(&s);	

		//if (s == '1') { //elevator 1 
		//	p1.Read(&s);
		//	flr = s - 48;
		//	e1.Post(flr);
		//	inc(flr, floor1);

		//}
		//else {
		//	p1.Read(&s);
		//	flr = s - 48;
		//	MOVE_CURSOR(50, 0);
		//	printf("halfway point for dispatcher");
		//	e2.Post(flr);
		//	inc2(flr, floor2);
		//}
	}



	e1.WaitForThread();
	e2.WaitForThread();
	m1.WaitForThread();
	m2.WaitForThread();

	return 0;
}


void Dispatcher :: inc(int dest, int curr) {

	CSemaphore P2("Status", 0, 1);
	CSemaphore C2("StatusDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());

	//while(!err){
	while (dest != curr) {
		//Keep getting updates from monitor
		P2.Wait();
		floor1 = MyDataPool->floor;
		curr = floor1;
		C2.Signal();
	}
	//}
	return;

}

void Dispatcher::inc2(int dest, int curr) {

	CSemaphore P4("Status2", 0, 1);
	CSemaphore C4("StatusDone2", 1, 1);
	CDataPool 		dp2("Elevator2", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool2 = (struct mydatapooldata*)(dp2.LinkDataPool());

	while (dest != curr) {
		//Keep getting updates from monitor
		P4.Wait();
		floor2 = MyDataPool2->floor;
		curr = floor2;
		C4.Signal();
	}
	return;



}

//int Dispatcher::checkMessage() {
//	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
//
//	int d;
//	int num;
//	int faultCode;// either 11 or 12 or 13 or 14
//	int dest;
//	int err = 0;
//
//	p1.Read(&num);// read the pipeline
//	if (num == '+') {
//		p1.Read(&num);
//		int faultCode = num - 48; //FIX TO READ PROPER NUMBER
//		if (faultCode == 11) { // elv 1
//			dest = floor1; // stay at the same flr
//			return dest;
//
//		}
//		else {// 12 // elv 2
//			dest = floor2; // stay at the same flr
//			return dest;
//		}
//	}
//	else if (num == '-') {
//		p1.Read(&num);
//		int faultCode = num - 48; //FIX TO READ PROPER NUMBER
//		if (faultCode == 13) {// elv 1
//			dest = floor1; // stay at the same flr
//			return dest;
//		}
//		else {// 14 // elv 2
//
//		}
//	}
//	else if (num == 'e') {
//
//	}
//	else {// here is dir and the floor stuff
//		p1.Read(&num);
//		d = num;// direction here 
//	}
//	return;
//}

