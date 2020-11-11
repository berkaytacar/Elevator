#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
};


CEvent   ElevatorUpdate("E1UPD");

int Dispatcher::main() {
	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
	CSemaphore P2("Status", 0, 1);
	CSemaphore C2("StatusDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());

	//Initialize Elevator and Monitors

	//Elevator e2(3);
	Monitor m1(4, "Bob");
	//Monitor m2(5);
	Elevator e1(2);
	e1.Resume();
	//e2.Resume();
	m1.Resume();
	//m2.Resume();

	while (1) {

		// Read Floor and Dir Passenger Wants to go

		int s;
		//while (p1.TestForData() < sizeof(s)) {
			///
		//}

		//RECIEVE UP OR DOWN (U= 117 / D = 100)
		p1.Read(&s);
		e1.Post(s); // SEND TO ELE 


		p1.Read(&s);		

		// Determine which elevator to send to that passenger
		// Send Elevator to Pick up Passenger

		int flr = s - 48; //FIX TO READ PROPER NUMBER
		printf("\n %d" ,flr);
		e1.Post(flr);

		//Recieving updates from Elevator
		while (floor1 != flr) {
			//Keep getting updates from monitor
			P2.Wait();
			floor1 = MyDataPool->floor;
			C2.Signal();
		}
		
		printf("reading...");
		// Read Floor and Dir Passenger Wants to go

		p1.Read(&s);		
		flr = s - 48;
		printf("\n%d\n", flr);
		e1.Post(flr);

		//Recieving updates from Elevator
		while (floor1 != flr) {
			//Keep getting updates from monitor
			P2.Wait();
			floor1 = MyDataPool->floor;
			C2.Signal();
		}

		printf("\n DISP DONE 1 ITERation\n");

	}



	e1.WaitForThread();
	//e2.WaitForThread();
	m1.WaitForThread();
	//m2.WaitForThread();

	return 0;
}
