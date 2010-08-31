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

#ifndef RUBYC_SCANNER_H
#define RUBYC_SCANNER_H

#include <cstdio>
#include "rubyc/token.h"

#include "structures/array.h"

namespace rubyc { namespace scanner {

	extern int    base;
	extern int    fixnum;
	extern int    line;
	extern double floatnum;
	extern int index;

	extern Array<char> buffer;

	extern TokenOp regexp();
	extern TokenOp string();

	/**
	 * Discards current lexeme.
	 */
	extern void    discard();

	/**
	 * Returns next token opcode
	 */
	extern TokenOp scan();

	/**
	 * Returns pointer to zero terminated string containing the current lexeme.
	 * String will stay in memory until it is overwritten or discarded.
	 */
	extern const char* lexeme();

	extern void init(FILE* _file=stdin);
} }

#endif
