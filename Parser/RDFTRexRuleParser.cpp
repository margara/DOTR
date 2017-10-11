#include "RDFTRexRuleParser.h"

//max len TRex vars
const int SIZE = 256;

void RDFTRexRuleParser::enterEvent_declaration(RDFTESLAParser::Event_declarationContext * ctx){
	eventId_map.insert(std::pair<std::string, int>(ctx->EVT_NAME()->getText(), stoi(ctx->INT_VAL()->getText())));
}

bool checkAllWithin(RDFTESLAParser::Positive_predicateContext* ctx){
	std::string sel = ctx->SEL_POLICY()->getText();
	if(sel.compare("all") == 0)
		return true;
	else
		return false;
}

CompKind getCompKind(RDFTESLAParser::Positive_predicateContext* ctx) {
	std::string sel = ctx->SEL_POLICY()->getText();
	if(sel.compare("each") == 0 || sel.compare("all") == 0 ) return EACH_WITHIN;
	else if (sel.compare("last") == 0)  return LAST_WITHIN;
	else if (sel.compare("first") == 0) return FIRST_WITHIN;
	else return EACH_WITHIN;
}

AggregateFun getAggregateFun(std::string fun) {
	if (fun.compare("AVG") == 0) 	 return AVG;
	if (fun.compare("SUM") == 0) 	 return SUM;
	if (fun.compare("COUNT") == 0) 	 return COUNT;
	if (fun.compare("MIN") == 0) 	 return MIN;
	if (fun.compare("MAX") == 0) 	 return MAX;
	else return AVG;
}

Op getConstrOp(std::string source) {
	if(source.compare("=") == 0)	return EQ;
	if (source.compare(">") == 0)	return GT;
	if (source.compare("<") == 0)	return LT;
	if (source.compare("<=") == 0)	return LE;
	if (source.compare(">=") == 0)	return GE;
	if (source.compare("!=") == 0) 	return NE;
	else return EQ;
}

ValType getValType(std::string vtype) {
	if (vtype.compare("int") == 0) 		 	return INT;
	else if (vtype.compare("float") == 0)   return FLOAT;
	else if (vtype.compare("bool") == 0) 	return BOOL;
	else if (vtype.compare("string") == 0)  return STRING;
	else return INT;
}

OpTreeOperation getBinOp(std::string op) {
	if (op.compare("+") == 0) 	   return ADD;
	else if (op.compare("-") == 0) return SUB;
	else if (op.compare("/") == 0) return DIV;
	else if (op.compare("*") == 0) return MUL;
	else if (op.compare("&") == 0) return AND;
	else if (op.compare("|") == 0) return OR;
	else return OR;
}

void RDFTRexRuleParser::enterCe_definition(RDFTESLAParser::Ce_definitionContext * ctx){
	int type = eventId_map.find(ctx->EVT_NAME()->getText())->second;
	templateCE = new Template;//freed by RDFConstructor
	templateCE->allRuleInfos = new AllHelper;//freed by RDFConstructor
	rule = new RulePkt(false);
	templateCE->eventType = type;
	templateCE->isRuleAllWithin = false;//change on the go if "all" is find
	templateCE->isRuleEachAllWithin = false;
	ceTRex = new CompositeEventTemplate(type);//freed by TRex
	rule->setCompositeEventTemplate(ceTRex);
	RDFTESLAParser::Rdf_patternContext* pattern = ctx->rdf_pattern();
	std::vector<RDFTESLAParser::TripleContext*> tripleList = pattern->triple();
	for(std::vector<RDFTESLAParser::TripleContext*>::iterator triple = tripleList.begin(); triple != tripleList.end(); triple++){
		TripleTemplate t;
		RDFTESLAParser::SubContext* subject = (*triple)->sub();
		RDFTESLAParser::PredContext* predicate = (*triple)->pred();
		RDFTESLAParser::ObjContext* object = (*triple)->obj();
		if (subject->uri() != NULL) {//it is not a var, just copy the uri
			strcpy(t.subject, subject->uri()->getText().c_str());
			t.isSubVar = false;
		} else if(subject->SPARQL_VAR()!= NULL){//it is a var
			strcpy(t.subject, subject->SPARQL_VAR()->getText().c_str());
			t.isSubVar = true;
		}
		if (predicate->uri() != NULL) {
			strcpy(t.predicate, predicate->uri()->getText().c_str());
			t.isPredVar = false;
		} else if(predicate->SPARQL_VAR()!= NULL){
			strcpy(t.predicate, predicate->SPARQL_VAR()->getText().c_str());
			t.isPredVar = true;
		}
		if (object->uri() != NULL) {
			strcpy(t.object, object->uri()->getText().c_str());
			t.isObjVar = false;
		} else if(object->SPARQL_VAR()!= NULL){
			strcpy(t.object, object->SPARQL_VAR()->getText().c_str());
			t.isObjVar = true;
		}
		templateCE->triples.push_back(t);
	}
}

void RDFTRexRuleParser::enterTerminator(RDFTESLAParser::TerminatorContext * ctx){
	int eventType = eventId_map.find(ctx->predicate()->EVT_NAME()->getText())->second;
	if(ctx->predicate()->SPARQL_QUERY() != NULL){
		std::string query = ctx->predicate()->SPARQL_QUERY()->getText();
		query.erase(0,1);//erase '['
		query.erase(query.end()-1, query.end());//erase ']'
		queries.push_back(std::make_tuple(eventType, ctx->predicate()->EVT_NAME()->getText(), query));
		if(ctx->predicate()->event_alias() != NULL){
			eventId_map.insert(std::pair<std::string, int>(ctx->predicate()->event_alias()->EVT_NAME()->getText(), eventType));
		}
	}
	int numConstr = ctx->predicate()->attr_constraint().size();
	if(numConstr == 0){
		rule->addRootPredicate(eventType, NULL, 0);
	}
	else{
		Constraint c[numConstr];
		for(int i=0; i< numConstr;i++){
			RDFTESLAParser::Attr_constraintContext* constrCtx = ctx->predicate()->attr_constraint(i);
			if(constrCtx->static_reference()->INT_VAL() != NULL){
				c[i].type = INT;
				c[i].intVal = stoi(constrCtx->static_reference()->INT_VAL()->getText());
			}else if(constrCtx->static_reference()->FLOAT_VAL() != NULL){
				c[i].type = FLOAT;
				c[i].floatVal = stof(constrCtx->static_reference()->FLOAT_VAL()->getText());
			}else if(constrCtx->static_reference()->BOOL_VAL() != NULL){
				c[i].type = BOOL;
				if(constrCtx->static_reference()->BOOL_VAL()->getText().compare("true") == 0) c[i].boolVal= true;
				else c[i].boolVal = false;
			}else if(constrCtx->static_reference()->STRING_VAL() != NULL){
				std::string string = constrCtx->static_reference()->STRING_VAL()->getText();
				//remove quotes from the string
				string.erase(0,1);//erase '"'
				string.erase(string.end()-1, string.end());//erase '"'
				strcpy(c[i].stringVal, string.c_str());
				c[i].type = STRING;
			}
			std::string name = constrCtx->SPARQL_VAR()->getText();
			strcpy(c[i].name, name.c_str()+1);//delete '?' or '$'
			c[i].op = getConstrOp(constrCtx->OPERATOR()->getText());
		}
		rule->addRootPredicate(eventType, c, numConstr);
	}
	templateCE->allRuleInfos->typeTerminator = eventType;
	predicatesIds.insert(std::make_pair(ctx->predicate()->EVT_NAME()->getText(), predicateCount));//predicateCount = 0 here
	predicateCount++;
}

void RDFTRexRuleParser::enterPositive_predicate(RDFTESLAParser::Positive_predicateContext * ctx){
	int eventType = eventId_map.find(ctx->predicate()->EVT_NAME()->getText())->second;
	if(ctx->neg_one_reference() != NULL){
		std::string refEvent = ctx->neg_one_reference()->EVT_NAME()->getText();
		int predId = predicatesIds.find(refEvent)->second;
		CompKind comp = getCompKind(ctx);
		if(ctx->predicate()->SPARQL_QUERY() != NULL){
			std::string query = ctx->predicate()->SPARQL_QUERY()->getText();
			query.erase(0,1);//erase '['
			query.erase(query.end()-1, query.end());//erase ']'
			queries.push_back(std::make_tuple(eventType, ctx->predicate()->EVT_NAME()->getText(), query));
			if(ctx->predicate()->event_alias() != NULL){
				eventId_map.insert(std::pair<std::string, int>(ctx->predicate()->event_alias()->EVT_NAME()->getText(), eventType));
			}
		}
		TimeMs time(stoi(ctx->neg_one_reference()->INT_VAL()->getText()));
		int numConstr = ctx->predicate()->attr_constraint().size();
		if(numConstr == 0){
			rule->addPredicate(eventType, NULL, 0, predId, time, comp);
		}
		else{
			Constraint c[numConstr];
			for(int i=0; i< numConstr;i++){
				RDFTESLAParser::Attr_constraintContext* constrCtx = ctx->predicate()->attr_constraint(i);
				if(constrCtx->static_reference()->INT_VAL() != NULL){
					c[i].type = INT;
					c[i].op = getConstrOp(constrCtx->OPERATOR()->getText());
					c[i].intVal = stoi(constrCtx->static_reference()->INT_VAL()->getText());
				}else if(constrCtx->static_reference()->FLOAT_VAL() != NULL){
					c[i].type = FLOAT;
					c[i].op = getConstrOp(constrCtx->OPERATOR()->getText());
					c[i].floatVal = stof(constrCtx->static_reference()->FLOAT_VAL()->getText());
				}else if(constrCtx->static_reference()->BOOL_VAL() != NULL){
					c[i].type = BOOL;
					c[i].op = getConstrOp(constrCtx->OPERATOR()->getText());
					if(constrCtx->static_reference()->BOOL_VAL()->getText().compare("true") == 0) c[i].boolVal= true;
					else c[i].boolVal = false;
				}else if(constrCtx->static_reference()->STRING_VAL() != NULL){
					std::string string = constrCtx->static_reference()->STRING_VAL()->getText();
					//remove quotes from the string
					string.erase(0,1);//erase '"'
					string.erase(string.end()-1, string.end());//erase '"'
					strcpy(c[i].stringVal, string.c_str());
					c[i].type = STRING;
					c[i].op = getConstrOp(constrCtx->OPERATOR()->getText());
				}
				std::string name = constrCtx->SPARQL_VAR()->getText();
				strcpy(c[i].name, name.c_str()+1);//delete '?' or '$'
			}
			rule->addPredicate(eventType, c, numConstr, predId, time, comp);
		}
		if(checkAllWithin(ctx)){
			templateCE->isRuleAllWithin = true;
			if(eventCompositions.find(refEvent)!=eventCompositions.end() && eventCompositions.find(refEvent)->second.compare("each") == 0){//rule is all within x from (event of type each)
				templateCE->isRuleEachAllWithin = true;
				templateCE->allRuleInfos->typeEventAll = eventType;
				templateCE->allRuleInfos->window = rule->getWinBetween(0, predicateCount);//0=root
			}
		}
		eventCompositions.insert(std::make_pair(ctx->predicate()->EVT_NAME()->getText(), ctx->SEL_POLICY()->getText()));
		predicatesIds.insert(std::make_pair(ctx->predicate()->EVT_NAME()->getText(), predicateCount));
		predicateCount++;
	}else if(ctx->neg_between() != NULL){
		//this (positive predicates with between) is not implemented in trex...so it's here but no use

		/*	int predId1 = predicatesIds.find(ctx->neg_between()->EVT_NAME(0)->getText())->second;
		int predId2 = predicatesIds.find(ctx->neg_between()->EVT_NAME(1)->getText())->second;
		if(ctx->predicate()->SPARQL_QUERY() != NULL){
			std::string query = ctx->predicate()->SPARQL_QUERY()->getText();
			query.erase(0,1);//erase '['
			query.erase(query.end()-1, query.end());//erase ']'
			queries.push_back(std::make_tuple(eventType, ctx->predicate()->EVT_NAME()->getText(), query));
			if(ctx->predicate()->event_alias() != NULL){
				eventId_map.insert(std::pair<std::string, int>(ctx->predicate()->event_alias()->EVT_NAME()->getText(), eventType));
			}
		}
		TimeMs time = rule->getWinBetween(predId1, predId2);
		int numConstr = ctx->predicate()->attr_constraint().size();
		if(numConstr == 0){
			rule->addPredicate(eventType, NULL, 0, predId1, time, getCompKind(ctx));
		}else{
			Constraint c[numConstr];
			for(int i=0; i< numConstr;i++){
				RDFTESLAParser::Attr_constraintContext* constrCtx = ctx->predicate()->attr_constraint(i);
				if(constrCtx->static_reference()->INT_VAL() != NULL){
					c[i].type = INT;
					c[i].intVal = stoi(constrCtx->static_reference()->INT_VAL()->getText());
				}else if(constrCtx->static_reference()->FLOAT_VAL() != NULL){
					c[i].type = FLOAT;
					c[i].floatVal = stof(constrCtx->static_reference()->FLOAT_VAL()->getText());
				}else if(constrCtx->static_reference()->BOOL_VAL() != NULL){
					c[i].type = BOOL;
					if(constrCtx->static_reference()->BOOL_VAL()->getText().compare("true") == 0) c[i].boolVal= true;
					else c[i].boolVal = false;
				}else if(constrCtx->static_reference()->STRING_VAL() != NULL){
					std::string string = constrCtx->static_reference()->STRING_VAL()->getText();
					//remove quotes from the string
					string.erase(0,1);//erase '"'
					string.erase(string.end()-1, string.end());//erase '"'
					strcpy(c[i].stringVal, string.c_str());
					c[i].type = STRING;
				}
				std::string name = constrCtx->SPARQL_VAR()->getText();
				strcpy(c[i].name, name.c_str()+1);//delete '?' or '$'
				c[i].op = getConstrOp(constrCtx->OPERATOR()->getText());
			}
			rule->addPredicate(eventType, c, numConstr, predId1, time, getCompKind(ctx));
		}
		if(checkAllWithin(ctx)){
			templateCE->isRuleAllWithin = true;
		}
		rule->addPredicate(eventType, NULL, 0, predId1, time, getCompKind(ctx));
		eventCompositions.insert(std::make_pair(ctx->predicate()->EVT_NAME()->getText(), ctx->SEL_POLICY()->getText()));
		predicatesIds.insert(std::make_pair(ctx->predicate()->EVT_NAME()->getText(), predicateCount));
		predicateCount++;
		 */
	}
}

void RDFTRexRuleParser::enterNegative_predicate(RDFTESLAParser::Negative_predicateContext * ctx){
	int eventType = eventId_map.find(ctx->predicate()->EVT_NAME()->getText())->second;
	if(ctx->predicate()->SPARQL_QUERY() != NULL){
		std::string query = ctx->predicate()->SPARQL_QUERY()->getText();
		query.erase(0,1);//erase '['
		query.erase(query.end()-1, query.end());//erase ']'
		queries.push_back(std::make_tuple(eventType, ctx->predicate()->EVT_NAME()->getText(), query));
		if(ctx->predicate()->event_alias() != NULL){
			eventId_map.insert(std::pair<std::string, int>(ctx->predicate()->event_alias()->EVT_NAME()->getText(), eventType));
		}
	}
	RDFTESLAParser::Neg_one_referenceContext* neg_one = ctx->neg_one_reference();
	RDFTESLAParser::Neg_betweenContext* neg_between = ctx->neg_between();
	if(neg_one != NULL){
		int predId = predicatesIds.find(neg_one->EVT_NAME()->getText())->second;
		TimeMs time(stoi(neg_one->INT_VAL()->getText()));
		int numConstr = ctx->predicate()->attr_constraint().size();
		if(numConstr == 0){
			rule->addTimeBasedNegation(eventType, NULL, 0, predId, time);
		}
		else{
			Constraint c[numConstr];
			for(int i=0; i< numConstr;i++){
				RDFTESLAParser::Attr_constraintContext* constrCtx = ctx->predicate()->attr_constraint(i);
				if(constrCtx->static_reference()->INT_VAL() != NULL){
					c[i].type = INT;
					c[i].intVal = stoi(constrCtx->static_reference()->INT_VAL()->getText());
				}else if(constrCtx->static_reference()->FLOAT_VAL() != NULL){
					c[i].type = FLOAT;
					c[i].floatVal = stof(constrCtx->static_reference()->FLOAT_VAL()->getText());
				}else if(constrCtx->static_reference()->BOOL_VAL() != NULL){
					c[i].type = BOOL;
					if(constrCtx->static_reference()->BOOL_VAL()->getText().compare("true") == 0) c[i].boolVal= true;
					else c[i].boolVal = false;
				}else if(constrCtx->static_reference()->STRING_VAL() != NULL){
					std::string string = constrCtx->static_reference()->STRING_VAL()->getText();
					//remove quotes from the string
					string.erase(0,1);//erase '"'
					string.erase(string.end()-1, string.end());//erase '"'
					strcpy(c[i].stringVal, string.c_str());
					c[i].type = STRING;
				}
				std::string name = constrCtx->SPARQL_VAR()->getText();
				strcpy(c[i].name, name.c_str()+1);//delete '?' or '$'
				c[i].op = getConstrOp(constrCtx->OPERATOR()->getText());
			}
			rule->addTimeBasedNegation(eventType, c, numConstr, predId, time);
		}
	}else if(neg_between != NULL){
		int predId1 = predicatesIds.find(neg_between->EVT_NAME(0)->getText())->second;
		int predId2 = predicatesIds.find(neg_between->EVT_NAME(1)->getText())->second;
		int numConstr = ctx->predicate()->attr_constraint().size();
		if(numConstr == 0){
			rule->addNegationBetweenStates(eventType, NULL, 0, predId1, predId2);
		}
		else{
			Constraint c[numConstr];
			for(int i=0; i< numConstr;i++){
				RDFTESLAParser::Attr_constraintContext* constrCtx = ctx->predicate()->attr_constraint(i);
				if(constrCtx->static_reference()->INT_VAL() != NULL){
					c[i].type = INT;
					c[i].op = getConstrOp(constrCtx->OPERATOR()->getText());
					c[i].intVal = stoi(constrCtx->static_reference()->INT_VAL()->getText());
				}else if(constrCtx->static_reference()->FLOAT_VAL() != NULL){
					c[i].type = FLOAT;
					c[i].floatVal = stof(constrCtx->static_reference()->FLOAT_VAL()->getText());
				}else if(constrCtx->static_reference()->BOOL_VAL() != NULL){
					c[i].type = BOOL;
					if(constrCtx->static_reference()->BOOL_VAL()->getText().compare("true") == 0) c[i].boolVal= true;
					else c[i].boolVal = false;
				}else if(constrCtx->static_reference()->STRING_VAL() != NULL){
					std::string string = constrCtx->static_reference()->STRING_VAL()->getText();
					//remove quotes from the string
					string.erase(0,1);//erase '"'
					string.erase(string.end()-1, string.end());//erase '"'
					strcpy(c[i].stringVal, string.c_str());
					c[i].type = STRING;
				}
				std::string name = constrCtx->SPARQL_VAR()->getText();
				strcpy(c[i].name, name.c_str()+1);//delete '?' or '$'
			}
			rule->addNegationBetweenStates(eventType, c, numConstr, predId1, predId2);
		}
	}
	negPredIds.insert(std::make_pair(ctx->predicate()->EVT_NAME()->getText(), negationCount));
	negationCount++;
}

void RDFTRexRuleParser::enterParametrization(RDFTESLAParser::ParametrizationContext * ctx){
	unsigned int numParam = ctx->packet_reference().size();
	for(unsigned int i = 0; i < numParam; i = i + 2){
		int predId1 = predicatesIds.find(ctx->packet_reference(i)->EVT_NAME()->getText())->second;
		int predId2 = predicatesIds.find(ctx->packet_reference(i+1)->EVT_NAME()->getText())->second;
		std::string var1 = ctx->packet_reference(i)->SPARQL_VAR()->getText();
		std::string var2 = ctx->packet_reference(i+1)->SPARQL_VAR()->getText();
		char* v1 = new char[SIZE];
		char* v2 = new char[SIZE];
		strcpy(v1, var1.c_str());
		strcpy(v2, var2.c_str());
		if(negPredIds.find(ctx->packet_reference(i)->EVT_NAME()->getText()) != negPredIds.end()){
			int negId1 = negPredIds.find(ctx->packet_reference(i)->EVT_NAME()->getText())->second;
			rule->addParameterForNegation(predId2, v2+1, negId1, v1+1);
		}else if(negPredIds.find(ctx->packet_reference(i+1)->EVT_NAME()->getText()) != negPredIds.end()){
			int negId2 = negPredIds.find(ctx->packet_reference(i+1)->EVT_NAME()->getText())->second;
			rule->addParameterForNegation(predId1, v1+1, negId2, v2+1);
		}else{
			rule->addParameterBetweenStates(predId1, v1+1, predId2, v2+1);//+1 drops the '?' or '$'
		}
		delete[] v1;
		delete[] v2;
	}
}

OpTree* RDFTRexRuleParser::recursivelyNavigateExpression(RDFTESLAParser::ExprContext* expr, OpTree* tree, ValType valType) {
	if (expr->param_atom() != NULL) {
		//This is a leaf!
		RDFTESLAParser::Param_atomContext* ctxParam = expr->param_atom();
		StaticValueReference* value = NULL;
		ValType vtype = INT;//init purposes
		if (ctxParam->static_reference() != NULL) {
			if (ctxParam->static_reference()->INT_VAL() != NULL) {
				int val = stoi(ctxParam->static_reference()->INT_VAL()->getText());
				value = new StaticValueReference(val);//freed by TRex?
				vtype = INT;
			}
			else if (ctxParam->static_reference()->FLOAT_VAL() != NULL) {
				float val = stof(ctxParam->static_reference()->FLOAT_VAL()->getText());
				value = new StaticValueReference(val);
				vtype = FLOAT;
			}
			else if (ctxParam->static_reference()->BOOL_VAL() != NULL) {
				bool b;
				if(ctxParam->static_reference()->BOOL_VAL()->getText().compare("true") == 0) b= true;
				else b = false;
				value = new StaticValueReference(b);
				vtype = BOOL;
			}
			else if (ctxParam->static_reference()->STRING_VAL() != NULL) {
				std::string string = ctxParam->static_reference()->STRING_VAL()->getText();
				//remove quotes from the string
				string.erase(0,1);//erase '"'
				string.erase(string.end()-1, string.end());//erase '"'
				char *s = new char[SIZE];
				strcpy(s, string.c_str());
				value = new StaticValueReference(s);
				vtype = STRING;
				delete[] s;
			}
			return new OpTree(value, vtype);
		}
		else if (ctxParam->packet_reference()!=NULL) {
			//this is a reference to an attribute from another query
			RDFTESLAParser::Packet_referenceContext* pkt_ctx = ctxParam->packet_reference();
			//I need to figure out the idx of the event in the sequence; it's not an aggregate
			int predId = predicatesIds.find(pkt_ctx->EVT_NAME()->getText())->second;
			std::string varName = pkt_ctx->SPARQL_VAR()->getText();
			char* name = new char[SIZE];
			strcpy(name, varName.c_str());
			RulePktValueReference* ref = new RulePktValueReference(predId, name+1 , STATE);//+1 drops '?' or '$'
			delete[] name;
			return new OpTree(ref, valType);
		}
	}
	else if (expr->aggregate_atom() != NULL) {
		//This is a reference to an aggregate
		RDFTESLAParser::Aggregate_atomContext* agCtx = expr->aggregate_atom();
		AggregateFun fun = getAggregateFun(agCtx->AGGR_FUN()->getText());
		int predId = predicatesIds.find(agCtx->packet_reference()->EVT_NAME()->getText())->second;
		if (agCtx->packet_reference() != NULL) {
			int constrLen = agCtx->attr_constraint().size();
			Constraint* c = new Constraint[constrLen];
			for(unsigned int i = 0; i < agCtx->attr_constraint().size(); i++){
				RDFTESLAParser::Attr_constraintContext* constr = agCtx->attr_constraint(i);
				std::string nameString = constr->SPARQL_VAR()->getText();
				strcpy(c[i].name, nameString.c_str()+1);
				if(constr->static_reference()->INT_VAL() != NULL){
					c[i].type = INT;
					c[i].op = getConstrOp(constr->OPERATOR()->getText());
					c[i].intVal = stoi(constr->static_reference()->INT_VAL()->getText());
				}else if(constr->static_reference()->FLOAT_VAL() != NULL){
					c[i].type = FLOAT;
					c[i].op = getConstrOp(constr->OPERATOR()->getText());
					c[i].floatVal = stof(constr->static_reference()->FLOAT_VAL()->getText());
				}else if(constr->static_reference()->BOOL_VAL() != NULL){
					c[i].type = BOOL;
					c[i].op = getConstrOp(constr->OPERATOR()->getText());
					if(constr->static_reference()->BOOL_VAL()->getText().compare("true") == 0) c[i].boolVal = true;
					else c[i].boolVal = false;
				}else if(constr->static_reference()->STRING_VAL() != NULL){
					c[i].type = STRING;
					c[i].op = getConstrOp(constr->OPERATOR()->getText());
					std::string string = constr->static_reference()->STRING_VAL()->getText();
					string.erase(0,1);//erase '"'
					string.erase(string.end()-1, string.end());//erase '"'
					strcpy(c[i].stringVal, string.c_str());
				}
			}
			for(unsigned int j = 0; j < agCtx->attr_parameter().size(); j++){
				//this is added for completeness, "SPARQL_VAR := expr" <---it has to be tested 
				//(here it just works for static constraints, i.e. expr is a static val (see previous for cycle)) 
				RDFTESLAParser::Attr_parameterContext* constrParam = agCtx->attr_parameter(j);
				std::string nameString = constrParam->SPARQL_VAR()->getText();
				char* name = new char[SIZE];
				strcpy(name, nameString.c_str());
				RulePktValueReference* sparqlValue = new RulePktValueReference(predId, name+1, STATE);
				OpTree* varTree = new OpTree(sparqlValue, getValType(constrParam->VALTYPE()->getText()));
				if(constrParam->expr()->param_atom() != NULL){
					rule->addComplexParameter(getConstrOp(constrParam->OPERATOR()->getText()), getValType(constrParam->VALTYPE()->getText()) , varTree, buildOpTree(constrParam->expr(), getValType(constrParam->VALTYPE()->getText())));
				}else if(constrParam->expr()->aggregate_atom() != NULL){
					rule->addComplexParameterForAggregate(getConstrOp(constrParam->OPERATOR()->getText()), getValType(constrParam->VALTYPE()->getText()), varTree, buildOpTree(constrParam->expr(), getValType(constrParam->VALTYPE()->getText())));
				}else{//this is an expr
					//not implemented (RDFTRex doesn't use parameters)... workaround possible?
				}
				delete[] name;
			}
			std::string predName = agCtx->packet_reference()->EVT_NAME()->getText();
			std::string attrName = agCtx->packet_reference()->SPARQL_VAR()->getText();
			int type = eventId_map.find(predName)->second;
			char* name = new char[SIZE];
			strcpy(name, attrName.c_str());
			if(agCtx->agg_one_reference() != NULL){
				TimeMs time(stoi(agCtx->agg_one_reference()->INT_VAL()->getText()));
				int predId = predicatesIds.find(agCtx->agg_one_reference()->EVT_NAME()->getText())->second;
				rule->addTimeBasedAggregate(type, c, constrLen, predId, time, name+1, fun);
			}else if(agCtx->agg_between() != NULL){
				int predId1 = predicatesIds.find(agCtx->agg_between()->EVT_NAME(0)->getText())->second;
				int predId2 = predicatesIds.find(agCtx->agg_between()->EVT_NAME(1)->getText())->second;
				rule->addAggregateBetweenStates(type, c, constrLen, predId1, predId2, name+1, fun);
			}
			RulePktValueReference* ref  = new RulePktValueReference(aggregateCount);
			aggregateCount++;
			delete[] name;
			delete[] c;
			return new OpTree(ref, valType);
		}
	}
	else {
		//this is an inner node
		std::vector<RDFTESLAParser::ExprContext*> exprVector = expr->expr();
		for(unsigned int m = 0; m < exprVector.size(); m++){
			RDFTESLAParser::ExprContext* subExpr = expr->expr(m);
			OpTreeOperation op = OR;
			if(expr->BINOP_MUL() != NULL){
				op = getBinOp(expr->BINOP_MUL()->getText());
			}else if(expr->BINOP_ADD() != NULL){
				op = getBinOp(expr->BINOP_ADD()->getText());
			}
			if(tree != NULL){
				tree = new OpTree(tree, recursivelyNavigateExpression(subExpr, tree, valType), op, valType);
			}else{
				tree = recursivelyNavigateExpression(subExpr, tree, valType);
			}
		}
	}
	return tree;
}

OpTree* RDFTRexRuleParser::buildOpTree(RDFTESLAParser::ExprContext* expr, ValType valType){
	OpTree* tree = NULL;
	tree = recursivelyNavigateExpression(expr, tree, valType);
	return tree;
}

void RDFTRexRuleParser::enterDefinitions(RDFTESLAParser::DefinitionsContext * ctx){
	//STATIC ATTRIBUTES
	unsigned int numAttr = ctx->staticAttr_definition().size();
	for(unsigned int i = 0; i < numAttr; i++){
		Attribute attr;
		RDFTESLAParser::Static_referenceContext* ref = ctx->staticAttr_definition(i)->static_reference();
		std::string name = ctx->staticAttr_definition(i)->SPARQL_VAR()->getText();
		strcpy(attr.name, name.c_str()+1);//+1 drops the '?' or '$'
		if(ref->INT_VAL() != NULL){
			attr.type = INT;
			attr.intVal = stoi(ref->INT_VAL()->getText());
		}else if(ref->FLOAT_VAL() != NULL){
			attr.type = FLOAT;
			attr.floatVal = stof(ref->FLOAT_VAL()->getText());
		}else if(ref->STRING_VAL() != NULL){
			attr.type = STRING;
			std::string string = ref->STRING_VAL()->getText();
			string.erase(0,1);//erase '"'
			string.erase(string.end()-1, string.end());//erase '"'
			strcpy(attr.stringVal, string.c_str());
		}else if(ref->BOOL_VAL() != NULL){
			attr.type = BOOL;
			if(ref->BOOL_VAL()->getText().compare("true") == 0) attr.boolVal = true;
			else attr.boolVal = false;
		}
		ceTRex->addStaticAttribute(attr);
	}
	//PARAMS/AGGREGATES
	unsigned int numParam = ctx->attr_definition().size();
	for(unsigned int j = 0; j < numParam; j++){
		char* name = new char[SIZE];
		ValType type = INT;
		std::string stringVar = ctx->attr_definition(j)->SPARQL_VAR()->getText();
		std::string valtype = ctx->attr_definition(j)->VALTYPE()->getText();
		strcpy(name, stringVar.c_str());
		if(valtype.compare("string") == 0) type = STRING;
		else if(valtype.compare("int") == 0) type = INT;
		else if(valtype.compare("float") == 0) type = FLOAT;
		else if(valtype.compare("bool") == 0) type = BOOL;
		OpTree* tree = buildOpTree(ctx->attr_definition(j)->expr(), type);
		ceTRex->addAttribute(name+1, tree);//+1 drops '?' or '$'
		delete[] name;
	}
}

void RDFTRexRuleParser::enterConsuming(RDFTESLAParser::ConsumingContext * ctx){
	for(unsigned int i = 0; i < ctx->EVT_NAME().size(); i++){
		int predId = predicatesIds.find(ctx->EVT_NAME(i)->getText())->second;
		rule->addConsuming(predId);
	}
}

//Parses a rule
void RDFTRexRuleParser::parse(std::string rule, RDFStore* store, TRexEngine* engine, RDFConstructor* constructor){
	antlr4::ANTLRInputStream input(rule);
	RDFTESLALexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	RDFTESLAParser parser(&tokens);
	antlr4::tree::ParseTree* tree = parser.trex_rdf_rule();
	antlr4::tree::ParseTreeListener* listener(this);
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(listener, tree);
	for(unsigned int i = 0; i < queries.size(); i ++){
		int type = (int)std::get<0>(queries[i]);
		std::string name = std::get<1>(queries[i]);
		std::string string = std::get<2>(queries[i]);
		store->addQuery(type, name, string);
	}
	constructor->addTemplate(templateCE->eventType, templateCE);
	engine->processRulePkt(this->rule);
}
