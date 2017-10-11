
// Generated from RDFTESLA.g4 by ANTLR 4.6

#pragma once


#include <antlr4-runtime.h>




class  RDFTESLAParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, ASSIGN = 16, DEFINE = 17, FROM = 18, WITH = 19, WHERE = 20, 
    CONSUMING = 21, VALTYPE = 22, SEL_POLICY = 23, AGGR_FUN = 24, OPERATOR = 25, 
    BINOP_MUL = 26, BINOP_ADD = 27, INT_VAL = 28, FLOAT_VAL = 29, BOOL_VAL = 30, 
    STRING_VAL = 31, SPARQL_QUERY = 32, EVT_NAME = 33, URI_PREFIX_NAME = 34, 
    URI_FULL_NAME = 35, SPARQL_VAR = 36, WS = 37
  };

  enum {
    RuleStatic_reference = 0, RulePacket_reference = 1, RuleParam_atom = 2, 
    RuleAgg_one_reference = 3, RuleAgg_between = 4, RuleAggregate_atom = 5, 
    RuleExpr = 6, RuleStaticAttr_definition = 7, RuleAttr_definition = 8, 
    RuleAttr_constraint = 9, RuleAttr_parameter = 10, RulePredicate = 11, 
    RuleEvent_alias = 12, RuleTerminator = 13, RulePositive_predicate = 14, 
    RuleNeg_one_reference = 15, RuleNeg_between = 16, RuleNegative_predicate = 17, 
    RulePattern_predicate = 18, RuleEvent_declaration = 19, RuleEvent_declarations = 20, 
    RuleParametrization = 21, RulePrefix_uri = 22, RuleFull_uri = 23, RuleUri = 24, 
    RuleSub = 25, RulePred = 26, RuleObj = 27, RuleTriple = 28, RuleRdf_pattern = 29, 
    RuleCe_definition = 30, RulePattern = 31, RuleDefinitions = 32, RuleConsuming = 33, 
    RuleEnding_rule = 34, RuleTrex_rdf_rule = 35
  };

  RDFTESLAParser(antlr4::TokenStream *input);
  ~RDFTESLAParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  std::stringstream ss; // can't make locals in lexer rules
  std::string str;


  class Static_referenceContext;
  class Packet_referenceContext;
  class Param_atomContext;
  class Agg_one_referenceContext;
  class Agg_betweenContext;
  class Aggregate_atomContext;
  class ExprContext;
  class StaticAttr_definitionContext;
  class Attr_definitionContext;
  class Attr_constraintContext;
  class Attr_parameterContext;
  class PredicateContext;
  class Event_aliasContext;
  class TerminatorContext;
  class Positive_predicateContext;
  class Neg_one_referenceContext;
  class Neg_betweenContext;
  class Negative_predicateContext;
  class Pattern_predicateContext;
  class Event_declarationContext;
  class Event_declarationsContext;
  class ParametrizationContext;
  class Prefix_uriContext;
  class Full_uriContext;
  class UriContext;
  class SubContext;
  class PredContext;
  class ObjContext;
  class TripleContext;
  class Rdf_patternContext;
  class Ce_definitionContext;
  class PatternContext;
  class DefinitionsContext;
  class ConsumingContext;
  class Ending_ruleContext;
  class Trex_rdf_ruleContext; 

  class  Static_referenceContext : public antlr4::ParserRuleContext {
  public:
    Static_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_VAL();
    antlr4::tree::TerminalNode *FLOAT_VAL();
    antlr4::tree::TerminalNode *STRING_VAL();
    antlr4::tree::TerminalNode *BOOL_VAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Static_referenceContext* static_reference();

  class  Packet_referenceContext : public antlr4::ParserRuleContext {
  public:
    Packet_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EVT_NAME();
    antlr4::tree::TerminalNode *SPARQL_VAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Packet_referenceContext* packet_reference();

  class  Param_atomContext : public antlr4::ParserRuleContext {
  public:
    Param_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Packet_referenceContext *packet_reference();
    Static_referenceContext *static_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Param_atomContext* param_atom();

  class  Agg_one_referenceContext : public antlr4::ParserRuleContext {
  public:
    Agg_one_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_VAL();
    antlr4::tree::TerminalNode *EVT_NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Agg_one_referenceContext* agg_one_reference();

  class  Agg_betweenContext : public antlr4::ParserRuleContext {
  public:
    Agg_betweenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> EVT_NAME();
    antlr4::tree::TerminalNode* EVT_NAME(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Agg_betweenContext* agg_between();

  class  Aggregate_atomContext : public antlr4::ParserRuleContext {
  public:
    Aggregate_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AGGR_FUN();
    Packet_referenceContext *packet_reference();
    Agg_one_referenceContext *agg_one_reference();
    Agg_betweenContext *agg_between();
    std::vector<Attr_parameterContext *> attr_parameter();
    Attr_parameterContext* attr_parameter(size_t i);
    std::vector<Attr_constraintContext *> attr_constraint();
    Attr_constraintContext* attr_constraint(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Aggregate_atomContext* aggregate_atom();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    Param_atomContext *param_atom();
    Aggregate_atomContext *aggregate_atom();
    antlr4::tree::TerminalNode *BINOP_MUL();
    antlr4::tree::TerminalNode *BINOP_ADD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  StaticAttr_definitionContext : public antlr4::ParserRuleContext {
  public:
    StaticAttr_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SPARQL_VAR();
    Static_referenceContext *static_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StaticAttr_definitionContext* staticAttr_definition();

  class  Attr_definitionContext : public antlr4::ParserRuleContext {
  public:
    Attr_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VALTYPE();
    antlr4::tree::TerminalNode *SPARQL_VAR();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Attr_definitionContext* attr_definition();

  class  Attr_constraintContext : public antlr4::ParserRuleContext {
  public:
    Attr_constraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SPARQL_VAR();
    antlr4::tree::TerminalNode *OPERATOR();
    Static_referenceContext *static_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Attr_constraintContext* attr_constraint();

  class  Attr_parameterContext : public antlr4::ParserRuleContext {
  public:
    Attr_parameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VALTYPE();
    antlr4::tree::TerminalNode *SPARQL_VAR();
    antlr4::tree::TerminalNode *OPERATOR();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Attr_parameterContext* attr_parameter();

  class  PredicateContext : public antlr4::ParserRuleContext {
  public:
    PredicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EVT_NAME();
    antlr4::tree::TerminalNode *SPARQL_QUERY();
    std::vector<Attr_constraintContext *> attr_constraint();
    Attr_constraintContext* attr_constraint(size_t i);
    Event_aliasContext *event_alias();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PredicateContext* predicate();

  class  Event_aliasContext : public antlr4::ParserRuleContext {
  public:
    Event_aliasContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EVT_NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Event_aliasContext* event_alias();

  class  TerminatorContext : public antlr4::ParserRuleContext {
  public:
    TerminatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PredicateContext *predicate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TerminatorContext* terminator();

  class  Positive_predicateContext : public antlr4::ParserRuleContext {
  public:
    Positive_predicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEL_POLICY();
    PredicateContext *predicate();
    Neg_one_referenceContext *neg_one_reference();
    Neg_betweenContext *neg_between();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Positive_predicateContext* positive_predicate();

  class  Neg_one_referenceContext : public antlr4::ParserRuleContext {
  public:
    Neg_one_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_VAL();
    antlr4::tree::TerminalNode *EVT_NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Neg_one_referenceContext* neg_one_reference();

  class  Neg_betweenContext : public antlr4::ParserRuleContext {
  public:
    Neg_betweenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> EVT_NAME();
    antlr4::tree::TerminalNode* EVT_NAME(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Neg_betweenContext* neg_between();

  class  Negative_predicateContext : public antlr4::ParserRuleContext {
  public:
    Negative_predicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PredicateContext *predicate();
    Neg_one_referenceContext *neg_one_reference();
    Neg_betweenContext *neg_between();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Negative_predicateContext* negative_predicate();

  class  Pattern_predicateContext : public antlr4::ParserRuleContext {
  public:
    Pattern_predicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Positive_predicateContext *positive_predicate();
    Negative_predicateContext *negative_predicate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Pattern_predicateContext* pattern_predicate();

  class  Event_declarationContext : public antlr4::ParserRuleContext {
  public:
    Event_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_VAL();
    antlr4::tree::TerminalNode *EVT_NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Event_declarationContext* event_declaration();

  class  Event_declarationsContext : public antlr4::ParserRuleContext {
  public:
    Event_declarationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Event_declarationContext *> event_declaration();
    Event_declarationContext* event_declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Event_declarationsContext* event_declarations();

  class  ParametrizationContext : public antlr4::ParserRuleContext {
  public:
    ParametrizationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Packet_referenceContext *> packet_reference();
    Packet_referenceContext* packet_reference(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParametrizationContext* parametrization();

  class  Prefix_uriContext : public antlr4::ParserRuleContext {
  public:
    Prefix_uriContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *URI_PREFIX_NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prefix_uriContext* prefix_uri();

  class  Full_uriContext : public antlr4::ParserRuleContext {
  public:
    Full_uriContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *URI_FULL_NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Full_uriContext* full_uri();

  class  UriContext : public antlr4::ParserRuleContext {
  public:
    UriContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Prefix_uriContext *prefix_uri();
    Full_uriContext *full_uri();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UriContext* uri();

  class  SubContext : public antlr4::ParserRuleContext {
  public:
    SubContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UriContext *uri();
    antlr4::tree::TerminalNode *SPARQL_VAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SubContext* sub();

  class  PredContext : public antlr4::ParserRuleContext {
  public:
    PredContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UriContext *uri();
    antlr4::tree::TerminalNode *SPARQL_VAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PredContext* pred();

  class  ObjContext : public antlr4::ParserRuleContext {
  public:
    ObjContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UriContext *uri();
    antlr4::tree::TerminalNode *SPARQL_VAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjContext* obj();

  class  TripleContext : public antlr4::ParserRuleContext {
  public:
    TripleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SubContext *sub();
    PredContext *pred();
    ObjContext *obj();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TripleContext* triple();

  class  Rdf_patternContext : public antlr4::ParserRuleContext {
  public:
    Rdf_patternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TripleContext *> triple();
    TripleContext* triple(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rdf_patternContext* rdf_pattern();

  class  Ce_definitionContext : public antlr4::ParserRuleContext {
  public:
    Ce_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EVT_NAME();
    Rdf_patternContext *rdf_pattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Ce_definitionContext* ce_definition();

  class  PatternContext : public antlr4::ParserRuleContext {
  public:
    PatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TerminatorContext *terminator();
    std::vector<Pattern_predicateContext *> pattern_predicate();
    Pattern_predicateContext* pattern_predicate(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PatternContext* pattern();

  class  DefinitionsContext : public antlr4::ParserRuleContext {
  public:
    DefinitionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StaticAttr_definitionContext *> staticAttr_definition();
    StaticAttr_definitionContext* staticAttr_definition(size_t i);
    std::vector<Attr_definitionContext *> attr_definition();
    Attr_definitionContext* attr_definition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DefinitionsContext* definitions();

  class  ConsumingContext : public antlr4::ParserRuleContext {
  public:
    ConsumingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> EVT_NAME();
    antlr4::tree::TerminalNode* EVT_NAME(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConsumingContext* consuming();

  class  Ending_ruleContext : public antlr4::ParserRuleContext {
  public:
    Ending_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Ending_ruleContext* ending_rule();

  class  Trex_rdf_ruleContext : public antlr4::ParserRuleContext {
  public:
    Trex_rdf_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    Event_declarationsContext *event_declarations();
    antlr4::tree::TerminalNode *DEFINE();
    Ce_definitionContext *ce_definition();
    antlr4::tree::TerminalNode *FROM();
    PatternContext *pattern();
    Ending_ruleContext *ending_rule();
    antlr4::tree::TerminalNode *WITH();
    ParametrizationContext *parametrization();
    antlr4::tree::TerminalNode *WHERE();
    DefinitionsContext *definitions();
    antlr4::tree::TerminalNode *CONSUMING();
    ConsumingContext *consuming();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Trex_rdf_ruleContext* trex_rdf_rule();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

