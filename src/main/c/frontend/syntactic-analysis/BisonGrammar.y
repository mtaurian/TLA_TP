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
%token <token> IS_EMPTY

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


/** Non-terminals. */
%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <question> question

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


question : 	QUESTION ID OPEN_BRACES  question_fg CLOSE_BRACES	
	;									
glitch : GLITCH OPEN_BRACES glitch_fg CLOSE_BRACES 
	;
gl_error : GL_ERROR OPEN_BRACES gl_error_fg CLOSE_BRACES 
	;
do : DO OPEN_BRACES do_fg CLOSE_BRACES 
	;
task : TASK OPEN_BRACES CLOSE_BRACES  // todo
	;

question_fg : question_sub_fg
	| question_sp 
	| question_sub_fg question_fg
	| question_sp question_fg
	;

question_sub_fg : showif 
	| glitch
	| do
	;

glitch_fg : gl_error
	;

gl_error_fg : condition MESSAGE
	| MESSAGE condition
	;

do_fg : task
	;

showif : SHOWIF OPEN_BRACES condition CLOSE_BRACES 
	;

condition: ID lib_function value logic_conector condition
	| ID lib_function value 
	| OPEN_PARENTHESIS condition CLOSE_PARENTHESIS
	;

lib_function:
//TODO: list alllibFunctions
	;

value: INTEGER 
	| FLOAT
	| STRING
	| DATE	
	;

logic_conector : AND 
	| OR 
	;

question_sp: DEFAULT STRING
	| DEFAULT FLOAT
	| DEFAULT INTEGER
	| TITLE STRING
	| type_definition
	| HELP STRING					
	| options
	| PLACE_HOLDER STRING
	;

options : OPEN_BRACKETS list_options CLOSE_BRACKETS
	;

list_options: option
	| option COMMA list_options
	;

option : STRING 
	| INTEGER 
	| FLOAT
	;

type_definition : TYPE CHECKBOX
	| TYPE RADIOS
	| TYPE SELECT
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
