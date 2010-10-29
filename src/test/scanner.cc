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
#include <cstdlib>
#include <cassert>
#include <cstring>

#include <rubyc/scanner.h>

using namespace rubyc;
using namespace rubyc::scanner;

void test_keywords()
{
	assert(scan() == tk_class);
	assert(scan() == tk_module);
	assert(scan() == tk_def);
	assert(scan() == tk_undef);
	assert(scan() == tk_begin);
	assert(scan() == tk_rescue);
	assert(scan() == tk_ensure);
	assert(scan() == tk_end);
	assert(scan() == tk_if);
	assert(scan() == tk_unless);
	assert(scan() == tk_then);
	assert(scan() == tk_elsif);
	assert(scan() == tk_else);
	assert(scan() == tk_case);
	assert(scan() == tk_when);
	assert(scan() == tk_while);
	assert(scan() == tk_eol);

	assert(scan() == tk_until);
	assert(scan() == tk_for);
	assert(scan() == tk_break);
	assert(scan() == tk_next);
	assert(scan() == tk_redo);
	assert(scan() == tk_retry);
	assert(scan() == tk_in);
	assert(scan() == tk_do);
	assert(scan() == tk_return);
	assert(scan() == tk_yield);
	assert(scan() == tk_super);
	assert(scan() == tk_self);
	assert(scan() == tk_alias);
	assert(scan() == tk_BEGIN);
	assert(scan() == tk_END);
	assert(scan() == tk_eol);

	assert(scan() == tk__LINE__);
	assert(scan() == tk__FILE__);
	assert(scan() == tk__END__);
	assert(scan() == tk__ENCODING__);
	assert(scan() == tk_continue);
	assert(scan() == tk_kand);
	assert(scan() == tk_kor);
	assert(scan() == tk_not);
	assert(scan() == tk_defined);
	assert(scan() == tk_nil);
	assert(scan() == tk_true);
	assert(scan() == tk_false);
	assert(scan() == tk_eol);
}

void test_operators()
{
	assert(scan() == tk_eol);

	assert(scan() == tk_and);
	assert(scan() == tk_eol);

	assert(scan() == tk_bar);
	assert(scan() == tk_neg);

	assert(scan() == tk_land);
	assert(scan() == tk_lor);
	assert(scan() == tk_not);

	assert(scan() == tk_plus);
	assert(scan() == tk_minus);
	assert(scan() == tk_star);
	assert(scan() == tk_div);
	assert(scan() == tk_pow);
	assert(scan() == tk_cmp);
	assert(scan() == tk_neq);
	assert(scan() == tk_eq);
	assert(scan() == tk_eqq);
	assert(scan() == tk_lt);
	assert(scan() == tk_gt);
	assert(scan() == tk_leq);
	assert(scan() == tk_geq);

	assert(scan() == tk_lshft);
	assert(scan() == tk_rshft);
	assert(scan() == tk_lbrack);
	assert(scan() == tk_rbrack);
	assert(scan() == tk_lbrace);
	assert(scan() == tk_rbrace);
	assert(scan() == tk_lparen);
	assert(scan() == tk_rparen);
	assert(scan() == tk_colon);
	assert(scan() == tk_colon2);
	assert(scan() == tk_assoc);
	assert(scan() == tk_comma);
	assert(scan() == tk_percent);
	assert(scan() == tk_assign);
	assert(scan() == tk_match);
	assert(scan() == tk_nmatch);
	assert(scan() == tk_eol);
}


void test_idents()
{
	assert(scan() == tk_ident);
	assert(strcmp("identifier", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("classified", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("defin", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("beginning", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("ending", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("aliases", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("cont", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("unle", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("th", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("BEG", scanner::lexeme())==0);
	assert(scan() == tk_ident);
	assert(strcmp("EN", scanner::lexeme())==0);
	assert(scan() == tk_eol);
	assert(scan() == tk_eol);
}

void test_vars()
{
	assert(scan() == tk_lvar);
	assert(strcmp("local_var292kk", scanner::lexeme())==0);
	assert(scan() == tk_cvar);
	assert(strcmp("class_variable982xx", scanner::lexeme())==0);
	assert(scan() == tk_gvar);
	assert(strcmp("globalvariable99xx___", scanner::lexeme())==0);
	assert(scan() == tk_eol);
	assert(scan() == tk_eol);
}

void test_string()
{
	assert(scan() == tk_string);
	assert(strcmp("Single Quote String \\ \'", scanner::lexeme())==0);
	assert(scan() == tk_eol);

	assert(scan() == tk_string);
	assert(strcmp("\"\\\a\b\r\n \t\"", scanner::lexeme())==0);
	assert(scan() == tk_eol);

	assert(scan() == tk_string);
	assert(scan() == tk_string_expr);
	assert(scan() == tk_eol);

	assert(scan() == tk_ident);
	assert(strcmp("puts", scanner::lexeme())==0);
	assert(scan() == tk_string);
	assert(strcmp("hello", scanner::lexeme())==0);
	assert(scan() == tk_eol);

	assert(scan() == tk_ident);
	assert(strcmp("puts", scanner::lexeme())==0);
	assert(scan() == tk_string);
	assert(scan() == tk_eol);

	assert(scan() == tk_string);
	assert(scan() == tk_method_call);
	assert(strcmp("each_char", scanner::lexeme())==0);
	assert(scan() == tk_lbrace);
	assert(scan() == tk_rbrace);
	assert(scan() == tk_eol);

	assert(scan() == tk_rbrace);
	assert(scanner::string() == tk_string);
	assert(strcmp(" hello", scanner::lexeme())==0);
	assert(scan() == tk_eol);

	assert(scan() == tk_string);
	assert(strcmp("Single Brace String", scanner::lexeme())==0);
	assert(scan() == tk_eol);

	assert(scan() == tk_string);
	assert(strcmp("Capital Q Brace String", scanner::lexeme())==0);
	assert(scan() == tk_eol);

	assert(scan() == tk_eol);
}

void fix_eq(int x) 
{
	assert(scan() == tk_fixnum);
	assert(scanner::fixnum == x);
}

void dump_buffer()
{
	for (char* x = buffer.begin(); x != buffer.end(); ++x)
	{
		char c = *x;
		putchar((c == 0) ? '\n' : *x);
	}
}

void dump()
{
	while (TokenOp t = scan())
		token::pp(t);
}

void test_scanner()
{
	puts("Testing Scanner");

	//vm::initialize();

	FILE* testfile = fopen("../../test/scanner.test", "r");
	//Value x, y;
	
	init(testfile);
	test_keywords();
	test_operators();
	test_idents();
	test_vars();
	
	assert(scan() == tk_def);
	assert(scan() == tk_ident);
	assert(strcmp("loadtest", scanner::lexeme())==0);
	assert(scan() == tk_lparen);
	assert(scan() == tk_ident);
	assert(strcmp("libname", scanner::lexeme())==0);
	assert(scan() == tk_rparen);
	assert(scan() == tk_eol);

	assert(scan() == tk_ident);
	assert(strcmp("require", scanner::lexeme())==0);
	assert(scan() == tk_lparen);
	assert(scan() == tk_ident);
	assert(strcmp("libname", scanner::lexeme())==0);
	assert(scan() == tk_rparen);
	assert(scan() == tk_eol);

	assert(scan() == tk_ident);
	assert(strcmp("in_critical", scanner::lexeme())==0);
	assert(scan() == tk_do);
	assert(scan() == tk_eol);

	assert(scan() == tk_ident);
	assert(strcmp("in_progname", scanner::lexeme())==0);
	assert(scan() == tk_lparen);
	assert(scan() == tk_ident);
	assert(strcmp("libpath", scanner::lexeme())==0);
	assert(scan() == tk_lparen);
	assert(scan() == tk_ident);
	assert(strcmp("libname", scanner::lexeme())==0);
	assert(scan() == tk_rparen);
	assert(scan() == tk_rparen);
	assert(scan() == tk_do);
	assert(scan() == tk_eol);

	assert(scan() == tk_ident);
	assert(strcmp("eval_part", scanner::lexeme())==0);
	assert(scan() == tk_lparen);
	assert(scan() == tk_ident);
	assert(strcmp("libname", scanner::lexeme())==0);
	assert(scan() == tk_comma);
	assert(scan() == tk_div);
	scanner::regexp();
	assert(scan() == tk_comma);
	assert(scan() == tk_string);
	assert(scan() == tk_rparen);
	assert(scan() == tk_eol);

	assert(scan() == tk_end);
	assert(scan() == tk_eol);

	assert(scan() == tk_end);
	assert(scan() == tk_eol);

	assert(scan() == tk_end);
	assert(scan() == tk_eol);
	assert(scan() == tk_eol);

	assert(scan() == tk_gvar);
	assert(strcmp(":", scanner::lexeme())==0);
	assert(scan() == tk_method_call);
	assert(strcmp("find", scanner::lexeme())==0);
	assert(scan() == tk_do);
	assert(scan() == tk_bar);
	assert(scan() == tk_ident);
	assert(strcmp("path", scanner::lexeme())==0);
	assert(scan() == tk_bar);
	assert(scan() == tk_eol);

	assert(scan() == tk_ident);
	assert(strcmp("File", scanner::lexeme())==0);
	assert(scan() == tk_method_call);
	assert(strcmp("file?", scanner::lexeme())==0);
	assert(scan() == tk_lparen);
	assert(scan() == tk_ident);
	assert(strcmp("testname", scanner::lexeme())==0);
	assert(scan() == tk_rparen);
	assert(scan() == tk_eol);

	assert(scan() == tk_end);
	assert(scan() == tk_eol);
	assert(scan() == tk_eol);

	test_string();

	fix_eq(1234567890);
	assert(scan() == tk_eol);

	assert(scan() == tk_bignum);
	assert(strcmp(scanner::lexeme(), "12345678901234567890")==0);
	discard();
	assert(scan() == tk_eol);
	
	fix_eq(123456789);
	assert(scan() == tk_eol);

	assert(scan() == tk_float);
	assert(scanner::floatnum == 12345.67890);
	assert(scan() == tk_eol);


	// 12345.to_f
	assert(scan() == tk_fixnum);
	assert(scanner::fixnum == 12345);
	assert(scan() == tk_method_call);
	assert(strcmp("to_f", scanner::lexeme())==0);
	assert(scan() == tk_eol);

	assert(scan() == tk_float);
	assert(scanner::floatnum == 123.222);
	assert(scan() == tk_method_call);
	assert(strcmp("abs", scanner::lexeme())==0);
	assert(scan() == tk_eol);

	// Hex
	fix_eq(0x01234abc);
	assert(scan() == tk_eol);

	assert(scan() == tk_bignum);
	assert(strcmp(lexeme(), "0123456789abcdef")==0);
	scanner::discard();
	assert(scan() == tk_eol);

	// Binary
	fix_eq(821);
	assert(scan() == tk_eol);
	
	assert(scan() == tk_bignum);
	assert(0==strcmp(scanner::lexeme(), "110011010111001101011100110101110011010111001101011100110101110011010111001101011100110101110011010110101110011010111001101011100110101110011010111001101011010111001101011100110101110011010111001101011100110101"));
	scanner::discard();
	assert(scan() == tk_eol);

	// Octal
	fix_eq(001234567);
	assert(scan() == tk_eol);
	
	assert(scan() == tk_bignum);
	assert(strcmp(scanner::lexeme(), "01234567001234567001234567")==0);
	scanner::discard();
	assert(scan() == tk_eol);
	assert(scan() == tk_eol);

	assert(scan() == tk_symbol);
	assert(strcmp("symbol123__", scanner::lexeme())==0);
	assert(scan() == tk_eol);
	assert(scan() == tk_eol);

	fix_eq(10);
	assert(scan() == tk_dot2);
	fix_eq(100);
	assert(scan() == tk_eol);

	fix_eq(1298);
	assert(scan() == tk_dot3);
	fix_eq(1010);
	assert(scan() == tk_eol);

	assert(scan() == tk_float);
	assert(scanner::floatnum == 1233.22);
	assert(scan() == tk_dot3);
	assert(scan() == tk_float);
	assert(scanner::floatnum == 20.2);
	assert(scan() == tk_eol);
	assert(scan() == tk_eol);

	assert(scan() == tk_float);
	assert(scanner::floatnum == 23000000000.0);
	assert(scan() == tk_eol);

	assert(scan() == tk_float);
	assert(scanner::floatnum == 2999330000000.0);
	assert(scan() == tk_eol);

	fix_eq(3333);
	assert(scan() == tk_eol);
	assert(scan() == tk_eol);

	fix_eq(2147483647);
	assert(scan() == tk_eol);

	assert(scan() == tk_bignum);
	assert(scan() == tk_eol);
	assert(scan() == tk_eol);

	assert(scan() == tk_ident);
	assert(strcmp("identifier_with_no_eol", scanner::lexeme())==0);

	assert(scan() == tk_nop);

	// output buffer ( should be zero terminated )
	// dump_buffer();

	fclose(testfile);
}

int main()
{
	test_scanner();
	return 0;
}
