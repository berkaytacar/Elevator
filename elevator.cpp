#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "elevator.h"
atomic_flag flag;
//Flags were only used to control printing onto the screen
//Semaphores were used for controlling everything else

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
};


int Elevator::main() {
	UINT Message;
	CMailbox myMail = CMailbox();

	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());

	MyDataPool->dir = 1;
	MyDataPool->floor = 0;
	MyDataPool->status = 1;
	CEvent   ElevatorUpdate("E1UPD");


	do {
		// Suspend until message arrives
		printf("\n Elevator waiting for next floor instruction \n");
		if (Message = myMail.GetMessage()) {
			// do something
			Sleep(5000);
			int destin = Message;
			printf("Elevator - %d", destin);
			int dir = MyDataPool->dir;
			//baed onn message choose what floor to go to

			for (int i = floor; i <= destin; i++) {
				MyDataPool->floor = i;
				floor++;
				ElevatorUpdate.Signal();
				Sleep(2000);
				
			}
			
		}
	} while (1); // continue forever ??

	return 0;
}

void Elevator::updateData() {


}

