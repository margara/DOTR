#ifndef WORKLOADGENERATOR_H_
#define WORKLOADGENERATOR_H_

#include <TRex2/Engine/TRexEngine.h>
#include "../RDFStore/RDFStore.h"
#include "../RDFConstructor/RDFConstructor.h"
#include "../RDFConstructor/RDFResultListener.h"

void generateKb(int numRooms, int numObjectsPerRoom, int numSensors, int numSensorTypes, int numAdditionalEntries);

void generateInputEvents(int numEvents, int numTriples, int numSensors, int percTermin, int numProperties, int numValues);

void generateInference(int numAdditionalRules, int numDynamicRules, int numSensorTypes);

void generateRuleQuery(int numOfRules, TRexEngine* engine, RDFStore* store, RDFConstructor* constructor, RDFResultListener *listener, int seqLen, CompKind compKind, bool sparqlFilter, int firstComplexEventType);

#endif /* WORKLOADGENERATOR_H_ */
