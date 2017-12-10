/*
 *			
 *		2-Local graded groups
 *
 *		Mod2GradedGroups.cpp
 *      Version 2.1, 31-Jan-2002, 02:53
 *		Alain Clement <alain.clement@ima.unil.ch>
 *
 *		Tools for graded groups.
 *		Show classes definitions below for more information.
 *
 */


#include <algorithm>
#include <iostream>
#include "Mod2GradedGroups.hpp"

using namespace std;

// Class <PowerOfCyclicGroup> =============================

void PoweredCyclicGroup::TeXShow(ostream& os)
{
	if (power==0) {
		return;
	}
	if (logorder==0) os<<"\\Z"; else {
		if (power>1) os<<"(";
		os<<"\\Z/2";
		if (logorder>1) os<<"^{"<<logorder<<"}";
	}
	if (power>1 && logorder>0) os<<")";
	if (power>1) os<<"^{\\oplus"<<power<<"}";
}

PoweredCyclicGroup tensor(
	PoweredCyclicGroup PCGroup1,PoweredCyclicGroup PCGroup2)
{
	PoweredCyclicGroup PCGroup;
	
	PCGroup.logorder=(PCGroup1.logorder <= PCGroup2.logorder) ? PCGroup1.logorder : PCGroup2.logorder;
	if (PCGroup1.logorder == 0) PCGroup.logorder=PCGroup2.logorder;
	if (PCGroup2.logorder == 0) PCGroup.logorder=PCGroup1.logorder;
	PCGroup.power=PCGroup1.power*PCGroup2.power;
	return PCGroup;
}

PoweredCyclicGroup Tor(
	PoweredCyclicGroup PCGroup1,PoweredCyclicGroup PCGroup2)
{
	PoweredCyclicGroup PCGroup;
	
	PCGroup.logorder=(PCGroup1.logorder <= PCGroup2.logorder) ? PCGroup1.logorder : PCGroup2.logorder;
	PCGroup.power=PCGroup1.power*PCGroup2.power;
	if (PCGroup1.logorder == 0 || PCGroup2.logorder == 0) PCGroup.power=0;
	return PCGroup;
}

PoweredCyclicGroup Hom(
	PoweredCyclicGroup PCGroup1,PoweredCyclicGroup PCGroup2)
{
	if(PCGroup1.logorder==0) return PCGroup2;
	PoweredCyclicGroup PCGroup;
	if(PCGroup2.logorder==0) {PCGroup.power=0; return PCGroup;}
	PCGroup.logorder=(PCGroup1.logorder <= PCGroup2.logorder) ? PCGroup1.logorder : PCGroup2.logorder;
	PCGroup.power=PCGroup1.power*PCGroup2.power;
	return PCGroup;	
}

PoweredCyclicGroup Ext(
	PoweredCyclicGroup PCGroup1,PoweredCyclicGroup PCGroup2)
{
	PoweredCyclicGroup PCGroup;
	if(PCGroup1.logorder==0) {PCGroup.power=0; return PCGroup;}
	if(PCGroup2.logorder==0) return PCGroup1;
	PCGroup.logorder=(PCGroup1.logorder <= PCGroup2.logorder) ? PCGroup1.logorder : PCGroup2.logorder;
	PCGroup.power=PCGroup1.power*PCGroup2.power;
	return PCGroup;
}

// Class <Group> ==========================================

class orderCmp {
	public:
		bool operator()(const PoweredCyclicGroup&,const PoweredCyclicGroup&) const;
};

bool orderCmp::operator()(const PoweredCyclicGroup& x,const PoweredCyclicGroup& y) const
{
	return (x.logorder<y.logorder);
}

void Group::add(Group group)
{
	int i;

	if (group.PCGroups.empty()==true) return;
	for(i=0;i<group.PCGroups.size();i++) {
		add(group.PCGroups[i]);
	}
}

void Group::add(PoweredCyclicGroup PCGroup)
{
	int i;

	if (PCGroup.power==0) return;
	for(i=0;i<PCGroups.size();i++) {
		if (PCGroups[i].logorder == PCGroup.logorder) {
			PCGroups[i].power+=PCGroup.power;
			return;}
	}
	PCGroups.push_back(PCGroup);
}

void Group::add(int logorder, long int power)
{
	int i;
	
	if (power == 0) return;
	for(i=0;i<PCGroups.size();i++) {
		if (PCGroups[i].logorder == logorder) {
			PCGroups[i].power+=power;
			return;}
	}

	PoweredCyclicGroup PCGroup;
	PCGroup.logorder=logorder;
	PCGroup.power=power;
	PCGroups.push_back(PCGroup);
}

void Group::TeXShow(ostream& os)
{
	int i;
	if (PCGroups.empty()==true) {
		os<<"(0)";
		return;
	}
	sort(PCGroups.begin(),PCGroups.end(),orderCmp());
	for(i=0;i<PCGroups.size()-1;i++) {
		PCGroups[i].TeXShow(os);
		os<<"\\oplus"; 
	}
	PCGroups[PCGroups.size()-1].TeXShow(os);

}

Group tensor(Group group1, Group group2)
{
	Group group;
	int i;
	int j;

	for(i=0;i<group1.PCGroups.size();i++)
		for(j=0;j<group2.PCGroups.size();j++) {
			group.add(tensor(group1.PCGroups[i],group2.PCGroups[j]));
		};
	return group;
}

Group Tor(Group group1,Group group2)
{
	Group group;
	int i;
	int j;

	for(i=0;i<group1.PCGroups.size();i++)
		for(j=0;j<group2.PCGroups.size();j++) {
			group.add(Tor(group1.PCGroups[i],group2.PCGroups[j]));
		};
	return group;
}

Group Hom(Group group1, Group group2)
{
	Group group;
	int i;
	int j;

	for(i=0;i<group1.PCGroups.size();i++)
		for(j=0;j<group2.PCGroups.size();j++) {
			group.add(Hom(group1.PCGroups[i],group2.PCGroups[j]));
		};
	return group;
}

Group Ext(Group group1, Group group2)
{
	Group group;
	int i;
	int j;

	for(i=0;i<group1.PCGroups.size();i++)
		for(j=0;j<group2.PCGroups.size();j++) {
			group.add(Ext(group1.PCGroups[i],group2.PCGroups[j]));
		};
	return group;
}

// Class <GradedGroup> ====================================

class degreeCmp {
	public:
		bool operator()(const SuspendedGroup&,const SuspendedGroup&) const;
};

bool degreeCmp::operator()(const SuspendedGroup& x,const SuspendedGroup& y) const
{
	return (x.degree<y.degree);
}

void GradedGroup::add(SuspendedGroup SGroup)
{
	int i;
	for(i=0;i<groups.size();i++) {
		if (groups[i].degree==SGroup.degree) {
			groups[i].add(SGroup);
			return;
		};
	};
	groups.push_back(SGroup);
}

void GradedGroup::add(Group group, int degree)
{
	SuspendedGroup SGroup;
	SGroup.PCGroups = group.PCGroups;
	SGroup.degree = degree;
	add(SGroup);
}

void GradedGroup::add(int logorder, long int power, int degree)
{
	SuspendedGroup SGroup;
	SGroup.add(logorder,power);
	SGroup.degree = degree;
	add(SGroup);
}

void GradedGroup::Show()
{
	int i;

	sort(groups.begin(),groups.end(),degreeCmp());
	for(i=0;i<groups.size();i++) {
		cout<<groups[i].degree<<": ";
		groups[i].TeXShow(cout);
		cout<<"\n";
	};
}

int GradedGroup::anticonnexity()
{
	sort(groups.begin(),groups.end(),degreeCmp());
	return groups[groups.size()-1].degree;	
}

Group GradedGroup::GroupIn(int degree)
{
	Group group;
	int i;
	for(i=0;i<groups.size();i++) {
		if (groups[i].degree==degree) {
			group.PCGroups = groups[i].PCGroups;
			return group;
		};
	};	
	return group;
}

GradedGroup Kunneth(GradedGroup GGroup1,GradedGroup GGroup2)
{
	GradedGroup GGroup;
	int anticonnexity;
	int anticonnexity1;
	int anticonnexity2;	
	int n;
	int i;
	
	
	anticonnexity1=GGroup1.anticonnexity();
	anticonnexity2=GGroup2.anticonnexity();
	anticonnexity = (anticonnexity1>=anticonnexity2) ? anticonnexity1 : anticonnexity2;

	for(n=0;n<=anticonnexity;n++) {
		for(i=0;i<=n;i++) {
			GGroup.add(tensor(GGroup1.GroupIn(i),GGroup2.GroupIn(n-i)),n);
		};
		for(i=0;i<=n-1;i++) {
			GGroup.add(Tor(GGroup1.GroupIn(i),GGroup2.GroupIn(n-1-i)),n);
		};
	};
	return GGroup;
}

GradedGroup UniversalCoefficients(GradedGroup GGroup1)
{
	GradedGroup GGroup;
	Group Z;
	int n;
	
	Z.add(0,1);
	
	for(n=0;n<=GGroup1.anticonnexity();n++) {
		GGroup.add(Ext(GGroup1.GroupIn(n-1),Z),n);
		GGroup.add(Hom(GGroup1.GroupIn(n),Z),n);
	};
	return GGroup;
}
