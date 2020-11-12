#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "elevator.h"
#include "Elevator2.h"
//atomic_flag flag;
//Flags were only used to control printing onto the screen
//Semaphores were used for controlling everything else

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
	int door;

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
	int d;
	int error = 0;
	do {
	top:
		// Suspend until message arrives
		if (Message = myMail.GetMessage()) {
			if ((Message == 'd' || Message == 'u') && status == 1) { //going down
				d = (Message == 'd') ? -1 : 1; // d = -1 if Message == d
				if (Message = myMail.GetMessage()) {
					// do something
					Sleep(5000);
					int destin = Message;
					//baed onn message choose what floor to go to

					while (floor != destin) {
						floor = floor + d;
						MyDataPool->floor = floor;
						MyDataPool->dir = (d == 1) ? 1 : 0;
						MyDataPool->door = (floor == destin) ? 1 : 0;
						ElevatorUpdate.Signal();
						Sleep(2000);
						if (myMail.TestForMessage()) {
							Message = myMail.GetMessage();
							if (Message == 'e' || Message == '-') {
								error = (Message == 'e') ? 1 : 2;
								break;
							}
						}
					}
				}
			}
			else if (Message == '1' && status == 1) {
				if (Message = myMail.GetMessage()) {
					// do something
					Sleep(5000);
					int destin = Message;
					if (destin - floor >= 0) {
						d = 1;
					}
					else {
						d = -1;
					}
					//baed onn message choose what floor to go to

					while (floor != destin) {
						floor = floor + d;
						MyDataPool->floor = floor;
						MyDataPool->dir = (d == 1) ? 1 : 0;
						MyDataPool->door = (floor == destin) ? 1 : 0;
						ElevatorUpdate.Signal();
						Sleep(2000);
						if (myMail.TestForMessage()) {
							Message = myMail.GetMessage();
							if (Message == 'e' || Message == '-') {
								error = (Message == 'e') ? 1 : 2;
								break;
							}
						}
					}
				}
			}
			else if (Message == 'e') { //error go to ground floor
				MyDataPool->status = 0;
				MyDataPool->dir = 0;
				MyDataPool->door = 0;
				status = 0;
				while (floor != 0) {
					floor = floor - 1;
					MyDataPool->floor = floor;
					ElevatorUpdate.Signal();
					Sleep(2000);
				}
			}
			else if (Message == '+') {
				MyDataPool->status = 1;
				MyDataPool->door = 1;
				status = 1;
				ElevatorUpdate.Signal();
			}
			else if (Message == '-') {
				MyDataPool->status = 0;
				MyDataPool->door = 0;
				status = 0;
				ElevatorUpdate.Signal();
			}


			if (error == 1) {
				MyDataPool->status = 0;
				MyDataPool->dir = 0;
				MyDataPool->door = 0;
				status = 0;
				while (floor != 0) {
					floor = floor - 1;
					MyDataPool->floor = floor;
					ElevatorUpdate.Signal();
					Sleep(2000);
				}
			}
			else if (error == 2) {
				MyDataPool->status = 0;
				MyDataPool->dir = 0;
				MyDataPool->door = 0;
				MyDataPool->floor = floor;
				status = 0;
				ElevatorUpdate.Signal();
				Sleep(2000);
				
			}


		}
	} while (error != 1); // continue forever ??

	return 0;
}

void Elevator::updateData() {


}


int ElevatorTwo::main() {
	UINT Message;
	CMailbox myMail = CMailbox();

	CDataPool 		dp2("Elevator2", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool2 = (struct mydatapooldata*)(dp2.LinkDataPool());

	MyDataPool2->dir = 1;
	MyDataPool2->floor = 0;
	MyDataPool2->status = 1;
	CEvent   ElevatorUpdate2("E2UPD");
	int d;
	int error = 0;

	do {
	top2:
		// Suspend until message arrives
		if (Message = myMail.GetMessage()) {
			if ((Message == 'd' || Message == 'u') && status == 1) { //going down
				d = (Message == 'd') ? -1 : 1; // d = -1 if Message == d
				if (Message = myMail.GetMessage()) {
					// do something
					Sleep(5000);
					int destin = Message;
					//baed onn message choose what floor to go to

					while (floor != destin) {
						floor = floor + d;
						MyDataPool2->dir = (d==1) ? 1 : 0;
						MyDataPool2->door = (floor == destin) ? 1 : 0;
						MyDataPool2->floor = floor;
						ElevatorUpdate2.Signal();
						Sleep(2000);
						if (myMail.TestForMessage()) {
							Message = myMail.GetMessage();
							if (Message == 'e' || Message == '-') {
								error = (Message == 'e') ? 1 : 2;
								break;
							}
						}
					}

				}
			}
			else if (Message == '2' && status == 1) {
				if (Message = myMail.GetMessage()) {
					// do something
					Sleep(5000);
					int destin = Message;
					if (destin - floor >= 0) {
						d = 1;
					}
					else {
						d = -1;
					}
					//baed onn message choose what floor to go to

					while (floor != destin) {
						floor = floor + d;
						MyDataPool2->floor = floor;
						MyDataPool2->dir = (d == 1) ? 1 : 0;
						MyDataPool2->door = (floor == destin) ? 1 : 0;
						ElevatorUpdate2.Signal();
						Sleep(2000);
						if (myMail.TestForMessage()) {
							Message = myMail.GetMessage();
							if (Message == 'e' || Message == '-') {
								error = (Message == 'e') ? 1 : 2;
								break;
							}
						}
					}
				}
			}
			else if (Message == 'e') { //error go to ground floor
				MyDataPool2->status = 0;
				MyDataPool2->dir = 0;
				MyDataPool2->door = 0;
				status = 0;
				while (floor != 0) {
					floor = floor - 1;
					MyDataPool2->floor = floor;
					ElevatorUpdate2.Signal();
					Sleep(2000);
				}
			}
			else if (Message == '+') {
				MyDataPool2->status = 1;
				MyDataPool2->door = 1;
				status = 1;
				ElevatorUpdate2.Signal();
			}
			else if (Message == '-') {
				MyDataPool2->status = 0;
				MyDataPool2->door = 0;
				status = 0;
				ElevatorUpdate2.Signal();
			}

			if (error == 1) {
				MyDataPool2->status = 0;
				MyDataPool2->door = 0;
				MyDataPool2->dir = 0;
				status = 0;
				while (floor != 0) {
					floor = floor - 1;
					MyDataPool2->floor = floor;
					ElevatorUpdate2.Signal();
					Sleep(2000);
				}
			}
			else if (error == 2) {
				MyDataPool2->status = 0;
				MyDataPool2->dir = 0;
				MyDataPool2->door = 0;
				MyDataPool2->floor = floor;
				status = 0;
				ElevatorUpdate2.Signal();
				Sleep(2000);
				error = 0;

			}

		}
	} while (error != 1); // continue forever ??

	return 0;
}
