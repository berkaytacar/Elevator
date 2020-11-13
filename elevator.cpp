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

	//Array of Next Floors
	int q[10] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
	int qsize = 0;
	int* qpt = q;

	int destin;

	do {
	top:
		// Suspend until message arrives
		//if (Message = myMail.GetMessage()) {
		if (myMail.TestForMessage()) {
			Message = myMail.GetMessage();
			if ((Message == 'd' || Message == 'u') && status == 1) { //going down
				d = (Message == 'd') ? -1 : 1; // d = -1 if Message == d
				if (Message = myMail.GetMessage()) {
					Sleep(3000);
					// SORT QUEUE DETERMINE NEXT FLOOR IN ORDER
					//int destin = Message;
					qsize++;
					qpt = sortQ(q, Message, &qsize, d);
					destin = *(qpt);
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
								qsize = 0;
								break;
							}
							if (Message == 'u' || Message == 'd') { // going up currently
								qsize++;
								d = (Message == 'd') ? -1 : 1;
								Message = myMail.GetMessage();
								qpt = sortQ(q, Message, &qsize, d);
								destin = *(qpt);
							}
						}
					}
					qsize--;
					qpt = removeQ(q, qsize);
					Sleep(3000);
				}
			}
			else if (Message == '1' && status == 1) {
				if (Message = myMail.GetMessage()) {
					// do something
					Sleep(3000);
					int destin = Message;
					if (destin - floor >= 0) {
						d = 1;
					}
					else {
						d = -1;
					}
					//baed onn message choose what floor to go to
					qsize++;
					qpt = sortQ(q, Message, &qsize, d);
					destin = *(qpt);
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
							if (Message == 'u' || Message == 'd') { // going up currently
								qsize++;
								d = (Message == 'd') ? -1 : 1;
								Message = myMail.GetMessage();
								qpt = sortQ(q, Message, &qsize, d);
								destin = *(qpt);
							}
						}
					}
					qsize--;
					qpt = removeQ(q, qsize);
					Sleep(3000);
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


		}

		else if (qsize != 0) {
			destin = *(qpt);
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
						qsize = 0;
						break;
					}
					if (Message == 'u' || Message == 'd') { // going up currently
						qsize++;
						d = (Message == 'd') ? -1 : 1;
						Message = myMail.GetMessage();
						qpt = sortQ(q, Message, &qsize, d);
						destin = *(qpt);
					}
				}
			}
			qsize--;
			qpt = removeQ(q, qsize);
			Sleep(3000);

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

	} while (error != 1); // continue forever ??

	return 0;
}

int* Elevator::sortQ(int arr[], int msg, int* n, int dir) {
	//idx     0    1    2   3
	//val     5    6    8
	if (dir == 1) {
		for (int i = 0; i < *n; i++) {
			if (msg == arr[i]) {
				*n--;
				return arr;
			}
			if (msg < arr[i]) {
				for (int j = *n - 1; j > i; j--) {
					arr[j] = arr[j - 1];
				}
				arr[i] = msg;
				return arr;
			}
		}
		arr[*n - 1] = msg;
	}
	else if (dir == -1) {
		for (int i = 0; i < *n; i++) {
			if (msg == arr[i]) {
				*n--;
				return arr;
			}
			if (msg > arr[i]) {
				for (int j = *n - 1; j > i; j--) {
					arr[j] = arr[j - 1];
				}
				arr[i] = msg;
				return arr;
			}
		}
		arr[*n - 1] = msg;
	}


	return arr;

}

int* Elevator::removeQ(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = arr[i + 1];
	}
	return arr;
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

	int q[10] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
	int qsize = 0;
	int* qpt = q;

	int destin;

	do {
	top2:
		// Suspend until message arrives
		//if (Message = myMail.GetMessage()) {
		
		if (myMail.TestForMessage()) {
			Message = myMail.GetMessage();
			if ((Message == 'd' || Message == 'u') && status == 1) { //going down
				d = (Message == 'd') ? -1 : 1; // d = -1 if Message == d
				if (Message = myMail.GetMessage()) {
					// do something
					Sleep(3000);

					qsize++;
					qpt = sortQ(q, Message, &qsize, d);
					destin = *(qpt);

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
							if (Message == 'u' || Message == 'd') { // going up currently
								qsize++;
								d = (Message == 'd') ? -1 : 1;
								Message = myMail.GetMessage();
								qpt = sortQ(q, Message, &qsize, d);
								destin = *(qpt);
							}
						}
					}
					qsize--;
					qpt = removeQ(q, qsize);
					Sleep(7000);

				}
			}
			else if (Message == '2' && status == 1) {
				//printf("got second passengers request");
				if (Message = myMail.GetMessage()) {
					// do something
					Sleep(3000);

					qsize++;
					qpt = sortQ(q, Message, &qsize, d);
					destin = *(qpt);

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
							if (Message == 'u' || Message == 'd') { // going up currently
								qsize++;
								d = (Message == 'd') ? -1 : 1;
								Message = myMail.GetMessage();
								qpt = sortQ(q, Message, &qsize, d);
								destin = *(qpt);
							}
						}
					}
					qsize--;
					qpt = removeQ(q, qsize);
					Sleep(3000);

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
		}

		else if (qsize != 0) {
			destin = *(qpt);
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
						if (Message == 'u' || Message == 'd') { // going up currently
							qsize++;
							d = (Message == 'd') ? -1 : 1;
							Message = myMail.GetMessage();
							qpt = sortQ(q, Message, &qsize, d);
							destin = *(qpt);
						}
					}
				}
				qsize--;
				qpt = removeQ(q, qsize);
				Sleep(3000);

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

	} while (error != 1); // continue forever ??

	return 0;
}

int* ElevatorTwo::sortQ(int arr[], int msg, int* n, int dir) {
	//idx     0    1    2   3
	//val     5    6    8
	if (dir == 1) {
		for (int i = 0; i < *n; i++) {
			if (msg == arr[i]) {
				*n--;
				return arr;
			}
			if (msg < arr[i]) {
				for (int j = *n - 1; j > i; j--) {
					arr[j] = arr[j - 1];
				}
				arr[i] = msg;
				return arr;
			}
		}
		arr[*n - 1] = msg;
	}
	else if (dir == -1) {
		for (int i = 0; i < *n; i++) {
			if (msg == arr[i]) {
				*n--;
				return arr;
			}
			if (msg > arr[i]) {
				for (int j = *n - 1; j > i; j--) {
					arr[j] = arr[j - 1];
				}
				arr[i] = msg;
				return arr;
			}
		}
		arr[*n - 1] = msg;
	}


	return arr;

}

int* ElevatorTwo::removeQ(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = arr[i + 1];
	}
	return arr;
}