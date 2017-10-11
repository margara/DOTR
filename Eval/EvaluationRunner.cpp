#include "EvaluationRunner.h"

#include "WorkloadGenerator.h"
#include "../RDFStore/EventConverter.h"
#include "../TestRDFListener.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>

#include "../Eval/EvalConsts.h"
#include "../Eval/EvalParams.h"

inline void processPubPkt(std::vector<PubPkt*> &pubPkts, TRexEngine *trex) {
	for (auto *pkt : pubPkts) {
		trex->processPubPkt(pkt);
	}
}

void runExperiment(std::string outfile, std::string label) {
	generateKb(numRooms, numObjectsPerRoom, numSensors, numSensorTypes, numAdditionalEntries);
	generateInputEvents(numEvents, numTriplesPerEvent, numSensors, percTermin, numSensorTypes, numValues);
	generateInference(numAdditionalInferenceRules, numDynamicInferenceRules, numSensorTypes);

	const char type[] = "seq"; // TODO
	const int prefixesArrayLength = 4;
	const char* prefixesArray[] = {"ad:", "http://my.org#", "a1:", "http://localhost#"};

	RDFStore *store = new RDFStore(type, kbPath.c_str(), infRulesPath.c_str(), prefixesArray, prefixesArrayLength);
	TRexEngine *trex = new TRexEngine(numThreads);
	RulePkt::resetCount();
	RDFConstructor *constructor = new RDFConstructor(prefixesArray, prefixesArrayLength);
	TestRDFListener *listener = new TestRDFListener();
	EventConverter eventConverter;
	eventConverter.setTimeDistanceBetweenEvents(1000); // Advance by 1 second
	generateRuleQuery(numRules, trex, store, constructor, listener, numSensorTypes, compKind, sparqlFilter, firstComplexEventId);
	trex->addResultListener(constructor->getTRexListener());
	trex->finalize();

	std::vector<std::string> pathToEvents;
	for (int i = 0; i < numEvents; i++) {
		std::stringstream s;
		s << eventPath << i << ".ttl";
		pathToEvents.push_back(s.str());
	}

	auto begin = std::chrono::high_resolution_clock::now();
	for (auto &path : pathToEvents) {
		std::vector<Event *> events;
		std::vector<PubPkt *> pkts;

		store->processRdfEvent(path.c_str(), events);
		eventConverter.convertToTesla(events, constructor, pkts, prefixesArray, prefixesArrayLength);
		processPubPkt(pkts, trex);
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() / (1000000.0 * numEvents);

	std::cout << outfile << "\t" << label << "\t" << duration << "\t" << listener->getNumResults() << std::endl;
	ofstream os;
	os.open((resultsPath + outfile + ".txt").c_str(), ios::app);
	os << label << "\t" << duration << "\t" << listener->getNumResults() << std::endl;
	os.close();

	delete trex;
	delete constructor;
	delete listener;
	delete store;
}

void runTimingExperiment(std::string outfile) {
	generateKb(numRooms, numObjectsPerRoom, numSensors, numSensorTypes, numAdditionalEntries);
	generateInputEvents(numEvents, numTriplesPerEvent, numSensors, percTermin, numSensorTypes, numValues);
	generateInference(numAdditionalInferenceRules, numDynamicInferenceRules, numSensorTypes);

	const char type[] = "seq"; // TODO
	const int prefixesArrayLength = 4;
	const char* prefixesArray[] = {"ad:", "http://my.org#", "a1:", "http://localhost#"};

	RDFStore *store = new RDFStore(type, kbPath.c_str(), infRulesPath.c_str(), prefixesArray, prefixesArrayLength);
	TRexEngine *trex = new TRexEngine(numThreads);
	RulePkt::resetCount();
	RDFConstructor *constructor = new RDFConstructor(prefixesArray, prefixesArrayLength);
	RDFResultListener *listener = new TestRDFListener();
	EventConverter eventConverter;
	eventConverter.setTimeDistanceBetweenEvents(1000); // Advance by 1 second
	generateRuleQuery(numRules, trex, store, constructor, listener, numSensorTypes, compKind, sparqlFilter, firstComplexEventId);
	trex->addResultListener(constructor->getTRexListener());
	trex->finalize();

	std::vector<std::string> pathToEvents;
	for (int i = 0; i < numEvents; i++) {
		std::stringstream s;
		s << eventPath << i << ".ttl";
		pathToEvents.push_back(s.str());
	}

	double totalKnowledgeUpdateTime = 0;
	double totalReasoningTime = 0;
	double totalQueryTime = 0;
	double totalInputTranslationTime = 0;
	double totalEventProcessingTime = 0;
	double totalOutputTranslationTime = 0;

	for (auto &path : pathToEvents) {
		std::vector<Event *> events;
		std::vector<PubPkt *> pkts;

		auto beginUpdateKnowledge = std::chrono::high_resolution_clock::now();
		store->updateKnowledge(path.c_str());
		auto endUpdateKnowledge = std::chrono::high_resolution_clock::now();
		totalKnowledgeUpdateTime += std::chrono::duration_cast<std::chrono::nanoseconds>(endUpdateKnowledge-beginUpdateKnowledge).count();

		auto beginReasoning = std::chrono::high_resolution_clock::now();
		store->performReasoning();
		auto endReasoning = std::chrono::high_resolution_clock::now();
		totalReasoningTime += std::chrono::duration_cast<std::chrono::nanoseconds>(endReasoning-beginReasoning).count();

		auto beginQueries = std::chrono::high_resolution_clock::now();
		store->evaluateQueries(events);
		auto endQueries = std::chrono::high_resolution_clock::now();
		totalQueryTime += std::chrono::duration_cast<std::chrono::nanoseconds>(endQueries-beginQueries).count();

		auto beginInputTranslation = std::chrono::high_resolution_clock::now();
		eventConverter.convertToTesla(events, constructor, pkts, prefixesArray, prefixesArrayLength);
		auto endInputTranslation = std::chrono::high_resolution_clock::now();
		totalInputTranslationTime += std::chrono::duration_cast<std::chrono::nanoseconds>(endInputTranslation-beginInputTranslation).count();

		auto beginEventProcessing = std::chrono::high_resolution_clock::now();
		processPubPkt(pkts, trex);
		auto endEventProcessing = std::chrono::high_resolution_clock::now();
		totalEventProcessingTime += std::chrono::duration_cast<std::chrono::nanoseconds>(endEventProcessing-beginEventProcessing).count();
	}

	TRexListener *l = dynamic_cast<TRexListener *>(constructor->getTRexListener());
	totalOutputTranslationTime = l->getTotalProcessingNanoTime();
	// The output translation time is also considered within the event processing time
	totalEventProcessingTime -= totalOutputTranslationTime;

	double totalTime = totalKnowledgeUpdateTime + totalReasoningTime + totalQueryTime + totalInputTranslationTime + totalEventProcessingTime + totalOutputTranslationTime;

	ofstream os;
	os.open((resultsPath + outfile + ".txt").c_str(), ios::app);

	os << "Knowledge update:\t" << totalKnowledgeUpdateTime / (1000000.0 * numEvents) << " ms\t";
	os << totalKnowledgeUpdateTime * 100 / totalTime << " %" << std::endl;

	os << "Reasoning:\t" << totalReasoningTime / (1000000.0 * numEvents) << " ms\t";
	os << totalReasoningTime * 100 / totalTime << " %" << std::endl;

	os << "Query evaluation:\t" << totalQueryTime / (1000000.0 * numEvents) << " ms\t";
	os << totalQueryTime * 100 / totalTime << " %" << std::endl;

	os << "Input translation:\t" << totalInputTranslationTime / (1000000.0 * numEvents) << " ms\t";
	os << totalInputTranslationTime * 100 / totalTime << " %" << std::endl;

	os << "Event processing:\t" << totalEventProcessingTime / (1000000.0 * numEvents) << " ms\t";
	os << totalEventProcessingTime * 100 / totalTime << " %" << std::endl;

	os << "Output translation:\t" << totalOutputTranslationTime / (1000000.0 * numEvents) << " ms\t";
	os << totalOutputTranslationTime * 100 / totalTime << " %" << std::endl;

	os << "Total:\t" << totalTime / (1000000.0 * numEvents) << " ms\t";
	os << "100 %" << std::endl;

	os.close();

	delete trex;
	delete constructor;
	delete listener;
	delete store;
}

void runDefault() {
	setDefaultParams();
	runExperiment("default", "1");
}

void runTiming() {
	setDefaultParams();
	runTimingExperiment("defaultTiming");
}

void runSeqLen() {
	setDefaultParams();
	for (int i=2; i<=6; i++) {
		numSensorTypes = i;
		enforceParamsDependencies();
		runExperiment("seqLen", std::to_string(i));
	}
}

void runSeqLenEach() {
	setDefaultParams();
	compKind = EACH_WITHIN;
	for (int i=2; i<=6; i++) {
		numSensorTypes = i;
		enforceParamsDependencies();
		runExperiment("seqLenEach", std::to_string(i));
	}
}

void runNumRules() {
	setDefaultParams();
	for (int i=1; i<=1000; ) {
		numRules = i;
		enforceParamsDependencies();
		runExperiment("numRules", std::to_string(i));
		if (i < 10) {
			i += 3;
		} else if (i < 100) {
			i += 30;
		} else if (i < 1000) {
			i += 300;
		} else if (i < 10000) {
			i += 3000;
		} else {
			i += 30000;
		}
	}
}

void runNumRulesTRexFilter() {
	setDefaultParams();
	for (int i=1; i<=1000; ) {
		numRules = i;
		sparqlFilter = false;
		enforceParamsDependencies();
		runExperiment("numRulesTRexFilter", std::to_string(i));
		if (i < 10) {
			i += 3;
		} else if (i < 100) {
			i += 30;
		} else if (i < 1000) {
			i += 300;
		} else if (i < 10000) {
			i += 3000;
		} else {
			i += 30000;
		}
	}
}

void runSizeKB() {
	setDefaultParams();
	for (int i=1000; i<=1000000; ) {
		numAdditionalEntries = i;
		enforceParamsDependencies();
		runExperiment("sizeKB", std::to_string(i));
		i *= 10;
	}
}

void runNumDynamicInferenceRules() {
	setDefaultParams();
	for (int i=1; i<=100000; ) {
		numDynamicInferenceRules = i;
		enforceParamsDependencies();
		runExperiment("numDynamicInfRules", std::to_string(i));
		if (i < 10) {
			i += 3;
		} else if (i < 100) {
			i += 30;
		} else if (i < 1000) {
			i += 300;
		} else if (i < 10000) {
			i += 3000;
		} else {
			i += 30000;
		}
	}
}

void runEvaluationSuite() {
	runDefault();
	runTiming();
	runSeqLen();
	runSeqLenEach();
	runSizeKB();
	runNumDynamicInferenceRules();
	runNumRulesTRexFilter();
	runNumRules();
}
