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

		// Read Floor and Dir Passenger Wants to go
		int d;
		int s;

		//RECIEVE UP OR DOWN (U= 117 / D = 100)
		p1.Read(&s);
		d = s; //direction
		p1.Read(&s);		

		// Determine which elevator to send to that passenger
		// Send Elevator to Pick up Passenger
		int flr = s - 48; //FIX TO READ PROPER NUMBER
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


	while (dest != curr) {
		//Keep getting updates from monitor
		P2.Wait();
		floor1 = MyDataPool->floor;
		curr = floor1;
		C2.Signal();
	}
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



