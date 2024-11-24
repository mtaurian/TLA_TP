#include "Generator.h"

#include <math.h>

#include "../domain-specific/symbol-table.h"
#define PATH(file) "./src/main/c/backend/code-generation/source-files/" file
const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger * _logger = NULL;

#include <stdio.h>
#include <stdlib.h>

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


void copyFile(const char *sourcePath, FILE *destFile) {
	logDebugging(_logger,__FUNCTION__);
	FILE *sourceFile = fopen(sourcePath, "rb");
	if (sourceFile == NULL) {
		logError(_logger, "Error opening source file to copy");
		return;
	}

	char buffer[32768];
	size_t bytesRead;
	while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
		fwrite(buffer, 1, bytesRead, destFile);
	}
	fclose(sourceFile);
}


void _applyTheme(FILE * file,CompilerState * compilerState) {
	logDebugging(_logger,__FUNCTION__);
	switch (compilerState->formConfig->theme) {
	case THEME_DEBUT:
		copyFile(PATH("themes/THEME_DEBUT.txt"),file);
		break;
	case THEME_FEARLESS:
		copyFile(PATH("themes/THEME_FEARLESS.txt"),file);
		break;
	case THEME_SPEAK_NOW:
		copyFile(PATH("themes/THEME_SPEAK_NOW.txt"),file);
		break;
	case THEME_RED:
		copyFile(PATH("themes/THEME_RED.txt"),file);
		break;
	case THEME_NINETEEN_EIGHTY_NINE:
		copyFile(PATH("themes/THEME_NINETEEN_EIGHTY_NINE.txt"),file);
		break;
	case THEME_REPUTATION:
		copyFile(PATH("themes/THEME_REPUTATION.txt"),file);
		break;
	case THEME_LOVER:
		copyFile(PATH("themes/THEME_LOVER.txt"),file);
		break;
	case THEME_FOLKLORE:
		copyFile(PATH("themes/THEME_FOLKLORE.txt"),file);
		break;
	case THEME_EVERMORE:
		copyFile(PATH("themes/THEME_EVERMORE.txt"),file);
		break;
	case THEME_MIDNIGHTS:
		copyFile(PATH("themes/THEME_MIDNIGHTS.txt"),file);
		break;
	case THEME_TTPD:
		copyFile(PATH("themes/THEME_TTPD.txt"),file);
		break;
	default:
		copyFile(PATH("themes/THEME_DEFAULT.txt"),file);
		break;
	}

}

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

void _addSectionsForStep(FILE * file, CompilerState * compilerState, size_t stepIdx, boolean checkStep) {
	logDebugging(_logger,__FUNCTION__);

	fprintf(file,
	"						sections : [\n");
	struct TableSections ** sections = ROWS(compilerState->tableSections,TableSections);
	boolean added=false;
	for(size_t i=0;i<compilerState->tableSections->size;i++) {
		if( !checkStep || sections[i]->stepIdx==stepIdx) {
			if(added){
				fprintf(file,
				",\n");
			}
			added=true;

			//open item
			fprintf(file,
			"							{\n");

			//add title
			fprintf(file,
			"								title : \"");
			fprintf(file,"%s",sections[i]->title );
			fprintf(file,"\",\n");

			//add description
			fprintf(file,
			"								description : \"");
			fprintf(file,"%s",sections[i]->description );
			fprintf(file,"\",\n");

			//add showIf
			fprintf(file,
			"								showif : ");
			generateCondition(file,compilerState,sections[i]->showIf);

			//close item
			fprintf(file,
			"\n							}");

		}

	}

	if(!added){
		fprintf(file,
	"							{\n"
		"								title : '',\n"
		"								description : '',\n"
		"								showif : () => true\n"
		"							}\n"
		"						]");
	}else {
		//close sections
		fprintf(file,
	"\n						]");
	}
}


void _addGetawaysForStep(FILE * file, CompilerState * compilerState, size_t stepIdx) {
	logDebugging(_logger,__FUNCTION__);

	//open getaways
	fprintf(file,
	"						getaways : [\n");
	boolean added=false;
	struct TableGetaways ** getaways = ROWS(compilerState->tableGetaways,TableGetaways);
	for(size_t i=0;i<compilerState->tableGetaways->size;i++) {
		if(getaways[i]->stepIdx==stepIdx) {
			if(added){
				fprintf(file,
				",\n");
			}
			added=true;

			//open item
			fprintf(file,
			"							{\n");


			//add showIf
			fprintf(file,
			"								condition : ");
			generateCondition(file,compilerState,getaways[i]->condition);

			//close item
			fprintf(file,
			",\n");

			//add description
			fprintf(file,
			"								step : ");
			if(getaways[i]->gotoStepId==NULL) {
				fprintf(file,"%zu\n",compilerState->tableSteps->size);
			} else {
				const struct EntrySymbols * step = hashmap_get(compilerState->tableSymbols,&(struct EntrySymbols){.id=getaways[i]->gotoStepId});
				if(step==NULL || step->entrySymbolsType!=ENTRY_SYMBOLS_STEP) {
					logError(_logger,"Goto to step not found in getaway");
					compilerState->succeed=false;
				} else if (step->index==stepIdx) {
					logError(_logger,"Autoreference encountered in getaway condition");
					compilerState->succeed=false;
				} else {
					fprintf(file,"%zu\n",step->index);
				}
			}
			//close item
			fprintf(file,
			"\n							}");
		}
	}

	//close getaways
	fprintf(file,
	"\n						]");
}
void _addSteps(FILE *file, CompilerState * compilerState) {
	logDebugging(_logger,__FUNCTION__);

	//open steps variable
	fprintf(file,
	"				const steps = ref([\n");
	struct TableSteps ** steps = ROWS(compilerState->tableSteps,TableSteps);
	for(size_t i=0;i<compilerState->tableSteps->size;i++) {
		if(i!=0){
			fprintf(file,
			",\n");
		}
		//open item
		fprintf(file,
		"					{\n");

		//add title
		fprintf(file,
		"						title : \"");
		fprintf(file,"%s",steps[i]->title );
		fprintf(file,"\",\n");

		//add description
		fprintf(file,
		"						description : \"");
		fprintf(file,"%s",steps[i]->description );
		fprintf(file,"\",\n");
		_addSectionsForStep(file,compilerState,i,true);

		//separete sections from getaways
		fprintf(file,",\n");

		_addGetawaysForStep(file,compilerState,i);
		//closer item
		fprintf(file,
		"\n					}");
	}

	if(compilerState->tableSteps->size==0) {
		//open item
		fprintf(file,
		"					{\n");

		//add title and description empty
		fprintf(file,
		"						title : '',\n"
			"						description : '',\n");

		_addSectionsForStep(file,compilerState,0,false);

		//close item
		fprintf(file,
		"					}\n");

	}
	//close steps variable
	fprintf(file,
	",\n					{\n"
		"						title : 'Form submited successfully',\n"
		"						description : closure,\n"
		"						sections : [],\n"
		"						getaways : []\n"
		"					}\n"
		"				]);\n");
}
void _addGlitches(FILE *file, CompilerState *compilerState, size_t questionIdx) {
	logDebugging(_logger,__FUNCTION__);

	//open erorrs
	fprintf(file,
	"						errors : [\n");
	struct TableGlitches ** glitches = ROWS(compilerState->tableGlitches,TableGlitches);
	boolean	added=false;
	for (size_t i=0;i<compilerState->tableGlitches->size;i++) {
		if(glitches[i]->questionIdx==questionIdx) {
			if(added){
				fprintf(file,
				",\n");
			}
			added=true;
			//open item
			fprintf(file,
			"							{\n");

			//add showIf
			fprintf(file,
			"								condition : ");
			generateCondition(file,compilerState,glitches[i]->condition);

			fprintf(file,
			",\n");

			//add showIf
			fprintf(file,
			"								msg : \"%s\"\n",glitches[i]->errorMessage);

			//close item
			fprintf(file,
			"							}");

		}

	}
	//close errors
	fprintf(file,
	"\n						]");
}

void _addOptions(FILE *file, CompilerState * compilerState,size_t questionIdx) {
	logDebugging(_logger,__FUNCTION__);

	//open erorrs
	fprintf(file,
	"						options : [\n");
	struct TableOptions ** options = ROWS(compilerState->tableOptions,TableOptions);
	boolean	added=false;
	for (size_t i=0;i<compilerState->tableOptions->size;i++) {
		if(options[i]->questionIdx==questionIdx) {
			if(added){
				fprintf(file,
				",\n");
			}
			added=true;
			//open item
			fprintf(file,
			"							{\n");

			//add condition
			fprintf(file,
			"								condition : ");
			generateCondition(file,compilerState,options[i]->condition);
			fprintf(file,
			",\n");

			switch (options[i]->optionValue->type) {
				case TYPE_STRING:
					fprintf(file,
					"								value : \"%s\",\n",options[i]->optionValue->v_string == NULL ? "" : options[i]->optionValue->v_string);
				break;
				case TYPE_FLOAT:
					fprintf(file,
					"								value : %f,\n",options[i]->optionValue->v_float);
				break;
				case TYPE_INTEGER:
					fprintf(file,
					"								value : %d,\n",options[i]->optionValue->v_integer);
				break;
				case TYPE_DATE:
					fprintf(file,
					"								value : new Date(\"%d-%d-%d\").toISOString().split('T')[0],\n",options[i]->optionValue->v_date->year,options[i]->optionValue->v_date->month,options[i]->optionValue->v_date->day);
				break;
				default:
					fprintf(file,
					"								value : null,\n");
				break;
			}

			//close item
			fprintf(file,
			"							}");

		}

	}
	//close errors
	fprintf(file,
	"\n						]");
}

void _addQuestions(FILE *fileHtml, FILE* fileGs,CompilerState * compilerState) {
	logDebugging(_logger,__FUNCTION__);

	//open questions variable
	fprintf(fileHtml,
	"				const questions = ref([\n");
	struct TableQuestions ** questions = ROWS(compilerState->tableQuestions,TableQuestions);
	for(size_t i=0;i<compilerState->tableQuestions->size;i++) {
		if(i!=0){
			fprintf(fileHtml,
			",\n");
			fprintf(fileGs,", ");
		}
		if(fileGs!=NULL) {
			fprintf(fileGs,"\"%s\"",questions[i]->title);
		}
		//open item
		fprintf(fileHtml,
		"					{\n");

		//add stepIdx
		fprintf(fileHtml,
		"						step : %zu,\n",questions[i]->stepIdx);

		//add sectionIdx
		fprintf(fileHtml,
		"						section : %zu,\n",questions[i]->sectionIdx);

		//add id
		fprintf(fileHtml,
		"						id : \"question_%zu\",\n",i);

		//add type
		fprintf(fileHtml,
		"						type : \"" );

		switch(questions[i]->type){
			case QUESTION_TYPE_CHECKBOX:
				fprintf(fileHtml,"checkbox\",\n");
			break;
			case QUESTION_TYPE_RADIOS:
				fprintf(fileHtml,"radios\",\n");
			break;
			case QUESTION_TYPE_SELECT_TEXT:
			case QUESTION_TYPE_SELECT_DATE:
			case QUESTION_TYPE_SELECT_NUMERIC:
			fprintf(fileHtml,"select\",\n");
			break;
			case QUESTION_TYPE_TEXT:
				fprintf(fileHtml,"text\",\n");

			break;
			case QUESTION_TYPE_IMAGE:
				fprintf(fileHtml,"image\",\n");

			break;
			case QUESTION_TYPE_DOCUMENT:
				fprintf(fileHtml,"file\",\n");

			break;
			case QUESTION_TYPE_LONGTEXT:
				fprintf(fileHtml,"textarea\",\n");

			break;
			case QUESTION_TYPE_NUMERIC:
				fprintf(fileHtml,"number\",\n");

			break;
			case QUESTION_TYPE_PASSWORD:
				fprintf(fileHtml,"password\",\n");

			break;
			case QUESTION_TYPE_DATE:
				fprintf(fileHtml,"date\",\n");

			break;
		}
		//add label
		fprintf(fileHtml,
		"						label : \"%s\",\n", questions[i]->title);

		//add type
		switch (questions[i]->defaultValue.type) {
			case TYPE_STRING:
				fprintf(fileHtml,
				"						value : \"%s\",\n",questions[i]->defaultValue.v_string ==NULL ? "" : questions[i]->defaultValue.v_string);
				break;
			case TYPE_FLOAT:
				fprintf(fileHtml,
				"						value : %f,\n",questions[i]->defaultValue.v_float);
				break;
			case TYPE_INTEGER:
				fprintf(fileHtml,
				"						value : %d,\n",questions[i]->defaultValue.v_integer);
				break;
			case TYPE_DATE:
				fprintf(fileHtml,
				"						value : new Date(\"%d-%d-%d\").toISOString().split('T')[0],\n",questions[i]->defaultValue.v_date->year,questions[i]->defaultValue.v_date->month,questions[i]->defaultValue.v_date->day);
				break;
			default:
				fprintf(fileHtml,
				"						value : null,\n");
				break;
		}
		//add required
		fprintf(fileHtml,
		"						required : %s,\n",questions[i]->required? "true":"false");

		_addGlitches(fileHtml,compilerState,i);
		fprintf(fileHtml,",\n");

		//add error
		fprintf(fileHtml,
		"						error: '',\n");



		_addOptions(fileHtml,compilerState,i);
		fprintf(fileHtml,",\n");

		//add showIf
		fprintf(fileHtml,
		"						showif : ");
		generateCondition(fileHtml,compilerState,questions[i]->showIf);
		fprintf(fileHtml,",\n");

		//add help message
		fprintf(fileHtml,
		"                        help: \"%s\",\n",questions[i]->help == NULL ? "" : questions[i]->help);

		//add placeholder
		fprintf(fileHtml,
		"                        placeholder: \"%s\",\n",questions[i]->placeholder == NULL ? "" : questions[i]->placeholder);

		//closer item
		fprintf(fileHtml,
		"					}");

	}

	//closer quesions variable
	fprintf(fileHtml,
	"\n				]);\n");

}
void _generateApp(FILE * fileHtml,FILE * fileGs,CompilerState * compilerState) {
	logDebugging(_logger,__FUNCTION__);

	fprintf(fileHtml,"	<script>");

	//define some variables and open app variable
	fprintf(fileHtml,
	"		const { createApp, ref , computed} = Vue;\n"
		"		const { createVuetify } = Vuetify;\n"
		"		const vuetify = createVuetify();\n"
		"		const app = createApp({\n"
		"			template: \"#app-template\",\n"
		"			setup() {\n"
		"\n");

	//set name Form
	fprintf(fileHtml,
	"				const formTitle = \"");
	fprintf(fileHtml,"%s",compilerState->formSpecifiers->title);
	fprintf(fileHtml,"\";\n");

	//set submitText
	fprintf(fileHtml,
	"				const submitText = \"");
	fprintf(fileHtml,"%s",compilerState->formConfig->submitText);
	fprintf(fileHtml,"\";\n");

	//manage steps
	fprintf(fileHtml,
	"				const currentStep = ref(0);\n"
		"				const stepHistory = ref([]);\n");
	fprintf(fileHtml,
	"				const closure = \"");
	fprintf(fileHtml,"%s",compilerState->formSpecifiers->closure);
	fprintf(fileHtml,"\"\n");

	_addSteps(fileHtml,compilerState);
	//manage steps
	fprintf(fileHtml,
	"				const stepsQty = steps.value.length;\n");

	if(compilerState->formConfig->safeAndSound) {
		fprintf(fileGs,
			"var SPREADSHEET_NAME = 'Form Answers';\n"
				"var SHEET_NAME = 'Answers';\n"
				"function getOrCreateSpreadsheet() {\n"
				"	var files = DriveApp.getFilesByName(SPREADSHEET_NAME);\n"
				"	if (files.hasNext()) {\n"
				"		var spreadsheet = SpreadsheetApp.open(files.next());\n"
				"	} else {\n"
				"		var spreadsheet = SpreadsheetApp.create(SPREADSHEET_NAME);\n"
				"	}\n"
				"	var sheet = spreadsheet.getSheetByName(SHEET_NAME);\n"
				"	if (!sheet) {\n"
				"		sheet = spreadsheet.insertSheet(SHEET_NAME);\n"
				"		sheet.appendRow([");
	}
	_addQuestions(fileHtml,fileGs,compilerState);

	//add Utils functions
	copyFile(PATH("main-elements/UTILS.txt"),fileHtml);

	fprintf(fileHtml,
	"\n				const submitForm = () => {\n"
		"					currentStep.value = steps.value.length - 1;\n");
	if(compilerState->formConfig->safeAndSound) {
		fprintf(fileGs,"]);\n"
			"	}\n"
			"	return sheet;\n"
			"}\n"
			"function submitFormData(formData) {\n"
			"	var sheet = getOrCreateSpreadsheet();\n"
			"	sheet.appendRow([");
		fprintf(fileHtml,
		"					var formData = {\n");
		for(size_t i =0;i<compilerState->tableQuestions->size;i++) {
			if(i!=0) {
				fprintf(fileGs,", ");
				fprintf(fileHtml,",\n");
			}
			fprintf(fileGs,"formData.question_%zu",i);
			fprintf(fileHtml,"						question_%zu: questions.value[%zu].value",i,i);
		}
		fprintf(fileGs,
			"]);\n"
				"}\n"
				"function doGet() {\n"
				"	return HtmlService.createHtmlOutputFromFile('Form');\n"
				"}");
		fprintf(fileHtml," || ''\n"
			"								};\n"
			"					google.script.run.submitFormData(formData);\n");
	}
	fprintf(fileHtml,
		"				};\n");

	//close setup
	fprintf(fileHtml,
				"				return { currentStep, questions, isStepValid, goesToEnd, nextStep, previousStep, submitForm, validateField, filteredOptions,sectionQuestions, stepSections, stepHistory, steps, formTitle, submitText };\n"
					"			}\n");

	//close app variable
	fprintf(fileHtml,
	"		});\n");

	//set vuetify
	fprintf(fileHtml,
	"        app.use(vuetify).mount('#app');\n");

	fprintf(fileHtml,
	"	</script>");
}

void _generateHeader(FILE * file) {
	copyFile(PATH("main-elements/HEADER.txt"),file);
}
void _generateBody(FILE * fileHtml,FILE * fileGs, CompilerState * compilerState) {
	logDebugging(_logger,__FUNCTION__);

	fprintf(fileHtml,"<body>\n");
	copyFile(PATH("main-elements/IDK_FILE.txt"),fileHtml);
	_generateApp(fileHtml,fileGs,compilerState);
	fprintf(fileHtml,"\n</body>\n");
	fprintf(fileHtml,"</html>\n");

}

/**
 * Generates an indentation string for the specified level.
 */
static char * _indentation(const unsigned int level) {
	return indentation(_indentationCharacter, level, _indentationSize);
}


void _generateEpilogue(FILE *file) {
	logDebugging(_logger,__FUNCTION__);
	copyFile(PATH("main-elements/FOOTER_SCRIPTS.txt"),file);
	logDebugging(_logger,"Script for footer generated");
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
	} else {
		QuestionType qType  = tableQuestions[identifier->index]->type ;
		if(qType != QUESTION_TYPE_CHECKBOX && qType != QUESTION_TYPE_RADIOS && qType != QUESTION_TYPE_SELECT_TEXT &&
		qType != QUESTION_TYPE_TEXT && qType != QUESTION_TYPE_PASSWORD && qType != QUESTION_TYPE_LONGTEXT && qType != QUESTION_TYPE_SELECT_NUMERIC){
			logError(_logger, "Bad reference: Identifier %s is not a string question", id);
			state->succeed = false;
			return false;
		}
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
	} else if (tableQuestions[identifier->index]->type != QUESTION_TYPE_DATE){
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
	} else if (tableQuestions[identifier->index]->type != QUESTION_TYPE_NUMERIC && tableQuestions[identifier->index]->type != QUESTION_TYPE_SELECT_NUMERIC){
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
            fprintf(file, "\"%d-%d-%d\"", function->v_date->year, function->v_date->month, function->v_date->day);
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
	logDebugging(_logger,__FUNCTION__);

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
	logDebugging(_logger,__FUNCTION__);

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
                    if (!assertNumericParameter(state, basicProp->function)) return;

                    fprintf(file, " longerThan( ");
                    generateId(file, state, basicProp->id);
                    fprintf(file, ", ");
                    generateLibFunctionParameter(file, state, basicProp->function);
                    fprintf(file, " ) ");
                    break;
                case LIB_FUNCTION_IS_SHORTER_THAN:
                    if (!assertStringId(state, basicProp->id)) return;
                    if (!assertNumericParameter(state, basicProp->function)) return;

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
            		break;
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
	logDebugging(_logger,__FUNCTION__);
    if (condition==NULL) return ;

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
    	default:
    		logError(_logger, "Invalid State: Condition type not found");
			state->succeed = false;
    		break;
    }
}

static void generateCondition(FILE * file, CompilerState * state, Condition * condition){
	logDebugging(_logger,__FUNCTION__);

	fprintf(file, " () => %s", condition==NULL ? "true" : "");
    generateConditionRec(file, state, condition);
}

/** PUBLIC FUNCTIONS */

#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>

#include <unistd.h>
void generate(CompilerState * compilerState) {
	initializeGeneratorModule();
	logDebugging(_logger,__FUNCTION__);
	const char *directory = "FlowForm";

	// Create directory if it does not exist
	struct stat st = {0};
	if (stat(directory, &st) == -1) {
		if (mkdir(directory, 0700) == -1) {
			logError(_logger, "Error creating FlowForm directory");
			rmdir(directory);
			compilerState->succeed=false;
			return;
		}
	}
	const char *fileOutputGs = "FlowForm/form.gs";
	FILE *fileGs = NULL;
	if(compilerState->formConfig->safeAndSound) {
		fileGs= fopen(fileOutputGs, "w");
		if (fileGs == NULL) {
			logError(_logger, "Error opening GS output file");
			compilerState->succeed=false;
			remove(fileOutputGs);
			rmdir(directory);
			return;
		}
	}
	const char *fileOutputHtml = "FlowForm/form.html";
	FILE *fileHtml = fopen(fileOutputHtml, "w");
	if (fileHtml == NULL) {
		logError(_logger, "Error opening HTML output file");
		compilerState->succeed=false;
		remove(fileOutputHtml);
		if(compilerState->formConfig->safeAndSound) {
			fclose(fileGs);
			remove(fileOutputGs);
		}
		rmdir(directory);
		return;
	}

	_generateHeader(fileHtml);
	_generateBody(fileHtml,fileGs, compilerState);
	_generateEpilogue(fileHtml);
	fprintf(fileHtml,"\n");
	_applyTheme(fileHtml, compilerState);
	logDebugging(_logger, "Generation is done.");

	fclose(fileHtml);
	fclose(fileGs);
	if (compilerState->succeed==false) {
		logError(_logger, "Error generation output file");
		remove(fileOutputHtml);
		remove(fileOutputGs);
		rmdir(directory);
		return;
	}
	shutdownGeneratorModule();
}
