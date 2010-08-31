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

#ifndef RUBYC_TOKEN_H
#define RUBYC_TOKEN_H

namespace rubyc { 

	enum TokenOp {
		tk_nop=0,
		// Keywords
		tk_class, tk_module, tk_def, tk_undef, tk_begin, tk_rescue, tk_ensure,
		tk_end, tk_if, tk_unless, tk_then, tk_elsif, tk_else, tk_case, tk_when,
		tk_while, tk_until, tk_for, tk_break, tk_next, tk_redo, tk_retry, tk_in,
		tk_do, tk_return, tk_yield, tk_super, tk_self, tk_alias, tk_defined, tk_BEGIN,
		tk_END, tk__LINE__, tk__FILE__, tk__END__, tk__ENCODING__, tk_continue, 
		// Operators
		tk_and, tk_or, tk_xor, tk_neg, tk_land, tk_lor, tk_not, tk_bar, tk_kand, tk_kor,
		tk_lt, tk_gt,
		tk_plus, tk_minus, tk_pow, tk_cmp, tk_neq, tk_eq, tk_eqq, 
		tk_geq, tk_leq, tk_match, tk_nmatch, tk_dot2, tk_dot3, 
		tk_aref /* [] */, tk_aset /* []= */, tk_lshft, tk_rshft,
		tk_colon2, tk_colon, tk_assoc /* => */, tk_lparen, tk_rparen, tk_lbrack, tk_rbrack,
		tk_lbrace, tk_rbrace, tk_star, tk_lambda, tk_comma, tk_percent, 
		tk_assign, 
		tk_passign,
		tk_div,	tk_question, tk_true, tk_false, tk_nil, tk_dot,

		tk_lvar, tk_gvar /* global */, tk_cvar /* class var */, tk_regexp,
		tk_method_call, tk_string_expr, tk_symbol, 
		
		tk_varmethod, tk_cmethod, tk_method,
		
		// Built In Types
		tk_fixnum, tk_float, tk_string, tk_bignum,
		// Built In Constants
		
		// Nodes
		tk_block, tk_range, tk_ref,

		// Bytecode
		tk_push, tk_call,
		
		// Misc
		tk_ident, tk_eol, tk_error

	};
	
	namespace token {

		extern const char* to_str(TokenOp op);
		extern void pp(TokenOp op);

	}

}

#endif