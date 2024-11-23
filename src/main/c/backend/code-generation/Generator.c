#include "Generator.h"

/* MODULE INTERNAL STATE */

const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger * _logger = NULL;

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PRIVATE FUNCTIONS */

static char * _indentation(const unsigned int indentationLevel);
static void _output(const unsigned int indentationLevel, const char * const format, ...);
static void generateId(FILE * file, CompilerState * state, char * id);
static boolean assertDateId(CompilerState * state, char * id);
static boolean assertDateParameter(CompilerState * state, LibFunction * function);
static boolean assertStringId(CompilerState * state, char * id);
static boolean assertStringParameter(CompilerState * state, LibFunction * function);
static boolean assertNumericId(CompilerState * state, char * id);
static boolean assertNumericParameter(CompilerState * state , LibFunction * function);
static void generateLibFunctionParameter(FILE * file, CompilerState * state, LibFunction * function);
static void generateNumericComparatorLibFunction(FILE * file, CompilerState * state, BasicProp * basicProp, char * compare);
static void generateDateComparatorLibFunction(FILE * file, CompilerState * state, BasicProp * basicProp, char * compare);
static void generateBasicCondition(FILE * file, CompilerState * state, BasicProp * basicProp);
static void generateConditionRec(FILE * file, CompilerState * state, Condition * condition);
static void generateCondition(FILE * file, CompilerState * state, Condition * condition);

/**
 * Generates an indentation string for the specified level.
 */
static char * _indentation(const unsigned int level) {
	return indentation(_indentationCharacter, level, _indentationSize);
}

/**
 * Outputs a formatted string to standard output. The "fflush" instruction
 * allows to see the output even close to a failure, because it drops the
 * buffering.
 */
static void _output(const unsigned int indentationLevel, const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	char * indentation = _indentation(indentationLevel);
	char * effectiveFormat = concatenate(2, indentation, format);
	vfprintf(stdout, effectiveFormat, arguments);
	fflush(stdout);
	free(effectiveFormat);
	free(indentation);
	va_end(arguments);
}


static boolean assertStringId(CompilerState * state, char * id){
    struct EntrySymbols * identifier = (struct EntrySymbols *) hashmap_get(state->tableSymbols, &(struct EntrySymbols){.id = id});
    struct TableQuestions ** tableQuestions = ROWS(state->tableQuestions, TableQuestions);

    if (identifier == NULL) {
        logError(_logger, "Bad reference: Identifier %s not found in the symbol table", id);
        state->succeed = false;
        return false;
    } else if (identifier->entrySymbolsType != ENTRY_SYMBOLS_QUESTION){
        logError(_logger, "Bad reference: Identifier %s is not a question", id);
        state->succeed = false;
        return false;
    } else if (strcmp(tableQuestions[identifier->index]->type, "text") != 0
    && strcmp(tableQuestions[identifier->index]->type, "select") != 0
    && strcmp(tableQuestions[identifier->index]->type, "textarea") != 0
    && strcmp(tableQuestions[identifier->index]->type, "password") != 0
    && strcmp(tableQuestions[identifier->index]->type, "checkbox") != 0
    && strcmp(tableQuestions[identifier->index]->type, "radios") != 0) {
        logError(_logger, "Bad reference: Identifier %s is not a text, select, textarea, radios, nor checkbox type question", id);
        state->succeed = false;
        return false;
    }

    return true;
}

static boolean assertDateParameter(CompilerState * state, LibFunction * function){
    if(function->parameterType == TYPE_ID){
        return assertDateId(state, function->v_id);
    }

    if (function->parameterType != TYPE_DATE){
        logError(_logger, "Bad reference: Date parameter expected");
        state->succeed = false;
        return false;
    }
    return true;
}

static boolean assertDateId(CompilerState * state, char * id){
    struct EntrySymbols * identifier = (struct EntrySymbols *) hashmap_get(state->tableSymbols, &(struct EntrySymbols){.id = id});
    struct TableQuestions ** tableQuestions = ROWS(state->tableQuestions, TableQuestions);

    if (identifier == NULL) {
        logError(_logger, "Bad reference: Identifier %s not found in the symbol table", id);
        state->succeed = false;
        return false;
    } else if (identifier->entrySymbolsType != ENTRY_SYMBOLS_QUESTION){
        logError(_logger, "Bad reference: Identifier %s is not a question", id);
        state->succeed = false;
        return false;
    } else if (strcmp(tableQuestions[identifier->index]->type, "date") != 0){
        logError(_logger, "Bad reference: Identifier %s is not a date question", id);
        state->succeed = false;
        return false;
    }

    return true;
}


static boolean assertStringParameter(CompilerState * state, LibFunction * function){
    if (function->parameterType == TYPE_ID){
        return assertStringId(state, function->v_id);
    }
    if (function->parameterType != TYPE_STRING){
        logError(_logger, "Bad reference: String parameter expected");
        state->succeed = false;
        return false;
    }
    return true;
}

static boolean assertNumericId(CompilerState * state, char * id){
    struct EntrySymbols * identifier = (struct EntrySymbols *) hashmap_get(state->tableSymbols, &(struct EntrySymbols){.id = id});
    struct TableQuestions ** tableQuestions = ROWS(state->tableQuestions, TableQuestions);

    if (identifier == NULL) {
        logError(_logger, "Bad reference: Identifier %s not found in the symbol table", id);
        state->succeed = false;
        return false;
    } else if (identifier->entrySymbolsType != ENTRY_SYMBOLS_QUESTION){
        logError(_logger, "Bad reference: Identifier %s is not a question", id);
        state->succeed = false;
        return false;
    } else if (strcmp(tableQuestions[identifier->index]->type, "number") != 0){
        logError(_logger, "Bad reference: Identifier %s is not a numeric question", id);
        state->succeed = false;
        return false;
    }

    return true;

}

static boolean assertNumericParameter(CompilerState * state , LibFunction * function){
    if (function->parameterType == TYPE_ID){
        return assertNumericId(state, function->v_id);
    }
    if (function->parameterType != TYPE_INTEGER && function->parameterType != TYPE_FLOAT){
        logError(_logger, "Bad reference: Numeric parameter expected");
        state->succeed = false;
        return false;
    }
    return true;
}

static void generateLibFunctionParameter(FILE * file, CompilerState * state, LibFunction * function){
    switch(function->parameterType){
        case TYPE_STRING:
            fprintf(file, " \"%s\" ", function->v_string);
            break;
        case TYPE_FLOAT:
            fprintf(file, " %f ", function->v_float);
            break;
        case TYPE_INTEGER:
            fprintf(file, " %d ", function->v_integer);
            break;
        case TYPE_DATE:
            fprintf(file, " %d-%d-%d ", function->v_date->year, function->v_date->month, function->v_date->day);
            break;
        case TYPE_ID:
             generateId(file, state, function->v_id);
            break;
        default:
            logError(_logger, "Invalid State: LibFunction parameter type not found");
            state->succeed = false;
            break;
    }
}

static void generateId(FILE * file, CompilerState * state, char * id){
    struct EntrySymbols * identifier = (struct EntrySymbols *) hashmap_get(state->tableSymbols, &(struct EntrySymbols){.id = id});
    if (identifier == NULL) {
        logError(_logger, "Bad reference: Identifier %s not found in the symbol table", id);
        state->succeed = false;
        return;
    } else if (identifier->entrySymbolsType != ENTRY_SYMBOLS_QUESTION){
        logError(_logger, "Bad reference: Identifier %s is not a question", id);
        state->succeed = false;
        return;
    } else {
        fprintf(file, " questions.value[%zu].value ", identifier->index);
    }
}

static void generateNumericComparatorLibFunction(FILE * file, CompilerState * state, BasicProp * basicProp, char * compare){
    if (!assertNumericId(state, basicProp->id)) return;
    if (!assertNumericParameter(state, basicProp->function)) return;

    generateId(file, state, basicProp->id);
    fprintf(file, " %s ", compare);
    generateLibFunctionParameter(file, state, basicProp->function);
}

static void generateDateComparatorLibFunction(FILE * file, CompilerState * state, BasicProp * basicProp, char * compare){
    if (!assertDateId(state, basicProp->id)) return;
    if (!assertDateParameter(state, basicProp->function)) return;

    fprintf(file, " %s(", compare);
    generateId(file, state, basicProp->id);
    fprintf(file, " , ");
    generateLibFunctionParameter(file, state, basicProp->function);
    fprintf(file, ")");
}

static void generateBasicCondition(FILE * file, CompilerState * state, BasicProp * basicProp){
    switch (basicProp->type) {
        case BASIC_PROP_TYPE_BOOLEAN:
            basicProp->truthValue ? fprintf(file, " true ") : fprintf(file, " false ");
            break;
        case BASIC_PROP_TYPE_FUNCTION:
            switch (basicProp->function->type) {
                case LIB_FUNCTION_IS_LOWER_THAN:
                    generateNumericComparatorLibFunction(file, state, basicProp, "<");
                    break;
                case LIB_FUNCTION_IS_GREATER_THAN:
                    generateNumericComparatorLibFunction(file, state, basicProp, ">");
                    break;
                case LIB_FUNCTION_IS_LOWER_OR_EQUAL_TO:
                    generateNumericComparatorLibFunction(file, state, basicProp, "<=");
                    break;
                case LIB_FUNCTION_IS_GREATER_OR_EQUAL_TO:
                    generateNumericComparatorLibFunction(file, state, basicProp, ">=");
                    break;
                case LIB_FUNCTION_EQUALS:
                    generateId(file, state, basicProp->id);
                    fprintf(file, " === ");
                    generateLibFunctionParameter(file, state, basicProp->function);
                    break;
                case LIB_FUNCTION_IS_DIFFERENT_FROM:
                    generateId(file, state, basicProp->id);
                    fprintf(file, " !== ");
                    generateLibFunctionParameter(file, state, basicProp->function);
                    break;
                case LIB_FUNCTION_IS_MULTIPLE_OF:
                    if (!assertNumericId(state, basicProp->id)) return;
                    if (!assertNumericParameter(state, basicProp->function)) return;

                    fprintf(file, " isMultipleOf( ");
                    generateId(file, state, basicProp->id);
                    fprintf(file, ", ");
                    generateLibFunctionParameter(file, state, basicProp->function);
                    fprintf(file, " ) ");
                    break;
                case LIB_FUNCTION_IS_DIVISOR_OF:
                    if (!assertNumericId(state, basicProp->id)) return;
                    if (!assertNumericParameter(state, basicProp->function)) return;

                    fprintf(file, " isDivisorOf( ");
                    generateId(file, state, basicProp->id);
                    fprintf(file, ", ");
                    generateLibFunctionParameter(file, state, basicProp->function);
                    fprintf(file, " ) ");
                    break;
                case LIB_FUNCTION_IS_TRUE:
                    generateId(file, state, basicProp->id);
                    fprintf(file, " === true ");
                    break;
                case LIB_FUNCTION_IS_FALSE:
                    generateId(file, state, basicProp->id);
                    fprintf(file, " === false ");
                    break;
                case LIB_FUNCTION_LIKE:
                    if (!assertStringId(state, basicProp->id)) return;
                    if (!assertStringParameter(state, basicProp->function)) return;

                    fprintf(file, " like( ");
                    generateId(file, state, basicProp->id);
                    fprintf(file, ", ");
                    generateLibFunctionParameter(file, state, basicProp->function);
                    fprintf(file, " ) ");

                    break;
                case LIB_FUNCTION_DOES_LENGTH_EQUAL:
                    if (!assertStringId(state, basicProp->id)) return;
                    if (!assertStringParameter(state, basicProp->function)) return;

                    fprintf(file, " lengthEquals( ");
                    generateId(file, state, basicProp->id);
                    fprintf(file, ", ");
                    generateLibFunctionParameter(file, state, basicProp->function);
                    fprintf(file, " ) ");
                    break;
                case LIB_FUNCTION_IS_LONGER_THAN:
                    if (!assertStringId(state, basicProp->id)) return;
                    if (!assertStringParameter(state, basicProp->function)) return;

                    fprintf(file, " longerThan( ");
                    generateId(file, state, basicProp->id);
                    fprintf(file, ", ");
                    generateLibFunctionParameter(file, state, basicProp->function);
                    fprintf(file, " ) ");
                    break;
                case LIB_FUNCTION_IS_SHORTER_THAN:
                    if (!assertStringId(state, basicProp->id)) return;
                    if (!assertStringParameter(state, basicProp->function)) return;

                    fprintf(file, " shorterThan( ");
                    generateId(file, state, basicProp->id);
                    fprintf(file, ", ");
                    generateLibFunctionParameter(file, state, basicProp->function);
                    fprintf(file, " ) ");
                    break;
                case LIB_FUNCTION_IS_EMPTY:
                    fprintf(file, " isEmpty( ");
                    generateId(file, state, basicProp->id);
                    fprintf(file, " ) ");
                    break;
                case LIB_FUNCTION_IS_BEFORE:
                    generateDateComparatorLibFunction(file, state, basicProp, "isBefore");
                case LIB_FUNCTION_IS_AFTER:
                    generateDateComparatorLibFunction(file, state, basicProp, "isAfter");
                    break;
                case LIB_FUNCTION_IS_WEEKEND:
                    if (!assertDateId(state, basicProp->id)) return;

                    fprintf(file, " isWeekend( ");
                    generateId(file, state, basicProp->id);
                    fprintf(file, " ) ");
                    break;
                case LIB_FUNCTION_MATH_VALID:
                    logWarning(_logger, "Function MathValid is not supported in this version of compiler");
                    break;
                case LIB_FUNCTION_SATISFIES:
                    logWarning(_logger, "Function Satisfies is not supported in this version of compiler");
                    break;
                case LIB_FUNCTION_CONTAINS:
                    logWarning(_logger, "Function Contains is not supported in this version of compiler");
                    break;
                case LIB_FUNCTION_IS_LOWEST:
                    logWarning(_logger, "Function Lowest is not supported in this version of compiler");
                    break;
                case LIB_FUNCTION_IS_GREATEST:
                    logWarning(_logger, "Function Greatest is not supported in this version of compiler");
                    break;
                default:
                    logError(_logger, "Invalid State: Function not found on the standard flow form library");
            }
            break;
        default:
            logError(_logger, "Invalid State: BasicProp type not found");
            state->succeed = false;
            break;
    }
}

static void generateConditionRec(FILE * file, CompilerState * state, Condition * condition) {
    if (!condition) return ;

    switch(condition->type){
        case CONDITION_TYPE_AND:
            fprintf(file, "(");
            generateConditionRec(file, state, condition->leftCondition);
            fprintf(file, " && ");
            generateConditionRec(file, state, condition->rightCondition);
            fprintf(file, ")");
            break;
        case CONDITION_TYPE_OR:
            fprintf(file, "(");
            generateConditionRec(file, state, condition->leftCondition);
            fprintf(file, " || ");
            generateConditionRec(file, state, condition->rightCondition);
            fprintf(file, ")");
            break;
        case CONDITION_TYPE_NOT:
            fprintf(file, "!");
            generateConditionRec(file, state, condition->condition);
            break;
        case CONDITION_TYPE_SINGLE:
            fprintf(file, "(");
            generateConditionRec(file, state, condition->condition);
            fprintf(file, ")");
            break;
        case CONDITION_TYPE_BASIC:
            generateBasicCondition(file, state, condition->basicProp);
            break;
    }
}

static void generateCondition(FILE * file, CompilerState * state, Condition * condition){
    fprintf(file, " () => ");
    generateConditionRec(file, state, condition);
}

/** PUBLIC FUNCTIONS */

