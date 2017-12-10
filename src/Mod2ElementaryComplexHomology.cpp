/*
 *			
 *		Mod-2 homology of elementary complexes
 *
 *		Mod2ElementaryComplexHomology.cpp
 *      Version 2.1, 31-Jan-2002, 02:53
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Provides mod-2 homology of elementary complexes.
 *		Show classes definitions below for more information.
 *
 */


#include<iostream>
#include "Mod2ElementaryComplexHomology.hpp"

using namespace std;

int nu_2(long int a)
{
	int n;
	n=0;
	while (a%2==0) {
		n++;
		a = a/2;
	};
	return n;
}

GradedGroup ECHomology(int degree,int logh,int anticonnexity)
{
	GradedGroup GGroup;
	int m;

	Group group;
	group.add(0,1);
	GGroup.add(group,0); // put an infinite cyclic group in degree 0
	
	for(m=1;m<=anticonnexity;m++) {
		if(degree%2==0) {
			if(m%degree==0) {
				GGroup.add(logh+nu_2(m/degree),1,m);
			};
		} else {
			if((m+1)%(degree+1)==0) {
				GGroup.add(logh,1,m);				
			};
		};
	};
	return GGroup;
}

GradedGroup ECCohomology(int degree,int logh,int anticonnexity)
{
	return UniversalCoefficients(ECHomology(degree,logh,anticonnexity));
}