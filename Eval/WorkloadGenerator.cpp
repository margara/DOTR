#include "WorkloadGenerator.h"

#include <TRex2/Packets/SubPkt.h>
#include <TRex2/Packets/PubPkt.h>
#include "../Eval/EvalConsts.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>

void generateKb(int numRooms, int numObjectsPerRoom, int numSensors, int numSensorTypes, int numAdditionalEntries) {
	std::ofstream kb(kbPath);
	kb << "@prefix a1: <http://localhost#>.\n\n";

	for(int i=0; i<numRooms; i++) {
		kb << "a1:Room" << i << " a1:number " << i << ".\n";
		for (int j=0; j<numObjectsPerRoom; j++) {
			kb << "a1:Obj" << (i*numObjectsPerRoom) + j << " a1:isequippedin a1:Room" << i << ".\n";
		}
	}

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,numObjectsPerRoom*numRooms -1);
	for (int i=0; i<numSensors; i++) {
		int obj = distribution(generator);
		kb << "a1:S" << i << " a1:isattachedto a1:Obj" << obj << ".\n";
	}

	for (int i=0; i<numAdditionalEntries; i++){
		kb << "a1:S" << i << " a1:test1 " << rand() % 10 << ".\n";
		kb << "a1:S" << i << " a1:test2 " << rand() % 10 << ".\n";
		kb << "a1:S" << i << " a1:test3 " << rand() % 10 << ".\n";
		kb << "a1:S" << i << " a1:test4 " << rand() % 10 << ".\n";
		kb << "a1:S" << i << " a1:test5 " << rand() % 10 << ".\n";
	}

	kb.close();
}

void generateInputEvents(int numEvents, int numTriples, int numSensors, int percTermin, int numProperties, int numValues) {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> percent(0, 99);
	std::uniform_int_distribution<int> values(0, numValues-1);
	std::uniform_int_distribution<int> properties(1, numProperties-1);
	std::uniform_int_distribution<int> sensors(0, numSensors-1);

	for (int i=0; i < numEvents; i++) {
		std::stringstream s;
		s << eventPath << i << ".ttl";
		std::ofstream inputEvent(s.str());
		inputEvent << "@prefix a1: <http://localhost#>.\n\n";
		for (int j = 0; j < numTriples; j++) {
			int value = values(generator);
			bool isTerm = percent(generator) < percTermin;
			int property = isTerm ? 0 : properties(generator);
			int sensor = sensors(generator);

			inputEvent << "a1:S" << sensor << " a1:prop" << property << " " << value << ".\n";
		}
		inputEvent.close();
	}
}

void generateInference(int numAdditionalRules, int numDynamicRules, int numSensorTypes) {
	std::ofstream infrule(infRulesPath);
	infrule << "@prefix a1: <http://localhost#>.\n\n";
	infrule << "a1:haslocation(?X, ?Z) :- a1:isattachedto(?X,?Y), a1:isequippedin(?Y, ?Z) .\n";
	for (int i = 0; i < numAdditionalRules; i++){
		infrule << "a1:rule" << i << "(?X, ?Z) :- a1:isattachedto(?X,?Y), a1:isequippedin(?Y, ?Z) .\n";
	}
	for (int i = 0; i < numDynamicRules; i++) {
		for (int j = 0; j < numSensorTypes; j++) {
			infrule << "a1:dynamicRule" << i << "(?X, ?Z) :- a1:prop" << j << "(?X, ?Y), a1:isattachedto(?X, ?Z) .\n";
		}
	}
	infrule.close();
}

// Consider the number of values...
void generateRuleQuery(int numOfRules, TRexEngine* engine, RDFStore* store, RDFConstructor* constructor, RDFResultListener *listener, int seqLen, CompKind compKind, bool sparqlFilter, int firstComplexEventId) {
	// TODO Check event type!!!
	int eventType = 0;
	for (int i = 0; i < numOfRules; i++){
		RulePkt *rule = new RulePkt(i==0);

		Template* templateCE = new Template;
		templateCE->eventType = firstComplexEventId + i;
		templateCE->isRuleAllWithin = false;		// Da cambiare a true se uso regole all-within
		templateCE->isRuleEachAllWithin = false;	// Da cambiare a true se uso regole all-within + each-within
		templateCE->allRuleInfos = new AllHelper;

		TripleTemplate t1;
		strcpy(t1.subject, "a1:risultato");
		strcpy(t1.predicate, "a1:is");
		strcpy(t1.object, "?num");
		t1.isSubVar = false;
		t1.isPredVar = false;
		t1.isObjVar = true;
		templateCE->triples.push_back(t1);

		int filter = 0; // FIXME!!! 10 * i;

		if (sparqlFilter) {
			rule->addRootPredicate(eventType, NULL, 0);

			std::stringstream q;
			q << "select ?sensor ?num ?room ";
			q << "where { ";
			q << "?sensor a1:prop0 ?num. ";
			q << "?sensor a1:haslocation ?room. ";
			q << "FILTER(?num > " << filter << ")}";
			std::string query = q.str();

			std::stringstream n;
			n << "query_" << i << "_0";
			std::string name = n.str();

			store->addQuery(eventType, name, query);
		} else {
			const int customEventType = 0;
			Constraint c[1];
			strcpy(c[0].name, "num");
			c[0].type = INT;
			c[0].op = GT;
			c[0].intVal = filter;
			rule->addRootPredicate(customEventType, c, 1);

			std::stringstream q;
			q << "select ?sensor ?num ?room ";
			q << "where { ";
			q << "?sensor a1:prop0 ?num. ";
			q << "?sensor a1:haslocation ?room. }";
			std::string query = q.str();

			std::stringstream n;
			n << "query_" << i << "_0";
			std::string name = n.str();

			store->addQuery(customEventType, name, query);
		}
		eventType++;

		for (int p = 1; p < seqLen; p++) {
			if (sparqlFilter) {
				TimeMs time(30 * 1000);
				std::stringstream q;
				q << "select ?sensor ?num ?room ";
				q << "where { ";
				q << "?sensor a1:prop" << p << " ?num. ";
				q << "?sensor a1:haslocation ?room. ";
				q << "FILTER(?num > " << filter << ")}";
				std::string query = q.str();

				std::stringstream n;
				n << "query_" << i << "_" << p;
				std::string name = n.str();

				store->addQuery(eventType, name, query);

				rule->addPredicate(eventType, NULL, 0, p-1, time, compKind);

				char room[] = "room";
				rule->addParameterBetweenStates(0, room, p, room);
			} else {
				const int customEventType = p;
				TimeMs time(30 * 1000);
				std::stringstream q;
				q << "select ?sensor ?num ?room ";
				q << "where { ";
				q << "?sensor a1:prop" << p << " ?num. ";
				q << "?sensor a1:haslocation ?room. }";
				std::string query = q.str();

				std::stringstream n;
				n << "query_" << i << "_" << p;
				std::string name = n.str();

				store->addQuery(customEventType, name, query);

				Constraint c[1];
				strcpy(c[0].name, "num");
				c[0].type = INT;
				c[0].op = GT;
				c[0].intVal = filter;
				rule->addPredicate(customEventType, c, 1, p-1, time, compKind);

				char room[] = "room";
				rule->addParameterBetweenStates(0, room, p, room);
			}
			eventType++;
		}

		char num[] = "num";
		RulePktValueReference *numref = new RulePktValueReference(0, num, STATE);
		CompositeEventTemplate* warn_tmplate = new CompositeEventTemplate(templateCE->eventType);
		OpTree* numOp = new OpTree(numref, INT);
		warn_tmplate->addAttribute(num, numOp);
		rule->setCompositeEventTemplate(warn_tmplate);
		engine->processRulePkt(rule);

		constructor->addTemplate(templateCE->eventType, templateCE);
		constructor->addRDFListener(listener);
	}
}
