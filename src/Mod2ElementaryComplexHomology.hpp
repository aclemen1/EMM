/*
 *			
 *		Mod-2 homology of elementary complexes
 *
 *		Mod2ElementaryComplexHomology.hpp
 *		Version 2.1, 31-Jan-2001, 02:27
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Provides mod-2 homology of elementary complexes.
 *
 */


#ifndef _Mod2ElementaryComplexHomology
#define _Mod2ElementaryComplexHomology

#include <vector>
#include "Mod2GradedGroups.hpp"

using namespace std;

GradedGroup ECHomology(
	int degree,
	int h,
	int anticonnexity);
GradedGroup ECCohomology(
	int degree,
	int h,
	int anticonnexity);

#endif
