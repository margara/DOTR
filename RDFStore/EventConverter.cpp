#include "EventConverter.h"

//Substitutes the first part of an IRI with its prefix, as defined in the RDF store
void shrinkIRI(char* lexicalForm, const char** prefixesArray, int prefixesLength){
	std::string string(lexicalForm);
	size_t found;
	for(int i = 0; i < prefixesLength; i = i+2){
		std::string prefix(*(prefixesArray+i+1));
		found = string.find(prefix);
		if(found == 0){//the position of the prefix IRI must be the first character
			string.replace(string.begin(), string.begin()+ prefix.size(), *(prefixesArray+i));
			strcpy(lexicalForm, string.c_str());
			break;
		}
	}
}

//See RDFox: Common.h for datatypeID
//    TRex: Const.h for ValType
void defineAttFromType(Attribute* att, Resource* res, Event* event, const char** prefixesArray, int prefixesLength) {
	switch(res->datatypeID){
	case 1://IRI
		att->type = STRING;
		shrinkIRI(res->lexicalForm, prefixesArray, prefixesLength); //cambio IRI col suo prefisso
		strcpy(att->stringVal, res->lexicalForm);
		break;
	case 5://INT
		att->type = INT;
		att->intVal = atoi(res->lexicalForm);
		break;
	case 6://FLOAT
		att->type = FLOAT;
		att->floatVal = (float)atof(res->lexicalForm);
		break;
	case 7://DOUBLE, loses precision
		att->type = FLOAT;
		att->floatVal = (float)atof(res->lexicalForm);
		break;
	case 8://BOOL
		att->type = BOOL;
		if (strcmp(res->lexicalForm, "true") == 0){
			att->boolVal = true;
		} else{
			att->boolVal = false;
		}
		break;
	default:
		att->type = STRING;
		strcpy(att->stringVal, res->lexicalForm);
		break;
	}
}

EventConverter::EventConverter() {
	timeDistanceBetweenEvents = 0;
	timeLastEvent = 0;
}

EventConverter::~EventConverter() {
	// Nothing to do
}

//Converts RdfEvent into TeslaEvent and frees memory about RdfEvent
void EventConverter::convertToTesla(std::vector<Event*> &events, RDFConstructor* constructor, std::vector<PubPkt*> &pubPkts, const char** prefixesArray, int prefixesLength) {
	std::map<int, Template*> templateMap = constructor->getRdfEventTemplates();
	if (timeDistanceBetweenEvents > 0) {
		timeLastEvent += timeDistanceBetweenEvents;
	}
	for (auto *event : events) {
		int num = event->attributes.size();
		int type = event->eventType;
		Attribute tempAtt[num];
		int i = 0;
		for (auto res : event->attributes) {
			strcpy(tempAtt[i].name, res.first.c_str());
			defineAttFromType(tempAtt+i, res.second, event, prefixesArray, prefixesLength);
			delete res.second;//PubPkt created, frees event memory (no more needed)
			i++;
		}
		PubPkt* temp = new PubPkt(type, tempAtt, num);
		if (timeDistanceBetweenEvents > 0) {
			temp->setTime(timeLastEvent);
		}
		for (auto it : templateMap) {
			Template* templateCE = it.second;
			if(templateCE->isRuleAllWithin == true){
				if (type == templateCE->allRuleInfos->typeTerminator){
					templateCE->allRuleInfos->RootTimestamps.push_back(temp->getTimeStamp());
				}
				if (type == templateCE->allRuleInfos->typeEventAll){
					templateCE->allRuleInfos->AllTimestamps.push_back(temp->getTimeStamp());
				}
			}
		}
		pubPkts.push_back(temp);
		delete event;
	}
}

void EventConverter::setTimeDistanceBetweenEvents(long timeDistanceBetweenEvents) {
	this->timeDistanceBetweenEvents = timeDistanceBetweenEvents;
}
