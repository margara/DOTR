#include <antlr4-runtime.h>
#include "RDFTESLALexer.h"
#include "RDFTESLAParser.h"
#include "RDFTESLABaseListener.h"
#include "../Common/RDFStructures.h"
#include <TRex2/Packets/RulePkt.h>
#include <TRex2/Common/Consts.h>
#include <TRex2/Common/Structures.h>
#include <TRex2/Packets/StaticValueReference.h>
#include <TRex2/Packets/RulePktValueReference.h>
#include <TRex2/Common/OpTree.h>
#include <TRex2/Engine/TRexEngine.h>
#include "../RDFStore/RDFStore.h"
#include "../RDFConstructor/RDFConstructor.h"
#include <string>


class RDFTRexRuleParser : public RDFTESLABaseListener{
public:

	void enterEvent_declaration(RDFTESLAParser::Event_declarationContext* ctx);

	void enterCe_definition(RDFTESLAParser::Ce_definitionContext * ctx);

	void enterTerminator(RDFTESLAParser::TerminatorContext * ctx);

	void enterPositive_predicate(RDFTESLAParser::Positive_predicateContext * ctx);

	void enterNegative_predicate(RDFTESLAParser::Negative_predicateContext * ctx);

	void enterParametrization(RDFTESLAParser::ParametrizationContext * ctx);

	void enterDefinitions(RDFTESLAParser::DefinitionsContext * ctx);

	void enterConsuming(RDFTESLAParser::ConsumingContext * ctx);

	void parse(std::string rule, RDFStore* store, TRexEngine* engine, RDFConstructor* constructor);

	RulePkt* getRule(){return rule;}
	std::vector<std::tuple<int, std::string, std::string> > getQueries(){return queries;}
	Template* getTemplateCE(){return templateCE;}

private:
	 std::map<std::string, int> eventId_map;
	 std::map<std::string, int> predicatesIds;
	 std::map<std::string, std::string> eventCompositions;
	 std::map<std::string, int> negPredIds;
	 int predicateCount = 0;
	 int aggregateCount = 0;
	 int negationCount = 0;
	 Template* templateCE;
	 CompositeEventTemplate* ceTRex;
	 std::vector<std::tuple<int, std::string, std::string> > queries;
	 RulePkt* rule;

	 OpTree* buildOpTree(RDFTESLAParser::ExprContext* expr, ValType valType);
	 OpTree* recursivelyNavigateExpression(RDFTESLAParser::ExprContext* expr, OpTree* tree, ValType valType);
};
