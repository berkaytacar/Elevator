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



int Monitor::main() {
	CSemaphore P1("Elv", 0, 1);
	CSemaphore C1("ElvDone", 1, 1);
	CSemaphore P2("Status", 0, 1);
	CSemaphore C2("StatusDone", 1, 1);

	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());

	CEvent   ElevatorUpdate("E1UPD");


	while (1) {
		ElevatorUpdate.Wait();
		C1.Wait();
		C2.Wait(); //Both IO and Dispatcher have read that Data
		printf("\nMonitor Reads Floor = %d", MyDataPool->floor);
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