#ifndef RDFCONSTRUCTOR_H
#define RDFCONSTRUCTOR_H

#include "TRexListener.h"
#include <TRex2/Engine/ResultListener.h>
#include <map>
#include <set>

/**
 * "Container" class useful for storing RDF templates and output listeners (subscriptions).
 * It has a TRex listener as a member, which is in charge of processing TRex events and convert them into RDF events.
 */
class RDFConstructor {
public:
	/**
	 * Constructor. It creates the TRex listener.
	 */
	RDFConstructor(const char** prefixesArray, int prefixesArrayLength);

	/*
	 * Destructor.
	 */
	~RDFConstructor();

	/**
	 * Retrieves TRex listener, which handles TRex results.
	 */
	ResultListener * getTRexListener(){
		return trexListener;
	}

	/**
	 * Retrieves RDF complex event patterns defined by RDF Tesla rules.
	 */
	std::map<int, Template*> &getRdfEventTemplates() {
		return rdfEventTemplates;
	}

	/**
	 * Adds a RDF complex event pattern into the container for further evaluation of generated events.
	 */
	void addTemplate(int type, Template* templateCE) {
		rdfEventTemplates.insert(std::make_pair(type, templateCE));
	}

	/**
	 * Adds an output rdf listener (subscription).
	 */
	void addRDFListener(RDFResultListener *rdfListener) {
		rdfListeners.insert(rdfListener);
	}

	/**
	 * Returns the set of output rdf listeners.
	 */
	std::set<RDFResultListener*> &getRDFListeners(){
		return rdfListeners;
	}

private:
	ResultListener* trexListener;
	std::map<int, Template*> rdfEventTemplates;
	std::set<RDFResultListener *> rdfListeners;
};
#endif /*RDFCONSTRUCTOR_H*/
