/*
	RubyCLIB - Ruby Compiler
    Copyright (C) 2010  Giancarlo Bellido

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <cmath>

#include "rubyc/scanner.h"

namespace rubyc { namespace scanner {

int      line;
FILE    *file;
char   *start;
char    current;
int     fixnum;
double  floatnum;
int     base;
int index;

#define TK_STRING_EXPR '\1'

Array<char> buffer; // Store Lexemes and Strings.

/** 
 * Pushes char c to buffer. 
 */ 
inline void push(char c)
{
	buffer.push(c);
}

/**
 * Returns next character in FILE file.
 */
inline char ignore_next()
{
	++index;
	return current = getc(file);
}

/**
 * Pushes current returns next 
 */
inline char next()
{
	push(current);
	return ignore_next();
}

/**
 * Discards current lexeme and rewinds buffer to save memory.
 */
void discard()
{
	buffer.rewind(start);
}

/**
 * Go next() and return token tk.
 */
inline TokenOp N(TokenOp tk) {
	ignore_next(); return tk; 
}

/**
 * Discard and return
 */
inline TokenOp D(TokenOp tk) {
	discard(); return tk;
}

/**
 * Returns true if current is not alphanumeric or '_'.
 */
inline bool nalnum()
{
	return !(isalnum(current) || (current == '_'));
}

/**
 * Scans an identifier.
 */
TokenOp ident()
{
	do  {
		switch(current) {
		case '_': continue;
		case '?': case '!':	next(); return tk_ident;
		default: if (nalnum()) return  tk_ident;				
		}
	} while (next());
	
	return tk_ident;
}

inline bool match(char x) { return (current == x) ? next(), true : false; }
inline bool nmatch(char x) { return ignore_next(), (current == x); }

inline TokenOp match_key(TokenOp o) 
{
	return nalnum() ? (discard(), o) : ident(); 
}

inline TokenOp match_key(char a, TokenOp o) 
{
	return (match(a) && nalnum()) ? (discard(), o) : ident(); 
}

inline TokenOp match_key(char a, char b, TokenOp o) 
{
	return (match(a) && match(b) && nalnum()) ? (discard(), o) : ident(); 
}

inline TokenOp match_key(char a, char b, char c, TokenOp o) 
{
	return (match(a) && match(b) && match(c) && nalnum()) ? (discard(), o) : ident(); 
}

inline TokenOp match_key(char a, char b, char c, char d, TokenOp o) 
{
	return (match(a) && match(b) && match(c) && match(d) && nalnum()) ? (discard(), o) : ident(); 
}

inline TokenOp match_key(char a, char b, char c, char d, char e, TokenOp o) 
{
	return (match(a) && match(b) && match(c) && match(d) && match(e) && nalnum()) ? (discard(), o) : ident(); 
}

inline void new_line()
{
	++line;
}

/*-------- TOKEN GENERATION ROUTINES ----------*/

const char* lexeme()
{
	push(0);
	return start;
}

/*-------------SCANNER HELPERS-----------*/

TokenOp single_quote_string()
{
	while (true) {
		switch(current) {
		case '\\':  
			switch (ignore_next()) 
			{
			case '\\': push('\\'); break;
			case '\'' : push('\'');  break;
			default  : push(current); 
			}
			ignore_next();
			break;
		case '\'':
			return N(tk_string);
		case '\n':
			new_line();
		default:
			next();
		}
	}

	return tk_string;
}

TokenOp single_brace_string()
{
	while (true) {
		switch(current) {
		case '\\':  
			switch (ignore_next()) 
			{
			case '\\': push('\\'); break;
			case '\'' : push('\'');  break;
			case '}': push('}'); break;
			default  : push(current); 
			}
			ignore_next();
			break;
		case '}':
			return N(tk_string);
		case '\n':
			new_line();
		default:
			next();
		}
	}

	return tk_string;
}

bool check_delimeter(const char* d)
{
	char* s = buffer.end();
	
	for (const char* i = d; *i != '\0'; i++, next())
	{
		if (*i != current)
			return false;
	}

	buffer.rewind(s);
	current = '\n';
	return true;
}

TokenOp delimeter_string(const char* delimeter)
{
	start = buffer.end();

	while (true) {
		switch(current) {
		case '#':  
			if (ignore_next() == '{') 
			{	
				current = TK_STRING_EXPR;
				return tk_string;
			}
		case '\n':
			new_line();
			next();
			if (check_delimeter(delimeter))
				break;
			continue;
		default:
			next();
			continue;
		}		
		break;
	}

	return tk_string;
}


// TODO Store actual string
TokenOp string()
{
	while (true) {
		switch(current) {
		case '\\':  
			switch (ignore_next()) 
			{
			case '\\': push('\\'); break;
			case '"' : push('"');  break;
			case 'a' : push('\a'); break;
			case 'b' : push('\b'); break;
			case 'r' : push('\r'); break;
			case 'n' : push('\n'); break;
			case 's' : push(' ');  break;
			case 't' : push('\t'); break;
			default  : push(current);
			}
			ignore_next();
			continue;
		case '#':  
			if (ignore_next() == '{') 
			{
				current = TK_STRING_EXPR;
				return tk_string;
			}
		case '"':
			ignore_next(); break;
		case '\n':
			new_line();
		default:
			next();
			continue;
		}		
		break;
	}

	return tk_string;
}

// TODO Store actual string
TokenOp double_brace_string()
{
	while (true) {
		switch(current) {
		case '\\':  
			switch (ignore_next()) 
			{
			case '\\': push('\\'); break;
			case '"' : push('"');  break;
			case 'a' : push('\a'); break;
			case 'b' : push('\b'); break;
			case 'r' : push('\r'); break;
			case 'n' : push('\n'); break;
			case 's' : push(' ');  break;
			case 't' : push('\t'); break;
			default  : push(current);
			}
			ignore_next();
			continue;
		case '#':  
			if (ignore_next() == '{') 
			{
				current = TK_STRING_EXPR;
				return tk_string;
			}
		case '}':
			ignore_next(); break;
		case '\n':
			new_line();
		default:
			next();
			continue;
		}		
		break;
	}

	return tk_string;
}


TokenOp regexp()
{
	while (next() != '/') {}
	next();
	return tk_regexp;
}

void init(FILE *_file/*=stdin*/)
{
	line   = 1;
	index = 0;
	file   = _file;
	next();
}

TokenOp gvar()
{
	ignore_next();
	switch (next()) {
	case '!': case '@': case '&': case '`': case '\'': case '+':
	case '~': case '=': case '/': case '\\': case ',': case ';':
	case '.': case '<': case '>': case '_': case '0': case '*':
	case '$': case '?': case ':': case '"':
		break;
	case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		while (isdigit(next())) { }
		break;
	case '-':
		if (isalnum(next()))
			ignore_next();
		break;
	default:
		ident();
		break;
	}

	return tk_gvar;
}

TokenOp method()
{
	do  {
		switch(current) {
		case '_': continue;
		case '?': case '!':	next(); return tk_method_call;
		default: if (nalnum()) return  tk_method_call;;				
		}
	} while (next());
	
	return tk_method_call;
}

TokenOp digits()
{
	unsigned int x = 0;

	 while (true) {
		switch (current) {
		case '0': x = x * 10; break;
		case '1': x = x * 10 + 1; break;
		case '2': x = x * 10 + 2; break;
		case '3': x = x * 10 + 3; break;
		case '4': x = x * 10 + 4; break;
		case '5': x = x * 10 + 5; break;
		case '6': x = x * 10 + 6; break;
		case '7': x = x * 10 + 7; break;
		case '8': x = x * 10 + 8; break;
		case '9': x = x * 10 + 9; break;		
		case '_':
			ignore_next(); continue;
		default:
			fixnum = x;
			discard();
			return tk_fixnum;
		}
		next();
		if (x > INT_MAX) break;
	}

 // BIGNUM:

	while (true) {
		switch (current) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9': 
			break;
		case '_':
			ignore_next(); continue;
		default:
			return tk_bignum;
		}
		next();
	}

}

void decimal()
{
	float divisor = 10;
	floatnum = 0;

	while (true) {
		switch(current) {
			case '0':break;
			case '1': floatnum += (1 / divisor); break;
			case '2': floatnum += (2 / divisor); break;
			case '3': floatnum += (3 / divisor); break;
			case '4': floatnum += (4 / divisor); break;
			case '5': floatnum += (5 / divisor); break;
			case '6': floatnum += (6 / divisor); break;
			case '7': floatnum += (7 / divisor); break;
			case '8': floatnum += (8 / divisor); break;
			case '9': floatnum += (9 / divisor); break;
			case '_': ignore_next(); continue;
			default:
				return;
		}
		ignore_next();
		divisor *= 10;
	}
}

void unget()
{
	ungetc(current, file);
	--index;
}

void unget(char prev)
{
	unget();
	current = prev;
}



TokenOp number()
{
	base = 10;
	TokenOp result = digits();

	if (current == '.') {
		switch(ignore_next()) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		case '_':
			decimal();
			floatnum = (result == tk_bignum) ? atof(start) : fixnum + floatnum;
			result = tk_float;
			break;
		default:			
			unget('.');			
		}
	}

	switch  (current) {
	case 'e': case 'E':

		switch(ignore_next()) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			if (result == tk_bignum)
				floatnum = atof(start);
			else if (result == tk_fixnum)
				floatnum = fixnum;

			digits();	
			
			floatnum = floatnum * pow(10.0, fixnum);
			
			result = tk_float;
			break;
		default:			
			unget('e');
		}
		break;
	}

	return result;
}

TokenOp octal()
{
	unsigned int x = 0;

	while(true) {
		switch (current) {
		case '0': x = ((x << 3)); break;
		case '1': x = ((x << 3) + 1); break;
		case '2': x = ((x << 3) + 2); break;
		case '3': x = ((x << 3) + 3); break;
		case '4': x = ((x << 3) + 4); break;
		case '5': x = ((x << 3) + 5); break;
		case '6': x = ((x << 3) + 6); break;
		case '7': x = ((x << 3) + 7); break;	
		case '_':
			ignore_next();
			continue;
		default:
			fixnum = x;
			discard();
			return tk_fixnum;
		}
		next();
		if (x > INT_MAX) break;
	}


	while(true) {
		switch (current) {
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
			break;
		case '_':
			continue;
		default:
			base = 8;
			return tk_bignum;
		}
		next();
	}
}

TokenOp binary()
{
	unsigned int x = 0;

	do {
		switch(current) {
		case '0': x = (x << 1); break;
		case '1': x = (x << 1) + 1; break;
		default:
			fixnum = x;
			discard();
			return tk_fixnum;
		}
		next();
	} while (x <= INT_MAX);
	
	while (true) {
		switch(current){ 
		case '0': case '1': 
			next();
			continue;
		}
		base = 2;
		return tk_bignum;
	}
}

TokenOp hex()
{
	unsigned int x = 0;

	 while (true) {
		switch (current) {
		case '0': x = (x << 4); break;
		case '1': x = (x << 4) + 1; break;
		case '2': x = (x << 4) + 2; break;
		case '3': x = (x << 4) + 3; break;
		case '4': x = (x << 4) + 4; break;
		case '5': x = (x << 4) + 5; break;
		case '6': x = (x << 4) + 6; break;
		case '7': x = (x << 4) + 7; break;
		case '8': x = (x << 4) + 8; break;
		case '9': x = (x << 4) + 9; break;
		case 'A':case 'a': x = (x << 4) + 10; break;
		case 'B':case 'b': x = (x << 4) + 11; break;
		case 'C':case 'c': x = (x << 4) + 12; break;
		case 'D':case 'd': x = (x << 4) + 13; break;
		case 'E':case 'e': x = (x << 4) + 14; break;
		case 'F':case 'f': x = (x << 4) + 15; break;

		case '_':
			ignore_next(); continue;
		default:
			fixnum = x;
			discard();
			return tk_fixnum;
		}
		if (x > INT_MAX) break;
		next();
	}

	// We got a bignum!

	while (true) {
		switch (current) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
			break;
		case '_':
			ignore_next(); continue;
		default:
			base = 16;
			return tk_bignum;
		}
		next();
	}

}

void comment()
{
	while (true) {
		switch(ignore_next()) {
		case '\n': case EOF:
			return;
		}
	}
}

/*Value token(TokenOp op)
{
	Value result = token::tokens.next();
	result->lexeme = lexeme();
	result->opcode = op;

	return result;
}*/

TokenOp scan()
{
	
while (!feof(file))
{	
	start = buffer.end();
	
	switch (current) {
	case '0': 
		switch (ignore_next()) {
		case 'x': ignore_next(); return hex();
		case 'b': ignore_next(); return binary();
		default : return octal();
		}		
	case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		return number();

	/* OPERATORS */
	case '<': 
		switch(ignore_next()) {
		case '<': 
			ignore_next();
			if (nalnum())
				return N(tk_lshft);

			ident();
			if (current == '\n')
			{
				new_line();
				next();
				return delimeter_string(lexeme());
			} else
				return tk_ident;
		case '=': return nmatch('>') ? N(tk_cmp) : D(tk_leq);
		}
		return D(tk_lt);
	case '>':
		switch(ignore_next()) {
		case '>': return N(tk_rshft);
		case '=': return N(tk_geq);
		default : return D(tk_gt);
		}
	case '+': return nmatch('=') ? N(tk_passign) : tk_plus;
	case '-': return N(tk_minus);
	case '{': return N(tk_lbrace);
	case '}': return N(tk_rbrace);
	case '[': return N(tk_lbrack);
	case ']': return N(tk_rbrack);
	case '(': return N(tk_lparen);
	case ')': return N(tk_rparen);
	case ';': return N(tk_eol);
	case ',': return N(tk_comma);
	case '%': 
		
		switch(ignore_next()) {
		case 'q':
			if (nmatch('{'))
			{
				ignore_next();
				return single_brace_string();
			}
			break;
		case 'Q':
			if (nmatch('{'))
			{
				ignore_next();
				return double_brace_string();
			}
			break;
		default:
			return tk_percent;
		}
		unget();
		return tk_percent;
	case '*': return nmatch('*') ? N(tk_pow)    : D(tk_star);
	case '.': 
		if (ignore_next() == '.')
			return (ignore_next() == '.') ? N(tk_dot3) : tk_dot2;
		
		return method();
	case '=':
		switch(ignore_next()) {
		case '=': return nmatch('=') ? N(tk_eqq) : D(tk_eq);
		case '>': return N(tk_assoc);
		case '~': return N(tk_match);
		default:  return D(tk_assign);
		}
	case '!': 
		switch (ignore_next()) {
		case '=': return N(tk_neq);
		case '~': return N(tk_nmatch);
		default : return D(tk_not);
		}
	case ':': 
		if (nmatch(':'))
			return N(tk_colon2);
		else if (nalnum())
			return D(tk_colon);
		ident();
		return tk_symbol;
	case '/': return N(tk_div);
	case '&': return nmatch('&') ? N(tk_land) : D(tk_and);
	case '|': return nmatch('|') ? N(tk_lor)  : D(tk_bar);
	case '~': return nmatch('=') ? N(tk_match): D(tk_neg);
	case '?': return N(tk_question);
	case '^': return N(tk_xor);

	/* VARIABLES */
	case '@': 
		if (ignore_next() == '@') {
			start=buffer.end();
			ignore_next();
			ident();
			return tk_cvar;
		} 
		return ident(), tk_lvar;
	case '$': 
		start = buffer.end();
		return gvar();

	/* KEYWORDS */
	case '_': if (next() == '_') {
			switch (next()) {
			case 'L': return next(),match_key('I', 'N', 'E', '_', '_', tk__LINE__);
			case 'F': return next(), match_key('I', 'L', 'E', '_', '_', tk__FILE__);
			case 'E': 
				if (next() == 'N') {
					switch(next()) {
					case 'D': return next(), match_key('_', '_', tk__END__);
					case 'C': 
						next();
						if (match('O') && match('D') && match('I') && 
						    match('N') && match('G') && match('_') &&
				                    match('_') && nalnum())
						        discard();
							return tk__ENCODING__;
					}
				}
			}
		  }
		  break;

	case 'B': return next(), match_key('E', 'G', 'I', 'N', tk_BEGIN);
	case 'E': return next(), match_key('N', 'D', tk_END);

	case 'a':
		switch (next()) {
		case 'n': return next(), match_key('d', tk_kand);
		case 'l': return next(), match_key('i', 'a', 's', tk_alias);	
		}
		break;
	
	case 'b': 
		switch(next()) {
		case 'e': return next(), match_key('g', 'i', 'n', tk_begin);
		case 'r': return next(), match_key('e', 'a', 'k', tk_break);
		default: return ident();
		}		
	case 'c': // class, continue, case
		switch (next()) {
		case 'a': return next(), match_key('s', 'e', tk_case);
		case 'l': return next(), match_key('a', 's', 's', tk_class);
		case 'o':
			next();
			if (match('n') && match('t') && match('i') && match('n') &&
			    match('u') && match('e') && nalnum())
			{
				discard();
				return tk_continue;
			}
		}
		break;
	case 'd':
		switch(next()) {
		case 'o': return next(), match_key(tk_do);
		case 'e': 
			if (next() == 'f') {
				if (next() == 'i')
					return next(), match_key('n', 'e', 'd', '?', tk_defined);
				else if (nalnum())
				{
					discard();
					return tk_def;
				}
			}
		}
		break;
	
	case 'e': // else, elsif, end
		switch (next()) {
		case 'l': 
			next();
			if (match('s'))
			{
				if (match('e') && nalnum())
					return discard(), tk_else;
				return match_key('i', 'f', tk_elsif);
			}
			return ident();
		case 'n': 
			switch(next()) {
			case 'd': return next(), match_key(tk_end);
			case 's': return next(), match_key('u', 'r', 'e', tk_ensure);
			}
		}
		break;
	case 'f': // false, for
		switch (next()) {
		case 'a': return next(), match_key('l', 's', 'e', tk_false);
		case 'o': return next(), match_key('r', tk_for);
		}
		break;
	case 'i': // if, in, 
		switch(next()) {
		case 'f': return next(), match_key(tk_if);				
		case 'n': return next(), match_key(tk_in);
		}
		break;
	case 'm': // module
		next();
		return (match('o') && match('d') && match('u') && match('l')
			&& match('e') && nalnum()) ? discard(), tk_module : ident();
	case 'n': // next
		switch(next()) {
		case 'e': return next(), match_key('x', 't', tk_next);
		case 'o': return next(), match_key('t', tk_not);
		case 'i': return next(), match_key('l', tk_nil);
		}
		break;
	case 'o': // or
		return next(), match_key('r', tk_kor);
	case 'r': // return, retry, redo
		next();
		if (match('e'))
		{
			switch (current)
			{
			case 'd': return next(), match_key('o', tk_redo);
			case 't':
				next();
				if (match('u')) return match_key('r', 'n', tk_return);
				if (match('r')) return match_key('y', tk_retry);
			case 's': return next(), match_key('c', 'u', 'e', tk_rescue);
			}
		}
		break;
	case 's': // super
		switch (next()) {
		case 'e': return next(), match_key('l', 'f', tk_self);
		case 'u': return next(), match_key('p', 'e', 'r', tk_super);
		}
		break;
	case 't': // true, then
		switch (next()) {
		case 'r': return next(), match_key('u', 'e', tk_true);
		case 'h': return next(), match_key('e', 'n', tk_then);
		}
		break;
	case 'u': // undef, unless, until
		switch (next())	{
		case 'n':
			switch(next()) {
			case 'd': return next(), match_key('e','f', tk_undef);
			case 'l': return next(), match_key('e', 's', 's', tk_unless);
			case 't': return next(), match_key('i', 'l', tk_until);
			}
		}
		break;
	case 'w': // while, when, 
		switch (next()) {
		case 'h':
			switch(next()) {
			case 'e': return next(), match_key('n', tk_when);
			case 'i': return next(), match_key('l', 'e', tk_while);
			}
		}
		break;
	case 'y': // yield
		return next(), match_key('i', 'e', 'l', 'd', tk_yield);
	// Comments
	case '\'': ignore_next(); return single_quote_string();
	case '"' : ignore_next(); return string();

	// OTHERS
	case TK_STRING_EXPR: return N(tk_string_expr);

	case '#': comment();
		if (current == EOF)
			return tk_nop;
	case '\n': new_line();
		ignore_next();
		return tk_eol;
	case '\\':
		if (nmatch('\n'))
		{
			ignore_next();
			new_line();
			continue;
		}

	case ' ': case '\t':  case '\v': case '\f': case '\r':
		ignore_next();
		continue;
	default:
		break;
	};
	return ident();
}
	return tk_nop;

}

} }
