/*
 *			
 *		Mod 2 admissible sequences
 *
 *		Mod2AdmissibleSequences.cpp
 *      Version 2.1, 31-Jan-2002, 02:53
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Computes mod 2 admissible sequences of given stable degree and excess.
 *		Show classes definitions below for more information.
 *
 */


#include<iostream>
#include "Mod2AdmissibleSequences.hpp"
#include "Mod2Words.hpp"

using namespace std;

// Class <IntSequence> =========================================================

void IntSequence::show()
{
	int i;
	cout<<"Showing sequence "<<this<<"\n";
	if (sequence.empty()==true) return;
	for(i=0;i<sequence.size()-1;i++)
		cout<<sequence[i]<<",";
	cout<<sequence[i]<<"\n";
}

void IntSequence::TeXShow(ostream& os)
{
	int i;
	if (sequence.empty()==true) 
		{
			os<<"$()$";
			return;
		}
	os<<"$(";
	for(i=0;i<sequence.size()-1;i++) {
		os<<sequence[i]<<",";
	}
	os<<sequence[i]<<")$";
}

void IntSequence::append(int value)
{
	sequence.push_back(value);
}

int IntSequence::first()
{
	if (sequence.empty()==true) return -1;
	return sequence[0];
}

int IntSequence::last()
{
	if (sequence.empty()==true) return -1;
	return sequence[sequence.size()-1];
}

// Class <Mod2AdmissibleSequence> ==============================================

bool Mod2AdmissibleSequence::admissible()
{
	int i;
	if (sequence.size()<2) return true;
	for(i=0;i<sequence.size()-1;i++)
		if (sequence[i]<2*sequence[i+1]) return false;
	return true;
}

int Mod2AdmissibleSequence::stableDegree()
{
	int i;
	int foo = 0;
	if (sequence.empty()==true) return -1;
	for(i=0;i<sequence.size();i++)
		foo+=sequence[i];
	return foo;
}

int Mod2AdmissibleSequence::excess()
{
	return 2*first()-stableDegree();
}

int Mod2AdmissibleSequence::genus()
{
	if(first()==0 || first()==1) return 1;
	if(last()%2==0) return 2;
	return 3;
}

void Mod2AdmissibleSequence::show()
{
	IntSequence::show();
	cout<<"(admissible: "<<admissible()
		<<", stable degree: "<<stableDegree()
		<<", excess       : "<<excess()<<")\n";
}

void Mod2AdmissibleSequence::TeXShow(ostream& os)
{
	IntSequence::TeXShow(os);
	os<<" is mod $2$ admissible of stable degree $"<<stableDegree()
		<<"$ and excess $"<<excess()<<"$";
}

Mod2AdmissibleSequence* firstCech(Mod2AdmissibleSequence *pIncomingSequence)
{
	Mod2AdmissibleSequence* pSequence;
	int i;

	pSequence = new Mod2AdmissibleSequence;
	for(i=0;i<pIncomingSequence->sequence.size()-1;i++) {
		pSequence->append(pIncomingSequence->sequence[i+1]);
	}
	return pSequence;
}

void g_function(Mod2Word* pWord, Mod2AdmissibleSequence* pIncomingSequence, int n, int s)
{
	Mod2AdmissibleSequence* pNewSequence;
	int a_0;
	int e;
	
	a_0=pIncomingSequence->first();
	e=pIncomingSequence->excess();

	if (a_0<=0) {
//		cout<<"\\sigma";
//		if (n>=1) cout<<"^{"<<n<<"}";
		pWord->concat(sigma,n);
		return;
	};
	if (a_0==1) {
//		if (n>=2) cout<<"\\sigma^{"<<n-1<<"}";
		if (n>=2) pWord->concat(sigma,n-1);
//		cout<<"\\psi";
//		if (s>1) cout<<"_{2^{"<<s<<"}}"; else cout<<"_2";
		pWord->concat(psi_2_to_s);
		return;
	};
	if (a_0%2==0 && e<n) {
//		cout<<"\\beta_2";
		pWord->concat(beta_2);
//		if (n-e-1>0) cout<<"\\sigma";
//		if (n-e-1>1) cout<<"^{"<<n-e-1<<"}";
		if (n-e-1>0) pWord->concat(sigma,n-e-1);
//		cout<<"\\varphi_2";
		pWord->concat(phi_2);

		pNewSequence = firstCech(pIncomingSequence);
		g_function(pWord,pNewSequence,pIncomingSequence->excess(),s);
		delete pNewSequence;
		return;
	};
	if (a_0%2==0 && e==n) {
//		cout<<"\\gamma_2";
		pWord->concat(gamma_2);

		pNewSequence = firstCech(pIncomingSequence);
		g_function(pWord,pNewSequence,n,s);
		delete pNewSequence;
		return;
	};
	if (a_0%2==1) {
//		if (n-e>0) cout<<"\\sigma";
//		if (n-e>1) cout<<"^{"<<n-e<<"}";
		if (n-e>0) pWord->concat(sigma,n-e);
//		cout<<"\\varphi_2";
		pWord->concat(phi_2);

		pNewSequence = firstCech(pIncomingSequence);
		g_function(pWord,pNewSequence,pIncomingSequence->excess()-1,s);
		delete pNewSequence;
		return;
	};
}

void Mod2AdmissibleSequence::TeXShowAsWord(ostream& os,int n, int s)
{
	Mod2Word* pWord;
	pWord = new Mod2Word;
	Mod2AdmissibleSequence* pSequence;
	pSequence = new Mod2AdmissibleSequence;
	pSequence->sequence=sequence;
	g_function(pWord,pSequence,n,s);
	delete pSequence;
	pWord->TeXShow(os,s);
	delete pWord;
}

void Mod2AdmissibleSequence::TeXShowAsWordButFirst(ostream& os,int n, int s)
{
	Mod2Word* pWord;
	pWord = new Mod2Word;
	Mod2AdmissibleSequence* pSequence;
	pSequence = new Mod2AdmissibleSequence;
	pSequence->sequence=sequence;
	g_function(pWord,pSequence,n,s);
	delete pSequence;
	firstCech(*pWord).TeXShow(os,s);
	delete pWord;
}

// Class <Mod2AdmissibleSequences> =============================================

Mod2AdmissibleSequences::Mod2AdmissibleSequences(void)
{
}

Mod2AdmissibleSequences::Mod2AdmissibleSequences(int stableDegree, int excess)
{
	if ((stableDegree+excess)%2 != 0) return;
	Mod2AdmissibleSequence *notYetAdmissible;
	notYetAdmissible = new Mod2AdmissibleSequence;
	iterate(notYetAdmissible,stableDegree,excess);
	delete notYetAdmissible;
}

Mod2AdmissibleSequences::Mod2AdmissibleSequences(int stableDegree, int minExcess, int maxExcess)
{
	int excess;
	Mod2AdmissibleSequence *notYetAdmissible;
	for (excess=minExcess;excess<=maxExcess;excess++)
		if ((stableDegree+excess)%2 == 0)
			{
				notYetAdmissible = new Mod2AdmissibleSequence;
				iterate(notYetAdmissible,stableDegree,excess);
				delete notYetAdmissible;
			}
}


void Mod2AdmissibleSequences::show()
{
	int i;
	cout<<"Showing sequences "<<this<<"\n";
	for(i=1;i<=sequences.size();i++)
		sequences[i-1].show();
	cout<<"\n";
}

void Mod2AdmissibleSequences::TeXShow(ostream& os)
{
	int i;
	os<<"The Mod 2 Admissible Sequences Machine\n\nAlain Cl\\'ement, University of Lausanne, Switzerland\n\n\n";
	for(i=1;i<=sequences.size();i++)
		{
			sequences[i-1].TeXShow(os);
			os<<"\n\n";
		}
	os<<"\\end\n\n";
}

void Mod2AdmissibleSequences::TeXShowAsWords(ostream& os,int n, int s)
{
	int i;
	os<<"The Mod 2 Admissible Sequences Machine\n\nAlain Cl\\'ement, University of Lausanne, Switzerland\n\n\n";
	for(i=1;i<=sequences.size();i++)
		{
			os<<"$";
			sequences[i-1].TeXShowAsWord(os,n,s);
			os<<"$\n\n";
		}
	os<<"\\end\n\n";
}

void Mod2AdmissibleSequences::append(Mod2AdmissibleSequence sequence)
{
	sequences.push_back(sequence);
}

void Mod2AdmissibleSequences::iterate(Mod2AdmissibleSequence* pIncomingSequence,int stableDegree, int excess)
{
	Mod2AdmissibleSequence* pInProgressSequence;
	int i;
	int a;
	int newStableDegree;
	int newExcess;

	if ((stableDegree+excess)%2 != 0) return;

	a = (stableDegree+excess)/2;
	if (a>stableDegree) return;

	if (excess == 0 && stableDegree == 0) {
		append(*pIncomingSequence);
		return;
	}

	newStableDegree = stableDegree-a;
	for (i=a/2-excess;i<=a/2;i++) {
		newExcess = 2*i-newStableDegree;
		if (newExcess>=0) {
			pInProgressSequence = new Mod2AdmissibleSequence;
			*pInProgressSequence = *pIncomingSequence;	
			pInProgressSequence->append(a);
			iterate(pInProgressSequence,newStableDegree,newExcess);
			delete pInProgressSequence;
		}
	}
}

void Mod2AdmissibleSequences::filterByHeight(int height)
{
	int i;
	for(i=1;i<=sequences.size();i++)
		if (sequences[i-1].first()%2 == 0 && sequences[i-1].excess() == height) 
			sequences.erase(sequences.begin()+i-1);
}

void Mod2AdmissibleSequences::filterByEvenFirst()
{
	int i;
	for(i=1;i<=sequences.size();i++)
		if (sequences[i-1].first()%2 != 0 && !sequences[i-1].sequence.empty()) 
			sequences.erase(sequences.begin()+i-1);
}

