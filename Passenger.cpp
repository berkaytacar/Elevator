#include "Passenger.h"
#include "C:\RTExamples\RTExamples\rt.h"


int Passenger::main() {
    CTypedPipe <int>	p2("Pipe2", 1024);

    while (1) {
        // decide start and finsih
        start = rand() % 10;
        finish = rand() % 10;
    
        if (start == finish) {
            if (start == 9) {
                finish--;
            }
            else if (finish == 0) {
                start++;
            }
            else {
                start--;
            }
        }
        // decide direction to go to
        if (start > finish) {
            //dir = -1;
            dir = 'd';
        }
        else if (start < finish) {
            //dir = 1;
            dir = 'u';
        }
        // now send them to the pipeline
        //int msg1 = dir; // msg1 is dir
        //int ms2 = start;
        //int msg3 = finish;
        // change these for algo to understand
        start += 48;
        finish += 48;
        //int arrPsg[3];// dir start finish

        m2->Wait();
        p2.Write(&dir);// send the direction first 
        p2.Write(&start);
        p2.Write(&finish);
        m2->Signal();


    }
	


	return 0;

}