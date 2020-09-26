#include "hash.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cctype>

using namespace std;

void loadDict(const string& name, hashTable *table);
void dictCheck(string in, string out, hashTable *table);
bool check_word(const std::string& word);

bool check_word(const std::string& word){
	if(word.size()>20)	return false;
	for(auto l: word){
		if(!isdigit(l) && !isalpha(l) && l!='-' && l!='\'')	return false;
		else	return true;
	}
}

int main(){
	string dict, infile, outfile;
	hashTable* newDict = new hashTable(30000);
	cout << "Load in the dictionary: "<<endl;
	cin >> dict;
	loadDict(dict, newDict);
	cout << "Finish making the hash table!"<<endl;
	cout << "Enter input file name: "<< endl;
	cin >> infile;
	cout << "Enter output file name: "<<endl;
	cin >> outfile;
	dictCheck(infile, outfile, newDict);
	cout << "Finish writing!" <<endl;
	return 0;
}

void loadDict(const string& name, hashTable *table){
	std::ifstream inn;
	inn.open(name);
	string line;
	if(inn.fail()){
		cout<<"ERROR: FAIL to open input file"<<endl;
		exit(-1);
	}
	if(inn.is_open()){
		table->insert("test");
		table->show("test");
		/*while(getline(inn, line)){
			cout<<"start parsing"<<endl;
			
				table->insert(line);
				int contains = table->contains(line);
				cout<<contains<<endl;
				//table->show(line);
		
			
		}*/
	}
	
	cout<<"finish loading dictionary!"<<endl;
	inn.close();
	
	
}


void dictCheck(string in, string out, hashTable *table){
	ifstream input;
	input.open(in);
	ofstream output;
	output.open(out);
	string line;
	
	int lines = 1;
	while(getline(input, line)){
		string word = "";
		char c;
		int read = 0;
		bool valid = true;
		while(read<line.size()){
			c = tolower(line[read++]);
			if(isdigit(c))	valid = false;
						
			if(isalnum(c) || c=='-' || c=='\''){
				word+=c;
			}else if(valid == true && word.size()!=0){
				if(word.size()>20){
					output<<"Long word at line "<<lines<<", starts: "<<word<<endl;
					cout<<"Long word at line "<<lines<<", starts: "<<word<<endl;
				}else if(!(*table).contains(word)){
					output<<"Unknown word at line "<<lines<<": "<<word<<endl;
					cout<<"Unknown word at line "<<lines<<": "<<word<<endl;
				}
				word = "";
			}else{
				word = "";
				valid = true;
			}
		}
		lines++;
	}
	input.close();
	output.close();
}

