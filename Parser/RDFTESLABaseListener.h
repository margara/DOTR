
// Generated from RDFTESLA.g4 by ANTLR 4.6

#pragma once


#include <antlr4-runtime.h>
#include "RDFTESLAListener.h"


/**
 * This class provides an empty implementation of RDFTESLAListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  RDFTESLABaseListener : public RDFTESLAListener {
public:

  virtual void enterStatic_reference(RDFTESLAParser::Static_referenceContext * /*ctx*/) override { }
  virtual void exitStatic_reference(RDFTESLAParser::Static_referenceContext * /*ctx*/) override { }

  virtual void enterPacket_reference(RDFTESLAParser::Packet_referenceContext * /*ctx*/) override { }
  virtual void exitPacket_reference(RDFTESLAParser::Packet_referenceContext * /*ctx*/) override { }

  virtual void enterParam_atom(RDFTESLAParser::Param_atomContext * /*ctx*/) override { }
  virtual void exitParam_atom(RDFTESLAParser::Param_atomContext * /*ctx*/) override { }

  virtual void enterAgg_one_reference(RDFTESLAParser::Agg_one_referenceContext * /*ctx*/) override { }
  virtual void exitAgg_one_reference(RDFTESLAParser::Agg_one_referenceContext * /*ctx*/) override { }

  virtual void enterAgg_between(RDFTESLAParser::Agg_betweenContext * /*ctx*/) override { }
  virtual void exitAgg_between(RDFTESLAParser::Agg_betweenContext * /*ctx*/) override { }

  virtual void enterAggregate_atom(RDFTESLAParser::Aggregate_atomContext * /*ctx*/) override { }
  virtual void exitAggregate_atom(RDFTESLAParser::Aggregate_atomContext * /*ctx*/) override { }

  virtual void enterExpr(RDFTESLAParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(RDFTESLAParser::ExprContext * /*ctx*/) override { }

  virtual void enterStaticAttr_definition(RDFTESLAParser::StaticAttr_definitionContext * /*ctx*/) override { }
  virtual void exitStaticAttr_definition(RDFTESLAParser::StaticAttr_definitionContext * /*ctx*/) override { }

  virtual void enterAttr_definition(RDFTESLAParser::Attr_definitionContext * /*ctx*/) override { }
  virtual void exitAttr_definition(RDFTESLAParser::Attr_definitionContext * /*ctx*/) override { }

  virtual void enterAttr_constraint(RDFTESLAParser::Attr_constraintContext * /*ctx*/) override { }
  virtual void exitAttr_constraint(RDFTESLAParser::Attr_constraintContext * /*ctx*/) override { }

  virtual void enterAttr_parameter(RDFTESLAParser::Attr_parameterContext * /*ctx*/) override { }
  virtual void exitAttr_parameter(RDFTESLAParser::Attr_parameterContext * /*ctx*/) override { }

  virtual void enterPredicate(RDFTESLAParser::PredicateContext * /*ctx*/) override { }
  virtual void exitPredicate(RDFTESLAParser::PredicateContext * /*ctx*/) override { }

  virtual void enterEvent_alias(RDFTESLAParser::Event_aliasContext * /*ctx*/) override { }
  virtual void exitEvent_alias(RDFTESLAParser::Event_aliasContext * /*ctx*/) override { }

  virtual void enterTerminator(RDFTESLAParser::TerminatorContext * /*ctx*/) override { }
  virtual void exitTerminator(RDFTESLAParser::TerminatorContext * /*ctx*/) override { }

  virtual void enterPositive_predicate(RDFTESLAParser::Positive_predicateContext * /*ctx*/) override { }
  virtual void exitPositive_predicate(RDFTESLAParser::Positive_predicateContext * /*ctx*/) override { }

  virtual void enterNeg_one_reference(RDFTESLAParser::Neg_one_referenceContext * /*ctx*/) override { }
  virtual void exitNeg_one_reference(RDFTESLAParser::Neg_one_referenceContext * /*ctx*/) override { }

  virtual void enterNeg_between(RDFTESLAParser::Neg_betweenContext * /*ctx*/) override { }
  virtual void exitNeg_between(RDFTESLAParser::Neg_betweenContext * /*ctx*/) override { }

  virtual void enterNegative_predicate(RDFTESLAParser::Negative_predicateContext * /*ctx*/) override { }
  virtual void exitNegative_predicate(RDFTESLAParser::Negative_predicateContext * /*ctx*/) override { }

  virtual void enterPattern_predicate(RDFTESLAParser::Pattern_predicateContext * /*ctx*/) override { }
  virtual void exitPattern_predicate(RDFTESLAParser::Pattern_predicateContext * /*ctx*/) override { }

  virtual void enterEvent_declaration(RDFTESLAParser::Event_declarationContext * /*ctx*/) override { }
  virtual void exitEvent_declaration(RDFTESLAParser::Event_declarationContext * /*ctx*/) override { }

  virtual void enterEvent_declarations(RDFTESLAParser::Event_declarationsContext * /*ctx*/) override { }
  virtual void exitEvent_declarations(RDFTESLAParser::Event_declarationsContext * /*ctx*/) override { }

  virtual void enterParametrization(RDFTESLAParser::ParametrizationContext * /*ctx*/) override { }
  virtual void exitParametrization(RDFTESLAParser::ParametrizationContext * /*ctx*/) override { }

  virtual void enterPrefix_uri(RDFTESLAParser::Prefix_uriContext * /*ctx*/) override { }
  virtual void exitPrefix_uri(RDFTESLAParser::Prefix_uriContext * /*ctx*/) override { }

  virtual void enterFull_uri(RDFTESLAParser::Full_uriContext * /*ctx*/) override { }
  virtual void exitFull_uri(RDFTESLAParser::Full_uriContext * /*ctx*/) override { }

  virtual void enterUri(RDFTESLAParser::UriContext * /*ctx*/) override { }
  virtual void exitUri(RDFTESLAParser::UriContext * /*ctx*/) override { }

  virtual void enterSub(RDFTESLAParser::SubContext * /*ctx*/) override { }
  virtual void exitSub(RDFTESLAParser::SubContext * /*ctx*/) override { }

  virtual void enterPred(RDFTESLAParser::PredContext * /*ctx*/) override { }
  virtual void exitPred(RDFTESLAParser::PredContext * /*ctx*/) override { }

  virtual void enterObj(RDFTESLAParser::ObjContext * /*ctx*/) override { }
  virtual void exitObj(RDFTESLAParser::ObjContext * /*ctx*/) override { }

  virtual void enterTriple(RDFTESLAParser::TripleContext * /*ctx*/) override { }
  virtual void exitTriple(RDFTESLAParser::TripleContext * /*ctx*/) override { }

  virtual void enterRdf_pattern(RDFTESLAParser::Rdf_patternContext * /*ctx*/) override { }
  virtual void exitRdf_pattern(RDFTESLAParser::Rdf_patternContext * /*ctx*/) override { }

  virtual void enterCe_definition(RDFTESLAParser::Ce_definitionContext * /*ctx*/) override { }
  virtual void exitCe_definition(RDFTESLAParser::Ce_definitionContext * /*ctx*/) override { }

  virtual void enterPattern(RDFTESLAParser::PatternContext * /*ctx*/) override { }
  virtual void exitPattern(RDFTESLAParser::PatternContext * /*ctx*/) override { }

  virtual void enterDefinitions(RDFTESLAParser::DefinitionsContext * /*ctx*/) override { }
  virtual void exitDefinitions(RDFTESLAParser::DefinitionsContext * /*ctx*/) override { }

  virtual void enterConsuming(RDFTESLAParser::ConsumingContext * /*ctx*/) override { }
  virtual void exitConsuming(RDFTESLAParser::ConsumingContext * /*ctx*/) override { }

  virtual void enterEnding_rule(RDFTESLAParser::Ending_ruleContext * /*ctx*/) override { }
  virtual void exitEnding_rule(RDFTESLAParser::Ending_ruleContext * /*ctx*/) override { }

  virtual void enterTrex_rdf_rule(RDFTESLAParser::Trex_rdf_ruleContext * /*ctx*/) override { }
  virtual void exitTrex_rdf_rule(RDFTESLAParser::Trex_rdf_ruleContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

