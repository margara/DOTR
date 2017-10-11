#include "TRexListener.h"

#include <chrono>

TRexListener::TRexListener(RDFConstructor* constructor, const char** prefixesArray, int prefixesArrayLength) {
	this->constructor = constructor;
	this->prefixesArray = prefixesArray;
	this->prefixesArrayLength = prefixesArrayLength;
	this->totalProcessingTime = 0;
}	

TRexListener::~TRexListener(){
}

//Converts the result string from RDFox into a compatible TRex value
void copyValue(char *dest, Attribute att){
	switch(att.type){
	case INT:
		strcpy(dest, std::to_string(att.intVal).c_str());
		break;
	case FLOAT:
		strcpy(dest, std::to_string(att.floatVal).c_str());
		break;
	case BOOL:
		strcpy(dest, std::to_string(att.boolVal).c_str());
		break;
	case STRING:
		strcpy(dest, att.stringVal);
		break;
	}
}

// Converts the PubPkt into an RDFEvent
RDFEvent* TRexListener::createRDF(PubPkt* pkt, Template* templateCE) {
	RDFEvent* event = new RDFEvent;
	event->eventType = pkt->getEventType();
	event->prefixesArray = prefixesArray;
	event->prefixesArrayLength = prefixesArrayLength;
	for (auto it : templateCE->triples) {
		Triple *t = new Triple;
		strcpy(t->subject, it.subject);
		strcpy(t->predicate, it.predicate);
		strcpy(t->object, it.predicate);
		event->triples.push_back(t);
	}
	for (int k = 0; k < pkt->getAttributesNum(); k++) {
		Attribute att = pkt->getAttribute(k);
		for (unsigned int i = 0; i < templateCE->triples.size(); i++){
			TripleTemplate temp = templateCE->triples[i];
			if (temp.isSubVar && strcmp((temp.subject+1), att.name) == 0) {//+1 removes the '?' or '$' of sparql var
				copyValue(event->triples[i]->subject, att);
			}
			if (temp.isPredVar && strcmp((temp.predicate+1), att.name) == 0) {
				copyValue(event->triples[i]->predicate, att);
			}
			if (temp.isObjVar && strcmp((temp.object+1), att.name) == 0) {
				copyValue(event->triples[i]->object, att);
			}
		}
	}
	return event;
}

//Called just for ALL_WITHIN rules
void TRexListener::createRDFAll(std::map<int, std::vector<PubPkt*> > typesOfGroupEvents, std::map<int, Template*> templates, std::vector<RDFEvent*> &results) {
	for (std::map<int, std::vector<PubPkt*> >::iterator it = typesOfGroupEvents.begin(); it != typesOfGroupEvents.end(); it++) {
		int nEventsToCreate;//init
		int numAllEvents = 0;
		std::vector<PubPkt*> pubPktVector = it->second;
		Template* templateCE = templates.find(it->first)->second;
		unsigned int numOfTriples = templateCE->triples.size();
		unsigned int numOfPkt =  pubPktVector.size();
		if (templateCE->isRuleEachAllWithin == true) { //workaround for rules with each-within and all-within together in the same pattern
			//Maintains the AllHelper structure defined in the template by deleting no more useful timestamps and counting number of events
			//it works for patterns like from A and each B from A and all C from B (simple each...all patterns), but for more complex ones?
			std::list<TimeMs>::iterator rootEvTime = templateCE->allRuleInfos->RootTimestamps.begin();
			std::list<TimeMs>::iterator allEvTime = templateCE->allRuleInfos->AllTimestamps.begin();
			bool deleted = false;
			//clean root timestamps no more useful
			while (rootEvTime != templateCE->allRuleInfos->RootTimestamps.end()){
				if (rootEvTime->getTimeVal() <= allEvTime->getTimeVal()){
					//terminator event happened before the all event, don't need this value anymore
					deleted = true;
					rootEvTime = templateCE->allRuleInfos->RootTimestamps.erase(rootEvTime);//side-effect: increase rootEvTime
				} else {
					//found root > allEvent (c'è per forza perchè è stato creato almeno un evento complesso)
					break;//found, can exit
				}
				if (deleted == false){//increment (if rootTimestamp has not been deleted)
					rootEvTime++;	//actually it never enters it (timeRoot is always found because a Complex Event has been created, but when it is found it exits thanks to break instruction)
				}
				deleted = false;
			}
			//loop on AllEvents, deleting the ones no more valid (out of window size)
			while (allEvTime != templateCE->allRuleInfos->AllTimestamps.end()){
				if ((rootEvTime->getTimeVal() - allEvTime->getTimeVal()) > templateCE->allRuleInfos->window.getTimeVal()){
					//window root/event > than max, can delete the element (no more useful)
					allEvTime = templateCE->allRuleInfos->AllTimestamps.erase(allEvTime);
				} else if(rootEvTime->getTimeVal() < allEvTime->getTimeVal()){
					//can exit, because allEvent > rootEvent
					templateCE->allRuleInfos->RootTimestamps.pop_front();//delete first element, we don't need it anymore
					break;
				} else{
					numAllEvents++;//count the number of "all" events for each "each"
					allEvTime++;
				}
			}
			nEventsToCreate = (numOfPkt / numAllEvents);			//one event for each "each"
		} else {
			nEventsToCreate = 1;									//one single event
			numAllEvents = numOfPkt;
		}
		for (int e = 0; e < nEventsToCreate; e++){
			RDFEvent* event = new RDFEvent;
			event->eventType = it->first;
			event->prefixesArray = prefixesArray;
			event->prefixesArrayLength = prefixesArrayLength;
			for (int j = 0 + e*numAllEvents; j < numAllEvents + e*numAllEvents; j++){
				std::vector<Triple *> dupTriples;
				for (unsigned int n = 0; n < numOfTriples; n++){
					TripleTemplate temp = templateCE->triples[n];
					if (j == (0 + e*numAllEvents)){//first PubPkt, no duplicates for sure
						Triple *t = new Triple;
						strcpy(t->subject, temp.subject);
						strcpy(t->predicate,temp.predicate);
						strcpy(t->object, temp.object);
						event->triples.push_back(t);
					} else { // It is not the first PubPkt, needs to be handled as a duplicate
						Triple *dt = new Triple;
						strcpy(dt->subject, temp.subject);
						strcpy(dt->predicate,temp.predicate);
						strcpy(dt->object, temp.object);
						dupTriples.push_back(dt);
					}
				}
				if (j != (0 + e*numAllEvents)) {
					event->duplicateTriples.push_back(dupTriples); // It's not first PubPkt, so push duplicate PubPkt into the vector
				}
			}
			results.push_back(event);
		}
	}
}


// Notifies listeners saved in the RDF Constructor
void TRexListener::notifyRDFListeners(RDFEvent* event){
	for (auto *listener : constructor->getRDFListeners()) {
		listener->handleResult(event);
	}
}

double TRexListener::getTotalProcessingNanoTime() {
	return totalProcessingTime;
}

// Implements the lifting rule, converting PubPkts into RDFEvents, and notifies rdf output listeners
void TRexListener::handleResult(std::set<PubPkt *> &genPkts, double procTime) {
	auto start = std::chrono::high_resolution_clock::now();
	bool atLeastOneAll = false;
	std::map<int, std::vector<PubPkt*> > typesOfGroupEvents;
	std::map<int, Template*> templates = this->constructor->getRdfEventTemplates();
	for (auto *pubPkt : genPkts) {
		int type = pubPkt->getEventType();
		Template* templateCE = templates.find(type)->second;
		if (templateCE->isRuleAllWithin == true) {
			atLeastOneAll = true;
			auto it = typesOfGroupEvents.find(type);
			if (it == typesOfGroupEvents.end()){
				// New complex event(=generated pkt) type, adds a vector for this type
				std::vector<PubPkt*> eventsToGroup;
				eventsToGroup.push_back(pubPkt);
				typesOfGroupEvents.insert(make_pair(type, eventsToGroup));
			} else {
				// Type already defined, adds the PubPkt in the existing vector
				it->second.push_back(pubPkt);
			}
		} else { //rule is not ALL_WITHIN
			// Generate RDF for single PubPkt
			RDFEvent *rdfEvent = createRDF(pubPkt, templateCE);
			notifyRDFListeners(rdfEvent);
			// Free memory of triples and duplicates
			for (auto *triple : rdfEvent->triples) {
				delete triple;
			}
			for (auto tripleVec : rdfEvent->duplicateTriples) {
				for (auto *triple : tripleVec) {
					delete triple;
				}
			}
			delete rdfEvent;
		}
	}
	if (atLeastOneAll == true) { // The rule has ALL_WITHIN, needs to call another function
		std::vector<RDFEvent*> rdfEventsAll;
		createRDFAll(typesOfGroupEvents, templates, rdfEventsAll);
		for (auto *event : rdfEventsAll) {
			this->notifyRDFListeners(event);
			// Free memory of triples and duplicates
			for (auto *triple : event->triples) {
				delete triple;
			}
			for (auto tripleVec : event->duplicateTriples) {
				for (auto *triple : tripleVec) {
					delete triple;
				}
			}
			delete event;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();

	totalProcessingTime += duration;
}
