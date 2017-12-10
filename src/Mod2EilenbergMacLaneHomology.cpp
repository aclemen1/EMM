/*
 *			
 *		Mod-2 Eilenberg-MacLane spaces homology
 *
 *		Mod2EilenbergMacLaneHomology.cpp
 *      Version 2.1, 31-Jan-2002, 02:53
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Computes the mod-2 homology of Eilenberg-MacLane spaces.
 *		Show classes definitions below for more information.
 *
 */


#include<iostream>
#include "Mod2EilenbergMacLaneHomology.hpp"
#include "Mod2AdmissibleSequences.hpp"

using namespace std;

GradedGroup EMHomology(int logorder,int connexityPlusOne,int anticonnexity)
{
	GradedGroup GGroup;
	Mod2AdmissibleSequences* pSequences;
	int stableDegree;
	int i;

	GGroup = ECHomology(connexityPlusOne,logorder,anticonnexity);
	
	for(stableDegree=0;stableDegree<=anticonnexity-connexityPlusOne;stableDegree++) {
		pSequences = new Mod2AdmissibleSequences(stableDegree,0,connexityPlusOne-1);
		pSequences->filterByEvenFirst();

		for(i=1;i<=pSequences->sequences.size();i++) {
			if (pSequences->sequences[i-1].stableDegree()>=0)
			GGroup=Kunneth(GGroup,ECHomology(pSequences->sequences[i-1].stableDegree()+connexityPlusOne,1,anticonnexity));
		};

	
		delete pSequences;	
	};

	return GGroup;
}

GradedGroup EMHomology(int logorder,int connexityPlusOne,int anticonnexity, Mod2AdmissibleSequences* generators)
{
	GradedGroup GGroup;
	Mod2AdmissibleSequences* pSequences;
	Mod2AdmissibleSequence stableDegreeZeroGenerator;
	int stableDegree;
	int i;

	GGroup = ECHomology(connexityPlusOne,logorder,anticonnexity);
	stableDegreeZeroGenerator.append(0);
	generators->append(stableDegreeZeroGenerator);
	
	for(stableDegree=0;stableDegree<=anticonnexity-connexityPlusOne;stableDegree++) {
		pSequences = new Mod2AdmissibleSequences(stableDegree,0,connexityPlusOne-1);
		pSequences->filterByEvenFirst();

		for(i=1;i<=pSequences->sequences.size();i++) {
			if (pSequences->sequences[i-1].stableDegree()>=0) {
				generators->append(pSequences->sequences[i-1]);
				GGroup=Kunneth(GGroup,ECHomology(pSequences->sequences[i-1].stableDegree()+connexityPlusOne,1,anticonnexity));
			}
		};

	
		delete pSequences;	
	};

	return GGroup;
}

GradedGroup EMCohomology(int logorder,int connexityPlusOne,int anticonnexity)
{
	return UniversalCoefficients(EMHomology(logorder,connexityPlusOne,anticonnexity));
}