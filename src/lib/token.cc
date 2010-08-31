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

#include <cstdio>

#include "rubyc/token.h"

namespace rubyc { 
	
	namespace token {	

	const char* to_str(TokenOp op)
	{
		static const char* op_names[] = {
			"EOF",
			"class", "module", "def", "undef", "begin", "rescue", "ensure",
			"end", "if", "unless", "then", "elsif", "else", "case", "when", 
			"while", "until", "for", "break", "next", "redo", "retry", "in",
			"do", "return", "yield", "super", "self", "alias", "defined", "BEGIN",
			"END", "__LINE__", "__FILE__", "__END__", "__ENCODING__", "continue",
			// Operators
			"and", "or", "xor", "~", "&&", "||", "!", "|", "&", "|",
			"<", ">", "+", "-", "**", "<=>", "!=", "==", "===",
			">=", "<=", "~=", "!~", "..", "...", 
			"[]", "[]=", "<<", ">>",
			"::", ":", "=>", "(", ")", "[", "]", 
			"{", "}", "*", "->", ",", "%", 
			"=", "+=",
			"/", "?", "true", "false", "nil", ".",

			"variable", "global", "class-variable", "Regexp",
			"call", "string-expr", "symbol",
			"var-method", "c-method", "method",
			"Fixnum", "Float", "String", "Bignum",

			"block", "range", "ref",

			"push", "call",
			
			"identifier", "EOL"
		};

		return op_names[op];
	}

	void pp(TokenOp op)
	{
		printf("%s", to_str(op));
	}

} }
