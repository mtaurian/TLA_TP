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
const int main(const int count, const char ** arguments) {
	Logger * logger = createLogger("EntryPoint");
	initializeFlexActionsModule();
	initializeBisonActionsModule();
	initializeSyntacticAnalyzerModule();
	initializeAbstractSyntaxTreeModule();
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
	};
	const SyntacticAnalysisStatus syntacticAnalysisStatus = parse(&compilerState);
	CompilationStatus compilationStatus = SUCCEED;
	if (syntacticAnalysisStatus == ACCEPT) {
		// ----------------------------------------------------------------------------------------
		// Beginning of the Backend... ------------------------------------------------------------
		logDebugging(logger, "Computing expression value...");
		FormFg * program = compilerState.abstractSyntaxtTree;
		//// ComputationResult computationResult = computeFormFg(program,compilerState.table);
		//if (computationResult.succeed) {
		//	compilerState.value = computationResult.value;
		//	generate(&compilerState);
		//}
		//else {
		//	logError(logger, "The computation phase rejects the input program.");
		//	compilationStatus = FAILED;
		//}*/
		//// ...end of the Backend. -----------------------------------------------------------------
		//// ----------------------------------------------------------------------------------------
		//logDebugging(logger, "Releasing AST resources...");
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
