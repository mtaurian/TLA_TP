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

%type <form> form
%type <form_fg> form_fg
%type <form_sub_fg> form_sub_fg
%type <question> question
%type <config> config
%type <section> section 
%type <setp> step
%type <getaway> getaway
%type <transport> transport
%type <transports> transports
%type <glitch> glitch
%type <gl_error> gl_error
%type <do> do
%type <task> task
%type <step_fg> step_fg
%type <step_sp> step_sp
%type <form_config_fg> form_config_fg
%type <form_config_sp> form_config_sp
%type <theme_sp> theme_sp
%type <section_fg> section_fg
%type <section_sub_fg> section_sub_fg
%type <section_sp> section_sp
%type <question_fg> question_fg
%type <question_sp> question_sp
%type <question_sub_fg> question_sub_fg
%type <glitch_fg> glitch_fg
%type <gl_error_fg> gl_error_fg
%type <do_fg> do_fg
%type <showif> showif
%type <showif_declaration> showif_declaration
%type <showif_call> showif_call
%type <showif_on_scope> showif_on_scope
%type <condition> condition
%type <lib_function> lib_function 
%type <number> number
%type <number_or_id> number_or_id
%type <string_or_id> string_or_id
%type <integer_or_id> integer_or_id
%type <date> date
%type <date_or_id> date_or_id
%type <value> value
%type <value_or_id> value_or_id
%type <options> options
%type <list_options> list_options
%type <value> option
%type <opt_showif> opt_showif
%type <type_definition> type_definition
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
form : form_fg 								{ currentCompilerState()->succeed = (0 < flexCurrentContext()) ? false : true; }
	;

form_fg : form_sub_fg
	| form_sp
	| form_sub_fg form_fg
	| form_sp form_fg
	;

form_sub_fg : config 
	| step 
	| section
	| question //esto acepta preguntas sueltas aunque hayan pasos definidos. TODO: Podemos rebotarlo en back o complejizar mas esta grmática.
	;

form_sp : TITLE STRING
	| DESCRIPTION STRING
	| CLOSURE STRING
	;

question : 	QUESTION ID OPEN_BRACES question_fg CLOSE_BRACES		
	;									
config: CONFIG OPEN_BRACES form_config_fg CLOSE_BRACES
	;
section: SECTION OPEN_BRACES section_fg CLOSE_BRACES
	;
step: STEP ID OPEN_BRACES step_fg CLOSE_BRACES
	;
getaway : GETAWAYCAR OPEN_BRACES transports CLOSE_BRACES
	;
transport : WHEN condition GOTO ID
	| WHEN condition GOTO END
	;
transports : transport
	| transport transports
	;
glitch : GLITCH OPEN_BRACES glitch_fg CLOSE_BRACES 
	;
gl_error : GL_ERROR OPEN_BRACES gl_error_fg CLOSE_BRACES 
	;
do : DO OPEN_BRACES do_fg CLOSE_BRACES 
	;
task : TASK OPEN_BRACES CLOSE_BRACES  // todo
	;

step_fg : step_sp
	| getaway
	| section
	| question
	| section step_fg
	| step_sp step_fg
	| getaway step_fg
	| question step_fg
	;

step_sp: TITLE STRING
	| DESCRIPTION STRING
	;

form_config_fg : form_config_sp
	| form_config_sp form_config_fg
	;

form_config_sp: SUBMIT_TEXT STRING 
	| SAFE_AND_SOUND 
	| THEME theme_sp 
	;

theme_sp: DEBUT
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

section_fg: section_sub_fg
	| section_sp
	| section_sp section_fg 
	| section_sub_fg section_fg
	;

section_sub_fg: question
	| showif
	;

section_sp: TITLE STRING
	| DESCRIPTION STRING
	;

question_fg : question_sub_fg
	| question_sp 
	| question_sp question_fg 
	| question_sub_fg question_fg
	;

question_sp: DEFAULT STRING
	| DEFAULT FLOAT
	| DEFAULT INTEGER
	| TITLE STRING
	| type_definition
	| HELP STRING					
	| options
	| PLACE_HOLDER STRING
	| REQUIRED
	;

question_sub_fg : showif 
	| glitch
	| do
	;

glitch_fg : gl_error glitch_fg
	| gl_error
	;

gl_error_fg : MESSAGE STRING showif_call
	| MESSAGE STRING showif_on_scope
	;

do_fg : task do_fg
	| task
	;

showif: showif_on_scope
	| showif_call
	| showif_declaration
	;

showif_declaration : SHOWIF ID OPEN_BRACES condition CLOSE_BRACES
	;

showif_call : SHOWIF OPEN_PARENTHESIS ID CLOSE_PARENTHESIS
	;

showif_on_scope : SHOWIF OPEN_BRACES condition CLOSE_BRACES 
	;

condition:TRUE
	| FALSE 
	| ID lib_function
	| condition AND condition
	| condition OR condition
	| NOT condition 
	| OPEN_PARENTHESIS condition CLOSE_PARENTHESIS
	;

lib_function: IS_LOWER_THAN number_or_id
	| IS_GREATER_THAN number_or_id
	| IS_LOWER_OR_EQUAL_TO number_or_id
	| IS_GREATER_OR_EQUAL_TO number_or_id
	| IS_LOWEST
	| IS_GREATEST
	| EQUALS value_or_id
	| IS_DIFFERENT_FROM value_or_id
	| IS_MULTIPLE_OF number
	| IS_DIVISOR_OF number
	| IS_IN_OPTIONS list_options
	| IS_TRUE
	| IS_FALSE
	| MATH_VALID
	| SATISFIES
	| LIKE string_or_id
	| CONTAINS string_or_id
	| DOES_LENGTH_EQUAL integer_or_id
	| IS_LONGER_THAN integer_or_id
	| IS_SHORTER_THAN integer_or_id
	| IS_EMPTY
	| IS_BEFORE date_or_id
	| IS_AFTER date_or_id
	| IS_WEEKEND
	;

number: INTEGER
	| FLOAT
	;

number_or_id: number
	| ID
	;

string_or_id: STRING
	| ID
	;

integer_or_id: INTEGER
	| ID
	;

date : DATE OPEN_PARENTHESIS INTEGER COMMA INTEGER COMMA INTEGER CLOSE_PARENTHESIS
	;

date_or_id: date
	| ID
	;

value: INTEGER 
	| FLOAT
	| STRING
	| date
	;

value_or_id: value
	| ID
	;

options : OPTIONS OPEN_BRACKETS list_options CLOSE_BRACKETS
	;

list_options: option opt_showif
	| option opt_showif COMMA list_options
	;

option : STRING 
	| INTEGER 
	| FLOAT
	| date
	;

opt_showif : showif_call 
	| showif_on_scope
	| %empty
	;

type_definition : TYPE CHECKBOX
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
