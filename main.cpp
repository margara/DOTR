#include "Test/Test.h"
#include "Test/TestCityBench.h"
#include "Eval/EvaluationRunner.h"

int main() {
	const int numEvents = 20000;

//	 runEvaluationSuite();
//
//	for (int i=1; i<=3000; ) {
//		cityBenchQuery(1, numEvents, i);
//		if (i<10) {
//			i += 3;
//		} else if (i<100) {
//			i += 30;
//		} else if (i<1000) {
//			i += 300;
//		} else {
//			i += 1000;
//		}
//	}

	for (int i=1; i<=3000; ) {
		cityBenchQuery(2, numEvents, i);
		if (i<10) {
			i += 3;
		} else if (i<100) {
			i += 30;
		} else if (i<1000) {
			i += 300;
		} else {
			i += 1000;
		}
	}

	return 0;
}
