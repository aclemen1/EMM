/*
 *			
 *		Mod-2 Eilenberg-MacLane spaces homology
 *
 *		Mod2EilenbergMacLaneHomology.hpp
 *		Version 2.1, 31-Jan-2001, 02:27
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Computes the mod-2 homology of
 *		Eilenberg-MacLane spaces.
 */


#ifndef _Mod2EilenbergMacLaneHomology
#define _Mod2EilenbergMacLaneHomology

#include <vector>
#include "Mod2AdmissibleSequences.hpp"
#include "Mod2GradedGroups.hpp"
#include "Mod2ElementaryComplexHomology.hpp"

using namespace std;

GradedGroup EMHomology(
	int logorder,
	int connexityPlusOne,
	int anticonnexity);

GradedGroup EMHomology(
	int logorder,
	int connexityPlusOne,
	int anticonnexity,
	Mod2AdmissibleSequences*);

GradedGroup EMCohomology(
	int logorder,
	int connexityPlusOne,
	int anticonnexity);

#endif
