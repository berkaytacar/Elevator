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

CCondition   U01("U0");
CCondition   U11("U1");
CCondition   U21("U2");
CCondition   U31("U3");
CCondition   U41("U4");
CCondition   U51("U5");
CCondition   U61("U6");
CCondition   U71("U7");
CCondition   U81("U8");
CCondition   U91("U9");
CCondition   D01("D0");
CCondition   D11("D1");
CCondition   D21("D2");
CCondition   D31("D3");
CCondition   D41("D4");
CCondition   D51("D5");
CCondition   D61("D6");
CCondition   D71("D7");
CCondition   D81("D8");
CCondition   D91("D9");


CCondition   U02("U02");
CCondition   U12("U12");
CCondition   U22("U22");
CCondition   U32("U32");
CCondition   U42("U42");
CCondition   U52("U52");
CCondition   U62("U62");
CCondition   U72("U72");
CCondition   U82("U82");
CCondition   U92("U92");
CCondition   D02("D02");
CCondition   D12("D12");
CCondition   D22("D22");
CCondition   D32("D32");
CCondition   D42("D42");
CCondition   D52("D52");
CCondition   D62("D62");
CCondition   D72("D72");
CCondition   D82("D82");
CCondition   D92("D92");


CCondition Max1("Full1");
CCondition Max2("Full2");


int Elevator::main() {
	UINT Message;
	CMailbox myMail = CMailbox();

	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());

	MyDataPool->dir = 1;
	MyDataPool->floor = 0;
	MyDataPool->status = 1;
	MyDataPool->door = 1;
	CEvent   ElevatorUpdate("E1UPD");
	int d;
	int error = 0;

	//Array of Next Floors
	int q[10] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
	int qsize = 0;
	int* qpt = q;

	int destin;

	int ppl = 0;
	int dppl[4] = { -1, -1, -1, -1 };

	do {
	top:
		// Suspend until message arrives
		//if (Message = myMail.GetMessage()) {
		if (myMail.TestForMessage()) {
			Message = myMail.GetMessage();
			if ((Message == 'd' || Message == 'u') && status == 1) { 
				d = (Message == 'd') ? -1 : 1; // d = -1 if Message == down 
				if (Message = myMail.GetMessage()) {
					//Sleep(3000);
					// SORT QUEUE DETERMINE NEXT FLOOR IN ORDER
					//int destin = Message;
					qsize++;
					qpt = sortQ(q, Message, &qsize, d);
					destin = *(qpt);
					//baed onn message choose what floor to go to
					
					while (floor != destin) {
						MyDataPool->dir = (d == 1) ? 1 : 0;
						MyDataPool->door = 0;
						MyDataPool->floor = floor;
						ElevatorUpdate.Signal();
						Sleep(2000);
						floor = floor + d;
						MyDataPool->floor = floor;
						MyDataPool->dir = (d == 1) ? 1 : 0;
						MyDataPool->door = (floor == destin) ? 1 : 0;
						ElevatorUpdate.Signal();
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
							/*else if (Message == '1') { //  MAYBE DLEETEL
								qsize++;
								Message = myMail.GetMessage();
								qpt = sortQ(q, Message, &qsize, d);
								destin = *(qpt);
							}*/
						}
					}
					qsize--;
					qpt = removeQ(q, qsize);
					raiseCond(d, floor);
					Sleep(1000);
				}
			}
			else if (Message == '1' && status == 1) {
				if (Message = myMail.GetMessage()) {
					// do something
					//Sleep(3000);
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
						MyDataPool->dir = (d == 1) ? 1 : 0;
						MyDataPool->door = 0;
						MyDataPool->floor = floor;
						ElevatorUpdate.Signal();
						Sleep(2000);
						floor = floor + d;
						MyDataPool->floor = floor;
						MyDataPool->dir = (d == 1) ? 1 : 0;
						MyDataPool->door = (floor == destin) ? 1 : 0;
						ElevatorUpdate.Signal();
						
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
					raiseCond(d, floor);
					Sleep(1000);
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
			//go to next queued floor

			while (floor != destin) {
				MyDataPool->dir = (d == 1) ? 1 : 0;
				MyDataPool->door = 0;
				MyDataPool->floor = floor;
				ElevatorUpdate.Signal();
				Sleep(2000);
				floor = floor + d;
				MyDataPool->floor = floor;
				MyDataPool->dir = (d == 1) ? 1 : 0;
				MyDataPool->door = (floor == destin) ? 1 : 0;
				ElevatorUpdate.Signal();
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
			raiseCond(d, floor);
			Sleep(1000);

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

void Elevator::raiseCond(int d, int f) {

	printf("dir = %d, floor = %d", d, f);
	if (d == 1) {
		switch (f) {
		case 0: U01.Signal();
			Sleep(1000);
			U01.Reset();
			break;
		case 1: U11.Signal();
			Sleep(1000);
			U11.Reset();
			break;
		case 2: U21.Signal();
			Sleep(1000);
			U21.Reset();
		case 3: U31.Signal();
			Sleep(1000);
			U31.Reset();
			break;
		case 4: U41.Signal();
			Sleep(1000);
			U41.Reset();
			break;
		case 5: U51.Signal();
			Sleep(1000);
			U51.Reset();
			break;
		case 6: U61.Signal();
			Sleep(1000);
			U61.Reset();
			break;
		case 7: U71.Signal();
			Sleep(1000);
			U71.Reset();
			break;
		case 8: U81.Signal();
			Sleep(1000);
			U81.Reset();
			break;
		case 9: U91.Signal();
			Sleep(1000);
			U91.Reset();
			break;
		default:
			break;
		}
	}
	else {
		switch (f) {
		case 0: D01.Signal();
			Sleep(1000);
			D01.Reset();
			break;
		case 1: D11.Signal();
			Sleep(1000);
			D11.Reset();
			break;
		case 2: D21.Signal();
			Sleep(1000);
			D21.Reset();
		case 3: D31.Signal();
			Sleep(1000);
			D31.Reset();
			break;
		case 4: D41.Signal();
			Sleep(1000);
			D41.Reset();
			break;
		case 5: D51.Signal();
			Sleep(1000);
			D51.Reset();
			break;
		case 6: D61.Signal();
			Sleep(1000);
			D61.Reset();
			break;
		case 7: D71.Signal();
			Sleep(1000);
			D71.Reset();
			break;
		case 8: D81.Signal();
			Sleep(1000);
			D81.Reset();
			break;
		case 9: D91.Signal();
			Sleep(1000);
			D91.Reset();
			break;
		default:
			break;
		}
		
	}

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
	Max2.Reset();
	MyDataPool2->dir = 1;
	MyDataPool2->floor = 0;
	MyDataPool2->status = 1;
	MyDataPool2->door = 1;
	CEvent   ElevatorUpdate2("E2UPD");
	int d;
	int error = 0;

	int q[10] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
	int qsize = 0;
	int* qpt = q;

	int destin;

	int ppl2 = 0;
	int dppl2[4] = { -1, -1, -1, -1 };

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
					//Sleep(3000);

					qsize++;
					qpt = sortQ(q, Message, &qsize, d);
					destin = *(qpt);

					//baed onn message choose what floor to go to

					while (floor != destin) {
						MyDataPool2->dir = (d == 1) ? 1 : 0;
						MyDataPool2->door = 0;
						MyDataPool2->floor = floor;
						ElevatorUpdate2.Signal();
						Sleep(2000);
						floor = floor + d;
						MyDataPool2->dir = (d==1) ? 1 : 0;
						MyDataPool2->door = (floor == destin) ? 1 : 0;
						MyDataPool2->floor = floor;
						ElevatorUpdate2.Signal();
						
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
							/*else if (Message == '2') {
								printf("HELLO");
								qsize++;
								Message = myMail.GetMessage();
								qpt = sortQ(q, Message, &qsize, d);
								destin = *(qpt);
							}*/
						}
					}
					qsize--;
					qpt = removeQ(q, qsize);
					raiseCond(d, floor);
					Sleep(1000);

				}
			}
			else if (Message == '2' && status == 1) {
				//printf("got second passengers request");
				if (Message = myMail.GetMessage()) {
					// do something
					//Sleep(3000);

					dppl2[ppl2] = Message;
					ppl2++;
					if (ppl2 == 4) {
						Max2.Signal();
					}
					


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
						MyDataPool2->dir = (d == 1) ? 1 : 0;
						MyDataPool2->door = 0;
						MyDataPool2->floor = floor;
						ElevatorUpdate2.Signal();
						Sleep(2000);
						floor = floor + d;
						MyDataPool2->floor = floor;
						MyDataPool2->dir = (d == 1) ? 1 : 0;
						MyDataPool2->door = (floor == destin) ? 1 : 0;
						ElevatorUpdate2.Signal();
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
					raiseCond(d, floor);
					Sleep(1000);

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
			printf("%d", destin);
					//baed onn message choose what floor to go to
				while (floor != destin) {
					MyDataPool2->dir = (d == 1) ? 1 : 0;
					MyDataPool2->door = 0;
					MyDataPool2->floor = floor;
					ElevatorUpdate2.Signal();
					Sleep(2000);
					floor = floor + d;
					MyDataPool2->dir = (d==1) ? 1 : 0;
					MyDataPool2->door = (floor == destin) ? 1 : 0;
					MyDataPool2->floor = floor;
					ElevatorUpdate2.Signal();
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
				raiseCond(d, floor);
				Sleep(1000);

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

		int rep = ppl2;
		for (int i = 0; i < rep; i++) {	
			if (floor = dppl2[i]) {
				for (int j = ppl2-1; j > i; j--) {
					dppl2[j] = dppl2[j - 1];
				}
				ppl2--;
				i--;
			}
		}
		if (ppl2 < 4) {
			Max2.Reset();
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


void ElevatorTwo::raiseCond(int d, int f) {

	if (d == 1) {
		switch (f) {
		case 0: U02.Signal();

			Sleep(1000);
			U02.Reset();
			break;
		case 1: U12.Signal();
			Sleep(1000);
			U12.Reset();
			break;
		case 2: U22.Signal();
			Sleep(1000);
			U22.Reset();
		case 3: U32.Signal();
			Sleep(1000);
			U32.Reset();
			break;
		case 4: U42.Signal();
			Sleep(1000);
			U42.Reset();
			break;
		case 5: U52.Signal();
			Sleep(1000);
			U52.Reset();
			break;
		case 6: U62.Signal();
			Sleep(1000);
			U62.Reset();
			break;
		case 7: U72.Signal();
			Sleep(1000);
			U72.Reset();
			break;
		case 8: U82.Signal();
			Sleep(1000);
			U82.Reset();
			break;
		case 9: U92.Signal();
			Sleep(1000);
			U92.Reset();
			break;
		default:
			break;
		}
	}
	else {
		switch (f) {
		case 0: D02.Signal();
			Sleep(1000);
			D02.Reset();
			break;
		case 1: D12.Signal();
			Sleep(1000);
			D12.Reset();
			break;
		case 2: D22.Signal();
			Sleep(1000);
			D22.Reset();
		case 3: D32.Signal();
			Sleep(1000);
			D32.Reset();
			break;
		case 4: D42.Signal();
			Sleep(1000);
			D42.Reset();
			break;
		case 5: D52.Signal();
			Sleep(1000);
			D52.Reset();
			break;
		case 6: D62.Signal();
			Sleep(1000);
			D62.Reset();
			break;
		case 7: D72.Signal();
			Sleep(1000);
			D72.Reset();
			break;
		case 8: D82.Signal();
			Sleep(1000);
			D82.Reset();
			break;
		case 9: D92.Signal();
			Sleep(1000);
			D92.Reset();
			break;
		default:
			break;
		}

	}

}


void ElevatorTwo::readInTwo() {
	for (int i = 0; i < 4; i++) {
		if (myMail.TestForMessage(100) != WAIT_TIMEOUT) {
			UINT Message = myMail.GetMessage();
			if (Message == '2' && status == 1) {
				//printf("got second passengers request");
				if (Message = myMail.GetMessage()) {
					// do something
					//Sleep(3000);

					dppl2[ppl2] = Message;
					ppl2++;
					if (ppl2 == 4) {
						Max2.Signal();
					}

					qsize++;
					qpt = sortQ(q, Message, &qsize, d);
					destin = *(qpt);
				}
			}
		}
	}
	return;
}