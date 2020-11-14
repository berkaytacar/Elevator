#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "updLink.h"
#include "inputPassenger.h"

// if elv arrives to start floor
// wait for a bit then safetogo
// then input your finish floor
// 0........9 floors
// 0 |
// 1st person|

//0 | finsih, x3 5 7 8 x x x x
//1 | 
//2 |
//3 |
//. |
//9 |
// [0][2]


int InputPassenger::main() {
	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
	CTypedPipe <int>	p2("Pipe2", 1024);
	/*CSemaphore P1("Elv", 0, 1);
	CSemaphore C1("ElvDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());
	int ecounter = 0;*/

	while (1) {
		int message;
		int message2;
		int message3;

		// getting the first msg from pipe2 DIRECTION
		p2.Read(&message);// get the first message

		// getting the second msg from pipe2 START FLOOR
		p2.Read(&message2);

		// getting the third msg from pipe2 START FLOOR
		p2.Read(&message3);

		m2->lock();
		p1.Write(&message);// direction
		p1.Write(&message2);// start floor
		m2->unlock();
		
		if (message == 'd') {
			downWait[message2 - 48][downNum[message2 - 48]] = message3;
			downNum[message2 - 48]++;

		}
		else {
			upWait[message2-48][upNum[message2-48]] = message3;
			upNum[message2-48]++;
		}
	}

	return 0;
}

// index 0 1 2 3 4 .... 9
// value finish

		//int d = 0;
		//int count = 0;
		//for (int i = 0; i < 3; i++) {
		//	count++;
		//	p2.Read(&message);// read the message
		//	// first read
		//	if (message == 'd') {
		//		d = 'd';
		//	}
		//	else if (message == 'u') {
		//		d = 'u';
		//	}
		//	else {
		//		// start and finish
		//		message = message - 48;
		//		if (count == 2) {
		//			upWait[message][]
		//		}
		//		
		//	}

	