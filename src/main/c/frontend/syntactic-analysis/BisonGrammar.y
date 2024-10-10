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
	ValueOrId * valueOrId;
	DateOrId * dateOrId;
	IntegerOrId * integerOrId;
	StringOrId * stringOrId;
	Number * number;
	NumberOrId * numberOrId;
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
%token <token> DO
%token <token> TASK
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
%token <token> IS_IN_OPTIONS
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

%token <token> POINT
%token <token> COMMA

%token <string> ID
%token <string> STRING

%token <integer> INTEGER
%token <t_float> FLOAT

//maths and logic
%token <token> AND
%token <token> OR
%token <token> NOT
%token <token> ADD
%token <token> DIV
%token <token> MUL
%token <token> SUB
%token <token> MATH_EQUALS
%token <token> MATH_GRATHER
%token <token> MATH_LOWER
%token <token> TRUE
%token <token> FALSE

/** Non-terminals. */
/*
%type <form> form
%type <formFg> formFg
%type <formSubFg> formSubFg
%type <question> question
%type <config> config
%type <section> section 
%type <setp> step
%type <getaway> getaway
%type <transport> transport
%type <transports> transports
%type <glitch> glitch
%type <glError> glError
%type <do> do
%type <task> task
%type <stepFg> stepFg
%type <stepSp> stepSp
%type <formConfigFg> formConfigFg
%type <formConfigSp> formConfigSp
%type <themeSp> themeSp
%type <sectionFg> sectionFg
%type <sectionSubFg> sectionSubFg
%type <sectionSp> sectionSp
%type <questionFg> questionFg
%type <questionSp> questionSp
%type <questionSubFg> questionSubFg
%type <glitchFg> glitchFg
%type <glErrorFg> glErrorFg
%type <doFg> doFg
%type <showIf> showIf
%type <showIfDeclaration> showIfDeclaration
%type <showIfCall> showIfCall
%type <showIfOnScope> showIfOnScope
%type <condition> condition
%type <libFunction> libFunction 
*/
%type <number> number
%type <numberOrId> numberOrId
%type <stringOrId> stringOrId
%type <integerOrId> integerOrId
%type <date> date
%type <dateOrId> dateOrId
%type <value> value
%type <value> option

%type <valueOrId> valueOrId
/*
%type <options> options
%type <listOptions> listOptions
%type <optShowIf> optShowIf
%type <typeDefinition> typeDefinition
*/
/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV

%left OR
%left AND
%right NOT

%%

// IMPORTANT: To use λ in the following grammar, use the %empty symbol.
form : formFg 								{ currentCompilerState()->succeed = (0 < flexCurrentContext()) ? false : true; }
	;

formFg : formSubFg
	| form_sp
	| formSubFg formFg
	| form_sp formFg
	;

formSubFg : config 
	| step 
	| section
	| question //esto acepta preguntas sueltas aunque hayan pasos definidos. TODO: Podemos rebotarlo en back o complejizar mas esta grmática.
	;

form_sp : TITLE STRING
	| DESCRIPTION STRING
	| CLOSURE STRING
	;

question : 	QUESTION ID OPEN_BRACES questionFg CLOSE_BRACES		
	;									
config: CONFIG OPEN_BRACES formConfigFg CLOSE_BRACES
	;
section: SECTION OPEN_BRACES sectionFg CLOSE_BRACES
	;
step: STEP ID OPEN_BRACES stepFg CLOSE_BRACES
	;
getaway : GETAWAYCAR OPEN_BRACES transports CLOSE_BRACES
	;
transport : WHEN condition GOTO ID
	| WHEN condition GOTO END
	;
transports : transport
	| transport transports
	;
glitch : GLITCH OPEN_BRACES glitchFg CLOSE_BRACES 
	;
glError : GL_ERROR OPEN_BRACES glErrorFg CLOSE_BRACES 
	;
do : DO OPEN_BRACES doFg CLOSE_BRACES 
	;
task : TASK OPEN_BRACES CLOSE_BRACES  // todo
	;

stepFg : stepSp
	| getaway
	| section
	| question
	| section stepFg
	| stepSp stepFg
	| getaway stepFg
	| question stepFg
	;

stepSp: TITLE STRING
	| DESCRIPTION STRING
	;

formConfigFg : formConfigSp
	| formConfigSp formConfigFg
	;

formConfigSp: SUBMIT_TEXT STRING 
	| SAFE_AND_SOUND 
	| THEME themeSp 
	;

themeSp: DEBUT
	| FEARLESS
	| SPEAK_NOW
	| RED
	| NINETEEN_EIGHTY_NINE
	| REPUTATION
	| LOVER
	| FOLKLORE
	| EVERMORE
	| MIDNIGHTS
	| TTPD
	;

sectionFg: sectionSubFg
	| sectionSp
	| sectionSp sectionFg 
	| sectionSubFg sectionFg
	;

sectionSubFg: question
	| showIf
	;

sectionSp: TITLE STRING
	| DESCRIPTION STRING
	;

questionFg : questionSubFg
	| questionSp 
	| questionSp questionFg 
	| questionSubFg questionFg
	;

questionSp: DEFAULT STRING
	| DEFAULT FLOAT
	| DEFAULT INTEGER
	| TITLE STRING
	| typeDefinition
	| HELP STRING					
	| options
	| PLACE_HOLDER STRING
	| REQUIRED
	;

questionSubFg : showIf 
	| glitch
	| do
	;

glitchFg : glError glitchFg
	| glError
	;

glErrorFg : MESSAGE STRING showIfCall
	| MESSAGE STRING showIfOnScope
	;

doFg : task doFg
	| task
	;

showIf: showIfOnScope
	| showIfCall
	| showIfDeclaration
	;

showIfDeclaration : SHOWIF ID OPEN_BRACES condition CLOSE_BRACES
	;

showIfCall : SHOWIF OPEN_PARENTHESIS ID CLOSE_PARENTHESIS
	;

showIfOnScope : SHOWIF OPEN_BRACES condition CLOSE_BRACES 
	;

condition:TRUE
	| FALSE 
	| ID libFunction
	| condition AND condition
	| condition OR condition
	| NOT condition 
	| OPEN_PARENTHESIS condition CLOSE_PARENTHESIS
	;

libFunction: IS_LOWER_THAN numberOrId
	| IS_GREATER_THAN numberOrId
	| IS_LOWER_OR_EQUAL_TO numberOrId
	| IS_GREATER_OR_EQUAL_TO numberOrId
	| IS_LOWEST
	| IS_GREATEST
	| EQUALS valueOrId
	| IS_DIFFERENT_FROM valueOrId
	| IS_MULTIPLE_OF number
	| IS_DIVISOR_OF number
	| IS_IN_OPTIONS listOptions
	| IS_TRUE
	| IS_FALSE
	| MATH_VALID
	| SATISFIES
	| LIKE stringOrId
	| CONTAINS stringOrId
	| DOES_LENGTH_EQUAL integerOrId
	| IS_LONGER_THAN integerOrId
	| IS_SHORTER_THAN integerOrId
	| IS_EMPTY
	| IS_BEFORE dateOrId
	| IS_AFTER dateOrId
	| IS_WEEKEND
	;

number: INTEGER					{$$ = NumberIntegerSemanticAction($1);}
	| FLOAT						{$$ = NumberFloatSemanticAction($1);}
	;

numberOrId: number				{$$ = NumberOrIdNumberSemanticAction($1);}
	| ID						{$$ = NumberOrIdIdSemanticAction($1);}
	;

stringOrId: STRING				{$$ = StringOrIdStringSemanticAction($1);}
	| ID						{$$ = StringOrIdIdSemanticAction($1);}
	;

integerOrId: INTEGER			{$$ = IntegerOrIdIntegerSemanticAction($1);}
	| ID						{$$ = IntegerOrIdIdSemanticAction($1);}
	;

date : DATE OPEN_PARENTHESIS INTEGER[day] COMMA INTEGER[month] COMMA INTEGER[year] CLOSE_PARENTHESIS  		{$$ = CreateDateSemanticAction($day, $month, $year);}
	;

dateOrId: date					{$$ = DateOrIdDateSemanticAction($1);}
	| ID						{$$ = DateOrIdIdSemanticAction($1);}
	;

value: INTEGER 					{$$ = ValueIntegerSemanticAction($1);}
	| FLOAT						{$$ = ValueFloatSemanticAction($1);}
	| STRING					{$$ = ValueStringSemanticAction($1);}
	| date						{$$ = ValueDateSemanticAction($1);}
	;

valueOrId: value				{$$ = ValueOrIdValueSemanticAction($1);}
	| ID						{$$ = ValueOrIdIdSemanticAction($1);}
	;

options : OPTIONS OPEN_BRACKETS listOptions CLOSE_BRACKETS
	;

listOptions: option optShowIf
	| option optShowIf COMMA listOptions
	;

option : value					//default action is OK
	;

optShowIf : showIfCall 
	| showIfOnScope
	| %empty
	;

typeDefinition : TYPE CHECKBOX
	| TYPE RADIOS
	| TYPE SELECT TEXT
	| TYPE SELECT NUMERIC
	| TYPE SELECT DATE
	| TYPE TEXT
	| TYPE IMAGE
	| TYPE DOCUMENT
	| TYPE LONGTEXT
	| TYPE NUMERIC
	| TYPE PASSWORD
	| TYPE DATE
	;

/*
program: expression													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

expression: expression[left] ADD expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
	| expression[left] DIV expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
	| expression[left] MUL expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
	| expression[left] SUB expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
	| factor														{ $$ = FactorExpressionSemanticAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorSemanticAction($2); }
	| constant														{ $$ = ConstantFactorSemanticAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	;
*/
%%
