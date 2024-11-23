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


boolean computeFormSubFg(const FormSubFg *formSubFg, CompilerState * cs, FormFlags *flags);
boolean computeFormConfigFg(const FormConfigFg *formConfigFg, CompilerState * cs, FormConfigFlags *flags);
boolean computeFormSp(const FormSp *formSp, CompilerState * cs);
boolean computeStepFg(const StepFg *stepFg,  CompilerState * cs, StepFlags *flags);
boolean computeStepSp(StepSp * stepSp, CompilerState * cs);
boolean computeGetaway(Transports * getaway, CompilerState * cs);
boolean computeSectionFgOrSp(SectionFg * section, CompilerState * cs);
boolean computeSectionSubFg(SectionFg * section, CompilerState * cs);


boolean computeSectionSp(SectionSp * sectionSp, CompilerState * cs) {
    logDebugging(_logger, __FUNCTION__ );
    if(sectionSp==NULL) return _unnecessaryComputation();

    boolean ret=true;
    struct TableSections ** tableSections = ROWS(cs->tableSections, TableSections);

    switch (sectionSp->type) {
        case SECTION_SP_TITLE:
            if(tableSections[cs->tableSections->size-1]->title!=NULL){
                ret = _invalidComputation("Redeclaration of #Title encountered");
            }
            tableSections[cs->tableSteps->size-1]->title=sectionSp->string;

            break;
        case SECTION_SP_DESCRIPTION:
            if(tableSections[cs->tableSections->size-1]->description!=NULL){
                ret = _invalidComputation("Redeclaration of #Description encountered");
            }
            tableSections[cs->tableSections->size-1]->description=sectionSp->string;
            break;
        default:
            return _invalidComputation("Invalid specification on Form");
    }
    return ret;
}

boolean computeSectionSubFg(SectionSubFg * sectionSubFg, CompilerState * cs) {
    logDebugging(_logger, __FUNCTION__ );
    if(sectionSubFg==NULL) return _unnecessaryComputation();

    boolean ret=true;
    struct TableShowIfDeclarations ** rowsShowIfDeclarations = ROWS(cs->tableShowIfDeclarations, TableShowIfDeclarations);
    struct TableSections ** rowsSections = ROWS(cs->tableSections, TableSections);

    switch (sectionSubFg->type) {
        case SECTION_SUB_FG_SHOW_IF_CALL:
            const struct EntrySymbols * declaration = hashmap_get(cs->tableSymbols,
                                                  &(struct EntrySymbols){.id = sectionSubFg->showIfCall->conditionId});
            if(declaration==NULL) {
                logError(_logger, "ShowIf declaration not previously defined: %s", sectionSubFg->showIfCall->conditionId);
                ret=false;
            } else {
                if(rowsSections[cs->tableSections->size -1 ]->showIf!=NULL){
                    logError(_logger, "Multiple declaration of @ShowIf condition in section");
                    ret=false;
                }
                rowsSections[cs->tableSections->size -1 ]->showIf=rowsShowIfDeclarations[declaration->index]->condition;
            }
            break;
        case SECTION_SUB_FG_SHOW_IF_ON_SCOPE:

            if(rowsSections[cs->tableSections->size -1]->showIf!=NULL){
                logError(_logger, "Multiple declaration of @ShowIf condition in section");
                ret=false;
            }
            rowsSections[cs->tableSections->size -1 ]->showIf=sectionSubFg->showIfOnScope->condition;

            break;
        case SECTION_SUB_FG_SHOW_IF_DECLARATION:
            if(hashmap_get(cs->tableSymbols, &(struct EntrySymbols) {.id = sectionSubFg->showIfDeclaration->id})){
                ret = false;
                logError(_logger, "Redeclaration of identifier: %s", sectionSubFg->showIfDeclaration->id);
            }
            hashmap_set(cs->tableSymbols, &(struct EntrySymbols) {.entrySymbolsType=ENTRY_SYMBOLS_SHOWIF_DECLARATION, .id = sectionSubFg->showIfDeclaration->id, .index = cs->tableShowIfDeclarations->size});
            addRow(cs->tableShowIfDeclarations, &(struct TableShowIfDeclarations){.condition = sectionSubFg->showIfDeclaration->condtion});
            break;
        case SECTION_SUB_FG_QUESTION:

                if(hashmap_get(cs->tableSymbols, &(struct EntrySymbols) {.id = sectionSubFg->question->id})){
                    ret = false;
                    logError(_logger, "Redeclaration of identifier: %s", sectionSubFg->question->id);
                }
                hashmap_set(cs->tableSymbols,
                    &(struct EntrySymbols) {.entrySymbolsType=ENTRY_SYMBOLS_QUESTION, .id = sectionSubFg->question->id, .index = cs->tableQuestions->size});
                addRow(cs->tableQuestions, &(struct TableQuestions){.stepIdx = cs->tableSteps->size-1, .sectionIdx = cs->tableSections->size-1});
                QuestionFlags questionFlags = {.glitchDone = false, .optionsDone = false, .requiredDone = false, .typeDone = false, .comingFrom = QUESTION_FROM_SECTION};
                pushStringStack(cs->contextStack, sectionSubFg->question->id);
                ret = ret && computeQuestion(sectionSubFg->question, cs, &questionFlags);
                popStringStack(cs->contextStack);

            break;
        default:
        return _invalidComputation("Invalid specification on Form");
    }


}

boolean computeSectionFgOrSp(SectionFg * section, CompilerState * cs) {
    logDebugging(_logger, __FUNCTION__ );
    if(section==NULL) return _unnecessaryComputation();
    boolean ret=true;
    struct TableSections ** tableSections = ROWS(cs->tableSections, TableSections);
    switch (section->type) {
        case SECTION_FG_SUB_FG:
            ret=computeSectionSubFg(section->sectionSubFg,cs);
            break;
        case SECTION_FG_SP:
            ret=computeSectionSp(section->sectionSp,cs);
            break;
        default:
            return _invalidComputation("Invalid specification on Form");
    }
    return ret && computeSectionFgOrSp(section->nextSectionSubFgsOrSps, cs);
}

boolean computeGetaway(Transports * getaway, CompilerState * cs) {
    logDebugging(_logger, __FUNCTION__ );
    if(getaway==NULL) return _unnecessaryComputation();
    boolean ret=true;
    addRow(cs->tableGetaways, &(struct TableGetaways){.stepIdx =cs->tableSteps->size-1, .gotoStepId = getaway->transport->goesToEnd ? NULL : getaway->transport->stepId, .condition = getaway->transport->when});

    return ret && computeGetaway(getaway->nextTransports, cs);
}

boolean computeStepSp(StepSp * stepSp, CompilerState * cs) {
    logDebugging(_logger, __FUNCTION__ );
    if(stepSp==NULL) return _unnecessaryComputation();

    boolean ret=true;
    struct TableSteps ** tableSteps = ROWS(cs->tableSteps, TableSteps);
    switch (stepSp->type) {
        case STEP_SP_TITLE:
            if(tableSteps[cs->tableSteps->size-1]->title!=NULL){
                ret = _invalidComputation("Redeclaration of #Title encountered");
            }
            tableSteps[cs->tableSteps->size-1]->title=stepSp->string;

            break;
        case STEP_SP_DESCRIPTION:
            if(tableSteps[cs->tableSteps->size-1]->description!=NULL){
                ret = _invalidComputation("Redeclaration of #Description encountered");
            }
            tableSteps[cs->tableSteps->size-1]->description=stepSp->string;
            break;
        default:
            return _invalidComputation("Invalid specification on Form");
    }
    return ret;
}

boolean computeStepFg(const StepFg *stepFg,  CompilerState * cs, StepFlags *flags) {
    logDebugging(_logger, __FUNCTION__ );
    if(stepFg==NULL) return _unnecessaryComputation();
    boolean ret=true;
    switch (stepFg->type) {
        case STEP_FG_STEP_SP:
            ret=computeStepSp(stepFg->stepSp,cs);
            break;
        case STEP_FG_GETAWAY:
            if(flags->getawayDone){
                ret = _invalidComputation("Redeclaration of #Getaway encountered");
            } else {
                flags->getawayDone=true;
                addRow(cs->tableGetaways, &(struct TableGetaways){.stepIdx =cs->tableSteps->size-1});
                ret = computeGetaway(stepFg->getaway,cs);
            }
            break;
        case STEP_FG_SECTION:
            if(flags->state==STEP_ONLY_QUESTIONS){
                ret = _invalidComputation("Wrong hierarchy of Step elements. Sections where found at same level as Questions");
            } else {
                if(flags->state==STEP_NOT_DEFINED) flags->state=STEP_ONLY_SECTIONS;
                addRow(cs->tableSections, &(struct TableSections){.stepIdx = cs->tableSteps->size-1});
                ret = computeSectionFgOrSp(stepFg->section,cs);
            }
            break;
        case STEP_FG_QUESTION:
            if(flags->state==STEP_ONLY_SECTIONS){
                ret = _invalidComputation("Wrong hierarchy of Step elements. Questions where found at same level as Sections");
            } else {
                if(flags->state==STEP_NOT_DEFINED) flags->state=STEP_ONLY_QUESTIONS;

                if(hashmap_get(cs->tableSymbols, &(struct EntrySymbols) {.id = stepFg->question->id})){
                    ret = false;
                    logError(_logger, "Redeclaration of identifier: %s", stepFg->question->id);
                }
                hashmap_set(cs->tableSymbols,
                    &(struct EntrySymbols) {.entrySymbolsType=ENTRY_SYMBOLS_QUESTION, .id = stepFg->question->id, .index = cs->tableQuestions->size});
                addRow(cs->tableQuestions, &(struct TableQuestions){.stepIdx = cs->tableSteps->size-1, .sectionIdx = 0});
                QuestionFlags questionFlags = {.glitchDone = false, .optionsDone = false, .requiredDone = false, .typeDone = false, .comingFrom = QUESTION_FROM_STEP};
                pushStringStack(cs->contextStack, stepFg->question->id);
                ret = ret && computeQuestion(stepFg->question, cs, &questionFlags);
                popStringStack(cs->contextStack);
            }
            break;
        return ret && computeStepFg(stepFg->nextStepFg, cs, flags);
    }
}


boolean computeFormSp(const FormSp *formSp, CompilerState * cs) {
    logDebugging(_logger, __FUNCTION__ );
    if(formSp==NULL) return _unnecessaryComputation();
    boolean ret=true;
    switch (formSp->type) {
        case FORM_SP_TITLE:
            if(cs->formSpecifiers.title!=NULL){
                ret = _invalidComputation("Redeclaration of #Title encountered");
            }
            cs->formSpecifiers.title = formSp->v_string;

            break;
        case FORM_SP_DESCRIPTION:
            if(cs->formSpecifiers.description!=NULL){
                ret = _invalidComputation("Redeclaration of #Description encountered");
            }
            cs->formSpecifiers.description = formSp->v_string;
            break;
        case FORM_SP_CLOSURE:
            if(cs->formSpecifiers.closure!=NULL){
                ret = _invalidComputation("Redeclaration of #Closure encountered");
            }
            cs->formSpecifiers.closure = formSp->v_string;
            break;
        default:
            return _invalidComputation("Invalid specification on Form");
    }
    return ret;
}


boolean computeFormFg(const FormFg * form, CompilerState * cs, FormFlags * flags) {
    logDebugging(_logger, __FUNCTION__ );
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

                if(hashmap_get(cs->tableSymbols, &(struct EntrySymbols) {.id = formSubFg->step->id})){
                    ret = false;
                    logError(_logger, "Redeclaration of identifier: %s", formSubFg->step->id);
                }

                hashmap_set(cs->tableSymbols, &(struct EntrySymbols){.entrySymbolsType=ENTRY_SYMBOLS_STEP, .id = formSubFg->step->id, .index = cs->tableSteps->size});
                addRow(cs->tableSteps, &(struct TableSteps){.description = NULL, .title = NULL});
                StepFlags stepFlags = {.state = STEP_NOT_DEFINED, .getawayDone = false};
                pushStringStack(cs->contextStack, formSubFg->step->id);
                ret = ret && computeStepFg(formSubFg->step->stepFg, cs, &stepFlags);
                popStringStack(cs->contextStack);
            }
            break;
		case FORM_SUB_FG_QUESTION:
            if (flags->state == FORM_ONLY_STEPS || flags->state == FORM_ONLY_SECTIONS){
                ret = _invalidComputation("Wrong hierarchy of Form elements. Questions where found at same level as Steps or Sections");
            } else {
                if (flags->state == FORM_NOT_DEFINED) flags->state = FORM_ONLY_QUESTIONS;

                if (hashmap_get(cs->tableSymbols, &(struct EntrySymbols) {.id = formSubFg->question->id})) {
                    logError(_logger, "Redeclaration of identifier: %s", formSubFg->question->id);
                    ret = false;
                }
                hashmap_set(cs->tableSymbols,
                            &(struct EntrySymbols) {.entrySymbolsType=ENTRY_SYMBOLS_QUESTION, .id = formSubFg->question->id, .index = cs->tableQuestions->size});
                addRow(cs->tableQuestions, &(struct TableQuestions) {.stepIdx = 0, .sectionIdx = 0});
                QuestionFlags questionFlags = {.glitchDone = false, .optionsDone = false, .requiredDone = false, .typeDone = false, .comingFrom = QUESTION_FROM_FORM};
                pushStringStack(cs->contextStack, formSubFg->question->id);
                ret = ret && computeQuestion(formSubFg->question, cs, &questionFlags);
                popStringStack(cs->contextStack);
            }
            break;
		case FORM_SUB_FG_SECTION:
            if (flags->state == FORM_ONLY_STEPS || flags->state == FORM_ONLY_QUESTIONS){
                ret = _invalidComputation("Wrong hierarchy of Form elements. Sections where found at same level as Steps or Questions");
            } else {
                if (flags->state == FORM_NOT_DEFINED) flags->state = FORM_ONLY_SECTIONS;

                addRow(cs->tableSections, &(struct TableSections){.stepIdx = 0});
                ret = computeSectionFgOrSp(formSubFg->section, cs);
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
