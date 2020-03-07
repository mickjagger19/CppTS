/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "asciimath_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerAsciiMathAction

WmarkScannerAsciiMathAction::WmarkScannerAsciiMathAction() throw()
{
}
WmarkScannerAsciiMathAction::~WmarkScannerAsciiMathAction() throw()
{
}

// IRdScannerAction
bool WmarkScannerAsciiMathAction::Scan(std::istream& stm, RdActionStack& stk, RdToken& token)
{
	token.uID = WMARK_TK_TEXT;
	do {
		//get a character
		char ch;
		char next;
		stm.get(ch);
		if( stm.eof() ) {
			return true;
		}
		if( !stm.good() )
			return false;
		
		int length = token.strToken.length();
		
		if (ch == '$'){
			stm.unget();
			if (length == 0) {
				stk.push(WMARK_SCANNER_TK_ACTION);
				return true;
			}
			break;
		}
		
		if (ch == ' '){
			if (neglectSpace) continue;
			else {
				if (length == 0){
					neglectSpace = true;
					token.uID = WMARK_TK_SPACE;
				} else {
					token.uID = WMARK_TK_TEXT;
					stm.unget();
				}
				return true;
			}
		}
		if (text == 1){
			if (ch == '\"'){
				text = 2;
				stm.unget();
				return true;
			}else {
				token.strToken += ch;
				token.infoEnd.uCol ++;
				continue;
			}
		}
		else {
			switch (ch) {
				case '=':
					if(length == 0) { // if it's the first char
						token.strToken = "=";
						token.infoEnd.uCol++;
						token.uID = WMARK_TK_OPERATOR;
						return true;
					}
					stm.unget();
					return true;
				case '*':
					if(length == 0) { // if it's the first char
						if(!stm.eof()) {
							token.uID = WMARK_TK_OPERATOR;
							stm.get(ch);
							if(ch == '*') {
								if(!stm.eof()) {
									stm.get(ch);
									if(ch == '*') {
										token.strToken = "&#x22C6;";
									}
									else {
										token.strToken = "&#x2217;";
										stm.unget();
									}
									return true;
								}
							}
							else {
								token.strToken = "&#x22C5;";
								stm.unget();
							}
							return true;
						}
					}
					stm.unget();
					return true;
				case '<':
					if(!stm.eof()) {
						stm.get(next);
						if(next == '<') {
							if(length == 0) {
								token.strToken = "&#x2329;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == '=') {
							if (!stm.eof()){
								stm.get(next);
								if (next == '>'){
									if (length == 0){
										token.strToken = "&#x21D4;";
										return true;
									}
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							if(length == 0) {
								token.strToken = "&#x2264;";
								token.infoEnd.uCol++;
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						if(length == 0) {
							token.strToken = "&lt;";
							return true;
						}
						stm.unget();
						stm.unget();
						return true;
					}
					break;
				case '>':
					if(!stm.eof()) {
						stm.get(next);
						if(next == '=') {
							if(length == 0) {
								token.uID = WMARK_TK_OPERATOR;
								token.strToken = "&#x2265;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == '-') {
							if(!stm.eof()) {
								stm.get(next);
								if(next == '=') {
									if(length == 0) {
										token.strToken = "&#x227D;";
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								else if(next == '>') {
									if(length == 0) {
										token.strToken = "&#x21A3;";
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							if(length == 0) {
								token.strToken = "&#x227B;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == '>') {
							if(length == 0) {
								token.strToken = "&#x232A;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
						if(length == 0) {
							token.strToken = ">";
							token.uID = WMARK_TK_OPERATOR;
							return true;
						}
						stm.unget();
						return true;
					}
					break;
				case '!':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'i' && !stm.eof()) {
							stm.get(next);
							if(next == 'n') {
								if(length == 0) {
									token.uID = WMARK_TK_OPERATOR;
									token.strToken = "&#x2209;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						else if(next == '=') {
							if(length == 0) {
								token.strToken = "&#x2260;";
								token.uID = WMARK_TK_OPERATOR;
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					stm.unget();
					break;
				case '-':
					if(!stm.eof()) {
						stm.get(next);
						if(next == ':') {
							if(length == 0) {
								token.strToken = "&divide;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == '<') {
							if(!stm.eof()) {
								stm.get(next);
								if(next == '=') {
									if(length == 0) {
										token.strToken = "&#x227C;";
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							if(length == 0) {
								token.strToken = "&#x227A;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == '>' && !stm.eof()) {
							stm.get(next);
							if(next == '>') {
								if(length == 0) {
									token.strToken = "&#x21A0;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						} else if(next == '=') {
							if(length == 0) {
								token.strToken = "&#x2261;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					if(length == 0) { // if it's the first char
						token.strToken = "&#x2212;";
						token.infoEnd.uCol++;
						token.uID = WMARK_TK_OPERATOR;
						return true;
					}
					stm.unget();
					return true;
				case '+':
					if(length == 0) {
						if(!stm.eof()) {
							stm.get(ch);
							if(ch == '-') {
								token.strToken = "&#x00B1;";
								token.infoEnd.uCol++;
								token.uID = WMARK_TK_OPERATOR;
								return true;
							}
							token.strToken = "+";
							token.infoEnd.uCol++;
							token.uID = WMARK_TK_OPERATOR;
							stm.unget();
							return true;
						}
					}
					stm.unget();
					return true;
				case '^':
					if(length == 0) {
						if(!stm.eof()) {
							stm.get(next);
							if(next == '^') {
								token.strToken = "&#x2227;";
								token.uID = WMARK_TK_OPERATOR;
								return true;
							}
							stm.unget();
						}
						token.strToken = "msup";
						token.uID = WMARK_TK_OPERATOR_CARET;
						return true;
					}
					stm.unget();
					return true;
				case '(':
					if(!stm.eof()) {
						stm.get(next);
						if(next == ':') {
							if(length == 0) {
								token.strToken = "&#x2329;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					if(length == 0) { // if it's the first char
						token.uID = WMARK_TK_OPERATOR_LEFT_PARENTHESES;
						if(abs == 1) {
							token.strToken = '|';
							abs = 2;
						}
						else if(floor == 1) {
							token.strToken = "&#x230A;";
							floor = 2;
						}
						else if(ceil == 1) {
							token.strToken = "&#x2308;";
							ceil = 2;
						}
						else token.strToken = '(';
						return true;
					}
					stm.unget();
					return true;
				case ')':
					if(length == 0) { // if it's the first char
						if(abs == 2) {
							token.strToken = '|';
							abs = 0;
						}
						else if(floor == 2) {
							token.strToken = "&#x230B;";
							floor = 0;
						}
						else if(ceil == 2) {
							token.strToken = "&#x2309;";
							ceil = 0;
						}
						else token.strToken = ')';
						token.uID = WMARK_TK_OPERATOR_RIGHT_PARENTHESES;
						return true;
					}
					stm.unget();
					return true;
				case '[':
					if(length == 0) {
						token.strToken = '[';
						token.uID = WMARK_TK_OPERATOR_LEFT_SQUARE_BRACKETS;
						return true;
					}
					stm.unget();
					return true;
				case ']':
					if(length == 0) {
						token.strToken = ']';
						token.uID = WMARK_TK_OPERATOR_RIGHT_SQUARE_BRACKETS;
						return true;
					}
					stm.unget();
					return true;
				case '{':
					if(length == 0) {
						token.strToken = '{';
						token.uID = WMARK_TK_OPERATOR_LEFT_CURLY_BRACES;
						return true;
					}
					stm.unget();
					return true;
				case '}':
					if(length == 0) {
						token.strToken = '}';
						token.uID = WMARK_TK_OPERATOR_RIGHT_CURLY_BRACES;
						return true;
					}
					stm.unget();
					return true;
				case '_':
					if(!stm.eof()) {
						stm.get(next);
						if(next == '_' && !stm.eof()) {
							stm.get(next);
							if(next == '|') {
								if(length == 0) { // right floor
									token.strToken = "&#x230B;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						} else if(next == '|' && !stm.eof()) {
							stm.get(next);
							if(next == '_') {
								if(length == 0) { // up tack
									token.strToken = "&#x22A5;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case '\"':
					token.uID = WMARK_TK_QUOTATION_MARK;
					if (text == 0) text++;
					else if (text == 2) text = 0;
					return true;
				case '/':
					if(!stm.eof()) {
						stm.get(next);
						if(next == '_') {
							if(!stm.eof()) {
								stm.get(next);
								if(next == '\\') {
									if(length == 0) { // triangle
										token.strToken = "&#x25B3;";
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							if(length == 0) { // /_
								token.strToken = "&#x29A3;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					if(length == 0) {
						token.uID = WMARK_TK_OPERATOR;
						token.strToken = "&#x2215;";
						return true;
					}
					stm.unget();
					return true;
				case '|':
					if(!stm.eof()) {
						stm.get(next);
						if(next == '_' && !stm.eof()) {
							stm.get(next);
							if(next == '_') {
								if(length == 0) {
									token.strToken = "&#x230A;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						else if(next == '~') {
							if(length == 0) {
								token.strToken = "&#x2308;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == '>' && !stm.eof()) {
							stm.get(next);
							if(next == '<' && !stm.eof()) {
								stm.get(next);
								if(next == '|') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR;
										token.strToken = "&#x22C8;";
										return true;
									}
									else {
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						else if(next == '-' && !stm.eof()) { // |-> mapsto
							stm.get(next);
							if(next == '>') {
								if(length == 0) {
									token.strToken = "&#x21A6;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							} else if(next == '-') {
								if(length == 0) { // right tack
									token.strToken = "&#x22A2;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
						} else if(next == '=' && !stm.eof()) { // |==
							stm.get(next);
							if(next == '=') {
								if(length == 0) {
									token.strToken = "&#x22A8;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case ':':
					if(!stm.eof()) {
						stm.get(next);
						if(next == '.') {
							if(length == 0) {
								token.strToken = "&#x2234;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == '\'') {
							if(length == 0) {
								token.strToken = "&#x2235;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == ')') {
							if(length == 0) {
								token.strToken = "&#x232A;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case '~':
					if(!stm.eof()) {
						stm.get(next);
						if(next == '~') {
							if(length == 0) {
								token.strToken = "&asymp;";
								token.uID = WMARK_TK_OPERATOR;
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}else if(next == '|') {
							if(length == 0) {
								token.strToken = "&#x2309;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}else if(next == '=') {
							if(length == 0) {
								token.strToken = "&#x2245;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
					}
					break;
				case 'a':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'b' && !stm.eof()) {
							stm.get(next);
							if(next == 's') {
								if(length == 0) {
									token.uID = WMARK_TK_OPERATOR_ABS;
									abs = 1;
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						else if(next == 'l' && !stm.eof()) {
							stm.get(next);
							if(next == 'p' && !stm.eof()) {
								stm.get(next);
								if(next == 'h' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&alpha;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							if(next == 'e' && !stm.eof()) {
								stm.get(next);
								if(next == 'p' && !stm.eof()) {
									stm.get(next);
									if(next == 'h') {
										if(length == 0) {
											token.strToken = "&#8501;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'A':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'A') {
							if(length == 0) {
								token.strToken = "&#x2200;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'b':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'e' && !stm.eof()) {
							stm.get(next);
							if(next == 't' && !stm.eof()) {
								stm.get(next);
								if(next == 'a') {
									if(length == 0) {
										token.strToken = "&beta;";
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}else if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'r') {
								if(length == 0) {
									token.strToken = "mover";
									token.uID = WMARK_TK_BAR;
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						else if(next == 'b') {
							if (!stm.eof()){
								stm.get(next);
								if (next == 'b'){
									if (length == 0){
										token.uID = WMARK_TK_BBB;
										neglectSpace = false;
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							if(length == 0) {
								token.uID = WMARK_TK_BB;
								neglectSpace = false;
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'c':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'h' && !stm.eof()) {
							stm.get(next);
							if(next == 'i') {
								if(length == 0) {
									token.strToken = "&chi;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}else if(next == 'e' && !stm.eof()) {
							stm.get(next);
							if(next == 'i' && !stm.eof()) {
								stm.get(next);
								if(next == 'l') {
									if(length == 0) { // ceil
										token.uID = WMARK_TK_OPERATOR_CEIL;
										ceil = 1;
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'C':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'C') {
							if(length == 0) {
								token.strToken = "&Copf;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'd':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 'r') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR;
										token.strToken = "&#x2193;";
										return true;
									}
									else {
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
							}
							stm.unget();
						}
						if(next == 'e' && !stm.eof()) {
							stm.get(next);
							if(next == 'l') {
								if(!stm.eof()) {
									stm.get(next);
									if(next == 't' && !stm.eof()) {
										stm.get(next);
										if(next == 'a') {
											if(length == 0) {
												token.strToken = "&delta;";
												return true;
											}
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											return true;
										}
										stm.unget();
									}
								}
								if(length == 0) {
									token.strToken = "&#x2202;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						if(next == 'i' && !stm.eof()) {
							stm.get(next);
							if(next == 'a' && !stm.eof()) {
								stm.get(next);
								if(next == 'm' && !stm.eof()) {
									stm.get(next);
									if(next == 'o' && !stm.eof()) {
										stm.get(next);
										if(next == 'n' && !stm.eof()) {
											stm.get(next);
											if(next == 'd') {
												if(length == 0) {
													token.strToken = "&#x25C7;";
													return true;
												}
												else {
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													return true;
												}
												stm.unget();
											}
											stm.unget();
										}
										stm.unget();
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'D':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'e' && !stm.eof()) {
							stm.get(next);
							if(next == 'l' && !stm.eof()) {
								stm.get(next);
								if(next == 't' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&Delta;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'e':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'p' && !stm.eof()) {
							stm.get(next);
							if(next == 's' && !stm.eof()) {
								stm.get(next);
								if(next == 'i' && !stm.eof()) {
									stm.get(next);
									if(next == 'l' && !stm.eof()) {
										stm.get(next);
										if(next == 'o' && !stm.eof()) {
											stm.get(next);
											if(next == 'n') {
												if(length == 0) {
													token.strToken = "&epsilon;";
													return true;
												}
												stm.unget();
												stm.unget();
												stm.unget();
												stm.unget();
												stm.unget();
												stm.unget();
												return true;
											}
											stm.unget();
										}
										stm.unget();
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						if(next == 't' && !stm.eof()) {
							stm.get(next);
							if(next == 'a') {
								if(length == 0) {
									token.strToken = "&eta;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'E':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'E') {
							if(length == 0) {
								token.strToken = "&#x2203;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'f':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'l' && !stm.eof()) {
							stm.get(next);
							if(next == 'o' && !stm.eof()) {
								stm.get(next);
								if(next == 'o' && !stm.eof()) {
									stm.get(next);
									if(next == 'r') {
										if(length == 0) {
											token.uID = WMARK_TK_OPERATOR_FLOOR;
											floor = 1;
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						else if(next == 'r' && !stm.eof()) {
							stm.get(next);
							if(next == 'a' && !stm.eof()) {
								stm.get(next);
								if(next == 'c') {
									if(length == 0) {
										token.strToken = "mfrac";
										token.uID = WMARK_TK_OPERATOR_FRAC;
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'g':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'm' && !stm.eof()) {
								stm.get(next);
								if(next == 'm' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&gamma;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						if(next == 'r' && !stm.eof()) {
							stm.get(next);
							if(next == 'a' && !stm.eof()) {
								stm.get(next);
								if(next == 'd') {
									if(length == 0) {
										token.strToken = "&#x2207;";
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'h':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'A' && !stm.eof()) {
							stm.get(next);
							if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 'r') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR;
										token.strToken = "&#x21D4;";
										return true;
									}
									else {
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						else if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 'r') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR;
										token.strToken = "&#x2194;";
										return true;
									}
									else {
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
					}
					break;
				case 'G':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'm' && !stm.eof()) {
								stm.get(next);
								if(next == 'm' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&Gamma;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'i':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'o' && !stm.eof()) {
							stm.get(next);
							if(next == 't' && !stm.eof()) {
								stm.get(next);
								if(next == 'a') {
									if(length == 0) {
										token.strToken = "&iota;";
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}
						else if(next == 'n' && !stm.eof()) {
							stm.get(next);
							if(next == 't' && !stm.eof()) {
								stm.get(next);
								if(next == '_') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR_INT;
										token.strToken = "&int;";
										neglectSpace = false;
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'k':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'p' && !stm.eof()) {
								stm.get(next);
								if(next == 'p' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&iota;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'l':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 'r') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR;
										token.strToken = "&#x2190;";
										return true;
									}
									else {
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							else if(next == 'm' && !stm.eof()) {
								stm.get(next);
								if(next == 'b' && !stm.eof()) {
									stm.get(next);
									if(next == 'd' && !stm.eof()) {
										stm.get(next);
										if(next == 'a') {
											if(length == 0) {
												token.strToken = "&lambda;";
												return true;
											}
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											return true;
										}
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						else if(next == 'A' && !stm.eof()) {
							stm.get(next);
							if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 'r') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR;
										token.strToken = "&#x21D0;";
										return true;
									}
									else {
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
					}
					break;
				case 'L':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'm' && !stm.eof()) {
								stm.get(next);
								if(next == 'b' && !stm.eof()) {
									stm.get(next);
									if(next == 'd' && !stm.eof()) {
										stm.get(next);
										if(next == 'a') {
											if(length == 0) {
												token.strToken = "&Lambda;";
												return true;
											}
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											return true;
										}
										stm.unget();
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'm':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'u') {
							if(length == 0) {
								token.strToken = "&mu;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'n':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'u') {
							if(length == 0) {
								token.strToken = "&nu;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						if(next == 'n' && !stm.eof()) {
							stm.get(next);
							if(next == 'n') {
								if(length == 0) {
									token.strToken = "&cap;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'N':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'N') {
							if(length == 0) {
								token.strToken = "&Nopf;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'o':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'm' && !stm.eof()) {
							stm.get(next);
							if(next == 'e' && !stm.eof()) {
								stm.get(next);
								if(next == 'g' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&omega;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						if(next == 'i' && !stm.eof()) {
							stm.get(next);
							if(next == 'n' && !stm.eof()) {
								stm.get(next);
								if(next == 't' && !stm.eof()) {
									stm.get(next);
									if(next == '_') {
										if(length == 0) {
											token.uID = WMARK_TK_OPERATOR_OINT;
											token.strToken = "&oint;";
											neglectSpace = false;
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						if(next == 'o') {
							if(length == 0) {
								token.strToken = "&#8734;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'O':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'm' && !stm.eof()) {
							stm.get(next);
							if(next == 'e' && !stm.eof()) {
								stm.get(next);
								if(next == 'g' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&Omega;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						else if(next == '/') {
							if(length == 0) {
								token.strToken = "&#x29B0;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
				case 'p':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'i') {
							if(length == 0) {
								token.strToken = "&pi;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == 'h' && !stm.eof()) {
							stm.get(next);
							if(next == 'i') {
								if(length == 0) {
									token.strToken = "&phi;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						else if(next == 's' && !stm.eof()) {
							stm.get(next);
							if(next == 'i') {
								if(length == 0) {
									token.strToken = "&psi;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						else if(next == 'r' && !stm.eof()) {
							stm.get(next);
							if(next == 'o' && !stm.eof()) {
								stm.get(next);
								if(next == 'p') {
									if(length == 0) {
										token.strToken = "&#x221D;";
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								else if(next == 'd' && !stm.eof()) {
									stm.get(next);
									if(next == '_') {
										if(length == 0) {
											token.uID = WMARK_TK_OPERATOR_PROD;
											token.strToken = "&prod;";
											neglectSpace = false;
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'P':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'h' && !stm.eof()) {
							stm.get(next);
							if(next == 'i') {
								if(length == 0) {
									token.strToken = "&Phi;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						else if(next == 's' && !stm.eof()) {
							stm.get(next);
							if(next == 'i') {
								if(length == 0) {
									token.strToken = "&Psi;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						else if(next == 'i') {
							if(length == 0) {
								token.strToken = "&Pi;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.get();
					}
					break;
				case 'q':
					break;
				case 'Q':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'Q') {
							if(length == 0) {
								token.strToken = "&Qopf;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'r':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 'r') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR;
										token.strToken = "&#x2192;";
										return true;
									}
									else {
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
							}
							stm.unget();
						}
						else if(next == 'A' && !stm.eof()) {
							stm.get(next);
							if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 'r') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR;
										token.strToken = "&#x21D2;";
										return true;
									}
									else {
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
							}
							stm.unget();
						}
						else if(next == 'h' && !stm.eof()) {
							stm.get(next);
							if(next == 'o') {
								if(length == 0) {
									token.strToken = "&rho;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						if(next == 'o' && !stm.eof()) {
							stm.get(next);
							if(next == 'o' && !stm.eof()) {
								stm.get(next);
								if(next == 't') {
									if(length == 0) {
										token.strToken = "mroot";
										token.uID = WMARK_TK_OPERATOR_ROOT;
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'R':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'R') {
							if(length == 0) {
								token.strToken = "&Ropf;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 's':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'u' && !stm.eof()) {
							stm.get(next);
							if(next == 'b') {
								if(!stm.eof()) {
									stm.get(next);
									if(next == 'e' && length == 0) { // sube
										token.strToken = "&#x2286;";
										return true;
									}
									stm.unget();
								}
								if(length == 0) { //sub
									token.strToken = "&#x2282;";
									return true;
								}
								else {
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
							}
							else if(next == 'p') {
								if(!stm.eof()) {
									stm.get(next);
									if(next == 'e' && length == 0) { // supe
										token.strToken = "&#x2287;";
										return true;
									}
									stm.unget();
								}
								if(length == 0) { // sup
									token.strToken = "&#x2283;";
									return true;
								}
								else {
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
							}
							else if(next == 'm' && !stm.eof()) {
								stm.get(next);
								if(next == '_' && length == 0) {
									token.uID = WMARK_TK_OPERATOR_SUM;
									token.strToken = "&sum;";
									neglectSpace = false;
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}
						else if(next == 'i' && !stm.eof()) {
							stm.get(next);
							if(next == 'g' && !stm.eof()) {
								stm.get(next);
								if(next == 'm' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&sigma;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						else if(next == 'q' && !stm.eof()) {
							stm.get(next);
							if(next == 'u' && !stm.eof()) {
								stm.get(next);
								if(next == 'a' && !stm.eof()) {
									stm.get(next);
									if(next == 'r' && !stm.eof()) {
										stm.get(next);
										if(next == 'e') {
											if(length == 0) {
												token.strToken = "&#x25A1;";
												return true;
											}
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											return true;
										}
										stm.unget();
									}
									stm.unget();
								}
								stm.unget();
							}
							else if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 't') {
									if(length == 0) {
										token.strToken = "msqrt";
										token.uID = WMARK_TK_OPERATOR_SQRT;
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'S':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'i' && !stm.eof()) {
							stm.get(next);
							if(next == 'g' && !stm.eof()) {
								stm.get(next);
								if(next == 'm' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&Sigma;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 't':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'h' && !stm.eof()) {
							stm.get(next);
							if(next == 'e' && !stm.eof()) {
								stm.get(next);
								if(next == 't' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&theta;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'u') {
								if(length == 0) {
									token.strToken = "&tau;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'T':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'h' && !stm.eof()) {
							stm.get(next);
							if(next == 'e' && !stm.eof()) {
								stm.get(next);
								if(next == 't' && !stm.eof()) {
									stm.get(next);
									if(next == 'a') {
										if(length == 0) {
											token.strToken = "&Theta;";
											return true;
										}
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						} else if(next == 'T') {
							if(length == 0) { // down tack
								token.strToken = "&#x22A4;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'u':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 'r') {
									if(length == 0) {
										token.uID = WMARK_TK_OPERATOR;
										token.strToken = "&#x2191;";
										return true;
									}
									else {
										stm.unget();
										stm.unget();
										stm.unget();
										stm.unget();
										return true;
									}
									stm.unget();
								}
							}
							stm.unget();
						}
						if(next == 'p' && !stm.eof()) {
							stm.get(next);
							if(next == 's' && !stm.eof()) {
								stm.get(next);
								if(next == 'i' && !stm.eof()) {
									stm.get(next);
									if(next == 'l' && !stm.eof()) {
										stm.get(next);
										if(next == 'o' && !stm.eof()) {
											stm.get(next);
											if(next == 'n') {
												if(length == 0) {
													token.strToken = "&upsilon;";
													return true;
												}
												stm.unget();
												stm.unget();
												stm.unget();
												stm.unget();
												stm.unget();
												stm.unget();
												return true;
											}
											stm.unget();
										}
										stm.unget();
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						if(next == 'u' && !stm.eof()) {
							stm.get(next);
							if(next == 'u') {
								if(length == 0) {
									token.strToken = "&cup;";
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'v':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'e' && !stm.eof()) {
							stm.get(next);
							if(next == 'c') {
								if(length == 0) {
									token.strToken = "mover";
									token.uID = WMARK_TK_VEC;
									return true;
								}
								stm.unget();
								stm.unget();
								stm.unget();
								return true;
							}
							stm.unget();
						}
						else if(next == 'v') {
							if(length == 0) {
								token.strToken = "&#x2228;";
								token.uID = WMARK_TK_OPERATOR;
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						else if(next == 'a' && !stm.eof()) {
							stm.get(next);
							if(next == 'r' && !stm.eof()) {
								stm.get(next);
								if(next == 't' && !stm.eof()) {
									stm.get(next);
									if(next == 'h' && !stm.eof()) {
										stm.get(next);
										if(next == 'e' && !stm.eof()) {
											stm.get(next);
											if(next == 't' && !stm.eof()) {
												stm.get(next);
												if(next == 'a') {
													if(length == 0) {
														token.strToken = "&vartheta;";
														return true;
													}
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													stm.unget();
													return true;
												}
												stm.unget();
											}
											stm.unget();
										}
										stm.unget();
									}
									stm.unget();
								}
								else if(next == 'e' && !stm.eof()) {
									stm.get(next);
									if(next == 'p' && !stm.eof()) {
										stm.get(next);
										if(next == 's' && !stm.eof()) {
											stm.get(next);
											if(next == 'i' && !stm.eof()) {
												stm.get(next);
												if(next == 'l' && !stm.eof()) {
													stm.get(next);
													if(next == 'o' && !stm.eof()) {
														stm.get(next);
														if(next == 'n') {
															if(length == 0) {
																token.strToken = "&varepsilon;";
																return true;
															}
															stm.unget();
															stm.unget();
															stm.unget();
															stm.unget();
															stm.unget();
															stm.unget();
															stm.unget();
															stm.unget();
															stm.unget();
															stm.unget();
															return true;
														}
														stm.unget();
													}
													stm.unget();
												}
												stm.unget();
											}
											stm.unget();
										}
										stm.unget();
									}
									stm.unget();
								}
								else if(next == 'p' && !stm.eof()) {
									stm.get(next);
									if(next == 'h' && !stm.eof()) {
										stm.get(next);
										if(next == 'i') {
											if(length == 0) {
												token.strToken = "&varphi;";
												return true;
											}
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											stm.unget();
											return true;
										}
										stm.unget();
									}
									stm.unget();
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'x':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'x') {
							if(length == 0) {
								token.strToken = "&#xD7;";
								token.uID = WMARK_TK_OPERATOR;
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						if(next == 'i') {
							if(length == 0) {
								token.strToken = "&xi;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'X':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'i') {
							if(length == 0) {
								token.strToken = "&Xi;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				case 'z':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'e' && !stm.eof()) {
							stm.get(next);
							if(next == 't' && !stm.eof()) {
								stm.get(next);
								if(next == 'a') {
									if(length == 0) {
										token.strToken = "&zeta;";
										return true;
									}
									stm.unget();
									stm.unget();
									stm.unget();
									stm.unget();
									return true;
								}
								stm.unget();
							}
							stm.unget();
						}
						stm.unget();
					}
					break;
				case 'Z':
					if(!stm.eof()) {
						stm.get(next);
						if(next == 'Z') {
							if(length == 0) {
								token.strToken = "&Zopf;";
								return true;
							}
							stm.unget();
							stm.unget();
							return true;
						}
						stm.unget();
					}
					break;
				default : {
				}
			}
		}
		
		token.strToken += ch;
		token.infoEnd.uCol ++;
	} while( true );
	
	token.uID = WMARK_TK_TEXT;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
