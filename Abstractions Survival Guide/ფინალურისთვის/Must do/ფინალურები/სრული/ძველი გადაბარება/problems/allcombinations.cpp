#include "allcombinations.h"
#include "queue.h"
#include "vector.h";

#include <string>


bool sheicavs(Vector<string> vec, string str){
	for(int i=0; i<vec.size(); i++){
		if(vec[i]==str){
			return true;
		}
	}
	return false;
}

Vector<string> permutationsOf(string str){
	Vector<string> result;
	if(str==""){
		if(!sheicavs(result, "")){
			result+=str;
		}
		return result;
	}else{
		for(int i=0; i<str.length(); i++){
			Vector<string> vec = permutationsOf(str.substr(0, i)+str.substr(i+1));
			foreach(string permutation in vec){
				if(!sheicavs(result, str[i]+permutation)){
					result+=str[i]+permutation;
				}
			}
		}
		return result;
	}
}
int findSecondIndex(int i, string str){
	int result;
	for(int k=str.length()-1; k>=0; k--){
		if(str[k]==integerToString(i)[0]){
			result = k;
			break;
		}
	}
	return result;
}

int findFirstIndex(int i, string str){
	int result;
	for(int k=0; k<str.length(); k++){
		if(str[k]==integerToString(i)[0]){
			result = k;
			break;
		}
	}
	return result;
}



bool akmayofilebs(string str){
	for(int i=1; i<=str.length()/2; i++){
		int index1 = findFirstIndex(i, str);
		int index2 = findSecondIndex(i, str);
		if(index2-index1!=i+1 && index2-index1!=i){
			return false;
		}
	}
	return true;
}



 
int allCombinations(int n)
{
	int result = 0;
	string str = "";
	for(int i=1; i<=n; i++){
		str=str+integerToString(i);
	}
	string s = str;
	str=str+s;
	cout<<str<<endl;
	Vector<string> mtavariVectori = permutationsOf(str);

	for(int i=0; i<mtavariVectori.size(); i++){
		if(akmayofilebs(mtavariVectori[i])){
			result++;
		}
	}
	cout<<result<<endl;
	return result;
}
