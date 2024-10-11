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
Condition * ConditionBooleanSemanticAction(Boolean the_truthValue);
Condition * ConditionFunctionSemanticAction( char * the_id, LibFunction * the_function);
Condition * ConditionAndSemanticAction(Condition * the_left, Condition * the_right);
Condition * ConditionOrSemanticAction(Condition * the_left, Condition * the_right);
Condition * ConditionNotSemanticAction(Condition * the_condition);
Condition * ConditionParenthesisSemanticAction(Condition * the_condition);
ShowIfDeclaration * ShowIfDeclarationSemanticAction(char * the_id, Condition * the_condition);
ShowIfCall * ShowIfCallSemanticAction(char * the_conditionId);
ShowIfOnScope * ShowIfOnScopeSemanticAction(Condition * the_condition);

ListOptions * ListOptionsShowIfCallSemanticAction(Value * the_value,ShowIfCall * the_showIfCall);
ListOptions * ListOptionsShowIfOnScopeSemanticAction(Value * the_value,ShowIfOnScope * the_showIfOnScope);
ListOptions * ListOptionsSemanticAction(Value * the_value);
ListOptions * ListOptionsExtendedShowIfCallSemanticAction(Value * the_value,ShowIfCall * the_showIfCall,ListOptions* the_nextOptions);
ListOptions * ListOptionsExtendedShowIfOnScopeSemanticAction(Value * the_value,ShowIfOnScope * the_showIfOnScope, ListOptions * the_nextOptions);
ListOptions * ListOptionsExtendedSemanticAction(Value * the_value,ListOptions * the_nextOptions);

GlErrorFg * GlErrorFgShowIfCallSemanticAction(char * the_message, ShowIfCall * the_showIfCall);
GlErrorFg * GlErrorFgShowIfOnScopeSemanticAction(char * the_message, ShowIfOnScope * the_showIfOnScope);
GlitchFg * GlitchFgSemanticAction(GlErrorFg * the_error);
GlitchFg * GlitchFgExtendedSemanticAction(GlErrorFg * the_error, GlitchFg * the_nextErrors );

QuestionSubFg * QuestionSubFgShowIfCallSemanticAction(ShowIfCall * the_showIfCall);
QuestionSubFg * QuestionSubFgShowIfOnScopeSemanticAction(ShowIfOnScope * the_showIfOnScope);
QuestionSubFg * QuestionSubFgShowIfDeclarationSemanticAction(ShowIfDeclaration * the_showIfDeclaration);
QuestionSubFg * QuestionSubFgGlitchSemanticAction(GlitchFg * the_glitchFg);

QuestionSp * QuestionSpStringSemanticAction(QuestionSpType the_questionSpType, char * the_string);
QuestionSp * QuestionSpDefaultIntegerSemanticAction(int the_integer);
QuestionSp * QuestionSpDefaultFloatSemanticAction(float the_float);
QuestionSp * QuestionSpQuestionTypeSemanticAction(QuestionType the_questionType);
QuestionSp * QuestionSpOptionSemanticAction(ListOptions *the_options);
QuestionSp * QuestionSpRequiredSemanticAction();


QuestionFg * QuestionFgSubFgSemanticAction(QuestionSubFg * the_questionSubFg);
QuestionFg * QuestionFgSpSemanticAction(QuestionSp * the_questionSp);
QuestionFg * QuestionFgExtendedSubFgSemanticAction(QuestionSubFg * the_questionSubFg,QuestionFg * the_nextQuestionSubFgsOrSps);
QuestionFg * QuestionFgExtendedSpSemanticAction(QuestionSp * the_questionSp,QuestionFg * the_nextQuestionSubFgsOrSps);


Question * QuestionSemanticAction(char * the_id, QuestionFg * the_questionFg);

SectionSp * SectionSpSemanticAction(SectionSpType the_type, char * the_string);

SectionSubFg * SectionSubFgShowIfCallSemanticAction(ShowIfCall * the_showIfCall);
SectionSubFg * SectionSubFgShowIfOnScopeSemanticAction(ShowIfOnScope * the_showIfOnScope);
SectionSubFg * SectionSubFgShowIfDeclarationSemanticAction(ShowIfDeclaration * the_showIfDeclaration);
SectionSubFg * SectionSubFgQuestionSemanticAction(Question * the_question);

SectionFg * SectionFgSubFgSemanticAction(SectionSubFg * the_sectionSubFg);
SectionFg * SectionFgSpSemanticAction(SectionSp * the_sectionSp);
SectionFg * SectionFgExtendedSubFgSemanticAction(SectionSubFg * the_sectionSubFg, SectionFg * the_nextSectionSubFgsOrSps);
SectionFg * SectionFgExtendedSpSemanticAction(SectionSp * the_sectionSp, SectionFg * the_nextSectionSubFgsOrSps);


StepSp * StepSpSemanticAction(StepSpType the_type, char * the_string);

Transport * TransportSemanticAction(Condition * the_condition, char * the_stepId, Boolean is_GoesToEnd);

Transports * TransportsSemanticAction(Transport * the_transport);
Transports * TransportsExtendedSemanticAction(Transport * the_transport, Transports * the_nextTransports);

StepFg * StepFgStepSpSemanticAction(StepSp * the_stepSp);
StepFg * StepFgGetawaySemanticAction(Transports * the_getaway);
StepFg * StepFgSectionSemanticAction(SectionFg * the_section);
StepFg * StepFgQuestionSemanticAction(Question * the_question);

StepFg * StepFgStepSpExtendedSemanticAction(StepSp * the_stepSp,StepFg * the_nextStepFG);
StepFg * StepFgGetawayExtendedSemanticAction(Transports * the_getaway,StepFg * the_nextStepFG);
StepFg * StepFgSectionExtendedSemanticAction(SectionFg * the_section,StepFg * the_nextStepFG);
StepFg * StepFgQuestionExtendedSemanticAction(Question * the_question,StepFg * the_nextStepFG);

Step * StepSemanticAction(char * the_id,StepFg * the_stepFg);

FormConfigSp * FormConfigSpSubmitSemanticAction(char * the_submitText);
FormConfigSp * FormConfigSpThemeSemanticAction(ThemeSp the_theme);
FormConfigSp * FormConfigSpSafeAndSoundSemanticAction();

FormConfigFg * FormConfigFgSemanticAction(FormConfigSp * the_sp);
FormConfigFg * FormConfigFgExtendedSemanticAction(FormConfigSp * the_sp, FormConfigFg * the_nextFgs);

FormSp * FormSpSemanticAction(char * the_string, FormSpType the_type);

#endif
