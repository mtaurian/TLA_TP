/*#include "FlowForm.h"

#include "symbol-table.h"
#include "../../shared/lib/hashmap.h"
#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
static boolean _invalidComputation() {
	return false;
};
static boolean _unnecessaryComputation(){
	return true;
};

boolean computeStep(const Step * step,struct hashmap * table);
boolean computeQuestion(const Question * question,struct hashmap * table);
boolean computeSection(const SectionFg * section,struct hashmap * table);
boolean computeFormSubFg(const FormSubFg *formSubFg, struct hashmap *table);
boolean computeStepFg(const StepFg *stepFg,struct hashmap *table);

boolean computeFormFg(const FormFg * form,struct hashmap *table) {
    if(form==NULL) return _unnecessaryComputation();
    const boolean retRec=computeFormFg(form->nextFormFgs,table);
	boolean ret=true;
    if(form->type==FORM_FG_SUB_FG){
        ret=computeFormSubFg(form->formSubFg,table);
    }
    return ret && retRec;
    
}

boolean computeFormSubFg(const FormSubFg *formSubFg, struct hashmap *table) {
	switch (formSubFg->type) {
		case FORM_SUB_FG_CONFIG:
			return _unnecessaryComputation();
		case FORM_SUB_FG_STEP:
			return computeStep(formSubFg->step, table);
		case FORM_SUB_FG_QUESTION:
			return computeQuestion(formSubFg->question,table);
		case FORM_SUB_FG_SECTION:
			return computeSection(formSubFg->section, table) ;
		default:
			return _invalidComputation();
	}
}

// &(struct user){ .name="Dale", .age=44 });
boolean computeStep(const Step * step,struct hashmap * table) {
	if(step==NULL || step->stepFg == NULL) _unnecessaryComputation();
	const boolean retRec=computeStepFg(step->stepFg->nextStepFg,table);

	if(!hashmap_get(table,&(struct symbolEntry){.id = step->id})) {
		_invalidComputation();
	}

	hashmap_set(table,&(struct symbolEntry){.id = step->id, .type = STEP});
	return retRec;

}
*/