/*
 *			
 *		Mod 2 words
 *
 *		Mod2Words.hpp
 *      Version 2.1, 31-Jan-2002, 02:53
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Provides a framework to deal with 
 *		mod-2 words. 
 *		Show classes definitions below for more information.
 *
 */


#include<iostream>
#include "Mod2Words.hpp"

using namespace std;

// Class <Mod2Word> =========================================================

void Mod2Word::concat(Mod2Letter letter,int power)
{
	Mod2PoweredLetter PLetter;

	if(letter==empty||power==0) return;
	PLetter = last();
	if (PLetter.power==0 || 
		PLetter.letter==empty ||
		PLetter.letter!=letter) {
			PLetter.letter=letter;
			PLetter.power=power;
			word.push_back(PLetter);
			return;
	}
	word[word.size()-1].power+=power;
}

void Mod2Word::concat(Mod2PoweredLetter PLetter)
{
	if(PLetter.power==0||PLetter.letter==empty) return;
	concat(PLetter.letter,PLetter.power);
}

Mod2PoweredLetter Mod2Word::first()
{
	if (word.empty()) return emptyMod2PoweredLetter;
	return word[0];
}

Mod2PoweredLetter Mod2Word::last()
{
	if (word.empty()) return emptyMod2PoweredLetter;
	return word[word.size()-1];
}

/*
int Mod2Word::genus()
{
	if(word.empty()) return 0;
	if(word.size()==0 && word[0].letter==sigma) return 1;
	if(word.last()==sigma) return 2;
	if(word.last()==psi_2_to_s) return 3;
	return 0;
}
*/

void Mod2Word::TeXShow(ostream& os,int s)
{
	int i;
	
	if (word.empty()) return;
	for(i=0;i<word.size();i++) {
		switch (word[i].letter) {
			case beta_2:
				os<<"\\beta_2";
				break;
			case sigma:
				os<<"\\sigma";
				break;
			case gamma_2:
				os<<"\\gamma_2";
				break;
			case phi_2:
				os<<"\\varphi_2";
				break;
			case psi_2_to_s:
				if(s==1)
					os<<"\\psi_2"; else
					os<<"\\psi_{2^{"<<s<<"}}";
				break;
		}
		if(word[i].power>1) os<<"^{"<<word[i].power<<"}";
	}
}

Mod2Word firstCech(Mod2Word IncomingWord)
{
	Mod2Word word;
	int i;

	for(i=0;i<IncomingWord.word.size()-1;i++) {
		word.concat(IncomingWord.word[i+1]);
	}
	return word;
}
