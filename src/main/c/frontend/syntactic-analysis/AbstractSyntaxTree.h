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


struct Constant {
	int value;
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


struct Factor {
	union {
		Constant * constant;
		Expression * expression;
	};
	FactorType type;
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
