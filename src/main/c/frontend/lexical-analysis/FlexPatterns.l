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


"@FormConfig"						{return MainFragmentLexemeAction(createLexicalAnalyzerContext(), CONFIG);}
"@Step"			        			{return MainFragmentLexemeAction(createLexicalAnalyzerContext(), STEP);}
"@Section"                          {return MainFragmentLexemeAction(createLexicalAnalyzerContext(), SECTION);}
"@Question"						    {return MainFragmentLexemeAction(createLexicalAnalyzerContext(), QUESTION);}
"@Glitch"                           {return MainFragmentLexemeAction(createLexicalAnalyzerContext(), GLITCH);}
"@Error"                            {return MainFragmentLexemeAction(createLexicalAnalyzerContext(), GL_ERROR);}
"@GetAwayCar"                       {return MainFragmentLexemeAction(createLexicalAnalyzerContext(), GETAWAYCAR);}
"@ShowIf"                           {return MainFragmentLexemeAction(createLexicalAnalyzerContext(), SHOWIF);}
"@Do"                               {return MainFragmentLexemeAction(createLexicalAnalyzerContext(), DO);}
"@Task"                             {return MainFragmentLexemeAction(createLexicalAnalyzerContext(), TASK);}

"#Closure"                          {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), CLOSURE);}
"#SubmitBtnText"                    {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), SUBMIT_TEXT);}
"#SafeAndSound"                     {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), SAFE_AND_SOUND);}
"#Theme"                            {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), THEME);}
"#Title"                            {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), TITLE);}
"#Description"                      {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), DESCRIPTION);}
"#Default"                          {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), DEFAULT);}
"#Type"                             {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), TYPE);}
"#Help"                             {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), HELP);}
"#Options"                          {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), OPTIONS);}
"#PlaceHolder"                      {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), PLACE_HOLDER);}
"#Message"                          {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), MESSAGE);}

"{"                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), OPEN_BRACKETS);}
"}"                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), CLOSE_BRACKETS);}
"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), OPEN_PARENTHESIS); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), CLOSE_PARENTHESIS); }
"."                                 {}
"="                                 {}
">"                                 {}
"<"                                 {}
"+"                                 {}
"-"                                 {}
"*"                                 {}
"/"                                 {}


"and"|"AND"                         { return logicLexemeAction(createLexicalAnalyzerContext(), AND);}
"or"|"OR"                           { return logicLexemeAction(createLexicalAnalyzerContext(), OR);}
"not"|"NOT"                         { return logicLexemeAction(createLexicalAnalyzerContext(), NOT);}

"value"                             {}
"selected"                          {}


[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }
[a-zA-Z][a-zA-Z0-9]*                { return alphaNumericLexemeAction(createLexicalAnalyzerContext());}

[[:space:]]+		    				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"\""                                { BEGIN(STRING_CONTEXT); }
<STRING_CONTEXT>"\""                { BEGIN(INITIAL);} 
<STRING_CONTEXT>[^\"]               { stringLexemeAction(createLexicalAnalyzerContext());} 
"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

.									                { return UnknownLexemeAction(createLexicalAnalyzerContext()); }


%%

#include "FlexExport.h"
