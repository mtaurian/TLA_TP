#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeAbstractSyntaxTreeModule() {
	_logger = createLogger("AbstractSyntxTree");
}

void shutdownAbstractSyntaxTreeModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PUBLIC FUNCTIONS */
void releaseQuestionSp(QuestionSp * questionSp){
	if (questionSp != NULL){
		free(questionSp->v_string);
		releaseListOptions(questionSp->options);
		free(questionSp);
	}
}

void releaseGlitchErrorFg(GlErrorFg * glErrorFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (glErrorFg != NULL){
		releaseShowIfCall(glErrorFg->showIfCall);
		releaseShowIfOnScope(glErrorFg->showIfOnScope);
		free(glErrorFg->message);
		free(glErrorFg);
	}	
}

void releaseGlitchFg(GlitchFg * glitchFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (glitchFg != NULL){
		releaseGlitchErrorFg(glitchFg->error);
		releaseGlitchFg(glitchFg->nextErrors);
		free(glitchFg);
	}
}

void releaseValue(Value * value){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (value != NULL){
		releaseDate(value->v_date);
		free(value->v_string);
		free(value);
	}
}

void releaseListOptions(ListOptions * options){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (options != NULL){
		releaseValue(options->value);
		releaseShowIfCall(options->showIfCall);
		releaseShowIfOnScope(options->showIfOnScope);
		releaseListOptions(options->nextOptions);
		free(options);
	}
}

void releaseQuestionSubFg(QuestionSubFg * questionSubFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(questionSubFg != NULL){
		releaseShowIfCall(questionSubFg->showIfCall);
		releaseShowIfDeclaration(questionSubFg->showIfDeclaration);
		releaseShowIfOnScope(questionSubFg->showIfOnScope);
		releaseGlitchFg(questionSubFg->glitchFg);
		releaseListOptions(questionSubFg->options);
		free(questionSubFg);
	}
}

void releaseQuestionFg(QuestionFg * questionFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (questionFg != NULL){
		releaseQuestionSubFg(questionFg->questionSubFg);
		releaseQuestionSp(questionFg->questionSp);
		releaseQuestionFg(questionFg->nextQuestionSubFgsOrSps);
		free(questionFg);
	}
}

void releaseQuestion(Question * question){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (question != NULL){
		releaseQuestionFg(question->questionFg);
		free(question->id);
		free(question);
	}
}

void releaseShowIfOnScope(ShowIfOnScope * showIfOnScope){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (showIfOnScope != NULL){
		releaseCondition(showIfOnScope->condition);
		free(showIfOnScope);
	} 
}

void releaseShowIfDeclaration(ShowIfDeclaration * showIfDeclaration){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (showIfDeclaration != NULL){
		releaseCondition(showIfDeclaration->condtion);
		free(showIfDeclaration->id);
		free(showIfDeclaration);
	}
}

void releaseShowIfCall(ShowIfCall * showIfCall){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (showIfCall != NULL){
		free(showIfCall->conditionId);
		free(showIfCall);
	}
}

void releaseSectionSubFg(SectionSubFg * sectionSubFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (sectionSubFg != NULL){
		releaseShowIfCall(sectionSubFg->showIfCall);
		releaseShowIfDeclaration(sectionSubFg->showIfDeclaration);
		releaseShowIfOnScope(sectionSubFg->showIfOnScope);
		releaseQuestion(sectionSubFg->question);
		free(sectionSubFg);
	}
}

void releaseSection(SectionFg * section){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (section != NULL){
		releaseSectionSubFg(section->sectionSubFg);
		releaseSectionSp(section->sectionSp);
		releaseSection(section->nextSectionSubFgsOrSps);
		free(section);
	}
}

void releaseDate(Date * date){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (date != NULL){
		free(date);
	}
}

void releaseLibFunction(LibFunction * libFunction){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (libFunction != NULL){
		releaseDate(libFunction->v_date);
		free(libFunction->v_string);
		free(libFunction->v_id);
		free(libFunction);
	}
}

void releaseBasicProp(BasicProp * basicProp){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (basicProp != NULL){
		releaseLibFunction(basicProp->function);
		free(basicProp->id);
		free(basicProp);
	}
}

void releaseCondition(Condition * condition){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (condition != NULL){
		releaseBasicProp(condition->basicProp);
		releaseCondition(condition->leftCondition);
		releaseCondition(condition->rightCondition);
		releaseCondition(condition->condition);
		free(condition);
	}
}

void releaseTransport(Transport * transport){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (transport != NULL){
		releaseCondition(transport->when);
		free(transport->stepId);
		free(transport);
	}
}

void releaseTransports(Transports * transports){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (transports != NULL){
		releaseTransport(transports->transport);
		releaseTransports(transports->nextTransports);
		free(transports);
	}
}

void releaseStepSp(StepSp * stepSp){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (stepSp != NULL){
		free(stepSp->string);
		free(stepSp);
	}
}

void releaseStepFg(StepFg * stepFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (stepFg != NULL){
		releaseTransports(stepFg->getaway);
		releaseQuestion(stepFg->question);
		releaseSection(stepFg->section);
		releaseStepSp(stepFg->stepSp);
		releaseStepFg(stepFg->nextStepFg);
		free(stepFg);
	}
}

void releaseStep(Step * step){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (step != NULL){
		free(step->id);
		releaseStepFg(step->stepFg);
		free(step);	
	}
}

void releaseConfigSp(FormConfigSp * configSp){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (configSp != NULL){
		free(configSp->submitText);
		free(configSp);
	}
}

void releaseConfig(FormConfigFg * config){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (config != NULL){
		releaseConfigSp(config->sp);
		releaseConfig(config->nextFgs);
		free(config);
	}
}

void releaseFormSp(FormSp * formSp){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (formSp != NULL){
		free(formSp->v_string);
		free(formSp);
	}	
}

void releaseFormSubFg(FormSubFg * formSubFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (formSubFg != NULL){
		releaseConfig(formSubFg->config);
		releaseQuestion(formSubFg->question);
		releaseSection(formSubFg->section);
		releaseStep(formSubFg->step);
		free(formSubFg);
	}	
}

void releaseFormFg(FormFg * formFg) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (formFg != NULL) {
		releaseFormSp(formFg->formSp);
		releaseFormSubFg(formFg->formSubFg);
		releaseFormFg(formFg->nextFormFgs);
		free(formFg);
	}
}


/*

void releaseConstant(Constant * constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant != NULL) {
		free(constant);
	}
}

void releaseExpression(Expression * expression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (expression != NULL) {
		switch (expression->type) {
			case ADDITION:
			case DIVISION:
			case MULTIPLICATION:
			case SUBTRACTION:
				releaseExpression(expression->leftExpression);
				releaseExpression(expression->rightExpression);
				break;
			case FACTOR:
				releaseFactor(expression->factor);
				break;
		}
		free(expression);
	}
}

void releaseFactor(Factor * factor) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (factor != NULL) {
		switch (factor->type) {
			case CONSTANT:
				releaseConstant(factor->constant);
				break;
			case EXPRESSION:
				releaseExpression(factor->expression);
				break;
		}
		free(factor);
	}
}

*/