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
		switch (questionSp->type){
			case QUESTION_SP_DEFAULT_STRING:
			case QUESTION_SP_TITLE:
			case QUESTION_SP_HELP:
			case QUESTION_SP_PLACE_HOLDER: free(questionSp->v_string);	break;
			case QUESTION_SP_OPTIONS: releaseListOptions(questionSp->options); break;
			default:break;
		}
		free(questionSp);
	}
}

void releaseGlitchErrorFg(GlErrorFg * glErrorFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (glErrorFg != NULL){
		switch (glErrorFg->showIfType){
			case SHOW_IF_CALL : releaseShowIfCall(glErrorFg->showIfCall);break;
			case SHOW_IF_ON_SCOPE :releaseShowIfOnScope(glErrorFg->showIfOnScope);break;
			default:break;
		}
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
		switch (value->type){
			case TYPE_STRING : free(value->v_string);break;
			case TYPE_DATE : releaseDate(value->v_date); break;		
			default:break;
		}
		free(value);
	}
}

void releaseListOptions(ListOptions * options){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (options != NULL){
		switch (options->hasShowIf){
			case CALL : releaseShowIfCall(options->showIfCall); break;
			case SCOPE : releaseShowIfOnScope(options->showIfOnScope);break;		
			default:break;
		}
		releaseValue(options->value);
		releaseListOptions(options->nextOptions);
		free(options);
	}
}

void releaseQuestionSubFg(QuestionSubFg * questionSubFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(questionSubFg != NULL){
		switch (questionSubFg->type){
			case QUESTION_SUB_FG_SHOW_IF_CALL : releaseShowIfCall(questionSubFg->showIfCall);break;
			case QUESTION_SUB_FG_SHOW_IF_ON_SCOPE : releaseShowIfOnScope(questionSubFg->showIfOnScope);break;
			case QUESTION_SUB_FG_SHOW_IF_DECLARATION : releaseShowIfDeclaration(questionSubFg->showIfDeclaration);break;
			case QUESTION_SUB_FG_GLITCH : releaseGlitchFg(questionSubFg->glitchFg);break;
			default:break;
		}
		free(questionSubFg);
	}
}

void releaseQuestionFg(QuestionFg * questionFg){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (questionFg != NULL){
		switch(questionFg->type){
			case QUESTION_FG_SUB_FG : releaseQuestionSubFg(questionFg->questionSubFg);break;
			case QUESTION_FG_SP : releaseQuestionSp(questionFg->questionSp);break;
			default:break;
		}
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
		switch (sectionSubFg->type){
			case SECTION_SUB_FG_SHOW_IF_CALL: releaseShowIfCall(sectionSubFg->showIfCall);break;
			case SECTION_SUB_FG_SHOW_IF_ON_SCOPE : releaseShowIfOnScope(sectionSubFg->showIfOnScope);break;
			case SECTION_SUB_FG_SHOW_IF_DECLARATION : releaseShowIfDeclaration(sectionSubFg->showIfDeclaration);break;
			case SECTION_SUB_FG_QUESTION : releaseQuestion(sectionSubFg->question);break;
			default: break;
		}
		free(sectionSubFg);
	}
}

void releaseSectionSp(SectionSp * sectionSp){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (sectionSp != NULL){
		free(sectionSp->string);
		free(sectionSp);
	}
}

void releaseSection(SectionFg * section){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (section != NULL){
		switch (section->type){
			case SECTION_FG_SUB_FG : releaseSectionSubFg(section->sectionSubFg);break;
			case SECTION_FG_SP : releaseSectionSp(section->sectionSp); break;
			default:break;
		}
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
		switch (libFunction->parameterType){
			case TYPE_STRING: free(libFunction->v_string);break;
			case TYPE_ID: free(libFunction->v_id);break;
			case TYPE_DATE: releaseDate(libFunction->v_date);break;
			default:break;
		}
		free(libFunction);
	}
}

void releaseBasicProp(BasicProp * basicProp){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (basicProp != NULL){
		switch (basicProp->type){
			case BASIC_PROP_TYPE_BOOLEAN:break;
			case BASIC_PROP_TYPE_FUNCTION:releaseLibFunction(basicProp->function); free(basicProp->id);break;
			default:break;
		}
		free(basicProp);
	}
}

void releaseCondition(Condition * condition){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (condition != NULL){
		switch (condition->type){
		case CONDITION_TYPE_BASIC: releaseBasicProp(condition->basicProp); break;
		case CONDITION_TYPE_NOT : case CONDITION_TYPE_SINGLE : releaseCondition(condition->condition);break;
		case CONDITION_TYPE_AND : case CONDITION_TYPE_OR : releaseCondition(condition->leftCondition); releaseCondition(condition->rightCondition);break;
		default:break;
		}
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
		switch(stepFg->type){
			case STEP_FG_GETAWAY	: releaseTransports(stepFg->getaway); break;
			case STEP_FG_QUESTION	: releaseQuestion(stepFg->question); break;
			case STEP_FG_SECTION	: releaseSection(stepFg->section); break;
			case STEP_FG_STEP_SP	: releaseStepSp(stepFg->stepSp); break;
		}
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
		if( configSp->type==FORM_CONFIG_SP_SUBMIT){
            free(configSp->submitText);
        }
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
		switch(formSubFg->type){
			case FORM_SUB_FG_CONFIG   	: releaseConfig(formSubFg->config); break;
			case FORM_SUB_FG_QUESTION 	: releaseQuestion(formSubFg->question); break;
			case FORM_SUB_FG_SECTION  	: releaseSection(formSubFg->section); break;
			case FORM_SUB_FG_STEP 		: releaseStep(formSubFg->step); break;
		}
		free(formSubFg);
	}	
}

void releaseFormFg(FormFg * formFg) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (formFg != NULL) {
		switch(formFg->type){
			case FORM_FG_SP : releaseFormSp(formFg->formSp); break;
			case FORM_FG_SUB_FG : releaseFormSubFg(formFg->formSubFg); break;
		}
		releaseFormFg(formFg->nextFormFgs);
		free(formFg);
	}
}
