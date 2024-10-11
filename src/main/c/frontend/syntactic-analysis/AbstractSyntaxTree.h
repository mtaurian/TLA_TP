#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */

typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;
typedef enum Types Types;
typedef enum LibFunctionType LibFunctionType;  
typedef enum BasicPropType BasicPropType;
typedef enum ConditionType ConditionType;
typedef enum QuestionType QuestionType;
typedef enum ListOptionsHasShowIf ListOptionsHasShowIf;
typedef enum ShowIfType ShowIfType;
typedef enum QuestionSubFgType QuestionSubFgType;
typedef enum QuestionSpType QuestionSpType;

typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;
typedef struct Question Question;
typedef struct Value Value;
typedef struct Date Date;
typedef struct LibFunction LibFunction;
typedef struct Condition Condition;
typedef struct BasicProp BasicProp;
typedef struct ShowIfDeclaration ShowIfDeclaration;
typedef struct ShowIfCall ShowIfCall;
typedef struct ShowIfOnScope ShowIfOnScope;
typedef struct ListOptions ListOptions;
typedef struct GlErrorFg GlErrorFg;
typedef struct GlitchFg GlitchFg;
typedef struct QuestionSubFg QuestionSubFg;
typedef struct  QuestionSp  QuestionSp;



typedef char Boolean;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum Types {
	TYPE_STRING,
	TYPE_FLOAT,
	TYPE_INTEGER,
	TYPE_DATE,
	TYPE_ID,
	TYPE_NONE,
	TYPE_VALUE,
	TYPE_NUMBER,
	TYPE_TRUE,
	TYPE_FALSE
};


enum QuestionType {
	QUESTION_TYPE_CHECKBOX,
	QUESTION_TYPE_RADIOS,
	QUESTION_TYPE_SELECT_TEXT,
	QUESTION_TYPE_SELECT_NUMERIC,
	QUESTION_TYPE_SELECT_DATE,
	QUESTION_TYPE_TEXT,
	QUESTION_TYPE_IMAGE,
	QUESTION_TYPE_DOCUMENT,
	QUESTION_TYPE_LONGTEXT,
	QUESTION_TYPE_NUMERIC,
	QUESTION_TYPE_PASSWORD,
	QUESTION_TYPE_DATE,
};
enum ExpressionType {
	ADDITION,
	DIVISION,
	FACTOR,
	MULTIPLICATION,
	SUBTRACTION
};

enum FactorType {
	CONSTANT,
	EXPRESSION
};

enum BasicPropType {
	BASIC_PROP_TYPE_BOOLEAN,
	BASIC_PROP_TYPE_FUNCTION
};

enum ConditionType {
	CONDITION_TYPE_AND,
	CONDITION_TYPE_OR,
	CONDITION_TYPE_NOT,
	CONDITION_TYPE_SINGLE,
	CONDITION_TYPE_BASIC
};

enum LibFunctionType {
	LIB_FUNCTION_IS_LOWER_THAN,			
	LIB_FUNCTION_IS_GREATER_THAN,
	LIB_FUNCTION_IS_LOWER_OR_EQUAL_TO,
	LIB_FUNCTION_IS_GREATER_OR_EQUAL_TO,
	LIB_FUNCTION_IS_LOWEST,
	LIB_FUNCTION_IS_GREATEST,
	LIB_FUNCTION_EQUALS,
	LIB_FUNCTION_IS_DIFFERENT_FROM,
	LIB_FUNCTION_IS_MULTIPLE_OF,
	LIB_FUNCTION_IS_DIVISOR_OF,
	LIB_FUNCTION_IS_IN_OPTIONS,
	LIB_FUNCTION_IS_TRUE,
	LIB_FUNCTION_IS_FALSE,
	LIB_FUNCTION_MATH_VALID,
	LIB_FUNCTION_SATISFIES,
	LIB_FUNCTION_LIKE,
	LIB_FUNCTION_CONTAINS,
	LIB_FUNCTION_DOES_LENGTH_EQUAL,
	LIB_FUNCTION_IS_LONGER_THAN,
	LIB_FUNCTION_IS_SHORTER_THAN,
	LIB_FUNCTION_IS_EMPTY,
	LIB_FUNCTION_IS_BEFORE,
	LIB_FUNCTION_IS_AFTER,
	LIB_FUNCTION_IS_WEEKEND
};

enum ListOptionsHasShowIf{
	CALL,
	SCOPE,
	NONE
};

enum ShowIfType{
	SHOW_IF_CALL,
	SHOW_IF_ON_SCOPE,
	SHOW_IF_DECLARATION
};
enum QuestionSubFgType {
	QUESTION_SUB_FG_SHOW_IF_CALL,
	QUESTION_SUB_FG_SHOW_IF_ON_SCOPE,
	QUESTION_SUB_FG_SHOW_IF_DECLARATION,
	QUESTION_SUB_FG_GLITCH
};

enum QuestionSpType{
	QUESTION_SP_DEFAULT_STRING,
	QUESTION_SP_DEFAULT_FLOAT,
	QUESTION_SP_DEFAULT_INTEGER,
	QUESTION_SP_QUESTION_TYPE,
	QUESTION_SP_OPTIONS,
	QUESTION_SP_TITLE,
	QUESTION_SP_HELP,					
	QUESTION_SP_PLACE_HOLDER,
	QUESTION_SP_REQUIRED
};

struct QuestionSubFg{
	union{
		ShowIfCall * showIfCalll;
		ShowIfDeclaration * showIfDeclaration;
		ShowIfOnScope * showIfOnScope;
		GlitchFg * glitchFg;
		ListOptions * options;
	};
	QuestionSubFgType type;
};
struct  QuestionSp{
	union{
		char * v_string;
		int v_integer;
		float v_float;
		ListOptions * options;
		QuestionType questionType;
	};
	QuestionSpType type;
};
struct ShowIfOnScope {
	Condition * condition;
};

struct ShowIfCall {
	char * conditionId;
};

struct ShowIfDeclaration {
	Condition * condtion;
	char * id;
};

struct ListOptions {
	
	Value * value;
	union{
		ShowIfCall * showIfCall;
		ShowIfOnScope * showIfOnScope;
	};
	ListOptions * nextOptions;
	ListOptionsHasShowIf hasShowIf;
};

struct BasicProp {
	union {
		Boolean truthValue;
		struct {
			char * id;
			LibFunction * function;
		};
	};
	BasicPropType type;
};

struct Condition {
	union {
		BasicProp * basicProp;
		struct {
			Condition * leftCondition;
			Condition * rightCondition;
		};
		Condition * condition;
	};
	ConditionType type;
};

struct GlErrorFg {
	char * message; 
	union{
		ShowIfCall * showIfCall;
		ShowIfOnScope * showIfOnScope;
	};
	ShowIfType showIfType;
};

struct GlitchFg  {
	GlErrorFg * error;
	GlitchFg * nextErrors; 
};

struct Factor {
	union {
		Constant * constant;
		Expression * expression;
	};
	FactorType type;
};

struct Constant {
	int value;
};

struct Expression {
	union {
		Factor * factor;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
	};
	ExpressionType type;
};


struct Program {
	Expression * expression;
};

struct Question {
	int * placeholder;
};

struct Date {
	int day;
	int month;
	int year;
};

struct Value {
	union {
		char * v_string;
		int v_integer;
		float v_float;
		Date  * v_date;
	};
	
	Types type;
};

struct LibFunction {

	union{
		float v_float;
		int v_integer;
		char * v_string;
		char * v_id;
		Date * v_date;
	};
	Types parameterType;
	LibFunctionType type;
};

/**
 * Node recursive destructors.
 */
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseFactor(Factor * factor);
void releaseProgram(Program * program);

#endif
