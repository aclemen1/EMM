/*
 *			
 *		Layout for LaTeX
 *
 *		LaTeXLayout.hpp
 *		Version 2.1, 30-Jan-2002, 17:15
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Provides a layout environment for outputing results of the EMM.
 *		Show classes definitions below for more information.
 *
 */


#include<iostream>
#include "LaTeXLayout.hpp"

using namespace std;

void LaTeXLayoutTopMatter(ostream& os)
{
	os<<"\\documentclass[12pt,a4paper]{article}\n";
	os<<"\\usepackage{amsfonts}\n";
	os<<"\\usepackage{supertabular}\n";
	os<<"\\begin{document}\n";
	os<<"\\newcommand{\\Z}{\\mathbb{Z}}\n";
	os<<"\\renewcommand{\\thefootnote}{\\fnsymbol{footnote}}";
	os<<"\\section*{The Eilenberg-MacLane machine\n";
	os<<"\\footnote{\\tiny Alain Cl\\'ement, Ph.D. Thesis, Institute of Mathematics, University of Lausanne, Switzerland.}\n";
	os<<"}\n";
	
	os<<"{\\it A C++ program designed to compute the integral homology and cohomology groups";
	os<<" of Eilenberg-MacLane spaces.}\\\\";
}

void LaTeXLayoutTwoColumns(ostream& os,GradedGroup GGroup1, GradedGroup GGroup2)
{
	int a1;
	int a2;
	int anticonnexity;
	int n;

	a1=GGroup1.anticonnexity();
	a2=GGroup2.anticonnexity();	
	anticonnexity=(a1>=a2)?a1:a2;


	os<<"\\tablehead{\\hline\%\n";
	os<<"\t$n$ &$H_n(-,\\Z)$ &$H^n(-,\\Z)$\\\\\%\n";
	os<<"\t\\hline &&\\\\}\n";
	os<<"\\tabletail{\\hline\%\n";
	os<<"\t\\multicolumn{3}{r}{\%\n";
	os<<"\t\\small\\slshape to be continued on the next page}\\\\}\n";
	os<<"\\tablelasttail{\\hline}\n";

	os<<"\\begin{supertabular}{|c|p{5.5cm}|p{5.5cm}|}\n";
	
	for(n=0;n<=anticonnexity;n++) {
		os<<"$"<<n<<"$\%\n";
		
		os<<"&$";
		GGroup1.GroupIn(n).TeXShow(os);
		os<<"$\%\n";

		os<<"&$";
		GGroup2.GroupIn(n).TeXShow(os);
		os<<"$\\\\\n";

		os<<"\n";
	}
	
	os<<"&&\\\\";
	os<<"\\end{supertabular}\n";
}

void LaTeXLayoutGenerators(ostream& os,Mod2AdmissibleSequences* generators,int n, int s=1)
{
	int i;
	Mod2AdmissibleSequence oneSequence;
	oneSequence.append(1);

	os<<"\\tablehead{\\hline\%\n";
	os<<"\tDegree &Genus &Generator\\\\\%\n";
	os<<"\t\\hline &&\\\\}\n";
	os<<"\\tabletail{\\hline\%\n";
	os<<"\t\\multicolumn{3}{r}{\%\n";
	os<<"\t\\small\\slshape to be continued on the next page}\\\\}\n";
	os<<"\\tablelasttail{\\hline}\n";

	os<<"\\begin{supertabular}{|c|c|p{9cm}|}\n";

	for(i=1;i<=generators->sequences.size();i++) {
		os<<"$"<<generators->sequences[i-1].stableDegree()+n<<"$\n";
		os<<"&$"<<generators->sequences[i-1].genus()<<"$ &$(";
		if(generators->sequences[i-1].stableDegree()==0)
			generators->sequences[i-1].TeXShowAsWord(os,n,s); else
			generators->sequences[i-1].TeXShowAsWord(os,n,1);
		os<<",";
		if(generators->sequences[i-1].stableDegree()==0)
			oneSequence.TeXShowAsWord(os,n,s); else
			generators->sequences[i-1].TeXShowAsWordButFirst(os,n,1);
		os<<")$\\\\\n";
	}

	os<<"&&\\\\";
	os<<"\\end{supertabular}\n";

}

void LaTeXLayoutBackMatter(ostream& os)
{
	os<<"\\end{document}\n";
}
