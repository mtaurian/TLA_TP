#ifndef FLOWFORM_H
#define FLOWFORM_H

#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"

typedef struct {
	boolean succeed;
} ComputationResult;

typedef ComputationResult (*BinaryOperator)(const int, const int);

// FormSubFg

typedef enum FormState {
	ONLY_STEPS = 0, ONLY_SECTIONS, ONLY_QUESTIONS, NOT_DEFINED
} FormState; 

typedef struct FormFlags {
	FormState state;
	boolean formConfigDone;
} FormFlags;

// StepFg

typedef enum StepState {
	ONLY_SECTIONS = 0, ONLY_QUESTIONS, NOT_DEFINED
} StepState; 

typedef struct StepFlags {
	StepState state;
	boolean getawayDone;
} StepFlags;

// Question

typedef struct QuestionFlags {
	boolean optionsDone;
	boolean glitchDone;
} QuestionFlags;

#endif //FLOWFORM_H
