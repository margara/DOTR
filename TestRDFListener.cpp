#include "./TestRDFListener.h"

#include "Eval/EvalConsts.h"

TestRDFListener::TestRDFListener() {
	numResults = 0;
}

TestRDFListener::~TestRDFListener() { }

// For further processing of RDFEvent, a copy must be done (event memory is freed by TRexListener)
void TestRDFListener::handleResult(RDFEvent* event) {
	numResults++;
	if (printResults) {
		bool isFirstEvent = true;
		printMessage("New complex event created:");
		for (int n = 0; n < event->prefixesArrayLength; n+=2) {
			std::cout << "@prefix " << event->prefixesArray[n] << " <" << event->prefixesArray[n+1] << "> ." << std::endl;
		}
		std::cout <<"{";
		for (auto triple : event->triples) {
			std::cout << triple->subject << " ";
			std::cout << triple->predicate << " ";
			std::cout << triple->object;
			std::cout << ".\n";
		}
		std::cout << "}\n";
		isFirstEvent = false;
		for (unsigned int i = 0; i < event->duplicateTriples.size(); i++) {
			if (isFirstEvent) {
				printMessage("New complex event created:");
			}
			isFirstEvent = false;
			std::cout <<"{";
			for (auto dupTriple : event->duplicateTriples[i]) {
				std::cout << dupTriple->subject << " ";
				std::cout << dupTriple->predicate << " ";
				std::cout << dupTriple->object;
				std::cout << ".\n";
			}
			std::cout << "}\n";
		}
	}
}

long TestRDFListener::getNumResults() {
	return numResults;
}
