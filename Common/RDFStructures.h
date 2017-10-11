#ifndef RDFSTRUCTURES_H
#define RDFSTRUCTURES_H

#include <TRex2/Common/Structures.h>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <CppRDFox/RDFoxDataStore.h>

#define MAX_LENGTH 500

/**
 * Represents a query extracted from parsing a RDF Tesla rule.
 */
typedef struct SparqlQuery {
	int eventType;
	std::string queryName;
	std::string queryString;
	std::vector<std::string> vars;
} RuleQuery;

/**
 * Represents one single variable result of a sparql query evaluated by the rdf store.
 * The value is saved inside a char buffer.
 * Noteworthy RDFox datatypeID values compatible with TRex:
 * D_IRI_REFERENCE = 1; //treated as string...
 * D_XSD_STRING = 3;
 * D_XSD_INTEGER = 5;
 * D_XSD_FLOAT = 6;
 * D_XSD_DOUBLE = 7;
 * D_XSD_BOOLEAN = 8.
 */
typedef struct SparqlResource {
	RDFoxDataStoreDatatypeID datatypeID; 	   //resource type as specified inside RDFox file Common.h
	char lexicalForm[MAX_LENGTH];
} Resource;

/**
 * A collection of query results evaluated by the rdf store.
 * A query produces bindings between a variable name and its actual value, and they are saved in a map.
 * As defined by the lowering rule, a query answer defines a Tesla event where sparql variables are its attributes.
 */
typedef struct SparqlAnswer {
	int eventType;				 					//event type == query type (as defined by the lowering rule)
	std::map<std::string, Resource*> attributes;
} Event;

/**
 * An helper structure to evaluate SCEP rules where each-within appears together with all-within (<---to divide correctly generated events)
 * Example:
 * From A and each B from A and all C from B <----all-within is considered as each by TRex, but we have to create an event for each "each" where
 * we regroup every "all", hence we must divide the generated events (generated as each...each) in a number of groups equal to the number of each
 * events (all the "all" events C participate in every "each" event B, but TRex generates each C for each B).
 * C1 C2 C3 B1 B2 A1 <----- 2 Complex Events (A1B1C1C2C3, A1B2C1C2C3) if using all-within, but originally TRex creates A1B1C1, A1B1C2, A1B1C3, A1B2C1, A1B2C2, A1B2C3. We save occurrence timestamps and divide the 6 events in 2 groups of 3 events (as 2 are the each event B received).
 * The structure is filled from the EventConverter (before sending events to TRex), then maintained by the TRexListener component.
 */
typedef struct AllWithin {
	int typeTerminator;
	int typeEventAll;
	TimeMs window;
	std::list<TimeMs> RootTimestamps; //dynamic buffer to avoid that some events overwrite values before they are processed by TRexListener
	std::list<TimeMs> AllTimestamps;
} AllHelper;

/**
 * Single triple pattern of a RDF complex event, extracted from parsing a rule.
 */
typedef struct RDFTripleTemplate {
	bool isSubVar;
	bool isPredVar;
	bool isObjVar;
	char subject[MAX_LENGTH];
	char predicate[MAX_LENGTH];
	char object[MAX_LENGTH];
} TripleTemplate;

/**
 * Template of a RDF complex event, extracted from parsing a rule.
 */
typedef struct RDFTemplate {
	int eventType;
	std::vector<TripleTemplate> triples;
	bool isRuleAllWithin;					//helps implementing a first version of ALL_WITHIN (without modifying TRex library)
	bool isRuleEachAllWithin;
	AllHelper* allRuleInfos;					//useful only if isRuleEachAllWithin is true
} Template;

/**
 * A single triple result, part of a generated RDF Complex Event.
 */
typedef struct RDFTriple {
	char subject[MAX_LENGTH];
	char predicate[MAX_LENGTH];
	char object[MAX_LENGTH];
} Triple;

/**
 * RDF Complex event, final result of RDF reasoning and CEP processing.
 * It is the RDF Complex event template, with TRex processing results instead of vars, as defined by the lifting rule.
 */
typedef struct ComplexEvent {
	int eventType;
	const char** prefixesArray; 							// RDF prefixes used for IRI (from RDF store)
	int prefixesArrayLength;
	std::vector<Triple *> triples;							// Triples of the first result event
	std::vector<std::vector<Triple *> > duplicateTriples;   // Duplicate triples as events of ALL_WITHIN rules (vector of events(=vector of triples))
} RDFEvent;

#endif /*RDFSTRUCTURES_H*/
