#ifndef FLOWFORM_H
#define FLOWFORM_H

#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"

typedef struct {
	boolean succeed;
} ComputationResult;

typedef ComputationResult (*BinaryOperator)(const int, const int);

#endif //FLOWFORM_H
