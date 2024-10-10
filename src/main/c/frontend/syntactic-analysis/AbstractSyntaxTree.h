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
typedef enum ValueType ValueType;
typedef enum ValueOrIdType ValueOrIdType;
typedef enum DateOrIdType DateOrIdType;
typedef enum IntegerOrIdType IntegerOrIdType;
typedef enum StringOrIdType StringOrIdType;

typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;
typedef struct Question Question;
typedef struct Value Value;
typedef struct Date Date;
typedef struct ValueOrId ValueOrId;
typedef struct DateOrId DateOrId;
typedef struct IntegerOrId IntegerOrId;
typedef struct StringOrId StringOrId;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum ExpressionType {
	ADDITION,
	DIVISION,
	FACTOR,
	MULTIPLICATION,
	SUBTRACTION
};

enum ValueType {
	VALUE_TYPE_STRING,
	VALUE_TYPE_INTEGER,
	VALUE_TYPE_FLOAT, 
	VALUE_TYPE_DATE
};
enum ValueOrIdType {
	VALUE_OR_ID_TYPE_VALUE,
	VALUE_OR_ID_TYPE_ID
};

enum DateOrIdType {
	DATE_OR_ID_TYPE_ID,
	DATE_OR_ID_TYPE_DATE
};

enum IntegerOrIdType {
	INTEGER_OR_ID_TYPE_ID,
	INTEGER_OR_ID_TYPE_INTEGER
};

enum StringOrIdType {
	STRING_OR_ID_TYPE_ID,
	STRING_OR_ID_TYPE_STRING
};
enum FactorType {
	CONSTANT,
	EXPRESSION
};

struct Constant {
	int value;
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
	
	ValueType type;
};

struct ValueOrId {

	union {
		Value * value;
		char * id;
	};
	ValueOrIdType type;
};

struct DateOrId {
	union {
		Date * date;
		char * id;
	};
	DateOrIdType type;
};

struct IntegerOrId {
	union {
		int v_integer;
		char * v_id;
	};
	IntegerOrIdType type;
};
struct StringOrId {
	union {
		char * string;
		char * id;
	};
	StringOrIdType type;
};

/**
 * Node recursive destructors.
 */
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseFactor(Factor * factor);
void releaseProgram(Program * program);

#endif
