grammar RDFTESLA;

/*
@header {
}
*/

@members {
std::stringstream ss; // can't make locals in lexer rules
std::string str;
}

ASSIGN     : 'Assign';
DEFINE     : 'Define';
FROM 	   : 'From';
WITH       : 'With';
WHERE 	   : 'Where';
CONSUMING  : 'Consuming';
VALTYPE    : 'string' | 'int' | 'float' | 'bool' ;
SEL_POLICY : 'each' | 'last' | 'first' | 'all' ;
AGGR_FUN   : 'AVG' | 'SUM' | 'MAX' | 'MIN' | 'COUNT' ;
OPERATOR   : '=' | '>' | '<' | '>=' | '<=' | '!=' | '&' | '|' ;
BINOP_MUL  : '*' | '/';
BINOP_ADD  : '+' | '-' ;
INT_VAL    : ('0' .. '9')+;
FLOAT_VAL  : ('0' .. '9')+ '.' ('0' .. '9')+ ;
BOOL_VAL   : 'false' | 'true' ;
STRING_VAL :   '"'
        (   '\\'
            (   'r'     {ss << '\r';}
            |   'n'     {ss << '\n';}
            |   't'     {ss << '\t';}
            |   '\\'    {ss << '\\';}
            |   '\"'   {ss << '"';}
            )
        |   ~('\\'|'"') {ss << ((char)_input->LA(-1));}
        )*
        '"'
        {str = ss.str();}
    ;
SPARQL_QUERY :   '['
         (   '\\'
            (   'r'     {ss << '\r';}
            |   'n'     {ss << '\n';}
            |   't'     {ss << '\t';}
            |   '\\'    {ss << '\\';}
            |   '\"'   {ss << '"';}
            )
        |    [ ]+ {ss << ' ';}
        |   ~('\\'|']') {ss << ((char)_input->LA(-1));}
        )*
        ']'
        {str = ss.str();}
    ;
EVT_NAME   : ('A' .. 'Z') (('A' .. 'Z') | ('a' .. 'z') | ('0' .. '9') | '_')*;
URI_PREFIX_NAME   : [a-zA-Z0-9@%_\\+~#&/=-]+ [:] [a-zA-Z0-9@%_\\+~#&/=-]+ ;
URI_FULL_NAME   : [<] [[a-zA-Z0-9@:%_\\+.~#&/=-]+ [>] ;
SPARQL_VAR :  [?] [a-zA-Z0-9]+ ;
WS : ( [ ]+ | [\t\r\n]+ ) -> skip ;

static_reference : (INT_VAL | FLOAT_VAL | STRING_VAL | BOOL_VAL);
packet_reference : (EVT_NAME '.' SPARQL_VAR);
param_atom : (packet_reference | static_reference); 
agg_one_reference : ('within' INT_VAL 'from' EVT_NAME);
agg_between : ('between' EVT_NAME 'and' EVT_NAME);
aggregate_atom : AGGR_FUN '(' packet_reference '(' ((attr_parameter | attr_constraint) (',' (attr_parameter | attr_constraint))* )? ')' ')' (agg_one_reference | agg_between) ; 
expr: expr BINOP_MUL expr | expr BINOP_ADD expr | '(' expr ')' | (param_atom | aggregate_atom);
staticAttr_definition: SPARQL_VAR ':=' static_reference;
attr_definition: '(' VALTYPE ')' SPARQL_VAR ':=' expr;
attr_constraint: SPARQL_VAR OPERATOR static_reference;
attr_parameter: '(' VALTYPE ')' SPARQL_VAR OPERATOR expr;
predicate : EVT_NAME (':=' SPARQL_QUERY ( '(' attr_constraint (',' attr_constraint)* ')' )? event_alias?)? ;
event_alias : 'as' EVT_NAME;
terminator : predicate;
positive_predicate : 'and' SEL_POLICY predicate (neg_one_reference | neg_between);
neg_one_reference: ('within' INT_VAL 'from' EVT_NAME);
neg_between: ('between' EVT_NAME 'and' EVT_NAME);
negative_predicate : 'and' 'not' predicate (neg_one_reference | neg_between);
pattern_predicate : positive_predicate | negative_predicate;
event_declaration : INT_VAL '=>' EVT_NAME;
event_declarations : event_declaration (',' event_declaration)*;
parametrization : packet_reference ':=' packet_reference (',' packet_reference ':=' packet_reference)*;
prefix_uri : URI_PREFIX_NAME ;
full_uri : URI_FULL_NAME ;
uri : prefix_uri | full_uri;  
sub : uri | SPARQL_VAR;
pred : uri | SPARQL_VAR; 
obj : uri | SPARQL_VAR;
triple : sub (WS)* pred (WS)* obj (WS)* '.' ; 
rdf_pattern : '{' (triple)* '}';
ce_definition : EVT_NAME ':=' rdf_pattern ; 
pattern : terminator (pattern_predicate)*;
definitions : (staticAttr_definition | attr_definition) (',' (staticAttr_definition | attr_definition))*;
consuming : EVT_NAME (',' EVT_NAME)*;
ending_rule : ';';
trex_rdf_rule : ASSIGN event_declarations DEFINE ce_definition FROM pattern (WITH parametrization)? (WHERE definitions)? (CONSUMING consuming)? ending_rule;
