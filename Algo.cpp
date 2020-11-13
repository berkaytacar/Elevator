#include "C:\RTExamples\RTExamples\rt.h"
#include "Algo.h"
#include "elevator.h"
#include "Elevator2.h"
#include "Reader.h"

int Algo::main() {

	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
	Elevator e1(2);
	ElevatorTwo e2(2);
	Reader rd1(1);
	ReaderTwo rd2(2);
	e1.Resume();
	e2.Resume();
	rd1.Resume();
	rd2.Resume();
	//// 
	int err = 0;
	
	int status1 = 1;
	int status2 = 1;
	while (err != 1) {
		//////////////////////////////////////////////////////////////////////////////////////////////
		// Read Floor and Dir Passenger Wants to go
		int d;
		int s;
		int dest;
		int flr;

		//RECIEVE UP OR DOWN (U= 117 / D = 100)
		p1.Read(&s);

		//if (s == '=' ) {
		if (s == '+') {
			//p1.Read(&s);
			//if (s == '+') {
			p1.Read(&s);
			if (s == '1') {// elv 1
				e1.Post('+');
			}
			else if (s == '2') {// 14 // elv 2
				e2.Post('+');
			}
		}
		else if (s == '-') {
			p1.Read(&s);
			if (s == '1') {// elv 1
				e1.Post('-');
			}
			else if (s == '2') {// 14 // elv 2
				e2.Post('-');
			}
		}
		else if (s == 'e') {
			p1.Read(&s);
			if (s == 'e') {
				e1.Post('e');// send elv1 and 2 to GROUND floor
				e2.Post('e');
				err = 1; // to exit
			}
		}
		else if (s == 'u' || s == 'd') {// here is dir and the floor stuff
			d = s;// direction here 
			p1.Read(&s); // read it for the second time for the floor 
			flr = s - 48;
			if ((abs(flr - rd1.floor1) >= abs(flr - rd2.floor2)) && status2 != 0) {
				d = (flr - rd2.floor2 >= 0) ? 'u' : 'd';
				e2.Post(d);
				e2.Post(flr);
				//err = inc2(flr, floor2);
			}
			else if (status1 != 0) {
				d = (flr - rd1.floor1 >= 0) ? 'u' : 'd';
				e1.Post(d);
				e1.Post(flr);
				//err = inc(flr, floor1);
			}
		}
		else if (s == '1' || s == '2') {
			if (s == '1' && status1 != 0) { //elevator 1 
				e1.Post('1');
				p1.Read(&s);
				flr = s - 48;
				e1.Post(flr);
				//err = inc(flr, floor1);

			}
			else if (s == '2' && status2 != 0) {
				e2.Post('2');
				p1.Read(&s);
				flr = s - 48;
				MOVE_CURSOR(50, 0);
				printf("halfway point for dispatcher");
				e2.Post(flr);
				//err = inc2(flr, floor2);
			}
		}

		//if (err == 1) {
		//	e1.Post('e');// send elv1 and 2 to GROUND floor
		//	e2.Post('e');
		//	floor();
		//}
		//else if (err == 2) {  //ele 1
		//	e1.Post('-');
		//	status1 = 0;
		//	P2.Wait();
		//	C2.Signal();
		//	err = 0;

		//}
		//else if (err == 3) { // ele 2
		//	e2.Post('-');
		//	status2 = 0;
		//	P4.Wait();
		//	C4.Signal();
		//	err = 0;
		//}

	}

	e1.WaitForThread();
	e2.WaitForThread();
	rd1.WaitForThread();
	rd2.WaitForThread();

	return 0;
}

