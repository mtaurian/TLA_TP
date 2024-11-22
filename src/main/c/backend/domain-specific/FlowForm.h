#ifndef FLOWFORM_H
#define FLOWFORM_H

#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "../../shared/CompilerState.h"


typedef enum FormState {
	FORM_ONLY_STEPS = 0, FORM_ONLY_SECTIONS, FORM_ONLY_QUESTIONS, FORM_NOT_DEFINED
} FormState; 

typedef struct FormFlags {
	FormState state;
	boolean formConfigDone;
} FormFlags;

typedef struct FormConfigFlags {
    boolean themeDone;
    boolean safeAndSoundDone;
} FormConfigFlags;

// StepFg

typedef enum StepState {
	STEP_ONLY_SECTIONS = 0, STEP_ONLY_QUESTIONS, STEP_NOT_DEFINED
} StepState; 

typedef struct StepFlags {
	StepState state;
	boolean getawayDone;
} StepFlags;

// Question

typedef enum QuestionComingFrom {
    QUESTION_FROM_STEP = 0, QUESTION_FROM_SECTION, QUESTION_FROM_FORM
} QuestionComingFrom;

typedef struct QuestionFlags {
	boolean optionsDone;
    boolean typeDone;
    boolean requiredDone;
	boolean glitchDone;
    QuestionComingFrom comingFrom;
} QuestionFlags;

void initializeFlowFormModule();
boolean computeFormFg(const FormFg * form, CompilerState * cs, FormFlags* flags);
boolean computeFormSubFg(const FormSubFg *formSubFg, CompilerState * cs, FormFlags *flags);
boolean computeFormConfigFg(const FormConfigFg *formConfigFg, CompilerState * cs, FormConfigFlags *flags);
//boolean computeStep(const Step * step,struct hashmap * table);
//boolean computeQuestion(const Question * question,struct hashmap * table);
//boolean computeSection(const SectionFg * section,struct hashmap * table);
//boolean computeStepFg(const StepFg *stepFg,struct hashmap *table);

#endif //FLOWFORM_H
