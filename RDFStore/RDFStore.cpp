#include "RDFStore.h"

RDFStore::RDFStore(const char* type, const char* kb, const char* dlog, const char** prefixes, int prefixesLength) {
	store = new RDFoxDataStore;
	oldEvent = new char[1000];
	firstRun = true;
	this->prefixesArray = prefixes;
	this->prefixesArrayLength = prefixesLength;
	RDFoxDataStore_Create(store, type, NULL , 0);
	RDFoxDataStore_Initialize(*store);
	RDFoxDataStore_ImportFile(*store, kb, 0, false);
	RDFoxDataStore_ImportFile(*store, dlog, 0, false);
	RDFoxDataStore_ApplyRules(*store, false);
}

RDFStore::~RDFStore(){
	RDFoxDataStore_Dispose(*store);
	delete store;
	for (auto &query : queries) {
		delete query.second;
	}
}

//Finds var specified in the query string
std::vector<std::string> getVars(std::string query, int all){
	std::vector<std::string> var;
	std::string temp;
	int isNewVar = 1;

	for(std::string::iterator it=query.begin(); it!=query.end(); it++){
		if(*it == '?' || *it == '$'){//found var
			it++;
			while (*it != ' '){
				temp.push_back(*it);
				it++;
			}
			if(all == 1){//checks for duplicates (for 'select *' queries, where pattern must be checked to extract vars)
				for(std::vector<std::string>::iterator itVars=var.begin(); itVars!=var.end(); itVars++){
					if(temp.compare(*itVars) == 0){
						isNewVar = 0;
						break;//it's a duplicate, can exit
					}
				}
			}
			if(isNewVar == 1){
				var.push_back(temp);
			}
			isNewVar = 1;
			temp.clear();
		}
	}
	return var;
}

//RDFox "select *" queries not properly working...(?s ?p ?o -> resource[0]=?p, [1]=?o, [2]=?s )
//It is better to specify all vars separatedly
std::vector<std::string> findVars(const char* query){
	std::string temp = query;
	std::string querystring = query;
	unsigned inizio, fine;
	size_t found;

	std::transform(querystring.begin(), querystring.end(), temp.begin(), ::tolower);
	inizio = temp.find("select");
	fine = temp.find(" where");
	std::string nuova = querystring.substr(inizio+7, (fine-7)-inizio+1);
	found = nuova.find_first_of("*");
	if (found != std::string::npos){
		return getVars(querystring.substr(querystring.find_first_of("{"), querystring.find_last_of("}")-querystring.find_first_of("{")+1), 1);
	} else{
		return getVars(nuova, 0);
	}
}

void RDFStore::addQuery(int type, std::string name, std::string string){
	if (queries.find(type) == queries.end()) { //add a new query if it is not present
		RuleQuery *temp = new RuleQuery;
		temp->eventType = type;
		temp->queryName = name;
		temp->queryString = string;
		temp->vars = findVars(string.c_str());
		queries.insert(std::make_pair(type, temp));
	}
}

//Import update: 0 ADD
//               1 SCHEDULE_FOR_ADDITION
//		 		 2 SCHEDULE_FOR_DELETION
//See RDFox: Common.h
void RDFStore::processRdfEvent(const char* event, std::vector<Event *> &teslaEvents) {
	updateKnowledge(event);
	performReasoning();
	evaluateQueries(teslaEvents);
}

void RDFStore::updateKnowledge(const char* event) {
	if (!firstRun) {
		RDFoxDataStore_ImportFile(*store, oldEvent, 2, false); //delete last event
	} else {
		firstRun = false;
	}
	RDFoxDataStore_ImportFile(*store, event, 1, false);//add new event
	strcpy(oldEvent, event);
}

void RDFStore::performReasoning() {
	RDFoxDataStore_ApplyRules(*store, true); //true = incrementally
}

void RDFStore::evaluateQueries(std::vector<Event *> &teslaEvents) {
	for (auto it : queries) {
		evaluateQuery(it.second, teslaEvents);
	}
}

//Calls RDFox API
void RDFStore::evaluateQuery(RuleQuery* q, std::vector<Event*> &events) {
	size_t numVars = 0;
	size_t isQueryMatched = 0;
	RDFoxDataStoreTupleIterator queryIterator;

	RDFoxDataStoreTupleIterator_CompileQuery(&queryIterator, *store, q->queryString.c_str(), NULL, 0, prefixesArray, prefixesArrayLength);
	RDFoxDataStoreTupleIterator_GetArity(&numVars, queryIterator);
	RDFoxDataStoreResourceID* const resourceIDs = new RDFoxDataStoreResourceID[numVars];
	RDFoxDataStoreTupleIterator_Open(&isQueryMatched, queryIterator, numVars, resourceIDs);

	while (isQueryMatched != 0) { // while there are still  query results, do the loop and create a new event
		Event *event = new Event;
		event->eventType = q->eventType;
		for (unsigned int j = 0; j<numVars; j++) { //define attributes of event (results of query variables)
			Resource *res = new Resource;
			size_t bufferLength;
			RDFoxDataStoreTupleIterator_GetResource(queryIterator, resourceIDs[j], &res->datatypeID, res->lexicalForm, &bufferLength);
			event->attributes.insert(std::make_pair(q->vars[j], res));
		}
		events.push_back(event);
		RDFoxDataStoreTupleIterator_GetNext(&isQueryMatched, queryIterator, numVars, resourceIDs);
	}

	RDFoxDataStoreTupleIterator_Dispose(queryIterator);
	delete[] resourceIDs;
}
