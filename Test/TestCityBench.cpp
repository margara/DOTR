#include "TestCityBench.h"

#include <TRex2/Engine/TRexEngine.h>
#include <TRex2/Engine/ResultListener.h>
#include <TRex2/Packets/SubPkt.h>
#include <TRex2/Packets/PubPkt.h>
#include "../TestRDFListener.h"
#include "../RDFStore/RDFStore.h"
#include "../RDFStore/EventConverter.h"
#include "../Parser/RDFTRexRuleParser.h"
#include "../RDFConstructor/RDFConstructor.h"
#include "../Eval/EvalConsts.h"
#include <vector>
#include <queue>

inline void processPubPkt(vector<PubPkt*> &pubPkts, TRexEngine* e) {
	for (auto &pubPkt : pubPkts) {
		e->processPubPkt(pubPkt);
	}
}

void cityBenchQueryOnly() {
	const char type[] = "seq";
	std::string kb_string = cityBenchIn + "Q1/rdf/static.ttl";
	const char *kb = kb_string.c_str();
	int prefixesArrayLength = 42;

	const char* prefixesArray[] = { //
			"def:", "http://www.insight-centre.org/dataset/SampleEventService#", //
			"prov:", "http://purl.org/NET/provenance.owl#", //
			"tl:", "http://purl.org/NET/c4dm/timeline.owl#", //
			"emvo:", "http://sense.deri.ie/vocab/emvo#", //
			"owlssp:", "http://www.daml.org/services/owl-s/1.2/ServiceParameter.owl#", //
			"ssn:", "http://purl.oclc.org/NET/ssnx/ssn#", //
			"xml:", "http://www.w3.org/XML/1998/namespace", //
			"ces:", "http://www.insight-centre.org/ces#", //
			"ct:", "http://www.insight-centre.org/citytraffic#", //
			"owls:", "http://www.daml.org/services/owl-s/1.2/Service.owl#", //
			"up:", "http://www.ict-citypulse.eu/ontologies/userprofile#", //
			"muo:", "http://purl.oclc.org/NET/muo/ucum/", //
			"rdfs:", "http://www.w3.org/2000/01/rdf-schema#", //
			"sao:", "http://purl.oclc.org/NET/sao/", //
			"sce1:", "http://ict-citypulse.eu/experiments/Scenario1/", //
			"q:", "http://www.ict-citypulse.eu/ontologies/streamQoI/Quality", //
			"owlssc:", "http://www.daml.org/services/owl-s/1.2/ServiceCategory.owl#", //
			"xsd:", "http://www.w3.org/2001/XMLSchema#", //
			"rdf:", "http://www.w3.org/1999/02/22-rdf-syntax-ns#", //
			"osm:", "http://www.insight-centre.org/ontologies/osm#", //
			"aoi:", "http://ict-citypulse.eu/ontologies/StreamQoI/" //
	};

	RDFoxDataStore store;

	RDFoxDataStore_Create(&store, type, NULL , 0);
	RDFoxDataStore_Initialize(store);
	RDFoxDataStore_ImportFile(store, kb , 0, false);
	//RDFoxDataStore_ImportFile(store, dlogRules , 0, false);
	//RDFoxDataStore_ApplyRules(store, false);

	std::string q("SELECT ?x WHERE { ?x rdf:type ct:CongestionLevel. }");

	size_t numVars = 0;
	size_t isQueryMatched = 0;
	RDFoxDataStoreTupleIterator queryIterator;
	RDFoxDataStoreTupleIterator_CompileQuery(&queryIterator, store, q.c_str(), NULL, 0, prefixesArray, prefixesArrayLength);
	RDFoxDataStoreTupleIterator_GetArity(&numVars, queryIterator);

	RDFoxDataStoreResourceID* const resourceIDs = new RDFoxDataStoreResourceID[numVars];
	RDFoxDataStoreTupleIterator_Open(&isQueryMatched, queryIterator, numVars, resourceIDs);
	while (isQueryMatched != 0) {
		for (unsigned int j = 0; j<numVars; j++) { //define attributes of event (results of query variables)
			Resource *res = new Resource;
			size_t bufferLength;
			RDFoxDataStoreTupleIterator_GetResource(queryIterator, resourceIDs[j], &res->datatypeID, res->lexicalForm, &bufferLength);
			std::cout << res->datatypeID << " " << res->lexicalForm << std::endl;
		}
		RDFoxDataStoreTupleIterator_GetNext(&isQueryMatched, queryIterator, numVars, resourceIDs);
	}
}

void cityBenchQuery(int numQuery, int numEvents, int timeBetweenEvents) {

	const char type[] = "seq";
	std::string kbString = std::string(cityBenchIn + "Q" + std::to_string(numQuery) + "/rdf/static.ttl");
	const char *kb = kbString.c_str();
	const char dlogRules[] = "";
	int prefixesArrayLength = 42;

	const char* prefixesArray[] = { //
			"def:", "http://www.insight-centre.org/dataset/SampleEventService#", //
			"prov:", "http://purl.org/NET/provenance.owl#", //
			"tl:", "http://purl.org/NET/c4dm/timeline.owl#", //
			"emvo:", "http://sense.deri.ie/vocab/emvo#", //
			"owlssp:", "http://www.daml.org/services/owl-s/1.2/ServiceParameter.owl#", //
			"ssn:", "http://purl.oclc.org/NET/ssnx/ssn#", //
			"xml:", "http://www.w3.org/XML/1998/namespace", //
			"ces:", "http://www.insight-centre.org/ces#", //
			"ct:", "http://www.insight-centre.org/citytraffic#", //
			"owls:", "http://www.daml.org/services/owl-s/1.2/Service.owl#", //
			"up:", "http://www.ict-citypulse.eu/ontologies/userprofile#", //
			"muo:", "http://purl.oclc.org/NET/muo/ucum/", //
			"rdfs:", "http://www.w3.org/2000/01/rdf-schema#", //
			"sao:", "http://purl.oclc.org/NET/sao/", //
			"sce1:", "http://ict-citypulse.eu/experiments/Scenario1/", //
			"q:", "http://www.ict-citypulse.eu/ontologies/streamQoI/Quality", //
			"owlssc:", "http://www.daml.org/services/owl-s/1.2/ServiceCategory.owl#", //
			"xsd:", "http://www.w3.org/2001/XMLSchema#", //
			"rdf:", "http://www.w3.org/1999/02/22-rdf-syntax-ns#", //
			"osm:", "http://www.insight-centre.org/ontologies/osm#", //
			"aoi:", "http://ict-citypulse.eu/ontologies/StreamQoI/" //
	};

	RDFStore* store = new RDFStore(type, kb, dlogRules, prefixesArray, prefixesArrayLength);
	TRexEngine *trex = new TRexEngine(1);
	RulePkt::resetCount();
	RDFConstructor *constructor= new RDFConstructor(prefixesArray, prefixesArrayLength);
	EventConverter eventConverter;
	trex->addResultListener(constructor->getTRexListener());

	// Parser
	RDFTRexRuleParser parser;
	std::ifstream regola("./citybench_q" + std::to_string(numQuery) + ".txt");
	std::stringstream buffer;
	buffer << regola.rdbuf();
	std::string str = buffer.str();
	parser.parse(str, store, trex, constructor);

	// Load a second copy of the rule with the elements in a different order to mimic the semantics of atemporal conjunction
	if (numQuery == 1) {
		RDFTRexRuleParser parser2;
		std::ifstream regola2("./citybench_q1_2.txt");
		std::stringstream buffer2;
		buffer2 << regola2.rdbuf();
		std::string str2 = buffer2.str();
		parser2.parse(str2, store, trex, constructor);
	} else if (numQuery == 2) {
		RDFTRexRuleParser parser2;
		std::ifstream regola2("./citybench_q2_2.txt");
		std::stringstream buffer2;
		buffer2 << regola2.rdbuf();
		std::string str2 = buffer2.str();
		parser2.parse(str2, store, trex, constructor);
	}

	trex->finalize();

	// Subscription
	TestRDFListener *listener = new TestRDFListener();
	constructor->addRDFListener(listener);

	std::vector<std::string> pathToEvents;

	eventConverter.setTimeDistanceBetweenEvents(timeBetweenEvents);

	for (int i=0; i<numEvents; i++) {
		stringstream strstr;
		strstr << cityBenchIn << "Q" << numQuery << "/rdf/event_" << i << ".ttl";
		pathToEvents.push_back(strstr.str());
	}

	auto begin = std::chrono::high_resolution_clock::now();
	int count = 0;
	for (auto &path : pathToEvents) {
		if (printResults) {
			std::cout << "Evento " << count << std::endl;
		}
		std::vector<Event*> events;
		std::vector<PubPkt*> pubPkts;

		store->processRdfEvent(path.c_str(), events);
		eventConverter.convertToTesla(events, constructor, pubPkts, prefixesArray, prefixesArrayLength);
		processPubPkt(pubPkts, trex);
		count++;
	}
	auto end = std::chrono::high_resolution_clock::now();
	double avgTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() / (1000000.0 * count);

	std::cout << timeBetweenEvents << "\t" << avgTime << "\t" << listener->getNumResults() << std::endl;

	delete trex;
	delete store;
	delete listener;
	delete constructor;
}

