#ifndef EVALPARAMS_H_
#define EVALPARAMS_H_

#include <TRex2/Common/Consts.h>
#include <string>

const int numThreads = 4;

int numRooms = 5;
int numObjectsPerRoom = 10;
int numSensors = 500;
int numSensorTypes = 2;
int numAdditionalEntries = 0;

int numEvents = 2000;
int numTriplesPerEvent = 1;
int percTermin = 20;
int numValues = 100;

int numDynamicInferenceRules = 0;
int numAdditionalInferenceRules = 10;

int numRules = 50;
CompKind compKind = LAST_WITHIN;
bool sparqlFilter = true;

int firstComplexEventId = numRules * numSensorTypes + 1;

void setDefaultParams() {
	numRooms = 5;
	numObjectsPerRoom = 10;
	numSensors = 500;
	numSensorTypes = 2;
	numAdditionalEntries = 0;

	numEvents = 2000;
	numTriplesPerEvent = 1;
	percTermin = 20;
	numValues = 100;

	numDynamicInferenceRules = 0;
	numAdditionalInferenceRules = 10;

	numRules = 50;
	compKind = LAST_WITHIN;
	sparqlFilter = true;

	firstComplexEventId = numRules * numSensorTypes + 1;
}

void enforceParamsDependencies() {
	firstComplexEventId = numRules * numSensorTypes + 1;
}

#endif /* EVALPARAMS_H_ */
