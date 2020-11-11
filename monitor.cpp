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



///////////////////////////////////////////////////////////////////////////////////////////


int MonitorTwo::main() {
	CSemaphore P3("Elv2", 0, 1);
	CSemaphore C3("ElvDone2", 1, 1);
	CSemaphore P4("Status2", 0, 1);
	CSemaphore C4("StatusDone2", 1, 1);

	CDataPool 		dp2("Elevator2", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp2.LinkDataPool());

	CEvent   ElevatorUpdate2("E2UPD");

	int floor;
	int __myNum = 0;

	while (1) {
		ElevatorUpdate2.Wait();
		C3.Wait();
		C4.Wait(); //Both IO and Dispatcher have read that Data

		P3.Signal();
		P4.Signal(); //Tell IO and Dispatcher that new Data is available
	}

	return 0;
}

int MonitorTwo::getElevatorStatus() {
	CDataPool 		dp2("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp2.LinkDataPool());
	return MyDataPool->floor;
}

void MonitorTwo::updateStatus() {
	return;
}
