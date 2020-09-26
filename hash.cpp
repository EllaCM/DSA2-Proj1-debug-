#include "hash.h"
#include <string>
#include <iostream>

using namespace std;

hashTable::hashTable(int size){
	capacity = getPrime(size);
	filled = 0;
	hashItem* item = new hashItem();
	item->key = "";
	item->isOccupied = false;
	item->isDeleted = false;
	item->pv = nullptr;
	this->data.resize(capacity);
}

int hashTable::insert(const std::string &key, void *pv){
	unsigned int pos = findPos(key);
	int wat = -1;
	while(data[pos].isOccupied){
		if(data[pos].key==key){
			if(!data[pos].isDeleted)	return 1;
			else{
				data[pos].isDeleted = false;
				return 0;	
			}
		}else{
			if(data[pos].isDeleted && wat==-1)	wat = pos;
		}

		if(pos==capacity-1)	pos = 0;
		else	pos++;
	}

	if(wat!=-1)	pos = wat;

	if(data[pos].isOccupied && !data[pos].isDeleted && data[pos].key==key)	return 1;
	data[pos].key = key;
	data[pos].pv = pv;
	data[pos].isOccupied = true;
	data[pos].isDeleted = false;
	
	filled+=1;
	if(filled*2>capacity){
		if(!rehash())	return 2;
	}
	return 0;
}

void *hashTable::getPointer(const string &key, bool *b){
	int pos = findPos(key);
	if(b!=nullptr){
		if(pos!=-1)	*b = true; 
		else	*b = false;
	}
	if(pos==-1)	return nullptr;
}

int hashTable::setPointer(const string& key, void *pv){
	unsigned int pos = findPos(key);
	if(pos==-1)	return 1;
	data[pos].pv = pv;
	return 0;
}

bool hashTable::contains(const string &key){
	unsigned int pos = findPos(key);
	if(pos==-1){
		return false;
	}
	return true;
}

bool hashTable::remove(const string &key){
	unsigned int pos = findPos(key);
	if(pos==-1)	return false;
	data[pos].isDeleted = true;
	return true;
}

int hashTable::findPos(const string &key){
	unsigned int pos = hash(key);
	while(data[pos].isOccupied){
		if(data[pos].key==key && !(data[pos].isDeleted))	return pos;
		if(data[pos].key!=key){
			if(pos==capacity-1)	pos = 0;
			else	pos=(pos+1)%capacity;
		}
	}
	return -1;
}

int hashTable::hash(const string &key){
	unsigned int hashV = 3671;
	char const *c = key.c_str();
	while(c++){
		hashV = hashV*33+(*c);
	}
	return hashV%capacity;
}

bool hashTable::rehash(){
	std::vector<hashItem> old = data;
	unsigned int reSize = getPrime(capacity*2);
	data.resize(reSize);
	if(data.size()!=reSize)	return false;
	for(auto i: data){
		i.key = "";
		i.isDeleted = false;
		i.isOccupied = false;
		i.pv = nullptr;
	}
	filled = 0;
	for(auto o: old){
		if(o.isOccupied && !o.isDeleted){
			insert(o.key, o.pv);
		}
	}
	return true;
}

void hashTable::show(const string &key){
	if(contains(key)){
		cout<<"pos: "<<findPos(key)<<endl;
	}else{
		cout<<"fail to insert!"<<endl;
	}
}

unsigned int hashTable::getPrime(int size){
	static unsigned int primes[] = {98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917};
	int i = 0;
	while(primes[i]<size){
		i++;
	}
	return primes[i];
}


