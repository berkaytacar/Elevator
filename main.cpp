#include "C:\RTExamples\RTExamples\rt.h"
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "io.h"
#include "Passenger.h"

int main() {
	Dispatcher disp(1);
	IO screen(10);
	//int x = rand() % 10;
	//// create passengers
	//for (int i = 0; i < x; i++) {

	//}
	//Passenger p1(1);
	//Passenger p2(2);
	//Passenger p3(3);
	//Passenger p4(4);

	disp.Resume();
	screen.Resume();
	//p1.Resume();
	//p2.Resume();
	//p3.Resume();
	//p4.Resume();



	//p1.WaitForThread();
	//p2.WaitForThread();
	//p3.WaitForThread();
	//p4.WaitForThread();

	disp.WaitForThread();
	screen.WaitForThread();

	return 0;
}