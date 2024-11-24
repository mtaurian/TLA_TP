#include "backend/code-generation/Generator.h"
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
void logComputedResults(Logger *logger,CompilerState *cs);
void freeTables(CompilerState *cs);
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
        .formConfig = calloc(1, sizeof(FormConfiguration)),
		.formSpecifiers = calloc(1, sizeof(FormSpecifiers))
	};

	const SyntacticAnalysisStatus syntacticAnalysisStatus = parse(&compilerState);
	CompilationStatus compilationStatus = SUCCEED;
	if (syntacticAnalysisStatus == ACCEPT) {
		// ----------------------------------------------------------------------------------------
		// Beginning of the Backend... ------------------------------------------------------------
		logDebugging(logger, "Computing expression value...");
		FormFg * program = compilerState.abstractSyntaxtTree;
		FormFlags initialFormFlags = { .state = FORM_NOT_DEFINED, .formConfigDone = false };
        compilerState.succeed = computeFormFg(program,&compilerState, &initialFormFlags);
		checkMandatorySpecifiers(&compilerState);
        if (compilerState.succeed) {
	        logComputedResults(logger, &compilerState);
			generate(&compilerState);
		}
		if( compilerState.succeed==false) {
		    logError(logger, "The computation phase rejects the input program.");
		    compilationStatus = FAILED;
		}
		//// ...end of the Backend. -----------------------------------------------------------------
		//// ----------------------------------------------------------------------------------------
		logDebugging(logger, "Releasing AST resources...");
	    freeTables(&compilerState);
	    hashmap_free(compilerState.tableSymbols);
	    freeStack(compilerState.contextStack);
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

void logComputedResults(Logger *logger,CompilerState *cs) {
    logInformation(logger, "Computed %zu steps successfully",cs->tableSteps->size);
    logInformation(logger, "Computed %zu sections successfully",cs->tableSections->size);
    logInformation(logger, "Computed %zu getaways successfully",cs->tableGetaways->size);
    logInformation(logger, "Computed %zu options successfully",cs->tableOptions->size);
    logInformation(logger, "Computed %zu showIf declarations successfully",cs->tableShowIfDeclarations->size);
    logInformation(logger, "Computed %zu glitches successfully",cs->tableGlitches->size);
    logInformation(logger, "Computed %zu questions successfully",cs->tableQuestions->size);
    logInformation(logger, "Computed %zu symbols successfully",hashmap_count(cs->tableSymbols));
}


void freeTables(CompilerState *cs) {
    freeTable(cs->tableSections);
    freeTable(cs->tableSteps);
    freeTable(cs->tableGetaways);
    freeTable(cs->tableOptions);
    freeTable(cs->tableShowIfDeclarations);
    freeTable(cs->tableGlitches);
    freeTable(cs->tableQuestions);
}
