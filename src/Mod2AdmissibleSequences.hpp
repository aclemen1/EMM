/*
 *			
 *		Mod 2 admissible sequences
 *
 *		Mod2AdmissibleSequences.hpp
 *		Version 2.1, 31-Jan-2001, 02:27
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Computes mod 2 admissible sequences of 
 *		given stable degree and excess.
 *
 */


#ifndef _Mod2AdmissibleSequences
#define _Mod2AdmissibleSequences

#include <vector>

using namespace std;

class IntSequence
{
	public:
		vector<int> sequence;
		void show();
		void TeXShow(ostream&);
		void append(int);
		int first();
		int last();
};

class Mod2AdmissibleSequence : virtual public IntSequence
{
	public:
		bool admissible();
		int stableDegree();
		int excess();
		int genus();
		void show();
		void TeXShow(ostream&);
		void TeXShowAsWord(ostream&,int n, int s=1);
		void TeXShowAsWordButFirst(
			ostream&,int n, int s=1);
};

class Mod2AdmissibleSequences
{
	public:
		vector<Mod2AdmissibleSequence> sequences;
		Mod2AdmissibleSequences();
		Mod2AdmissibleSequences(int stableDegree, 
								int excess);
		Mod2AdmissibleSequences(int stableDegree, 
								int minExcess, 
								int maxExcess);
		void filterByHeight(int height);
		void filterByEvenFirst();
		void show();
		void TeXShow(ostream&);
		void TeXShowAsWords(ostream&,int n, int s=1);
		void append(Mod2AdmissibleSequence);

	private:
		void iterate(
			Mod2AdmissibleSequence*,
			int stableDegree, 
			int excess);
};

#endif
