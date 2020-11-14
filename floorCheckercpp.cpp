#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "updLink.h"
#include "inputPassenger.h"
#include "floorChecker.h"



int floorChecker::main() {
	InputPassenger ip(5, m2);
	ip.Resume();
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



	while (1) {
		if (U01.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(0, ip, 1, 1);
		}
		else if (U11.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(1, ip, 1, 1);

		}
		else if (U21.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(2, ip, 1, 1);

		}
		else if (U31.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(3, ip, 1, 1);

		}
		else if (U41.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(4, ip, 1, 1);

		}
		else if (U51.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(5, ip, 1, 1);

		}
		else if (U61.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(6, ip, 1, 1);

		}
		else if (U71.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(7, ip, 1, 1);

		}
		else if (U81.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(8, ip, 1, 1);

		}
		else if (U91.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(9, ip, 1, 1);

		}
		else if (U02.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(0, ip, 2, 1);

		}
		else if (U12.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(1, ip, 2, 1);

		}
		else if (U22.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(2, ip, 2, 1);

		}

		else if (U32.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(3, ip, 2, 1);

		}
		else if (U42.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(4, ip, 2, 1);

		}
		else if (U52.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(5, ip, 2, 1);

		}
		else if (U62.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(6, ip, 2, 1);

		}
		else if (U72.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(7, ip, 2, 1);

		}
		else if (U82.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(8, ip, 2, 1);

		}
		else if (U92.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(9, ip, 2, 1);

		}
		else if (D01.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(0, ip, 1, 2);
		}
		else if (D11.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(1, ip, 1, 2);

		}
		else if (D21.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(2, ip, 1, 2);

		}
		else if (D31.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(3, ip, 1, 2);

		}
		else if (D41.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(4, ip, 1, 2);

		}
		else if (D51.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(5, ip, 1, 2);

		}
		else if (D61.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(6, ip, 1, 2);

		}
		else if (D71.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(7, ip, 1, 2);

		}
		else if (D81.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(8, ip, 1, 2);

		}
		else if (D91.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(9, ip, 1, 2);

		}
		else if (D02.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(0, ip, 2, 2);

		}
		else if (D12.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(1, ip, 2, 2);

		}
		else if (D22.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(2, ip, 2, 2);

		}

		else if (D32.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(3, ip, 2, 2);

		}
		else if (D42.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(4, ip, 2, 2);

		}
		else if (D52.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(5, ip, 2, 2);

		}
		else if (D62.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(6, ip, 2, 2);

		}
		else if (D72.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(7, ip, 2, 2);

		}
		else if (D82.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(8, ip, 2, 2);

		}
		else if (D92.Wait(1) != WAIT_TIMEOUT) {
			sendPpl(9, ip, 2, 2);

		}

	}


	ip.WaitForThread();
	return 0;
}



void floorChecker::sendPpl(int f, InputPassenger& i, int e, int dir) {
	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines

	CCondition Max1("Full1");
	CCondition Max2("Full2");

	//DIR = 1 (up)  DIR = 2 (DOWN)
	if (Max2.Wait(50) != WAIT_TIMEOUT) {
		return;
	}

	if (dir == 1) {

		int n = i.upNum[f];
		printf("%d", n);
		for (int j = 0; j < n; j++) {
			int val = i.upWait[f][j];
			//printf("%d", val);
			m2->lock();
			e = '2';
			p1.Write(&e);
			p1.Write(&val);
			m2->unlock();
			i.upNum[f]--;
			if (Max2.Wait(80) != WAIT_TIMEOUT) {
				return;
			}
		}
		//not true
		
	}
	else {
		int n = i.downNum[f];
		for (int j = 0; j < n; j++) {
			int val = i.downWait[f][j];
			//printf("%d", val);
			m2->lock();
			e = 'd';
			p1.Write(&e);
			p1.Write(&val);
			m2->unlock();
		}
		//not true
		i.downNum[f] = 0;
	}


	return;


}
