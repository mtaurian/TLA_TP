#include "backend/code-generation/Generator.h"
#include "backend/domain-specific/Calculator.h"
#include "frontend/lexical-analysis/FlexActions.h"
#include "frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "frontend/syntactic-analysis/BisonActions.h"
#include "frontend/syntactic-analysis/SyntacticAnalyzer.h"
#include "shared/CompilerState.h"
#include "shared/Environment.h"
#include "shared/Logger.h"
#include "shared/String.h"
#include "backend/domain-specific/symbol-table.h"
#include "backend/domain-specific/FlowForm.h"
/**
 * The main entry-point of the entire application. If you use "strtok" to
 * parse anything inside this project instead of using Flex and Bison, I will
 * find you, and I will kill you (Bryan Mills; "Taken", 2008).
 */

void printCompilerState(CompilerState * cs);

const int main(const int count, const char ** arguments) {
	Logger * logger = createLogger("EntryPoint");
	initializeFlexActionsModule();
	initializeBisonActionsModule();
	initializeSyntacticAnalyzerModule();
	initializeAbstractSyntaxTreeModule();
    initializeFlowFormModule();
	// initializeCalculatorModule();
	// initializeGeneratorModule();

	// Logs the arguments of the application.
	for (int k = 0; k < count; ++k) {
		logDebugging(logger, "Argument %d: \"%s\"", k, arguments[k]);
	}

	// Begin compilation process.
	CompilerState compilerState = {
		.abstractSyntaxtTree = NULL,
		.succeed = false,
		.tableSymbols = hashmap_new(sizeof(struct  EntrySymbols ), 0, 0, 0, entrySymbolHash,entrySymbolCompare, NULL, NULL),
		.tableShowIfDeclarations = initTable(sizeof(struct TableShowIfDeclarations)),
		.tableSteps = initTable(sizeof(struct TableSteps)),
		.tableSections = initTable(sizeof(struct TableSections)),
		.tableQuestions =initTable(sizeof(struct TableQuestions)),
		.tableGetaways = initTable(sizeof(struct TableGetaways)),
		.tableOptions = initTable(sizeof(struct TableOptions)),
		.tableGlitches = initTable(sizeof(struct TableGlitches)),
		.contextStack = initStringStack(),
        .formConfig = malloc(sizeof(FormConfiguration)),
		.formSpecifiers = malloc(sizeof(FormSpecifiers))
	};
	const SyntacticAnalysisStatus syntacticAnalysisStatus = parse(&compilerState);
	CompilationStatus compilationStatus = SUCCEED;
	if (syntacticAnalysisStatus == ACCEPT) {
		// ----------------------------------------------------------------------------------------
		// Beginning of the Backend... ------------------------------------------------------------
		logDebugging(logger, "Computing expression value...");
		FormFg * program = compilerState.abstractSyntaxtTree;
		FormFlags initialFormFlags = { .state = FORM_NOT_DEFINED, .formConfigDone = false };
        boolean computationResult = computeFormFg(program,&compilerState, &initialFormFlags);
		if (computationResult) {
			//generate(&compilerState);
		}
		else {
			logError(logger, "The computation phase rejects the input program.");
			compilationStatus = FAILED;
		}
		//// ...end of the Backend. -----------------------------------------------------------------
		//// ----------------------------------------------------------------------------------------
		//logDebugging(logger, "Releasing AST resources...");
        printCompilerState(&compilerState);
		releaseFormFg(program);
	}
	else {
		logError(logger, "The syntactic-analysis phase rejects the input program.");
		compilationStatus = FAILED;
	}

	logDebugging(logger, "Releasing modules resources...");
	/*shutdownGeneratorModule();
	shutdownCalculatorModule();*/
	shutdownAbstractSyntaxTreeModule();
	shutdownSyntacticAnalyzerModule();
	shutdownBisonActionsModule();
	shutdownFlexActionsModule();
	logDebugging(logger, "Compilation is done.");
	destroyLogger(logger);
	return compilationStatus;
}


#include <stdio.h>

void printTableSections(struct TableSections **table, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Section %zu:\n", i + 1);
        printf("  Step Index: %zu\n", table[i]->stepIdx);
        printf("  Title: %s\n", table[i]->title);
        printf("  Description: %s\n", table[i]->description);
        if (table[i]->showIf != NULL) {
            printf("  Show If: Condition present\n");
        } else {
            printf("  Show If: NULL\n");
        }
        printf("\n");
    }
}

void printTableSteps(struct TableSteps **table, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Step %zu:\n", i + 1);
        printf("  Title: %s\n", table[i]->title);
        printf("  Description: %s\n", table[i]->description);
        printf("\n");
    }
}

void printTableGetaways(struct TableGetaways **table, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Getaway %zu:\n", i + 1);
        printf("  Step Index: %zu\n", table[i]->stepIdx);
        if (table[i]->condition != NULL) {
            printf("  Condition: Condition present\n");
        } else {
            printf("  Condition: NULL\n");
        }
        printf("  Goto Step ID: %s\n", table[i]->gotoStepId);
        printf("\n");
    }
}

void printTableOptions(struct TableOptions **table, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Option %zu:\n", i + 1);
        printf("  Question Index: %zu\n", table[i]->questionIdx);
        if (table[i]->condition != NULL) {
            printf("  Condition: Condition present\n");
        } else {
            printf("  Condition: NULL\n");
        }
        if (table[i]->optionValue != NULL) {
            switch (table[i]->optionValue->type) {
                case STRING:
                    printf("  Option Value: %s\n", table[i]->optionValue->v_string);
                    break;
                case INTEGER:
                    printf("  Option Value: %d\n", table[i]->optionValue->v_integer);
                    break;
                case FLOAT:
                    printf("  Option Value: %f\n", table[i]->optionValue->v_float);
                    break;
                case DATE:
                    printf("  Option Value: %d-%d-%d\n", table[i]->optionValue->v_date->day, table[i]->optionValue->v_date->month, table[i]->optionValue->v_date->year);
                    break;
                default:
                    printf("  Option Value: Unknown type\n");
            }
        } else {
            printf("  Option Value: NULL\n");
        }
        printf("\n");
    }
}

void printTableGlitches(struct TableGlitches **table, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Glitch %zu:\n", i + 1);
        printf("  Question Index: %zu\n", table[i]->questionIdx);
        if (table[i]->condition != NULL) {
            printf("  Condition: Condition present\n");
        } else {
            printf("  Condition: NULL\n");
        }
        printf("  Error Message: %s\n", table[i]->errorMessage);
        printf("\n");
    }
}

#include <stdio.h>

void printTableQuestions(struct TableQuestions **table, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Question %zu:\n", i + 1);
        printf("  Step Index: %zu\n", table[i]->stepIdx);
        printf("  Section Index: %zu\n", table[i]->sectionIdx);
        printf("  Type: %s\n", table[i]->type);
        printf("  Title: %s\n", table[i]->title);
        printf("  Placeholder: %s\n", table[i]->placeholder);
        printf("  Required: %d\n", table[i]->required);
        if (true) {
            switch (table[i]->defaultValue.type) {
                case STRING:
                    printf("  Default Value: %s\n", table[i]->defaultValue.v_string);
                    break;
                case INTEGER:
                    printf("  Default Value: %d\n", table[i]->defaultValue.v_integer);
                    break;
                case FLOAT:
                    printf("  Default Value: %f\n", table[i]->defaultValue.v_float);
                    break;
                case DATE:
                    printf("  Default Value: %d-%d-%d\n", table[i]->defaultValue.v_date->day, table[i]->defaultValue.v_date->month, table[i]->defaultValue.v_date->year);
                    break;
                default:
                    printf("  Default Value: Unknown type\n");
            }
        } else {
            printf("  Default Value: NULL\n");
        }
        printf("  Help: %s\n", table[i]->help);
        if (table[i]->showIf != NULL) {
            printf("  Show If: Condition present\n");
        } else {
            printf("  Show If: NULL\n");
        }
        printf("\n");
    }
}

void printCompilerState(CompilerState * cs){
    struct TableSteps ** tableSteps = ROWS(cs->tableSteps, TableSteps);
    struct TableGetaways ** tableGetaways = ROWS(cs->tableGetaways, TableGetaways);
    struct TableSections ** tableSections = ROWS(cs->tableSections, TableSections);
    struct TableQuestions ** tableQuestions = ROWS(cs->tableQuestions, TableQuestions);
    struct TableOptions ** tableOptions = ROWS(cs->tableOptions, TableOptions);
    struct TableGlitches ** tableGlitches = ROWS(cs->tableGlitches, TableGlitches);

    printf("Steps:\n");
    printTableSteps(tableSteps, cs->tableSteps->size);
    printf("Getaways:\n");
    printTableGetaways(tableGetaways, cs->tableGetaways->size);
    printf("Sections:\n");
    printTableSections(tableSections, cs->tableSections->size);
    printf("Questions:\n");
    printTableQuestions(tableQuestions, cs->tableQuestions->size);
    printf("Options:\n");
    printTableOptions(tableOptions, cs->tableOptions->size);
    printf("Glitches:\n");
    printTableGlitches(tableGlitches, cs->tableGlitches->size);
    printf("Symbols table:\n");
    hashmap_scan(cs->tableSymbols, entrySymbolIter, NULL);
}
