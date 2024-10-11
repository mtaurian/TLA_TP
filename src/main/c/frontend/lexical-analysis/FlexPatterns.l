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

"isLowerThan"                       {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_LOWER_THAN);}
"isGreaterThan"                     {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_GREATER_THAN);}
"isLowerOrEqualTo"                  {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_LOWER_OR_EQUAL_TO);}
"isGreaterOrEqualTo"                {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_GREATER_OR_EQUAL_TO);}
"isLowest"                          {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_LOWEST);}
"isGreatest"                        {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_GREATEST);}
"equals"                            {return LibraryLexemeAction(createLexicalAnalyzerContext(), EQUALS);}
"isDifferentFrom"                   {return LibraryLexemeAction(createLexicalAnalyzerContext(), IS_DIFFERENT_FROM);}
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

"when"|"WHEN"                              {return TransportLexemeAction(createLexicalAnalyzerContext(), WHEN);}
"goto"|"GOTO"                              {return TransportLexemeAction(createLexicalAnalyzerContext(), GOTO);}
"end"|"END"                               {return TransportLexemeAction(createLexicalAnalyzerContext(), END);}

"CheckBox"|"CHECKBOX"|"checkbox"                          {return TypesLexemeAction(createLexicalAnalyzerContext(), CHECKBOX);}
"Radios"|"RADIOS"|"radios"                            {return TypesLexemeAction(createLexicalAnalyzerContext(), RADIOS);}
"Select"|"SELECT"|"select"                            {return TypesLexemeAction(createLexicalAnalyzerContext(), SELECT);}
"Text"|"TEXT"|"text"                              {return TypesLexemeAction(createLexicalAnalyzerContext(), TEXT);}
"Image"|"IMAGE"|"image"                             {return TypesLexemeAction(createLexicalAnalyzerContext(), IMAGE);}
"Document"|"DOCUMENT"|"document"                          {return TypesLexemeAction(createLexicalAnalyzerContext(), DOCUMENT);}
"LongText"|"LONGTEXT"|"longtext"                          {return TypesLexemeAction(createLexicalAnalyzerContext(), LONGTEXT);}
"Numeric"|"NUMERIC"|"numeric"                           {return TypesLexemeAction(createLexicalAnalyzerContext(), NUMERIC);}
"Password"|"PASSWORD"|"password"                          {return TypesLexemeAction(createLexicalAnalyzerContext(), PASSWORD);}
"Date"|"DATE"|"date"                              {return TypesLexemeAction(createLexicalAnalyzerContext(), DATE);}

"Debut"                              {return ThemesLexemeAction(createLexicalAnalyzerContext(), DEBUT);}
"Fearless"                           {return ThemesLexemeAction(createLexicalAnalyzerContext(), FEARLESS);}
"SpeakNow"                           {return ThemesLexemeAction(createLexicalAnalyzerContext(), SPEAK_NOW);}
"Red"                                {return ThemesLexemeAction(createLexicalAnalyzerContext(), RED);}
"1989"                               {return ThemesLexemeAction(createLexicalAnalyzerContext(), NINETEEN_EIGHTY_NINE);}
"Reputation"                         {return ThemesLexemeAction(createLexicalAnalyzerContext(), REPUTATION);}
"Lover"                              {return ThemesLexemeAction(createLexicalAnalyzerContext(), LOVER);}
"Folklore"                           {return ThemesLexemeAction(createLexicalAnalyzerContext(), FOLKLORE);}
"Evermore"                           {return ThemesLexemeAction(createLexicalAnalyzerContext(), EVERMORE);}
"Midnights"                          {return ThemesLexemeAction(createLexicalAnalyzerContext(), MIDNIGHTS);}
"TTPD"                               {return ThemesLexemeAction(createLexicalAnalyzerContext(), TTPD);}

"["                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), OPEN_BRACKETS);}
"]"                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), CLOSE_BRACKETS);}
"{"                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), OPEN_BRACES);}
"}"                                 { return BracketsLexemeAction(createLexicalAnalyzerContext(), CLOSE_BRACES);}
"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), OPEN_PARENTHESIS); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), CLOSE_PARENTHESIS); }
"."                                 { return PointLexemeAction(createLexicalAnalyzerContext());}
","                                 { return CommaLexemeAction(createLexicalAnalyzerContext());}
"+"                                 { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext(), ADD);}
"-"                                 { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext(), SUB);}
"*"                                 { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext(), MUL);}
"/"                                 { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext(), DIV);}


"and"|"AND"                         { return LogicLexemeAction(createLexicalAnalyzerContext(), AND);}
"or"|"OR"                           { return LogicLexemeAction(createLexicalAnalyzerContext(), OR);}
"not"|"NOT"                         { return LogicLexemeAction(createLexicalAnalyzerContext(), NOT);}
"true"|"TRUE"                         { return LogicLexemeAction(createLexicalAnalyzerContext(), TRUE);}
"false"|"FALSE"                         { return LogicLexemeAction(createLexicalAnalyzerContext(), FALSE);}

[[:digit:]]+						        { return IntegerLexemeAction(createLexicalAnalyzerContext()); }
[[:alpha:]][[:alnum:]]+                     { return IDLexemeAction(createLexicalAnalyzerContext());}
[+-]?([0-9]*[.])?[0-9]+([eE][+-]?[0-9]+)?   { return FloatLexemeAction(createLexicalAnalyzerContext());}

[[:space:]]+		    			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"\""                                { BEGIN(STRING_CONTEXT); }
<STRING_CONTEXT>"\""                { BEGIN(INITIAL);} 
<STRING_CONTEXT>[^\"]+              { return stringLexemeAction(createLexicalAnalyzerContext());} 
"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }


%%

#include "FlexExport.h"
