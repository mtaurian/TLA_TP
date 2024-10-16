%{

#include "BisonActions.h"

%}

// You touch this, and you die.
%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
	Token token;
	char * string;
	float t_float;

	/** Non-terminals. */

	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
	Question * question;
	Value * value;
	Date * date;
	LibFunction * libFunction;
	Condition * condition;
	QuestionType questionType;
	ShowIfDeclaration * showIfDeclaration;
	ShowIfCall * showIfCall;
	ShowIfOnScope * showIfOnScope;
	ListOptions * listOptions;
	GlErrorFg * glErrorFg;
	GlitchFg * glitchFg;
	QuestionSubFg *questionSubFg;
	QuestionSp * questionSp;
	QuestionFg * questionFg;
	SectionSp * sectionSp;
	SectionSubFg * sectionSubFg;
	SectionFg * sectionFg;
	StepSp * stepSp;
	StepFg * stepFg;
	Step * step;
	ThemeSp themeSp;
	Transport * transport;
	Transports * transports;
	FormConfigSp * formConfigSp;
	FormConfigFg * formConfigFg;
	FormSp * formSp;
	FormSubFg * formSubFg;
	FormFg * formFg;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach. To use this mechanism, the AST must be translated into
 * another structure.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseFactor($$); } <factor>
%destructor { releaseProgram($$); } <program>
*/

/** Terminals. */

//the ones we are actually using:
%token <token> UNKNOWN
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> CONFIG
%token <token> STEP
%token <token> SECTION
%token <token> QUESTION
%token <token> GLITCH
%token <token> GL_ERROR
%token <token> GETAWAYCAR
%token <token> SHOWIF
%token <token> CLOSURE
%token <token> SUBMIT_TEXT
%token <token> SAFE_AND_SOUND
%token <token> THEME
%token <token> TITLE
%token <token> DESCRIPTION
%token <token> DEFAULT
%token <token> TYPE
%token <token> HELP
%token <token> OPTIONS
%token <token> PLACE_HOLDER
%token <token> MESSAGE
%token <token> REQUIRED

%token <token> OPEN_BRACKETS
%token <token> CLOSE_BRACKETS
%token <token> OPEN_BRACES
%token <token> CLOSE_BRACES

%token <token> IS_LOWER_THAN
%token <token> IS_GREATER_THAN
%token <token> IS_LOWER_OR_EQUAL_TO
%token <token> IS_GREATER_OR_EQUAL_TO
%token <token> IS_LOWEST
%token <token> IS_GREATEST
%token <token> EQUALS
%token <token> IS_DIFFERENT_FROM
%token <token> IS_MULTIPLE_OF
%token <token> IS_DIVISOR_OF
%token <token> IS_TRUE
%token <token> IS_FALSE
%token <token> MATH_VALID
%token <token> SATISFIES
%token <token> LIKE
%token <token> CONTAINS
%token <token> DOES_LENGTH_EQUAL
%token <token> IS_LONGER_THAN
%token <token> IS_SHORTER_THAN
%token <token> IS_EMPTY
%token <token> IS_BEFORE
%token <token> IS_AFTER
%token <token> IS_WEEKEND

%token <token> WHEN
%token <token> GOTO
%token <token> END

%token <token> CHECKBOX
%token <token> RADIOS
%token <token> SELECT
%token <token> TEXT
%token <token> IMAGE
%token <token> DOCUMENT
%token <token> LONGTEXT
%token <token> NUMERIC
%token <token> PASSWORD
%token <token> DATE

%token <token> DEBUT
%token <token> FEARLESS
%token <token> SPEAK_NOW
%token <token> RED
%token <token> NINETEEN_EIGHTY_NINE
%token <token> REPUTATION
%token <token> LOVER
%token <token> FOLKLORE
%token <token> EVERMORE
%token <token> MIDNIGHTS
%token <token> TTPD

%token <token> COMMA

%token <string> ID
%token <string> STRING

%token <integer> INTEGER
%token <t_float> FLOAT

//maths and logic
%token <token> AND
%token <token> OR
%token <token> NOT
%token <token> TRUE
%token <token> FALSE

/** Non-terminals. */

%type <formFg> formFg
%type <formSubFg> formSubFg
%type <formSp> formSp
%type <formConfigFg> config
%type <formConfigFg> formConfigFg
%type <formConfigSp> formConfigSp
%type <step> step
%type <stepFg> stepFg
%type <transports> getaway
%type <transports> transports
%type <transport> transport
%type <themeSp> themeSp
%type <stepSp> stepSp
%type <sectionFg> section 
%type <sectionFg> sectionFg
%type <sectionSubFg> sectionSubFg
%type <sectionSp> sectionSp
%type <question> question
%type <questionFg> questionFg
%type <questionSp> questionSp
%type <questionSubFg> questionSubFg
%type <glitchFg> glitch
%type <glitchFg> glitchFg
%type <glErrorFg> glError
%type <glErrorFg> glErrorFg
%type <showIfOnScope> showIfOnScope
%type <showIfCall> showIfCall
%type <showIfDeclaration> showIfDeclaration
%type <condition> condition
%type <libFunction> libFunction 
%type <date> date
%type <value> value



%type <listOptions> options

%type <listOptions> listOptions

%type <questionType> questionType

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */

%left OR
%left AND
%right NOT

%%

// IMPORTANT: To use λ in the following grammar, use the %empty symbol.

formFg : formSubFg			{$$ = FormFgSubFgSemanticAction($1,currentCompilerState());}
	| formSp				{$$ = FormFgSpSemanticAction($1,currentCompilerState());}
	| formSubFg formFg		{$$ = FormFgExtendedSubFgSemanticAction($1,$2,currentCompilerState());}
	| formSp formFg			{$$ = FormFgExtendedSpSemanticAction($1,$2,currentCompilerState());}
	;

formSubFg : config			{$$ = FormSubFgConfigSemanticAction($1);}
	| step 					{$$ = FormSubFgStepSemanticAction($1);}	
	| question 				{$$ = FormSubFgQuestionSemanticAction($1);}
	| section				{$$ = FormSubFgSectionSemanticAction($1);}
	;				

formSp : TITLE STRING															{$$ = FormSpSemanticAction($2, FORM_SP_TITLE);}
	| DESCRIPTION STRING														{$$ = FormSpSemanticAction($2, FORM_SP_DESCRIPTION);}
	| CLOSURE STRING															{$$ = FormSpSemanticAction($2, FORM_SP_CLOSURE);}
	;

question : 	QUESTION ID OPEN_BRACES questionFg CLOSE_BRACES						{$$ = QuestionSemanticAction($2,$4);}
	;									
config: CONFIG OPEN_BRACES formConfigFg CLOSE_BRACES							{$$ = $3;}
	;
section: SECTION OPEN_BRACES sectionFg CLOSE_BRACES								{$$ = $3;}
	;
step: STEP ID OPEN_BRACES stepFg CLOSE_BRACES									{$$ = StepSemanticAction($2,$4);}
	;
getaway : GETAWAYCAR OPEN_BRACES transports CLOSE_BRACES						{$$ = $3;}
	;
transport : WHEN condition GOTO ID												{$$ = TransportSemanticAction($2, $4, 0);}
	| WHEN condition GOTO END													{$$ = TransportSemanticAction($2, 0x0, 1);}
	;
transports : transport															{$$ = TransportsSemanticAction($1);}	
	| transport transports														{$$ = TransportsExtendedSemanticAction($1, $2);}
	;

formConfigFg : formConfigSp														{$$ = FormConfigFgSemanticAction($1);}
	| formConfigSp formConfigFg													{$$ = FormConfigFgExtendedSemanticAction($1, $2);}
	;

formConfigSp: SUBMIT_TEXT STRING 												{$$ = FormConfigSpSubmitSemanticAction($2);}
	| SAFE_AND_SOUND 															{$$ = FormConfigSpSafeAndSoundSemanticAction();}
	| THEME themeSp 															{$$ = FormConfigSpThemeSemanticAction($2);}
	;

themeSp: DEBUT						{$$= THEME_DEBUT;}
	| FEARLESS						{$$= THEME_FEARLESS;}
	| SPEAK_NOW						{$$= THEME_SPEAK_NOW;}
	| RED							{$$= THEME_RED;}
	| NINETEEN_EIGHTY_NINE			{$$= THEME_NINETEEN_EIGHTY_NINE;}
	| REPUTATION					{$$= THEME_REPUTATION;}
	| LOVER							{$$= THEME_LOVER;}
	| FOLKLORE						{$$= THEME_FOLKLORE;}
	| EVERMORE						{$$= THEME_EVERMORE;}
	| MIDNIGHTS						{$$= THEME_MIDNIGHTS;}
	| TTPD							{$$= THEME_TTPD;}
	;

stepFg : stepSp											{$$=StepFgStepSpSemanticAction($1);}
	| getaway						{$$=StepFgGetawaySemanticAction($1);}
	| section						{$$=StepFgSectionSemanticAction($1);}
	| question						{$$=StepFgQuestionSemanticAction($1);}
	| stepSp stepFg					{$$=StepFgStepSpExtendedSemanticAction($1,$2);}
	| getaway stepFg				{$$=StepFgGetawayExtendedSemanticAction($1,$2);}
	| section stepFg				{$$=StepFgSectionExtendedSemanticAction($1,$2);}
	| question stepFg				{$$=StepFgQuestionExtendedSemanticAction($1,$2);}
	;

stepSp: TITLE STRING									{$$ = StepSpSemanticAction(STEP_SP_TITLE, $2);}
	| DESCRIPTION STRING								{$$ = StepSpSemanticAction(STEP_SP_TITLE, $2);}
	;

sectionFg: sectionSubFg									{$$ = SectionFgSubFgSemanticAction($1);}
	| sectionSp											{$$ = SectionFgSpSemanticAction($1);}
	| sectionSubFg sectionFg							{$$ = SectionFgExtendedSubFgSemanticAction($1, $2);}
	| sectionSp sectionFg 								{$$ = SectionFgExtendedSpSemanticAction($1, $2);}
	;

sectionSubFg: question									{$$ = SectionSubFgQuestionSemanticAction($1);}
	| showIfOnScope										{$$ = SectionSubFgShowIfOnScopeSemanticAction($1);}
	| showIfDeclaration									{$$ = SectionSubFgShowIfDeclarationSemanticAction($1);}
	| showIfCall										{$$ = SectionSubFgShowIfCallSemanticAction($1);}									
	;

sectionSp: TITLE STRING 								{$$ = SectionSpSemanticAction(SECTION_SP_TITLE, $2);}
	| DESCRIPTION STRING								{$$ = SectionSpSemanticAction(SECTION_SP_DESCRIPTION, $2);}
	;

questionFg : questionSubFg								{$$ = QuestionFgSubFgSemanticAction($1);}
	| questionSp 										{$$ = QuestionFgSpSemanticAction($1);}
	| questionSubFg questionFg							{$$ = QuestionFgExtendedSubFgSemanticAction($1,$2);}
	| questionSp questionFg 							{$$ = QuestionFgExtendedSpSemanticAction($1,$2);}
	;

questionSp: DEFAULT STRING								{$$ = QuestionSpStringSemanticAction(QUESTION_SP_DEFAULT_STRING,$2);}
	| DEFAULT FLOAT										{$$ = QuestionSpDefaultFloatSemanticAction($2);}
	| DEFAULT INTEGER									{$$ = QuestionSpDefaultIntegerSemanticAction($2);}
	| questionType										{$$ = QuestionSpQuestionTypeSemanticAction($1);}
	| options											{$$ = QuestionSpOptionSemanticAction($1);}
	| TITLE STRING										{$$ = QuestionSpStringSemanticAction(QUESTION_SP_TITLE,$2);}
	| HELP STRING										{$$ = QuestionSpStringSemanticAction(QUESTION_SP_HELP,$2);}
	| PLACE_HOLDER STRING								{$$ = QuestionSpStringSemanticAction(QUESTION_SP_PLACE_HOLDER,$2);}
	| REQUIRED											{$$ = QuestionSpRequiredSemanticAction();}
	;

questionSubFg : showIfOnScope							{$$ = QuestionSubFgShowIfOnScopeSemanticAction($1);}
	| showIfCall										{$$ = QuestionSubFgShowIfCallSemanticAction($1);}
	| showIfDeclaration									{$$ = QuestionSubFgShowIfDeclarationSemanticAction($1);}
	| glitch											{$$ = QuestionSubFgGlitchSemanticAction($1);}
	;

glitch : GLITCH OPEN_BRACES glitchFg CLOSE_BRACES 		{$$ = $3;}
	;
glError : GL_ERROR OPEN_BRACES glErrorFg CLOSE_BRACES 	{$$ = $3;}
	;

glitchFg : glError glitchFg								{$$ = GlitchFgExtendedSemanticAction($1, $2);}
	| glError											{$$ = GlitchFgSemanticAction($1);}
	;

glErrorFg : MESSAGE STRING showIfCall									{$$ = GlErrorFgShowIfCallSemanticAction($2, $3);}
	| MESSAGE STRING showIfOnScope  									{$$ = GlErrorFgShowIfOnScopeSemanticAction($2, $3);}
	;

showIfDeclaration : SHOWIF ID OPEN_BRACES condition CLOSE_BRACES 		{$$ = ShowIfDeclarationSemanticAction($2, $4);}
	;

showIfCall : SHOWIF OPEN_PARENTHESIS ID CLOSE_PARENTHESIS				{ $$ = ShowIfCallSemanticAction($3);}
	;

showIfOnScope : SHOWIF OPEN_BRACES condition CLOSE_BRACES 				{ $$ = ShowIfOnScopeSemanticAction($3);}
	;

condition: TRUE												{$$ = ConditionBooleanSemanticAction(1);}
	| FALSE 												{$$ = ConditionBooleanSemanticAction(0);}
	| ID libFunction										{$$ = ConditionFunctionSemanticAction($1, $2);}
	| condition AND condition								{$$ = ConditionAndSemanticAction($1, $3);}
	| condition OR condition								{$$ = ConditionOrSemanticAction($1, $3);}
	| NOT condition 										{$$ = ConditionNotSemanticAction($2);}
	| OPEN_PARENTHESIS condition CLOSE_PARENTHESIS			{$$ = ConditionParenthesisSemanticAction($2);}
	;

libFunction: IS_LOWER_THAN INTEGER 			 	{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_IS_LOWER_THAN,$2);}
	| IS_LOWER_THAN FLOAT      					{$$ = LibFunctionFloatSemanticAction(LIB_FUNCTION_IS_LOWER_THAN,$2);}
	| IS_LOWER_THAN ID							{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_LOWER_THAN,$2);}
	| IS_GREATER_THAN INTEGER  					{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_IS_GREATER_THAN,$2);}
	| IS_GREATER_THAN FLOAT 					{$$ = LibFunctionFloatSemanticAction(LIB_FUNCTION_IS_GREATER_THAN,$2);}
	| IS_GREATER_THAN ID						{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_GREATER_THAN,$2);}
	| IS_LOWER_OR_EQUAL_TO INTEGER 				{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_IS_LOWER_OR_EQUAL_TO,$2);}
	| IS_LOWER_OR_EQUAL_TO FLOAT 				{$$ = LibFunctionFloatSemanticAction(LIB_FUNCTION_IS_LOWER_OR_EQUAL_TO,$2);}
	| IS_LOWER_OR_EQUAL_TO ID 					{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_LOWER_OR_EQUAL_TO,$2);}
	| IS_GREATER_OR_EQUAL_TO INTEGER 			{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_IS_GREATER_OR_EQUAL_TO,$2);}
	| IS_GREATER_OR_EQUAL_TO FLOAT				{$$ = LibFunctionFloatSemanticAction(LIB_FUNCTION_IS_GREATER_OR_EQUAL_TO,$2);}
	| IS_GREATER_OR_EQUAL_TO ID 				{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_GREATER_OR_EQUAL_TO,$2);}
	| IS_LOWEST 								{$$ = LibFunctionNoneSemanticAction(LIB_FUNCTION_IS_LOWEST);}
	| IS_GREATEST 								{$$ = LibFunctionNoneSemanticAction(LIB_FUNCTION_IS_GREATEST);}
	| EQUALS INTEGER 							{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_EQUALS,$2);}
	| EQUALS FLOAT 								{$$ = LibFunctionFloatSemanticAction(LIB_FUNCTION_EQUALS,$2);}
	| EQUALS STRING 							{$$ = LibFunctionStringSemanticAction(LIB_FUNCTION_EQUALS,$2);}
	| EQUALS date								{$$ = LibFunctionDateSemanticAction(LIB_FUNCTION_EQUALS,$2);}
	| EQUALS ID 								{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_EQUALS,$2);}
	| IS_DIFFERENT_FROM INTEGER 				{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_IS_DIFFERENT_FROM,$2);}
	| IS_DIFFERENT_FROM FLOAT					{$$ = LibFunctionFloatSemanticAction(LIB_FUNCTION_IS_DIFFERENT_FROM,$2);}
	| IS_DIFFERENT_FROM STRING					{$$ = LibFunctionStringSemanticAction(LIB_FUNCTION_IS_DIFFERENT_FROM,$2);}
	| IS_DIFFERENT_FROM date 					{$$ = LibFunctionDateSemanticAction(LIB_FUNCTION_IS_DIFFERENT_FROM,$2);}
	| IS_DIFFERENT_FROM ID  					{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_DIFFERENT_FROM,$2);}
	| IS_MULTIPLE_OF INTEGER					{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_IS_MULTIPLE_OF,$2);}
	| IS_MULTIPLE_OF FLOAT						{$$ = LibFunctionFloatSemanticAction(LIB_FUNCTION_IS_MULTIPLE_OF,$2);}
	| IS_MULTIPLE_OF ID							{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_MULTIPLE_OF,$2);}
	| IS_DIVISOR_OF INTEGER 					{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_IS_DIVISOR_OF,$2);}
	| IS_DIVISOR_OF FLOAT						{$$ = LibFunctionFloatSemanticAction(LIB_FUNCTION_IS_DIVISOR_OF,$2);}
	| IS_DIVISOR_OF ID 							{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_DIVISOR_OF,$2);}
	| IS_TRUE 									{$$ = LibFunctionNoneSemanticAction(LIB_FUNCTION_IS_TRUE);}
	| IS_FALSE 									{$$ = LibFunctionNoneSemanticAction(LIB_FUNCTION_IS_FALSE);}
	| MATH_VALID 								{$$ = LibFunctionNoneSemanticAction(LIB_FUNCTION_MATH_VALID);}
	| SATISFIES 								{$$ = LibFunctionNoneSemanticAction(LIB_FUNCTION_SATISFIES);}
	| LIKE STRING								{$$ = LibFunctionStringSemanticAction(LIB_FUNCTION_LIKE,$2);}
	| LIKE ID									{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_LIKE,$2);}
	| CONTAINS STRING							{$$ = LibFunctionStringSemanticAction(LIB_FUNCTION_CONTAINS,$2);}
	| CONTAINS ID								{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_CONTAINS,$2);}
	| DOES_LENGTH_EQUAL INTEGER 				{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_DOES_LENGTH_EQUAL,$2);}
	| DOES_LENGTH_EQUAL ID 						{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_DOES_LENGTH_EQUAL,$2);}
	| IS_LONGER_THAN INTEGER 					{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_IS_LONGER_THAN,$2);}
	| IS_LONGER_THAN ID							{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_LONGER_THAN,$2);}
	| IS_SHORTER_THAN INTEGER 					{$$ = LibFunctionIntegerSemanticAction(LIB_FUNCTION_IS_SHORTER_THAN,$2);}
	| IS_SHORTER_THAN ID 						{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_SHORTER_THAN,$2);}
	| IS_EMPTY 									{$$ = LibFunctionNoneSemanticAction(LIB_FUNCTION_IS_EMPTY);}
	| IS_BEFORE date							{$$ = LibFunctionDateSemanticAction(LIB_FUNCTION_IS_BEFORE,$2);}
	| IS_BEFORE ID								{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_BEFORE,$2);}
	| IS_AFTER date								{$$ = LibFunctionDateSemanticAction(LIB_FUNCTION_IS_AFTER,$2);}
	| IS_AFTER ID								{$$ = LibFunctionIdSemanticAction(LIB_FUNCTION_IS_AFTER,$2);}
	| IS_WEEKEND								{$$ = LibFunctionNoneSemanticAction(LIB_FUNCTION_IS_WEEKEND);}
	;

date : DATE OPEN_PARENTHESIS INTEGER[day] COMMA INTEGER[month] COMMA INTEGER[year] CLOSE_PARENTHESIS  		{$$ = CreateDateSemanticAction($day, $month, $year);}
	;

value: INTEGER 					{$$ = ValueIntegerSemanticAction($1);}
	| FLOAT						{$$ = ValueFloatSemanticAction($1);}
	| STRING					{$$ = ValueStringSemanticAction($1);}
	| date						{$$ = ValueDateSemanticAction($1);}
	;


options : OPTIONS OPEN_BRACKETS listOptions CLOSE_BRACKETS			{$$ = $3;}
	;

listOptions: value showIfCall						{$$ = ListOptionsShowIfCallSemanticAction($1,$2);}
	| value showIfOnScope							{$$ = ListOptionsShowIfOnScopeSemanticAction($1,$2);}
	| value											{$$ = ListOptionsSemanticAction($1);}
	| value showIfCall COMMA listOptions      		{$$ = ListOptionsExtendedShowIfCallSemanticAction($1,$2,$4);}
	| value showIfOnScope COMMA listOptions			{$$ = ListOptionsExtendedShowIfOnScopeSemanticAction($1,$2,$4);}
	| value COMMA listOptions						{$$ = ListOptionsExtendedSemanticAction($1,$3);}
	;


	;

questionType : TYPE CHECKBOX   		{$$ = QUESTION_TYPE_CHECKBOX;}
	| TYPE RADIOS					{$$ = QUESTION_TYPE_RADIOS;}
	| TYPE SELECT TEXT				{$$ = QUESTION_TYPE_SELECT_TEXT;}
	| TYPE SELECT NUMERIC			{$$ = QUESTION_TYPE_SELECT_NUMERIC;}
	| TYPE SELECT DATE				{$$ = QUESTION_TYPE_SELECT_DATE;}
	| TYPE TEXT						{$$ = QUESTION_TYPE_TEXT;}
	| TYPE IMAGE					{$$ = QUESTION_TYPE_IMAGE;}
	| TYPE DOCUMENT					{$$ = QUESTION_TYPE_DOCUMENT;}
	| TYPE LONGTEXT					{$$ = QUESTION_TYPE_LONGTEXT;}
	| TYPE NUMERIC					{$$ = QUESTION_TYPE_NUMERIC;}
	| TYPE PASSWORD					{$$ = QUESTION_TYPE_PASSWORD;}
	| TYPE DATE						{$$ = QUESTION_TYPE_DATE;}


%%
