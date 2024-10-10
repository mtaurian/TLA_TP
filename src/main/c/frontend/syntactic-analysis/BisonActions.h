#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

Constant * IntegerConstantSemanticAction(const int value);
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression);
Value * ValueStringSemanticAction(char * the_string);
Value * ValueIntegerSemanticAction(int the_integer);
Value * ValueFloatSemanticAction(float the_float);
Date * CreateDateSemanticAction(int the_day, int the_month, int the_year);
Value * ValueDateSemanticAction( Date * the_date);
ValueOrId * ValueOrIdValueSemanticAction(Value * the_value);
ValueOrId * ValueOrIdIdSemanticAction(char * the_id);
DateOrId * DateOrIdIdSemanticAction(char * the_id);
DateOrId * DateOrIdDateSemanticAction(Date * the_date);
IntegerOrId * IntegerOrIdIdSemanticAction(char * the_id);
IntegerOrId * IntegerOrIdIntegerSemanticAction(int the_integer);
#endif
