#include "RDFConstructor.h"

//Creates a new TRexlistener, defined as inner member
RDFConstructor::RDFConstructor(const char** prefixesArray, int prefixesArrayLength) {
	trexListener = new TRexListener(this, prefixesArray, prefixesArrayLength);
}

//Frees memory about rdf templates and the TRex listener
RDFConstructor::~RDFConstructor(){
	for (std::map<int, Template*>::iterator it=rdfEventTemplates.begin(); it !=rdfEventTemplates.end(); it++){
		delete it->second->allRuleInfos;
		delete it->second;
	}
	delete trexListener;
}
