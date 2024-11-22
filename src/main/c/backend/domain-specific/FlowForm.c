#include "FlowForm.h"


static Logger * _logger = NULL;

void initializeFlowFormModule() {
    _logger = createLogger("FlowForm");
}

static boolean _invalidComputation(char * msg) {
    logError(_logger, msg);
    return false;
};
static boolean _unnecessaryComputation(){
	return true;
};



boolean computeFormFg(const FormFg * form, CompilerState * cs, FormFlags * flags) {
    if(form==NULL) return _unnecessaryComputation();
    const boolean retRec=computeFormFg(form->nextFormFgs,cs, flags);
	boolean ret=true;
    if(form->type==FORM_FG_SUB_FG){
        ret=computeFormSubFg(form->formSubFg,cs, flags);
    } else if (form->type==FORM_FG_SP) {
        ret = computeFormSp(form->formSp, cs);
    } else {
        ret = _invalidComputation("Invalid state on Form");
    }
    return ret && retRec;
}

boolean computeFormSubFg(const FormSubFg *formSubFg, CompilerState * cs, FormFlags * flags) {
    logDebugging(_logger, __FUNCTION__ );

    boolean ret = true;

	switch (formSubFg->type) {
		case FORM_SUB_FG_CONFIG:
            if(flags->formConfigDone){
                ret = _invalidComputation("Redeclaration of @FormConfig encountered");
            } else {
                flags->formConfigDone=true;
                FormConfigFlags  configFlags = {.themeDone=false, .safeAndSoundDone=false};
                ret = computeFormConfigFg(formSubFg->config,cs, &configFlags);

                if(ret) logInformation(_logger, "Form Configuration set");
            }
            break;
		case FORM_SUB_FG_STEP:
            if (flags->state == FORM_ONLY_SECTIONS || flags->state == FORM_ONLY_QUESTIONS){
                ret = _invalidComputation("Wrong hierarchy of Form elements. Steps where found at same level as Sections or Questions");
            } else {
                if (flags->state == FORM_NOT_DEFINED) flags->state = FORM_ONLY_STEPS;

                hashmap_set(cs->tableSymbols, &(struct EntrySymbols){.entrySymbolsType=ENTRY_SYMBOLS_STEP, .id = formSubFg->step->id, .index = cs->tableSteps->size});
                addRow(cs->tableSteps, &(struct TableSteps){.description = NULL, .title = NULL});
                StepFlags stepFlags = {.state = STEP_NOT_DEFINED, .getawayDone = false};
                pushStringStack(cs->contextStack, formSubFg->step->id);
                ret = computeStep(formSubFg->step, cs, &stepFlags);
                popStringStack(cs->contextStack);
            }
            break;
		case FORM_SUB_FG_QUESTION:
            if (flags->state == FORM_ONLY_STEPS || flags->state == FORM_ONLY_SECTIONS){
                ret = _invalidComputation("Wrong hierarchy of Form elements. Questions where found at same level as Steps or Sections");
            } else {
                if (flags->state == FORM_NOT_DEFINED) flags->state = FORM_ONLY_QUESTIONS;

                if (hashmap_get(cs->tableSymbols, &(struct EntrySymbols) {.id = formSubFg->question->id})) {
                    ret = false;
                    logError(_logger, "Redeclaration of identifier: %s", formSubFg->question->id);
                }
                hashmap_set(cs->tableSymbols,
                            &(struct EntrySymbols) {.entrySymbolsType=ENTRY_SYMBOLS_QUESTION, .id = formSubFg->question->id, .index = cs->tableQuestions->size});
                addRow(cs->tableQuestions, &(struct TableQuestions) {.stepId = 0, .sectionId = 0});
                QuestionFlags questionFlags = {.glitchDone = false, .optionsDone = false, .requiredDone = false, .typeDone = false, .comingFrom = QUESTION_FROM_FORM};
                pushStringStack(cs->contextStack, formSubFg->question->id);
                ret = computeQuestion(formSubFg->question, cs, &questionFlags);
                popStringStack(cs->contextStack);
            }
            break;
		case FORM_SUB_FG_SECTION:
            if (flags->state == FORM_ONLY_STEPS || flags->state == FORM_ONLY_QUESTIONS){
                ret = _invalidComputation("Wrong hierarchy of Form elements. Sections where found at same level as Steps or Questions");
            } else {
                if (flags->state == FORM_NOT_DEFINED) flags->state = FORM_ONLY_SECTIONS;

                addRow(cs->tableSections, &(struct TableSections){.stepId = 0});
                ret = computeSection(formSubFg->section, cs);
            }
            break;
		default:
			ret = _invalidComputation("Invalid state on Form");
	}
    return ret;
}

boolean computeFormConfigFg(const FormConfigFg * formConfigFg, CompilerState * cs, FormConfigFlags * flags){

    if(formConfigFg==NULL) return _unnecessaryComputation();

    boolean ret = true;

    switch(formConfigFg->sp->type){
        case FORM_CONFIG_SP_THEME:
            if(flags->themeDone){
                 ret = _invalidComputation("Redeclaration of #Theme encountered");
                 break;
            } else {
                flags->themeDone=true;
                cs->formConfig->theme = formConfigFg->sp->theme;
            }
            break;
        case FORM_CONFIG_SP_SUBMIT:
            if(cs->formConfig->submitText != NULL){
                 ret = _invalidComputation("Redeclaration of #SubmitBtnText encountered");
                 break;
            } else {
                cs->formConfig->submitText = formConfigFg->sp->submitText;
            }
            break;
        case FORM_CONFIG_SP_SAFE_AND_SOUND:
            if(flags->safeAndSoundDone){
                 ret = _invalidComputation("Redeclaration of #SafeAndSound encountered");
                 break;
            } else {
                flags->safeAndSoundDone=true;
                cs->formConfig->safeAndSound = true;
            }
            break;
            default:
            ret = _invalidComputation("Invalid state on FormConfig");
    }
    return ret && computeFormConfigFg(formConfigFg->nextFgs,cs, flags);
}

//boolean computeStep(const Step * step,struct hashmap * table) {
//	if(step==NULL || step->stepFg == NULL) _unnecessaryComputation();
//	const boolean retRec=computeStepFg(step->stepFg->nextStepFg,table);
//
//	if(!hashmap_get(table,&(struct symbolEntry){.id = step->id})) {
//		_invalidComputation();
//	}
//
//	hashmap_set(table,&(struct symbolEntry){.id = step->id, .type = STEP});
//	return retRec;
//
//}
 