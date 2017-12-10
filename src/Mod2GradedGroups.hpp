/*
 *			
 *		2-Local graded groups
 *
 *		Mod2GradedGroups.hpp
 *		Version 2.1, 31-Jan-2001, 02:27
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Tools for graded groups.
 *
 */


#ifndef _Mod2GradedGroups
#define _Mod2GradedGroups

#include <vector>

using namespace std;

class PoweredCyclicGroup
{
	public:
		int logorder;
		long int power;
		void TeXShow(ostream&);
		int exp();
};
PoweredCyclicGroup tensor(
	PoweredCyclicGroup,
	PoweredCyclicGroup);
PoweredCyclicGroup Tor(
	PoweredCyclicGroup,
	PoweredCyclicGroup);
PoweredCyclicGroup Hom(
	PoweredCyclicGroup,
	PoweredCyclicGroup);
PoweredCyclicGroup Ext(
	PoweredCyclicGroup,
	PoweredCyclicGroup);

class Group
{
	public:
		vector<PoweredCyclicGroup> PCGroups;
		void show();
		void TeXShow(ostream&);
		void add(Group);
		void add(PoweredCyclicGroup);
		void add(int logorder, long int power);
};
Group tensor(Group,Group);
Group Tor(Group,Group);
Group Hom(Group,Group);
Group Ext(Group,Group);

class SuspendedGroup : virtual public Group
{
	public:
		int degree;
};

class GradedGroup
{
	public:
		vector<SuspendedGroup> groups;
		void add(SuspendedGroup);
		void add(Group, int degree);
		void add(int logorder, long int power, int degree);
		void Show();
		Group GroupIn(int degree);
		int anticonnexity();
};
GradedGroup Kunneth(GradedGroup,GradedGroup);
GradedGroup UniversalCoefficients(GradedGroup);

#endif
