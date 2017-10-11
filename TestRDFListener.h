#ifndef TESTRDFLISTENER_H_
#define TESTRDFLISTENER_H_

#include <TRex2/Packets/SubPkt.h>
#include <TRex2/Packets/PubPkt.h>
#include "RDFConstructor/RDFResultListener.h"
#include "Common/RDFStructures.h"

/**
 * RDF output listener, implementing the abstract class RDFResultListener.
 * This class in particular handles the RDFEvent and prints on screen triples in a turtle-similar format.
 */
class TestRDFListener: public RDFResultListener {
public:
	/**
	 * Constructor saving subscription to event (eventually with constraints).
	 */
	TestRDFListener();

	virtual ~TestRDFListener();

	/**
	 * Takes the RDFEvent, checks subscription constraints and prints results.
	 */
	virtual void handleResult(RDFEvent* event);

	long getNumResults();

private:
	long numResults;
	void printMessage(std::string msg);
};

#endif /* TESTRDFLISTENER_H_ */
