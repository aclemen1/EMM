/*
 *			
 *		Layout for LaTeX
 *
 *		LaTeXLayout.hpp
 *		Version 2.1, 30-Jan-2002, 17:15
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Provides a layout environment for
 *		outputing results of the EMM.
 *
 */


#ifndef _LaTeXLayout
#define _LaTeXLayout

#include <iostream>
#include "Mod2GradedGroups.hpp"
#include "Mod2AdmissibleSequences.hpp"

using namespace std;

void LaTeXLayoutTopMatter(ostream&);
void LaTeXLayoutTwoColumns(ostream&,
	GradedGroup,
	GradedGroup);
void LaTeXLayoutGenerators(
	ostream&,
	Mod2AdmissibleSequences*,
	int,
	int);
void LaTeXLayoutBackMatter(ostream&);

#endif
