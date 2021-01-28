/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "queue.h"
using namespace std;
void listAll(string protein, Map<char, Set<string> >& codons , Queue<string>& list);

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	string protein;
	cout<<"input protein name :";
	cin>>protein;
	listAllRNAStrandsFor(protein, codons);
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
//wrapper function
void listAll(string protein, Map<char, Set<string> >& codons, Queue<string>& list){
	if(protein.length() == 0)return;					
	int length = list.size();
	for(int i = length; i > 0; i--){
		string curr = list.dequeue();
		foreach(string codon in codons[protein[0]]){
			list.enqueue(curr+codon);
		}
	}
	listAll(protein.substr(1), codons, list);	
}
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
    Queue<string> list;
	list.enqueue("");
	listAll(protein, codons,list);
	cout<<list<<endl;
	cout<<list.size()<<endl;
}