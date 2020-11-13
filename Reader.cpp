#include "C:\RTExamples\RTExamples\rt.h"
#include "Reader.h"

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
	int door;

};

int Reader::main() {

	CSemaphore P2("Status", 0, 1);
	CSemaphore C2("StatusDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());
	
	while (1) {
		P2.Wait();
		// floor, status 
		floor1 = MyDataPool->floor;
		status1 = MyDataPool->status;
		C2.Signal();
	}

	return 0;
}




int ReaderTwo::main() {

	CSemaphore P4("Status2", 0, 1);
	CSemaphore C4("StatusDone2", 1, 1);
	CDataPool 		dp2("Elevator2", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool2 = (struct mydatapooldata*)(dp2.LinkDataPool());


	while (1) {
		P4.Wait();
		floor2 = MyDataPool2->floor;
		status2 = MyDataPool2->status;
		C4.Signal();
	}

	return 0;
}
