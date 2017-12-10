/*
 *      
 *      The Eilenberg-MacLane Machine
 *
 *      EMM.cpp
 *      Version 2.1, 31-Jan-2002, 02:53
 *      Alain Clement <alain.clement@ima.unil.ch>
 *
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Mod2GradedGroups.hpp"
#include "Mod2EilenbergMacLaneHomology.hpp"
#include "LaTeXLayout.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	int s;
	int n;
	int range;

	GradedGroup homology;
	GradedGroup cohomology;

	switch(argc) {

	case 0:
	case 1:

		cout<<"\nThe Eilenberg-MacLane machine\n"
			<<"=============================\n"
			<<"Version 2.1, 31-jan-2002\n\n"
			<<"Alain Clement\n"
			<<"Institute of Mathematics\n"
			<<"Faculty of Sciences\n"
			<<"University of Lausanne\n"
			<<"Switzerland\n\n"
			<<"This program computes the integral homology and\n"
			<<"cohomology groups of Eilenberg-MacLane spaces\n"
			<<"associated to cyclic groups of order a power of 2,\n"
			<<"namely spaces of the form K(Z/2^s,n).\n\n"
			<<"If do you want a LaTeX file as output, you can\n"
			<<"also quit and execute the machine again with the\n"
			<<"following arguments: EMM [s] [n] [range]\n\n";


	 	while(1) 
		{
			cout<<"s (0 to quit) ............: ";
			cin>>s;
			if (s==0) return 0;
			cout<<"n ........................: ";
			cin>>n;
			cout<<"range (0 to ?) ...........: ";
			cin>>range;

			Mod2AdmissibleSequences* generators;
			generators = new Mod2AdmissibleSequences;

			homology=EMHomology(s,n,range,generators);
			cohomology=UniversalCoefficients(homology);

			cout<<"\n";
			homology.Show();
			cout<<"\n";

			cout<<"Results are outputed in the LaTeX file \"output.tex\".\n";
			cout<<"Use your preferred LaTeX environment to compile this file.\n\n";

			ofstream file("output.tex");
			if (file) {

				LaTeXLayoutTopMatter(file);
				file<<"\\subsection*{Homology and cohomology groups of $K(\\Z/2^{"<<s<<"},"<<n<<")$.}";
				LaTeXLayoutTwoColumns(file,homology,cohomology);
				file<<"\\newpage";
				file<<"\\subsection*{Generators involved in the calculus.}";
				LaTeXLayoutGenerators(file,generators,n,s);
				LaTeXLayoutBackMatter(file);
				
			}
			file.close();
			
			delete generators;

		}

	break;

	case 4:

		s=atoi(argv[1]);
		n=atoi(argv[2]);
		range=atoi(argv[3]);

		Mod2AdmissibleSequences* generators;
		generators = new Mod2AdmissibleSequences;

		homology=EMHomology(s,n,range,generators);
		cohomology=UniversalCoefficients(homology);
	
		LaTeXLayoutTopMatter(cout);
		cout<<"\\subsection*{Homology and cohomology groups of $K(\\Z/2^{"<<s<<"},"<<n<<")$.}";
		LaTeXLayoutTwoColumns(cout,homology,cohomology);
		cout<<"\\newpage";
		cout<<"\\subsection*{Generators involved in the calculus.}";
		LaTeXLayoutGenerators(cout,generators,n,s);
		LaTeXLayoutBackMatter(cout);

		delete generators;

	break;

	default:
	
		cerr<<"Invalid arguments. Aborting.";
		return -1;

	}
	
	return 0;
}
