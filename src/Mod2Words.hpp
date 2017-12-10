/*
 *			
 *		Mod 2 words
 *
 *		Mod2Words.hpp
 *		Version 2.1, 31-Jan-2001, 02:27
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Provides a framework to deal with mod-2 words.
 *
 */


#ifndef _Mod2Words
#define _Mod2Words

#include <vector>

using namespace std;

enum Mod2Letter {empty,beta_2,sigma,gamma_2,phi_2,psi_2_to_s};

class Mod2PoweredLetter
{
	public:
		Mod2Letter letter;
		int power;
};

const Mod2PoweredLetter emptyMod2PoweredLetter = {empty,0};

class Mod2Word
{
	public:
		vector<Mod2PoweredLetter> word;
		void TeXShow(ostream&,int s=1);
		void concat(Mod2Letter, int power=1);
		void concat(Mod2PoweredLetter);
		Mod2PoweredLetter first();
		Mod2PoweredLetter last();
		int genus();
};
Mod2Word firstCech(Mod2Word);

#endif