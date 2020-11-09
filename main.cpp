#include "C:\RTExamples\RTExamples\rt.h"
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "io.h"


int main() {
	Dispatcher disp(1);
	IO screen(10);

	disp.Resume();
	screen.Resume();

	disp.WaitForThread();
	screen.WaitForThread();
	return 0;
}