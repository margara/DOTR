#ifndef EVENTCONVERTER_H
#define EVENTCONVERTER_H

#include <TRex2/Packets/PubPkt.h>
#include "RDFStore.h"
#include "../Common/RDFStructures.h"
#include "../RDFConstructor/RDFConstructor.h"
#include <vector>
#include <string>

class EventConverter {
public:
	EventConverter();

	virtual ~EventConverter();

	/**
	 * Implements the lowering rule.
	 * It is just a function, kept separated from the RDF store,
	 * just to emphasize the implementation of the lowering rule.
	 */
	void convertToTesla(std::vector<Event*> &events, RDFConstructor* constructor, std::vector<PubPkt*> &pubPkts, const char** prefixesArray, int prefixesLength);

	void setTimeDistanceBetweenEvents(long timeDistanceBetweenEvents);

private:
	long timeDistanceBetweenEvents;
	long timeLastEvent;

};
#endif /*EVENTCONVERTER_H*/
