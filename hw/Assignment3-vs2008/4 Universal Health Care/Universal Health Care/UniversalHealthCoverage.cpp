/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool wrapper(Set<string>& cities, Vector< Set<string> >& locations,int numHospitals,Vector< Set<string> >& result, int index = 0 ){
	if(cities.size()==0)return true;	
	if(numHospitals == 0)return false;
	Set<string> curr ;
	for(int i = index; i < locations.size(); i++){
		curr=locations[i];
		if(wrapper(cities - curr, locations,numHospitals - 1, result, index+1)){
			result.add(curr);
			return true;
		}
	}
	return false;	
}

bool  canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations,int numHospitals,Vector< Set<string> >& result){
	return wrapper(cities,locations,numHospitals,result);
}


int main() {
	Set<string> cities ;
	string city ; 
	//input cities
	cout<<" input cities ( or -1 to stop)" <<endl;
	while(true){
		cin>> city ;
		if(city =="-1")break;
		cities.add(city);
	}
	// input locations
	Vector< Set<string> > locations ;
	Set<string> currRange ;
	cout<<" input  locations (or -2 to stop)" <<endl;
	while(true){
		cout<<" input cities ( or -1 to start next  hospital's range or -2 to stop input)" <<endl;
		while(true){
			cin>> city ;
			if(city =="-1"||city =="-2" )break;
			currRange.add(city);
		}
		if(!currRange.isEmpty()){
			locations.add(currRange);
		}
		if(city=="-2")break;
		currRange.clear();	
	}
	//input hospital limit 
	int numHospitals ;
	cout<<"input max number of hospitals"<<endl;
	cin>>numHospitals;
	// print out result 
	Vector< Set<string> > result;
	if(canOfferUniversalCoverage(cities,locations,numHospitals,result)){
		cout<<"YES"<<endl;
		cout<<"result"<<result<<endl;
	}else{
		cout<<"NO"<<endl;
	}
	cout<<"cities" << cities<<endl;
	cout<<"locations" << locations<<endl;
    return 0;
}
