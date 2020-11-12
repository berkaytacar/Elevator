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
	int door;

};


CEvent   ElevatorUpdate("E1UPD");

int checkable[5] = { 11, 12, 13, 14, 'e' };

int Dispatcher::main() {
	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
	
	CSemaphore P2("Status", 0, 1);
	CSemaphore C2("StatusDone", 1, 1);
	CSemaphore P4("Status2", 0, 1);
	CSemaphore C4("StatusDone2", 1, 1);


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
	int err = 0;
	status1 = 1;
	status2 = 1;


	while (err != 1) {
		//////////////////////////////////////////////////////////////////////////////////////////////
		// Read Floor and Dir Passenger Wants to go
		int d;
		int s;
		int dest;
		int flr;

		//RECIEVE UP OR DOWN (U= 117 / D = 100)
		p1.Read(&s);

		if (s == '=') {
			MOVE_CURSOR(0, 4);
			printf("saw the plus sign");
			//p1.Read(&s);
			//if (s == '+') {
			p1.Read(&s);
				if (s == '1') {// elv 1
					printf("ele # 1 ");
					e1.Post('+');
					status1 = 1;
					P2.Wait();
					C2.Signal();
				}
				else if (s == '2') {// 14 // elv 2
					e2.Post('+');
					status2 = 1;
					P4.Wait();
					C4.Signal();
				}
			//}
		}
		else if (s == '-') {
			p1.Read(&s);
			if (s == '1') {// elv 1
				e1.Post('-');
				status1 = 0;
				P2.Wait();
				C2.Signal();

			}
			else if (s == '2'){// 14 // elv 2
				e2.Post('-');
				status2 = 0;
				P4.Wait();
				C4.Signal();
			}
		}
		else if (s == 'e') {
			p1.Read(&s);
			if (s == 'e') {
				e1.Post('e');// send elv1 and 2 to GROUND floor
				e2.Post('e');
				floor();
			}
		}
		else if (s == 'u' || s == 'd') {// here is dir and the floor stuff
			d = s;// direction here 
			p1.Read(&s); // read it for the second time for the floor 
			flr = s - 48;
			if ((abs(flr - floor1) >= abs(flr - floor2)) && status2 != 0) {
				d = (flr - floor2 >= 0) ? 'u' : 'd';
				e2.Post(d);
				e2.Post(flr);
				err = inc2(flr, floor2);
			}
			else if (status1 != 0) {
				d = (flr - floor1 >= 0) ? 'u' : 'd';
				e1.Post(d);
				e1.Post(flr);
				err = inc(flr, floor1);
			}
		}
		else if (s == '1' || s == '2') {
			if (s == '1' && status1 != 0) { //elevator 1 
				e1.Post('1');
				p1.Read(&s);
				flr = s - 48;
				e1.Post(flr);
				err = inc(flr, floor1);

			}
			else if (s == '2' && status2 != 0) {
				e2.Post('2');
				p1.Read(&s);
				flr = s - 48;
				MOVE_CURSOR(50, 0);
				printf("halfway point for dispatcher");
				e2.Post(flr);
				err = inc2(flr, floor2);
			}
		} 

		if (err == 1) {
			e1.Post('e');// send elv1 and 2 to GROUND floor
			e2.Post('e');
			floor();
		}
		else if (err == 2) {  //ele 1
			e1.Post('-');
			status1 = 0;
			P2.Wait();
			C2.Signal();
			err = 0;

		}
		else if (err == 3) { // ele 2
			e2.Post('-');
			status2 = 0;
			P4.Wait();
			C4.Signal();
			err = 0;
		}

	}

	e1.WaitForThread();
	e2.WaitForThread();
	m1.WaitForThread();
	m2.WaitForThread();

	return 0;
}
void Dispatcher::floor() {
	CSemaphore P2("Status", 0, 1);
	CSemaphore C2("StatusDone", 1, 1);
	CSemaphore P4("Status2", 0, 1);
	CSemaphore C4("StatusDone2", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());
	CDataPool 		dp2("Elevator2", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool2 = (struct mydatapooldata*)(dp2.LinkDataPool());

	while (floor1 != 0 && floor2 != 0) {
		P2.Wait();
		P4.Wait();
		floor1 = MyDataPool->floor;
		floor2 = MyDataPool2->floor;
		C2.Signal();
		C4.Signal();
	}
	while (floor1 != 0) {
		P2.Wait();
		floor1 = MyDataPool->floor;
		C2.Signal();
	}
	while (floor2 != 0) {
		P4.Wait();
		floor2 = MyDataPool2->floor;
		C4.Signal();
	}
}

int Dispatcher :: inc(int dest, int curr) {

	CSemaphore P2("Status", 0, 1);
	CSemaphore C2("StatusDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());
	CTypedPipe <int>	p1("Pipe1", 1024);
	int i;

	while (dest != curr) {
		//Keep getting updates from monitor
		P2.Wait();
		floor1 = MyDataPool->floor;
		curr = floor1;
		Sleep(100);
		if ((p1.TestForData()) >= 1) {
			p1.Read(&i);
			Sleep(100);
			if (i == '-') { //check for new fault
				p1.Read(&i);
				if (i == '1') {
					return 2;
				}
			}
			else if (i == 'e') { //check for exit
				p1.Read(&i);
				if (i == 'e') {
					return 1;
				}
			}
		}
		C2.Signal();
		//		int i = pipeEmpty();
		
	}
	return 0;

}

int Dispatcher::inc2(int dest, int curr) {

	CSemaphore P4("Status2", 0, 1);
	CSemaphore C4("StatusDone2", 1, 1);
	CDataPool 		dp2("Elevator2", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool2 = (struct mydatapooldata*)(dp2.LinkDataPool());
	CTypedPipe <int>	p1("Pipe1", 1024);
	int i;
	while (dest != curr) {
		//Keep getting updates from monitor
		P4.Wait();
		floor2 = MyDataPool2->floor;
		curr = floor2;
		C4.Signal();
//		int i = pipeEmpty();
		Sleep(100);
		if ((p1.TestForData()) >= 1) {
			p1.Read(&i);
			Sleep(100);
			if (i == '-') { //check for new fault
				p1.Read(&i);
				if (i == '2') {
					printf("-1 for elevator 2 while running");
					return 3;
				}
			}
			else if (i == 'e') { //check for exit
				p1.Read(&i);
				if (i == 'e') {
					return 1;
				}
			}
		}
	}
	return 0;

}

int Dispatcher::pipeEmpty() {
	int i;
	CTypedPipe <int>	p1("Pipe1", 1024);

	if ((p1.TestForData()) >= sizeof(int)) {
		printf("read an e");
		p1.Read(&i);
		if (i == '-') { //check for new fault
			p1.Read(&i);
			if (i == 1 || i == 2) {
				return '-';
			}
		}
		else if (i == 'e') { //check for exit
			p1.Read(&i);
			if (i == 'e') {
				return 'e';
			}
		}
		return 1; 
	}
	else {
		//printf("pipe empty");
		return 1;

	}

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

