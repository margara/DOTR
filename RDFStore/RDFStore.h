#ifndef RDFSTORE_H_
#define RDFSTORE_H_

#include <CppRDFox/RDFoxDataStore.h>
#include "../Common/RDFStructures.h"
#include <algorithm>
#include <iostream>
#include <string.h>

/**
 * Singleton representing the main memory triple store RDFox.
 */
class RDFStore {
public:

	/**
	 * Sets parameters for creating the RDFox store:
	 * one turtle file representing the ontology, the knowledge base;
	 * one file representing inference rules, a datalog file;
	 * one array and its length, for RDF prefixes: even positions for prefix, odd position for full URI
	 */
	RDFStore(const char* type, const char* kb, const char* dlog, const char** prefixes, int prefixesLength);

	~RDFStore();

	/**
	 * Adds a query that will be evaluated on the store during runtime execution.
	 * Queries are extracted from RDF Tesla rules.
	 */
	void addQuery(int eventType, std::string queryName, std::string queryString);

	/**
	 * Returns prefixes used in the store.
	 */
	const char** getPrefixesArray(){return prefixesArray;}

	int getPrefixesArrayLength(){return prefixesArrayLength;}

	std::map<int, RuleQuery*> &getQueryMap(){return queries;}

	/**
	 * Processes incoming events, importing a new one and deleting the old one,
	 * and evaluates stored queries after triple materialization.
	 * Queries results are stored as a vector of Events.
	 */
	void processRdfEvent(const char* event, std::vector<Event*> &teslaEvents);

	/**
	 * These three functions should be private and invoked only by processRdfEvent.
	 * They are currently public to simplify performance analysis
	 */
	void updateKnowledge(const char* event);
	void performReasoning();
	void evaluateQueries(std::vector<Event *> &teslaEvents);

protected:

	RDFStore();

private:
	RDFoxDataStore *store;

	// Pre-processing parameters
	const char** prefixesArray;
	int prefixesArrayLength;

	std::map<int, RuleQuery*> queries;
	char *oldEvent;
	bool firstRun;

	void evaluateQuery(RuleQuery* q, std::vector<Event*> &events);
};
#endif /*RDFSTORE_H*/
