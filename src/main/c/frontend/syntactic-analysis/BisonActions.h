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
Value * ValueDateSemanticAction( Date * the_date);
Date * CreateDateSemanticAction(int the_day, int the_month, int the_year);
LibFunction * LibFunctionIntegerSemanticAction(LibFunctionType the_libFunctionType,int the_param);
LibFunction * LibFunctionFloatSemanticAction(LibFunctionType the_libFunctionType,float the_param);
LibFunction * LibFunctionStringSemanticAction(LibFunctionType the_libFunctionType,char* the_param);
LibFunction * LibFunctionDateSemanticAction(LibFunctionType the_libFunctionType,Date* the_param);
LibFunction * LibFunctionIdSemanticAction(LibFunctionType the_libFunctionType,char * the_param);
LibFunction * LibFunctionNoneSemanticAction(LibFunctionType the_libFunctionType);
Condition * ConditionBooleanSemanticAction(Types the_type);
Condition * ConditionFunctionSemanticAction( char * the_id, LibFunction * the_function);
Condition * ConditionAndSemanticAction(Condition * the_left, Condition * the_right);
Condition * ConditionOrSemanticAction(Condition * the_left, Condition * the_right);
Condition * ConditionNotSemanticAction(Condition * the_condition);
Condition * ConditionParenthesisSemanticAction(Condition * the_condition);
ShowIfDeclaration * ShowIfDeclarationSemanticAction(char * the_id, Condition * the_condition);
ShowIfCall * ShowIfCallSemanticAction(char * the_conditionId);
ShowIfOnScope * ShowIfOnScopeSemanticAction(Condition * the_condition);
#endif
