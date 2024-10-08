#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"
#include <stdio.h>
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeFlexActionsModule();

/** Shutdown module's internal state. */
void shutdownFlexActionsModule();

/**
 * Flex lexeme processing actions.
 */


Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);

//the ones we are actually using
Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token MainFragmentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token alphaNumericLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token LogicLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token stringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token SpecifiersLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token LibraryLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token PointLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token CommaLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token TypesLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token BracketsLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token FloatLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
#endif
