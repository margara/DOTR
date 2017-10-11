#ifndef RDFRESULTLISTENER_H_
#define RDFRESULTLISTENER_H_

#include "../Common/RDFStructures.h"

/**
 * Abstract class similar to TRex abstract class ResultListener, but handling RDFEvent instead of PubPkt.
 */
class RDFResultListener {
public:
	virtual ~RDFResultListener() { }

	/**
	 * Handles the generated RDFEvent.
	 */
	virtual void handleResult(RDFEvent* event) = 0;
};

#endif /*RDFRESULTLISTENER_H_*/
