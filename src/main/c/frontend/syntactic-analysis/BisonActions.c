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
	value->type = VALUE_TYPE_STRING;
	return value;
}

Value * ValueIntegerSemanticAction(int the_integer){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Value * value = calloc(1, sizeof(Value));
	value->v_integer = the_integer;
	value->type = VALUE_TYPE_INTEGER;
	return value;
}

Value * ValueFloatSemanticAction(float the_float){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Value * value = calloc(1, sizeof(Value));
	value->v_float = the_float;
	value->type = VALUE_TYPE_FLOAT;
	return value;
}

Value * ValueDateSemanticAction( Date * the_date){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Value * value = calloc(1, sizeof(Value));
	value->v_date = the_date;
	value->type = VALUE_TYPE_DATE;
	return value;
}

ValueOrId * ValueOrIdValueSemanticAction(Value * the_value){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		ValueOrId * valueOrId = calloc(1,sizeof(ValueOrId));
		valueOrId->value=the_value;
		valueOrId->type=VALUE_OR_ID_TYPE_VALUE;
		return valueOrId;
}

ValueOrId * ValueOrIdIdSemanticAction(char * the_id){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		ValueOrId * valueOrId = calloc(1,sizeof(ValueOrId));
		valueOrId->id=the_id;
		valueOrId->type=VALUE_OR_ID_TYPE_ID;
		return valueOrId;
}
DateOrId * DateOrIdIdSemanticAction(char * the_id){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		DateOrId * dateOrId = calloc(1,sizeof(DateOrId));
		dateOrId->id=the_id;
		dateOrId->type=DATE_OR_ID_TYPE_ID;
		return dateOrId;
}
DateOrId * DateOrIdDateSemanticAction(Date * the_date){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		DateOrId * dateOrId = calloc(1,sizeof(DateOrId));
		dateOrId->date=the_date;
		dateOrId->type=DATE_OR_ID_TYPE_DATE;
		return dateOrId;
}

IntegerOrId * IntegerOrIdIdSemanticAction(char * the_id){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		IntegerOrId * integerOrId = calloc(1,sizeof(IntegerOrId));
		integerOrId->v_id=the_id;
		integerOrId->type=INTEGER_OR_ID_TYPE_ID;
		return integerOrId;
}
IntegerOrId * IntegerOrIdIntegerSemanticAction(int the_integer){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		IntegerOrId * integerOrId = calloc(1,sizeof(IntegerOrId));
		integerOrId->v_integer=the_integer;
		integerOrId->type=INTEGER_OR_ID_TYPE_INTEGER;
		return integerOrId;
}


StringOrId * StringOrIdStringSemanticAction(char * the_string){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StringOrId * stringOrId = calloc(1,sizeof(StringOrId));
		stringOrId->string=the_string;
		stringOrId->type=STRING_OR_ID_TYPE_STRING;
		return stringOrId;
}
StringOrId * StringOrIdIdSemanticAction(char * the_id){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StringOrId * stringOrId = calloc(1,sizeof(StringOrId));
		stringOrId->id=the_id;
		stringOrId->type=STRING_OR_ID_TYPE_ID;
		return stringOrId;
}

Number * NumberIntegerSemanticAction(int the_integer){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		Number * number= calloc(1,sizeof(Number));
		number->v_integer=the_integer;
		number->type=NUMBER_TYPE_INTEGER;
		return number;
}
Number * NumberFloatSemanticAction(float the_float){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		Number * number= calloc(1,sizeof(Number));
		number->v_float=the_float;
		number->type=NUMBER_TYPE_FLOAT;
		return number;
}
NumberOrId * NumberOrIdNumberSemanticAction(Number * the_number){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		NumberOrId * numberOrId= calloc(1,sizeof(NumberOrId));
		numberOrId->number=the_number;
		numberOrId->type=NUMBER_OR_ID_TYPE_NUMBER;
		return numberOrId;
}
NumberOrId * NumberOrIdIdSemanticAction(char * the_id){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		_logSyntacticAnalyzerAction(__FUNCTION__);
		NumberOrId * numberOrId= calloc(1,sizeof(NumberOrId));
		numberOrId->id=the_id;
		numberOrId->type=NUMBER_OR_ID_TYPE_ID;
		return numberOrId;
}

Date * CreateDateSemanticAction(int the_day, int the_month, int the_year){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Date * date = calloc(1, sizeof(Date));
	date->day =  the_day;
	date->month = the_month;
	date->year = the_year;
	return date;
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
