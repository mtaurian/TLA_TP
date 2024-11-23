#ifndef COMPILER_STATE_HEADER
#define COMPILER_STATE_HEADER

#include "../shared/lib/hashmap.h"
#include "../shared/lib/tables.h"
#include "../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../shared/lib/stringStack.h"

/**
 * The general status of a compilation.
*/
typedef enum {
	SUCCEED = 0,
	FAILED = 1
} CompilationStatus;

typedef enum EntrySymbolsType {
    ENTRY_SYMBOLS_STEP = 0,
    ENTRY_SYMBOLS_SHOWIF_DECLARATION,
    ENTRY_SYMBOLS_SECTION,
    ENTRY_SYMBOLS_QUESTION,
    ENTRY_SYMBOLS_GETAWAY,
    ENTRY_SYMBOLS_OPTION,
    ENTRY_SYMBOLS_GLITCH
} EntrySymbolsType;

typedef struct FormSpecifiers {
	char * title;
	char * description;
	char * closure;
}FormSpecifiers;

struct EntrySymbols {
	char * id;
    EntrySymbolsType  entrySymbolsType;
	size_t index;
};

struct TableShowIfDeclarations {
	Condition * condition;
};

struct TableSteps {
	char * title;
	char * description;
};

struct TableSections {
	size_t stepIdx;
	char * title;
	char * description;
	Condition * showIf;
};

struct TableQuestions {
	size_t stepIdx;
	size_t sectionIdx;
	QuestionType type;
	char * title;
	char * placeholder;
	boolean required;
	Value * defaultValue;
	char * help;
	Condition * showIf;
};

struct TableGetaways {
	size_t stepIdx;
	Condition * condition;
	char * gotoStepId;
};

struct TableOptions {
	size_t questionIdx;
	Condition * condition;
	Value * optionValue;
};

struct TableGlitches {
	size_t questionIdx;
	Condition * condition;
	char * errorMessage;
};

typedef struct FormConfiguration {
    ThemeSp theme;
    char * submitText;
    boolean safeAndSound;
}FormConfiguration;

/**
 * The global state of the compiler. Should transport every data structure
 * needed across the different phases of a compilation.
 */
typedef struct {
	// The root node of the AST.
	void * abstractSyntaxtTree;

	// A flag that indicates the current state of the compilation so far.
	boolean succeed;

    FormConfiguration * formConfig;

	struct hashmap * tableSymbols;
	struct Table * tableShowIfDeclarations;
	struct Table * tableSteps;
	struct Table * tableSections;
	struct Table * tableQuestions;
	struct Table * tableGetaways;
	struct Table * tableOptions;
	struct Table * tableGlitches;
	stringStack * contextStack;

	FormSpecifiers formSpecifiers;

} CompilerState;

#endif
