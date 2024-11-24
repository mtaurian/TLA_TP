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
"#Required"                         {return SpecifiersLexemeAction(createLexicalAnalyzerContext(), REQUIRED);}

"isLowerThan"|"<"                   {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_LOWER_THAN);}
"isGreaterThan"|">"                 {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_GREATER_THAN);}
"isLowerOrEqualTo"|"<="             {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_LOWER_OR_EQUAL_TO);}
"isGreaterOrEqualTo"|">="           {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_GREATER_OR_EQUAL_TO);}
"isLowest"                          {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_LOWEST);}
"isGreatest"                        {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_GREATEST);}
"equals"|"="                        {return LibraryLexemeAction(createLexicalAnalyzerContext(), EQUALS);}
"isDifferentFrom"|"!="              {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_DIFFERENT_FROM);}
"isMultipleOf"                      {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_MULTIPLE_OF);}
"isDivisorOf"                       {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_DIVISOR_OF);}
"isTrue"                            {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_TRUE);}
"isFalse"                           {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_FALSE);}
"mathValid"                         {return LibraryLexemeAction(createLexicalAnalyzerContext(), MATH_VALID);}
"satisfies"                         {return LibraryLexemeAction(createLexicalAnalyzerContext(), SATISFIES);}
"like"                              {return LibraryLexemeAction(createLexicalAnalyzerContext(), LIKE);}
"contains"                          {return LibraryLexemeAction(createLexicalAnalyzerContext(), CONTAINS);}
"doesLengthEqual"                   {return LibraryLexemeAction(createLexicalAnalyzerContext(), DOES_LENGTH_EQUAL);}
"isLongerThan"                      {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_LONGER_THAN);}
"isShorterThan"                     {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_SHORTER_THAN);}
"isEmpty"                           {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_EMPTY);}
"isBefore"                          {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_BEFORE);}
"isAfter"                           {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_AFTER);}
"isWeekend"                         {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_WEEKEND);}

"WHEN"                              {return TransportLexemeAction(createLexicalAnalyzerContext(), WHEN);}
"GOTO"                              {return TransportLexemeAction(createLexicalAnalyzerContext(), GOTO);}
"END"                               {return TransportLexemeAction(createLexicalAnalyzerContext(), END);}

"CHECKBOX"                          {return TypesLexemeAction(createLexicalAnalyzerContext(), CHECKBOX);}
"RADIOS"                            {return TypesLexemeAction(createLexicalAnalyzerContext(), RADIOS);}
"SELECT"                            {return TypesLexemeAction(createLexicalAnalyzerContext(), SELECT);}
"TEXT"                              {return TypesLexemeAction(createLexicalAnalyzerContext(), TEXT);}
"IMAGE"                             {return TypesLexemeAction(createLexicalAnalyzerContext(), IMAGE);}
"DOCUMENT"                          {return TypesLexemeAction(createLexicalAnalyzerContext(), DOCUMENT);}
"LONGTEXT"                          {return TypesLexemeAction(createLexicalAnalyzerContext(), LONGTEXT);}
"NUMERIC"                           {return TypesLexemeAction(createLexicalAnalyzerContext(), NUMERIC);}
"PASSWORD"                          {return TypesLexemeAction(createLexicalAnalyzerContext(), PASSWORD);}
"DATE"                              {return TypesLexemeAction(createLexicalAnalyzerContext(), DATE);}

"_Debut"                             {return ThemesLexemeAction(createLexicalAnalyzerContext(), DEBUT);}
"_Fearless"                          {return ThemesLexemeAction(createLexicalAnalyzerContext(), FEARLESS);}
"_SpeakNow"                          {return ThemesLexemeAction(createLexicalAnalyzerContext(), SPEAK_NOW);}
"_Red"                               {return ThemesLexemeAction(createLexicalAnalyzerContext(), RED);}
"_1989"                              {return ThemesLexemeAction(createLexicalAnalyzerContext(), NINETEEN_EIGHTY_NINE);}
"_Reputation"                        {return ThemesLexemeAction(createLexicalAnalyzerContext(), REPUTATION);}
"_Lover"                             {return ThemesLexemeAction(createLexicalAnalyzerContext(), LOVER);}
"_Folklore"                          {return ThemesLexemeAction(createLexicalAnalyzerContext(), FOLKLORE);}
"_Evermore"                          {return ThemesLexemeAction(createLexicalAnalyzerContext(), EVERMORE);}
"_Midnights"                         {return ThemesLexemeAction(createLexicalAnalyzerContext(), MIDNIGHTS);}
"_TTPD"                              {return ThemesLexemeAction(createLexicalAnalyzerContext(), TTPD);}

"["                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), OPEN_BRACKETS);}
"]"                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), CLOSE_BRACKETS);}
"{"                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), OPEN_BRACES);}
"}"                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), CLOSE_BRACES);}
"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), OPEN_PARENTHESIS); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), CLOSE_PARENTHESIS); }
","                                 { return CommaLexemeAction(createLexicalAnalyzerContext());}

"AND"                               { return LogicLexemeAction(createLexicalAnalyzerContext(), AND);}
"OR"                                { return LogicLexemeAction(createLexicalAnalyzerContext(), OR);}
"NOT"                               { return LogicLexemeAction(createLexicalAnalyzerContext(), NOT);}
"TRUE"                              { return LogicLexemeAction(createLexicalAnalyzerContext(), TRUE);}
"FALSE"                             { return LogicLexemeAction(createLexicalAnalyzerContext(), FALSE);}

[[:digit:]]+						        { return IntegerLexemeAction(createLexicalAnalyzerContext()); }
[[:alpha:]][[:alnum:]]+                     { return IDLexemeAction(createLexicalAnalyzerContext());}
[+-]?([0-9]*[.])?[0-9]+([eE][+-]?[0-9]+)?   { return FloatLexemeAction(createLexicalAnalyzerContext());}

[[:space:]]+		    			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"\""                                { BEGIN(STRING_CONTEXT); }
<STRING_CONTEXT>"\""                { BEGIN(INITIAL);} 
<STRING_CONTEXT>[^\"]+              { return StringLexemeAction(createLexicalAnalyzerContext());} 
"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }


%%

#include "FlexExport.h"
