#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "io.h"

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
};


int IO::main() {
	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
	CSemaphore P1("Elv", 0, 1);
	CSemaphore C1("ElvDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());



	while (1) { //SignalMail from Dispatcher when time to quit 
		// Get Current Floor + Direction
		int message = _getch();
		int message2;
		printf("%d", message);
		if (message == 100 || message == 117) {
			p1.Write(&message);
			message2 = _getch();
			if (message2 > '0' && message2 < '9') {
				p1.Write(&message2); //send to dispatcher
			}
		}
		else {
			continue;
		}

		
		int destFloor = message2 - 48;
		int floor;
		// Wait For Eleavator to go to Destination Floor
		do {
			P1.Wait();
			floor = MyDataPool->floor;
			C1.Signal();

		} while (destFloor != floor);

		printf("\n ENTER DEST FLOOR : ");

		//ignore first part
		//send floor u wanna go to
		message = _getch();
		printf("%d \n", message - 48);
		if (message > '0' && message <= '9') {
			string m1s = std::to_string(message);
			char b[100];
			strcpy_s(b, m1s.c_str());
			p1.Write(&message);
		}

		destFloor = message - 48;
		do {
			P1.Wait();
			floor = MyDataPool->floor;
			C1.Signal();
		} while (destFloor != floor);
		printf("\nIO DONE 1 ITER");

	}

	return 0;
}
