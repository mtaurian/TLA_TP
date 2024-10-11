#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

Value * ValueStringSemanticAction(char * the_string){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Value * value = calloc(1, sizeof(Value));
	value->v_string = the_string;
	value->type = TYPE_STRING;
	return value;
}

Value * ValueIntegerSemanticAction(int the_integer){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Value * value = calloc(1, sizeof(Value));
	value->v_integer = the_integer;
	value->type = TYPE_INTEGER;
	return value;
}

Value * ValueFloatSemanticAction(float the_float){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Value * value = calloc(1, sizeof(Value));
	value->v_float = the_float;
	value->type = TYPE_FLOAT;
	return value;
}

Value * ValueDateSemanticAction( Date * the_date){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Value * value = calloc(1, sizeof(Value));
	value->v_date = the_date;
	value->type = TYPE_DATE;
	return value;
}


LibFunction * LibFunctionIntegerSemanticAction(LibFunctionType the_libFunctionType,int the_param){
	_logSyntacticAnalyzerAction(__FUNCTION__);
		LibFunction *libFunction =calloc(1,sizeof(LibFunction));
		libFunction->parameterType=TYPE_INTEGER;
		libFunction->type=the_libFunctionType;
		libFunction->v_integer=the_param;
		return libFunction;

}
LibFunction * LibFunctionFloatSemanticAction(LibFunctionType the_libFunctionType,float the_param){
	_logSyntacticAnalyzerAction(__FUNCTION__);
		LibFunction *libFunction =calloc(1,sizeof(LibFunction));
		libFunction->parameterType=TYPE_FLOAT;
		libFunction->type=the_libFunctionType;
		libFunction->v_float=the_param;
		return libFunction;

}
LibFunction * LibFunctionStringSemanticAction(LibFunctionType the_libFunctionType,char* the_param){
	_logSyntacticAnalyzerAction(__FUNCTION__);
		LibFunction *libFunction =calloc(1,sizeof(LibFunction));
		libFunction->parameterType=TYPE_STRING;
		libFunction->type=the_libFunctionType;
		libFunction->v_string=the_param;
		return libFunction;
}
LibFunction * LibFunctionDateSemanticAction(LibFunctionType the_libFunctionType, Date * the_param){
	_logSyntacticAnalyzerAction(__FUNCTION__);
		LibFunction *libFunction =calloc(1,sizeof(LibFunction));
		libFunction->parameterType=TYPE_DATE;
		libFunction->type=the_libFunctionType;
		libFunction->v_date=the_param;
		return libFunction;
}
LibFunction * LibFunctionIdSemanticAction(LibFunctionType the_libFunctionType,char * the_param){
	_logSyntacticAnalyzerAction(__FUNCTION__);
		LibFunction *libFunction =calloc(1,sizeof(LibFunction));
		libFunction->parameterType=TYPE_ID;
		libFunction->type=the_libFunctionType;
		libFunction->v_id=the_param;
		return libFunction;
}
LibFunction * LibFunctionNoneSemanticAction(LibFunctionType the_libFunctionType){
	_logSyntacticAnalyzerAction(__FUNCTION__);
		LibFunction *libFunction =calloc(1,sizeof(LibFunction));
		libFunction->parameterType=TYPE_NONE;
		libFunction->type=the_libFunctionType;
		return libFunction;
}

Date * CreateDateSemanticAction(int the_day, int the_month, int the_year){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Date * date = calloc(1, sizeof(Date));
	date->day =  the_day;
	date->month = the_month;
	date->year = the_year;
	return date;
}


Condition * ConditionBooleanSemanticAction(Types the_type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Condition * condition = calloc(1, sizeof(Condition));
	condition->type = CONDITION_TYPE_BASIC;
	condition->basicProp = calloc(1, sizeof(BasicProp));
	condition->basicProp->truthValue = the_type == TYPE_TRUE ? 1 : 0;
	condition->basicProp->type = BASIC_PROP_TYPE_BOOLEAN;
	return condition;
}

Condition * ConditionFunctionSemanticAction( char * the_id, LibFunction * the_function){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Condition * condition = calloc(1, sizeof(Condition));
	condition->type = CONDITION_TYPE_BASIC;
	condition->basicProp = calloc(1, sizeof(BasicProp));
	condition->basicProp->function = the_function;
	condition->basicProp->id = the_id;
	condition->basicProp->type = BASIC_PROP_TYPE_FUNCTION;
	return condition;
}

Condition * ConditionAndSemanticAction(Condition * the_left, Condition * the_right){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Condition * condition = calloc(1, sizeof(Condition));
	condition->type = CONDITION_TYPE_AND;
	condition->leftCondition = the_left;
	condition->leftCondition = the_right;
	return condition;
}

Condition * ConditionOrSemanticAction(Condition * the_left, Condition * the_right){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Condition * condition = calloc(1, sizeof(Condition));
	condition->type = CONDITION_TYPE_OR;
	condition->leftCondition = the_left;
	condition->leftCondition = the_right;
	return condition;
}

Condition * ConditionNotSemanticAction(Condition * the_condition){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Condition * condition = calloc(1, sizeof(Condition));
	condition->type = CONDITION_TYPE_NOT;
	condition->condition = the_condition;
	return condition;
}

Condition * ConditionParenthesisSemanticAction(Condition * the_condition){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Condition * condition = calloc(1, sizeof(Condition));
	condition->type = CONDITION_TYPE_SINGLE;
	condition->condition = the_condition;
	return condition;
}

Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * FactorExpressionSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

Factor * ConstantFactorSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->constant = constant;
	factor->type = CONSTANT;
	return factor;
}

Factor * ExpressionFactorSemanticAction(Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->expression = expression;
	factor->type = EXPRESSION;
	return factor;
}

Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->expression = expression;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else {
		compilerState->succeed = true;
	}
	return program;
}
