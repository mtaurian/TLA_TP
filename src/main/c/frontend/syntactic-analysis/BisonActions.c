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


Condition * ConditionBooleanSemanticAction(Boolean the_truthValue){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Condition * condition = calloc(1, sizeof(Condition));
	condition->type = CONDITION_TYPE_BASIC;
	condition->basicProp = calloc(1, sizeof(BasicProp));
	condition->basicProp->truthValue = the_truthValue ;
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

ShowIfDeclaration * ShowIfDeclarationSemanticAction(char * the_id, Condition * the_condition){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ShowIfDeclaration * showIfDeclaration = calloc(1, sizeof(ShowIfDeclaration));
	showIfDeclaration->id = the_id;
	showIfDeclaration->condtion = the_condition;
	return showIfDeclaration;
}

ShowIfCall * ShowIfCallSemanticAction(char * the_conditionId){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ShowIfCall * showIfCall = calloc(1, sizeof(ShowIfCall));
	showIfCall->conditionId = the_conditionId;
	return showIfCall;
}

ShowIfOnScope * ShowIfOnScopeSemanticAction(Condition * the_condition){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ShowIfOnScope * ShowIfOnScope = calloc(1, sizeof(ShowIfOnScope));
	ShowIfOnScope->condition = the_condition;
	return ShowIfOnScope;
}


ListOptions * ListOptionsShowIfCallSemanticAction(Value * the_value,ShowIfCall * the_showIfCall){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ListOptions * listOptions = calloc(1,sizeof(ListOptions));
	listOptions->value=the_value;
	listOptions->showIfCall=the_showIfCall;
	listOptions->hasShowIf=CALL;
	return listOptions;

}
ListOptions * ListOptionsShowIfOnScopeSemanticAction(Value * the_value,ShowIfOnScope * the_showIfOnScope){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ListOptions * listOptions = calloc(1,sizeof(ListOptions));
	listOptions->value=the_value;
	listOptions->showIfOnScope=the_showIfOnScope;
	listOptions->hasShowIf=SCOPE;
	return listOptions;
}
ListOptions * ListOptionsSemanticAction(Value * the_value){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ListOptions * listOptions = calloc(1,sizeof(ListOptions));
	listOptions->value=the_value;
	listOptions->hasShowIf=NONE;
	return listOptions;
}

ListOptions * ListOptionsExtendedShowIfCallSemanticAction(Value * the_value,ShowIfCall * the_showIfCall,ListOptions* the_nextOptions){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ListOptions * listOptions = calloc(1,sizeof(ListOptions));
	listOptions->value=the_value;
	listOptions->showIfCall=the_showIfCall;
	listOptions->nextOptions=the_nextOptions;
	listOptions->hasShowIf=CALL;
	return listOptions;
}
ListOptions * ListOptionsExtendedShowIfOnScopeSemanticAction(Value * the_value,ShowIfOnScope * the_showIfOnScope, ListOptions * the_nextOptions){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ListOptions * listOptions = calloc(1,sizeof(ListOptions));
	listOptions->value=the_value;
	listOptions->showIfOnScope=the_showIfOnScope;
	listOptions->nextOptions=the_nextOptions;
	listOptions->hasShowIf=SCOPE;
	return listOptions;
}
ListOptions * ListOptionsExtendedSemanticAction(Value * the_value,ListOptions * the_nextOptions){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ListOptions * listOptions = calloc(1,sizeof(ListOptions));
	listOptions->value=the_value;
	listOptions->nextOptions=the_nextOptions;
	listOptions->hasShowIf=NONE;
	return listOptions;
}

GlErrorFg * GlErrorFgShowIfCallSemanticAction(char * the_message, ShowIfCall * the_showIfCall){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GlErrorFg * glErrorFg = calloc(1, sizeof(GlErrorFg));
	glErrorFg->message = the_message;
	glErrorFg->showIfCall = the_showIfCall;
	return glErrorFg;
}

GlErrorFg * GlErrorFgShowIfOnScopeSemanticAction(char * the_message, ShowIfOnScope * the_showIfOnScope){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GlErrorFg * glErrorFg = calloc(1, sizeof(GlErrorFg));
	glErrorFg->message = the_message;
	glErrorFg->showIfOnScope = the_showIfOnScope;
	return glErrorFg;
}

GlitchFg * GlitchFgSemanticAction(GlErrorFg * the_error){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GlitchFg * glitchFg = calloc(1, sizeof(GlitchFg));
	glitchFg->error = the_error;

	return glitchFg;
}
GlitchFg * GlitchFgExtendedSemanticAction(GlErrorFg * the_error, GlitchFg * the_nextErrors ){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GlitchFg * glitchFg = calloc(1, sizeof(GlitchFg));
	glitchFg->error = the_error;
	glitchFg->nextErrors = the_nextErrors;
	return glitchFg;
}


QuestionSubFg * QuestionSubFgShowIfCallSemanticAction(ShowIfCall * the_showIfCall){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSubFg * questionSubFg=calloc(1,sizeof(QuestionSubFg));
	questionSubFg->showIfCall=the_showIfCall;
	questionSubFg->type=QUESTION_SUB_FG_SHOW_IF_CALL;
	return questionSubFg;
}
QuestionSubFg * QuestionSubFgShowIfOnScopeSemanticAction(ShowIfOnScope * the_showIfOnScope){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSubFg * questionSubFg=calloc(1,sizeof(QuestionSubFg));
	questionSubFg->showIfOnScope=the_showIfOnScope;
	questionSubFg->type=QUESTION_SUB_FG_SHOW_IF_ON_SCOPE;
	return questionSubFg;
}
QuestionSubFg * QuestionSubFgShowIfDeclarationSemanticAction(ShowIfDeclaration * the_showIfDeclaration){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSubFg * questionSubFg=calloc(1,sizeof(QuestionSubFg));
	questionSubFg->showIfDeclaration=the_showIfDeclaration;
	questionSubFg->type=QUESTION_SUB_FG_SHOW_IF_DECLARATION;
	return questionSubFg;
}
QuestionSubFg * QuestionSubFgGlitchSemanticAction(GlitchFg * the_glitchFg){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSubFg * questionSubFg=calloc(1,sizeof(QuestionSubFg));
	questionSubFg->glitchFg=the_glitchFg;
	questionSubFg->type=QUESTION_SUB_FG_GLITCH;
	return questionSubFg;
}


QuestionSp * QuestionSpStringSemanticAction(QuestionSpType the_questionSpType, char * the_string){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSp * questionSp=calloc(1,sizeof(QuestionSp));
	questionSp->type=the_questionSpType;
	questionSp->v_string=the_string;
	return questionSp;

}
QuestionSp * QuestionSpDefaultIntegerSemanticAction(int the_integer){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSp * questionSp=calloc(1,sizeof(QuestionSp));
	questionSp->type=QUESTION_SP_DEFAULT_INTEGER;
	questionSp->v_integer=the_integer;
	return questionSp;
}
QuestionSp * QuestionSpDefaultFloatSemanticAction(float the_float){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSp * questionSp=calloc(1,sizeof(QuestionSp));
	questionSp->type=QUESTION_SP_DEFAULT_FLOAT;
	questionSp->v_float=the_float;
	return questionSp;
}
QuestionSp * QuestionSpQuestionTypeSemanticAction(QuestionType the_questionType){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSp * questionSp=calloc(1,sizeof(QuestionSp));
	questionSp->type=QUESTION_SP_QUESTION_TYPE;
	questionSp->questionType=the_questionType;
	return questionSp;
}
QuestionSp * QuestionSpOptionSemanticAction(ListOptions *the_options){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSp * questionSp=calloc(1,sizeof(QuestionSp));
	questionSp->type=QUESTION_SP_OPTIONS;
	questionSp->options=the_options;
	return questionSp;
}
QuestionSp * QuestionSpRequiredSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionSp * questionSp=calloc(1,sizeof(QuestionSp));
	questionSp->type=QUESTION_SP_REQUIRED;
	return questionSp;
}

QuestionFg * QuestionFgSubFgSemanticAction(QuestionSubFg * the_questionSubFg){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionFg * questionFg=calloc(1,sizeof(QuestionFg));
	questionFg->questionSubFg=the_questionSubFg;
	questionFg->type=QUESTION_FG_SUB_FG;
	return questionFg;
}
QuestionFg * QuestionFgSpSemanticAction(QuestionSp * the_questionSp){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionFg * questionFg=calloc(1,sizeof(QuestionFg));
	questionFg->questionSp=the_questionSp;
	questionFg->type=QUESTION_FG_SP;
	return questionFg;
}
QuestionFg * QuestionFgExtendedSubFgSemanticAction(QuestionSubFg * the_questionSubFg,QuestionFg * the_nextQuestionSubFgsOrSps){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionFg * questionFg=calloc(1,sizeof(QuestionFg));
	questionFg->questionSubFg=the_questionSubFg;
	questionFg->nextQuestionSubFgsOrSps=the_nextQuestionSubFgsOrSps;
	questionFg->type=QUESTION_FG_SUB_FG;
	return questionFg;
}
QuestionFg * QuestionFgExtendedSpSemanticAction(QuestionSp * the_questionSp,QuestionFg * the_nextQuestionSubFgsOrSps){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	QuestionFg * questionFg=calloc(1,sizeof(QuestionFg));
	questionFg->questionSp=the_questionSp;
	questionFg->nextQuestionSubFgsOrSps=the_nextQuestionSubFgsOrSps;
	questionFg->type=QUESTION_FG_SP;
	return questionFg;
}


Question * QuestionSemanticAction(char * the_id, QuestionFg * the_questionFg){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Question * question=calloc(1,sizeof(Question));
	question->id-the_id;
	question->questionFg=the_questionFg;
	return question;
}

SectionSp * SectionSpSemanticAction(SectionSpType the_type, char * the_string){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SectionSp * sectionSp = calloc(1, sizeof(SectionSp));
	sectionSp->string = the_string;
	sectionSp->type = the_type;
	return sectionSp;
}

SectionSubFg * SectionSubFgShowIfCallSemanticAction(ShowIfCall * the_showIfCall){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SectionSubFg * sectionSubFg=calloc(1,sizeof(SectionSubFg));
	sectionSubFg->showIfCall=the_showIfCall;
	sectionSubFg->type=SECTION_SUB_FG_SHOW_IF_CALL;
	return sectionSubFg;
}

SectionSubFg * SectionSubFgShowIfOnScopeSemanticAction(ShowIfOnScope * the_showIfOnScope){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SectionSubFg * sectionSubFg=calloc(1,sizeof(SectionSubFg));
	sectionSubFg->showIfOnScope=the_showIfOnScope;
	sectionSubFg->type=SECTION_SUB_FG_SHOW_IF_ON_SCOPE;
	return sectionSubFg;
}

SectionSubFg * SectionSubFgShowIfDeclarationSemanticAction(ShowIfDeclaration * the_showIfDeclaration){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SectionSubFg * sectionSubFg=calloc(1,sizeof(SectionSubFg));
	sectionSubFg->showIfDeclaration=the_showIfDeclaration;
	sectionSubFg->type=SECTION_SUB_FG_SHOW_IF_DECLARATION;
	return sectionSubFg;
}

SectionSubFg * SectionSubFgQuestionSemanticAction(Question * the_question){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SectionSubFg * sectionSubFg=calloc(1,sizeof(SectionSubFg));
	sectionSubFg->question=the_question;
	sectionSubFg->type=SECTION_SUB_FG_QUESTION;
	return sectionSubFg;
}

SectionFg * SectionFgSubFgSemanticAction(SectionSubFg * the_sectionSubFg){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SectionFg * sectionFg=calloc(1,sizeof(SectionFg));
	sectionFg->sectionSubFg=the_sectionSubFg;
	sectionFg->type=SECTION_FG_SUB_FG;
	return sectionFg;
}

SectionFg * SectionFgSpSemanticAction(SectionSp * the_sectionSp){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SectionFg * sectionFg=calloc(1,sizeof(SectionFg));
	sectionFg->sectionSp=the_sectionSp;
	sectionFg->type=SECTION_FG_SP;
	return sectionFg;
}

SectionFg * SectionFgExtendedSubFgSemanticAction(SectionSubFg * the_sectionSubFg, SectionFg * the_nextSectionSubFgsOrSps){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SectionFg * sectionFg=calloc(1,sizeof(SectionFg));
	sectionFg->sectionSubFg=the_sectionSubFg;
	sectionFg->nextSectionSubFgsOrSps=the_nextSectionSubFgsOrSps;
	sectionFg->type=SECTION_FG_SUB_FG;
	return sectionFg;
}

SectionFg * SectionFgExtendedSpSemanticAction(SectionSp * the_sectionSp, SectionFg * the_nextSectionSubFgsOrSps){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SectionFg * sectionFg=calloc(1,sizeof(SectionFg));
	sectionFg->sectionSp=the_sectionSp;
	sectionFg->nextSectionSubFgsOrSps=the_nextSectionSubFgsOrSps;
	sectionFg->type=SECTION_FG_SP;
	return sectionFg;
}

StepSp * StepSpSemanticAction(StepSpType the_type, char * the_string){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StepSp * stepSp = calloc(1, sizeof(StepSp));
	stepSp->string = the_string;
	stepSp->type = the_type;
	return stepSp;
}

Transport * TransportSemanticAction(Condition * the_condition, char * the_stepId, Boolean is_GoesToEnd){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Transport * transport = calloc(1, sizeof(Transport));
	transport->when = the_condition;
	transport->stepId = the_stepId;
	transport->goesToEnd = is_GoesToEnd;
	return transport;
}

Transports * TransportsSemanticAction(Transport * the_transport){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Transports * transports = calloc(1, sizeof(Transports));
	transports->transport = the_transport;
	return transports;
}

Transports * TransportsExtendedSemanticAction(Transport * the_transport, Transports * the_nextTransports){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Transports * transports = calloc(1, sizeof(Transports));
	transports->transport = the_transport;
	transports->nextTransports = the_nextTransports;
	return transports;
}

StepFg * StepFgStepSpSemanticAction(StepSp * the_stepSp){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StepFg * stepFg=calloc(1,sizeof(StepFg));
		stepFg->stepSp=the_stepSp;
		stepFg->type=STEP_FG_STEP_SP;
		return stepFg;
}
StepFg * StepFgGetawaySemanticAction(Transports * the_getaway){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StepFg * stepFg=calloc(1,sizeof(StepFg));
		stepFg->getaway=the_getaway;
		stepFg->type=STEP_FG_GETAWAY;
		return stepFg;
}
StepFg * StepFgSectionSemanticAction(SectionFg * the_section){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StepFg * stepFg=calloc(1,sizeof(StepFg));
		stepFg->section=the_section;
		stepFg->type=STEP_FG_SECTION;
		return stepFg;
}
StepFg * StepFgQuestionSemanticAction(Question * the_question){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StepFg * stepFg=calloc(1,sizeof(StepFg));
		stepFg->question=the_question;
		stepFg->type=STEP_FG_QUESTION;
		return stepFg;
}

StepFg * StepFgStepSpExtendedSemanticAction(StepSp * the_stepSp,StepFg * the_nextStepFG){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StepFg * stepFg=calloc(1,sizeof(StepFg));
		stepFg->stepSp=the_stepSp;
		stepFg->type=STEP_FG_STEP_SP;
		stepFg->nextStepFg=the_nextStepFG;
		return stepFg;
}
StepFg * StepFgGetawayExtendedSemanticAction(Transports * the_getaway,StepFg * the_nextStepFG){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StepFg * stepFg=calloc(1,sizeof(StepFg));
		stepFg->getaway=the_getaway;
		stepFg->type=STEP_FG_GETAWAY;
		return stepFg;
}
StepFg * StepFgSectionExtendedSemanticAction(SectionFg * the_section,StepFg * the_nextStepFG){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StepFg * stepFg=calloc(1,sizeof(StepFg));
		stepFg->section=the_section;
		stepFg->type=STEP_FG_SECTION;
		stepFg->nextStepFg=the_nextStepFG;
		return stepFg;
}
StepFg * StepFgQuestionExtendedSemanticAction(Question * the_question,StepFg * the_nextStepFG){
		_logSyntacticAnalyzerAction(__FUNCTION__);
		StepFg * stepFg=calloc(1,sizeof(StepFg));
		stepFg->question=the_question;
		stepFg->type=STEP_FG_QUESTION;
		stepFg->nextStepFg=the_nextStepFG;
		return stepFg;
}



Step * StepSemanticAction(char * the_id, StepFg * the_stepFg){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Step * step=calloc(1,sizeof(Step));
	step->id-the_id;
	step->stepFg=the_stepFg;
	return step;
}

FormConfigSp * FormConfigSpSubmitSemanticAction(char * the_submitText){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormConfigSp * formConfigSp = calloc(1, sizeof(FormConfigSp));
	formConfigSp->submitText = the_submitText;
	formConfigSp->type = FORM_CONFIG_SP_SUBMIT;
	return formConfigSp;
}

FormConfigSp * FormConfigSpThemeSemanticAction(ThemeSp the_theme){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormConfigSp * formConfigSp = calloc(1, sizeof(FormConfigSp));
	formConfigSp->theme = the_theme;
	formConfigSp->type = FORM_CONFIG_SP_THEME;
	return formConfigSp;
}

FormConfigSp * FormConfigSpSafeAndSoundSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormConfigSp * formConfigSp = calloc(1, sizeof(FormConfigSp));
	formConfigSp->type = FORM_CONFIG_SP_SAFE_AND_SOUND;
	return formConfigSp;
}

FormConfigFg * FormConfigFgSemanticAction(FormConfigSp * the_sp){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormConfigFg * formConfigFg = calloc(1, sizeof(FormConfigFg));
	formConfigFg->sp = the_sp;
	return formConfigFg;
}

FormConfigFg * FormConfigFgExtendedSemanticAction(FormConfigSp * the_sp, FormConfigFg * the_nextFgs){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormConfigFg * formConfigFg = calloc(1, sizeof(FormConfigFg));
	formConfigFg->sp = the_sp;
	formConfigFg->nextFgs = the_nextFgs;
	return formConfigFg;
}

FormSp * FormSpSemanticAction(char * the_string, FormSpType the_type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormSp * formSp = calloc(1, sizeof(FormSp));
	formSp->v_string = the_string;
	formSp->type = the_type;
	return formSp;
}

FormSubFg * FormSubFgConfigSemanticAction(FormConfigFg * the_config){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormSubFg * formSubFg=calloc(1,sizeof(FormSubFg));
	formSubFg->config=the_config;
	formSubFg->type=FORM_SUB_FG_CONFIG;
	return formSubFg;
}
FormSubFg * FormSubFgStepSemanticAction(Step * the_step){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormSubFg * formSubFg=calloc(1,sizeof(FormSubFg));
	formSubFg->step=the_step;
	formSubFg->type=FORM_SUB_FG_STEP;
	return formSubFg;
}
FormSubFg * FormSubFgQuestionSemanticAction(Question * the_question){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormSubFg * formSubFg=calloc(1,sizeof(FormSubFg));
	formSubFg->question=the_question;
	formSubFg->type=FORM_SUB_FG_QUESTION;
	return formSubFg;
}
FormSubFg * FormSubFgSectionSemanticAction(SectionFg * the_section){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormSubFg * formSubFg=calloc(1,sizeof(FormSubFg));
	formSubFg->section=the_section;
	formSubFg->type=FORM_SUB_FG_SECTION;
	return formSubFg;
}


FormFg * FormFgSubFgSemanticAction(FormSubFg * the_formSubFg,CompilerState * compilerState){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormFg * formFg=calloc(1,sizeof(FormFg));
	formFg->formSubFg=the_formSubFg;
	formFg->type=FORM_FG_SUB_FG;
	compilerState->abstractSyntaxtTree = formFg;
    if (0 < flexCurrentContext()) {
        logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
        compilerState->succeed = false;
    }
    else {
        compilerState->succeed = true;
    }
	return formFg;
}
FormFg * FormFgSpSemanticAction(FormSp * the_formSp,CompilerState * compilerState){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormFg * formFg=calloc(1,sizeof(FormFg));
	formFg->formSp=the_formSp;
	formFg->type=FORM_FG_SP;
	compilerState->abstractSyntaxtTree = formFg;
    if (0 < flexCurrentContext()) {
        logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
        compilerState->succeed = false;
    }
    else {
        compilerState->succeed = true;
    }
	return formFg;
}
FormFg * FormFgExtendedSubFgSemanticAction(FormSubFg * the_formSubFg,FormFg * the_nextFormFgs,CompilerState * compilerState){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormFg * formFg=calloc(1,sizeof(FormFg));
	formFg->formSubFg=the_formSubFg;
	formFg->type=FORM_FG_SUB_FG;
	formFg->nextFormFgs=the_nextFormFgs;
	compilerState->abstractSyntaxtTree = formFg;
    if (0 < flexCurrentContext()) {
        logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
        compilerState->succeed = false;
    }
    else {
        compilerState->succeed = true;
    }
	return formFg;
}
FormFg * FormFgExtendedSpSemanticAction(FormSp * the_formSp,FormFg * the_nextFormFgs,CompilerState * compilerState){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FormFg * formFg=calloc(1,sizeof(FormFg));
	formFg->formSp=the_formSp;
	formFg->type=FORM_FG_SP;
	formFg->nextFormFgs=the_nextFormFgs;
	compilerState->abstractSyntaxtTree = formFg;
    if (0 < flexCurrentContext()) {
        logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
        compilerState->succeed = false;
    }
    else {
        compilerState->succeed = true;
    }
	return formFg;
}