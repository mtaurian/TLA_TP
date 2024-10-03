%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
%x MULTILINE_COMMENT
%x STRING_CONTEXT

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%


%{ /* Main Fragments */ %}
"@FormConfig"						{}
"@Step"			        			{}
"@Section"                          {}
"@Question"						    {}
"@Glitch"                           {}
"@Error"                            {}
"@GetAwayCar"                       {}
"@ShowIf"                           {}
"@Do"                               {}
"@Task"                             {}

%{ /* Statements */ %}
"#Closure"                          {}
"#SubmitBtnText"                    {}
"#SafeAndSound"                     {}
"#Theme"                            {}
"#Title"                            {}
"#Description"                      {}
"#Default"                          {}
"#Type"                             {}
"#Help"                             {}
"#Options"                          {}
"#PlaceHolder"                      {}
"#Message"                          {}

%{ /* General Context or Scope Utils */ %}
"{"                                 {}
"}"                                 {}
"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), OPEN_PARENTHESIS); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), CLOSE_PARENTHESIS); }
"."                                 {}
"="                                 {}
">"                                 {}
"<"                                 {}

%{ /* Logic */ %}

"and"|"AND"                         {}
"or"|"OR"                           {}
"not"|"NOT"                         {}

%{ /* Lib */ %}
"value"                             {}
"selected"                          {}


%{ /* Names and Numbers */ %}
[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }
[[:alpha:]][[:alnum]]+              {}

%{ /* Ignored Section */ %}
[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

%{ /* Other Contexts */ %}
"\""                                { BEGIN(STRING_CONTEXT); }
<STRING_CONTEXT>"\""                { BEGIN(INITIAL);} 

"/*"								                { BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				                { EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT, STRING_CONTEXT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT, STRING_CONTEXT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT, STRING_CONTEXT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

%{ /* Unknown */ %}
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }


%%

#include "FlexExport.h"
