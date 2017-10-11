
// Generated from RDFTESLA.g4 by ANTLR 4.6

#pragma once


#include <antlr4-runtime.h>
#include "RDFTESLAParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by RDFTESLAParser.
 */
class  RDFTESLAListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStatic_reference(RDFTESLAParser::Static_referenceContext *ctx) = 0;
  virtual void exitStatic_reference(RDFTESLAParser::Static_referenceContext *ctx) = 0;

  virtual void enterPacket_reference(RDFTESLAParser::Packet_referenceContext *ctx) = 0;
  virtual void exitPacket_reference(RDFTESLAParser::Packet_referenceContext *ctx) = 0;

  virtual void enterParam_atom(RDFTESLAParser::Param_atomContext *ctx) = 0;
  virtual void exitParam_atom(RDFTESLAParser::Param_atomContext *ctx) = 0;

  virtual void enterAgg_one_reference(RDFTESLAParser::Agg_one_referenceContext *ctx) = 0;
  virtual void exitAgg_one_reference(RDFTESLAParser::Agg_one_referenceContext *ctx) = 0;

  virtual void enterAgg_between(RDFTESLAParser::Agg_betweenContext *ctx) = 0;
  virtual void exitAgg_between(RDFTESLAParser::Agg_betweenContext *ctx) = 0;

  virtual void enterAggregate_atom(RDFTESLAParser::Aggregate_atomContext *ctx) = 0;
  virtual void exitAggregate_atom(RDFTESLAParser::Aggregate_atomContext *ctx) = 0;

  virtual void enterExpr(RDFTESLAParser::ExprContext *ctx) = 0;
  virtual void exitExpr(RDFTESLAParser::ExprContext *ctx) = 0;

  virtual void enterStaticAttr_definition(RDFTESLAParser::StaticAttr_definitionContext *ctx) = 0;
  virtual void exitStaticAttr_definition(RDFTESLAParser::StaticAttr_definitionContext *ctx) = 0;

  virtual void enterAttr_definition(RDFTESLAParser::Attr_definitionContext *ctx) = 0;
  virtual void exitAttr_definition(RDFTESLAParser::Attr_definitionContext *ctx) = 0;

  virtual void enterAttr_constraint(RDFTESLAParser::Attr_constraintContext *ctx) = 0;
  virtual void exitAttr_constraint(RDFTESLAParser::Attr_constraintContext *ctx) = 0;

  virtual void enterAttr_parameter(RDFTESLAParser::Attr_parameterContext *ctx) = 0;
  virtual void exitAttr_parameter(RDFTESLAParser::Attr_parameterContext *ctx) = 0;

  virtual void enterPredicate(RDFTESLAParser::PredicateContext *ctx) = 0;
  virtual void exitPredicate(RDFTESLAParser::PredicateContext *ctx) = 0;

  virtual void enterEvent_alias(RDFTESLAParser::Event_aliasContext *ctx) = 0;
  virtual void exitEvent_alias(RDFTESLAParser::Event_aliasContext *ctx) = 0;

  virtual void enterTerminator(RDFTESLAParser::TerminatorContext *ctx) = 0;
  virtual void exitTerminator(RDFTESLAParser::TerminatorContext *ctx) = 0;

  virtual void enterPositive_predicate(RDFTESLAParser::Positive_predicateContext *ctx) = 0;
  virtual void exitPositive_predicate(RDFTESLAParser::Positive_predicateContext *ctx) = 0;

  virtual void enterNeg_one_reference(RDFTESLAParser::Neg_one_referenceContext *ctx) = 0;
  virtual void exitNeg_one_reference(RDFTESLAParser::Neg_one_referenceContext *ctx) = 0;

  virtual void enterNeg_between(RDFTESLAParser::Neg_betweenContext *ctx) = 0;
  virtual void exitNeg_between(RDFTESLAParser::Neg_betweenContext *ctx) = 0;

  virtual void enterNegative_predicate(RDFTESLAParser::Negative_predicateContext *ctx) = 0;
  virtual void exitNegative_predicate(RDFTESLAParser::Negative_predicateContext *ctx) = 0;

  virtual void enterPattern_predicate(RDFTESLAParser::Pattern_predicateContext *ctx) = 0;
  virtual void exitPattern_predicate(RDFTESLAParser::Pattern_predicateContext *ctx) = 0;

  virtual void enterEvent_declaration(RDFTESLAParser::Event_declarationContext *ctx) = 0;
  virtual void exitEvent_declaration(RDFTESLAParser::Event_declarationContext *ctx) = 0;

  virtual void enterEvent_declarations(RDFTESLAParser::Event_declarationsContext *ctx) = 0;
  virtual void exitEvent_declarations(RDFTESLAParser::Event_declarationsContext *ctx) = 0;

  virtual void enterParametrization(RDFTESLAParser::ParametrizationContext *ctx) = 0;
  virtual void exitParametrization(RDFTESLAParser::ParametrizationContext *ctx) = 0;

  virtual void enterPrefix_uri(RDFTESLAParser::Prefix_uriContext *ctx) = 0;
  virtual void exitPrefix_uri(RDFTESLAParser::Prefix_uriContext *ctx) = 0;

  virtual void enterFull_uri(RDFTESLAParser::Full_uriContext *ctx) = 0;
  virtual void exitFull_uri(RDFTESLAParser::Full_uriContext *ctx) = 0;

  virtual void enterUri(RDFTESLAParser::UriContext *ctx) = 0;
  virtual void exitUri(RDFTESLAParser::UriContext *ctx) = 0;

  virtual void enterSub(RDFTESLAParser::SubContext *ctx) = 0;
  virtual void exitSub(RDFTESLAParser::SubContext *ctx) = 0;

  virtual void enterPred(RDFTESLAParser::PredContext *ctx) = 0;
  virtual void exitPred(RDFTESLAParser::PredContext *ctx) = 0;

  virtual void enterObj(RDFTESLAParser::ObjContext *ctx) = 0;
  virtual void exitObj(RDFTESLAParser::ObjContext *ctx) = 0;

  virtual void enterTriple(RDFTESLAParser::TripleContext *ctx) = 0;
  virtual void exitTriple(RDFTESLAParser::TripleContext *ctx) = 0;

  virtual void enterRdf_pattern(RDFTESLAParser::Rdf_patternContext *ctx) = 0;
  virtual void exitRdf_pattern(RDFTESLAParser::Rdf_patternContext *ctx) = 0;

  virtual void enterCe_definition(RDFTESLAParser::Ce_definitionContext *ctx) = 0;
  virtual void exitCe_definition(RDFTESLAParser::Ce_definitionContext *ctx) = 0;

  virtual void enterPattern(RDFTESLAParser::PatternContext *ctx) = 0;
  virtual void exitPattern(RDFTESLAParser::PatternContext *ctx) = 0;

  virtual void enterDefinitions(RDFTESLAParser::DefinitionsContext *ctx) = 0;
  virtual void exitDefinitions(RDFTESLAParser::DefinitionsContext *ctx) = 0;

  virtual void enterConsuming(RDFTESLAParser::ConsumingContext *ctx) = 0;
  virtual void exitConsuming(RDFTESLAParser::ConsumingContext *ctx) = 0;

  virtual void enterEnding_rule(RDFTESLAParser::Ending_ruleContext *ctx) = 0;
  virtual void exitEnding_rule(RDFTESLAParser::Ending_ruleContext *ctx) = 0;

  virtual void enterTrex_rdf_rule(RDFTESLAParser::Trex_rdf_ruleContext *ctx) = 0;
  virtual void exitTrex_rdf_rule(RDFTESLAParser::Trex_rdf_ruleContext *ctx) = 0;


};

