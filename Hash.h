/*
*			Data Structures and Algorithms II Term Project
*			2020-Fall
*			Ýlker Kýlýnçarslan
*			1600002148
*/
#pragma once
#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

struct student {
	long id; // 9-digit student id,
	char name[30]; //student name, surname
	char address[50]; //address of the student
	double gpa;	
	friend bool operator==(student const&, student const&);

	friend bool operator==(student const& a, student const& b)
	{
		return a.id == b.id && strcmp(a.name, b.name) == 0 &&
			strcmp(a.address, b.address) == 0 && a.gpa == b.gpa;
	}
};

class Hash
{
public:
	~Hash();
	Hash();
	Hash(int htype,int tsize);
	void insert(struct student std);
	void remove(struct student std);
	int hash1(struct student std);
	int hash2(struct student std);
	int hash3(struct student std);
	bool search(struct student std);
	void destroy();
	void display();
	int hash_template(struct student std, int (Hash::*hashFunc)(struct student std));
	void utilization();	
	int numOfElements(list<struct student> cell);
	void replaceWith1(list<struct student>* hashTable, list<struct student>* hashTableNew, int i);
	void replaceWith2(list<struct student>* hashTable, list<struct student>* hashTableNew, int i);
	void replaceWith3(list<struct student>* hashTable, list<struct student>* hashTableNew, int i);
	void fillTable(list<struct student>* hashTable, list<struct student>* hashTableNew);
private:
	int size; //use a prime number for more unique results
	list<struct student> *hashTable;	
	int hashType;
	int nodes;
};

Hash::Hash()
{
	this->size = 11;
	this->hashType = 1;
	hashTable = new list<struct student>[this->size];	
	this->nodes = 0;
}

Hash::Hash(int htype,int tsize)
{
	this->size = tsize;
	this->hashType = htype;
	hashTable = new list<struct student>[this->size];	
	this->nodes = 0;
}

Hash::~Hash()
{
	delete [] hashTable;
}

void Hash::remove(struct student std)
{
	cout << "...remove()... called\n" << endl;
	int (Hash:: * hashFunc)(struct student std);
	int index = -1;
	if (search(std))
	{
		switch (hashType)
		{
		case 1:
			hashFunc = &Hash::hash1;
			index = hash_template(std, hashFunc);
			break;
		case 2:
			hashFunc = &Hash::hash2;
			index = hash_template(std, hashFunc);			
			break;
		case 3:
			hashFunc = &Hash::hash3;
			index = hash_template(std, hashFunc);
			break;
		default:
			cout << "remove() default case" << endl;			
		}
		auto it = find(hashTable[index].begin(), hashTable[index].end(), std);
		if (it == hashTable[index].end()) 
			return;		
		cout << it->name << " removed.\n" << endl;
		hashTable[index].erase(it);		
		cout << "Updated List :" << endl;
		display();
	}
	else
		cout << "!WARNING! Cannot remove !" <<std.name << " is NOT exist!" << endl;	
	cout << "...remove()... returned\n" << endl;
}

int Hash::hash1(struct student std)
{
	long key = std.id;
	return int(key % size);
}

int Hash::hash2(struct student std)
{
	int value = 0;
	string str = std.name;
	for (unsigned int i = 0; i < str.length(); i++)	
		value += str[i];

	return value % size;	
}

int Hash::hash3(struct student std)
{
	int value = 0;
	string str = std.address;
	for (unsigned int i = 0; i < str.length(); i++)	
		value = 37 * value + str[i];
	
	value %= size;
	if (value < 0)
		value += size;

	return value;
}

void Hash::insert(struct student std)
{
	bool isExist = search(std);
	int tableIndex = -1;
	int (Hash::*hashFunc)(struct student std);	

	if (!isExist)
	{
		switch (hashType)
		{
		case 1:
			hashFunc = &Hash::hash1;
			tableIndex = hash_template(std, hashFunc);
			break;
		case 2:
			hashFunc = &Hash::hash2;
			tableIndex = hash_template(std, hashFunc);
			break;
		case 3:
			hashFunc = &Hash::hash3;
			tableIndex = hash_template(std, hashFunc);
			break;
		default:
			cout << "insert() default case" << endl;
		}
		hashTable[tableIndex].push_back(std);
		nodes++;
	}
	else
		cout << "! WARNING ! cannot duplicate " << std.name << ". ALREADY exist !" << endl;
}

bool Hash::search(struct student std)
{	
	int (Hash:: * hashFunc)(struct student std);
	int index = -1;
	switch (hashType)
	{
	case 1:
		hashFunc = &Hash::hash1;
		index = hash_template(std, hashFunc);
		break;
	case 2:
		hashFunc = &Hash::hash2;
		index = hash_template(std, hashFunc);
		break;
	case 3:
		hashFunc = &Hash::hash3;
		index = hash_template(std, hashFunc);
		break;
	default:
		cout << "search() default state" << endl;
	}	
	auto it = find(hashTable[index].begin(), hashTable[index].end(), std);
	if (it == hashTable[index].end())
		return false;
	return true;	
}

void Hash::destroy()
{
	cout << "...destroy()... called\n" << endl;
	for(int i=0;i<size;i++)
		hashTable[i].clear();
	cout << "Table has been destroyed." << endl;	
	display();
	cout << "...destroy()... returned\n" << endl;
}

void Hash::display()
{
	for (int i = 0; i < size; i++)
	{
		cout << i << " -> ";
		for (auto itr = hashTable[i].begin(); itr != hashTable[i].end(); itr++)
		{
			cout << itr->name << " -> ";
		}
		cout << endl;
	}
	cout << endl;
}

int Hash::hash_template(struct student std, int (Hash::*fp)(struct student std))
{	
	int index = (this->*fp)(std);
	return index;
}

void Hash::utilization()
{
	cout << "...utilization()... called\n" << endl;
	int otherHash1 = -1;
	int otherHash2 = -1;

	switch (hashType)
	{
	case 1:
		otherHash1 = 2;
		otherHash2 = 3;
		break;
	case 2:
		otherHash1 = 1;
		otherHash2 = 3;
		break;
	case 3:
		otherHash1 = 1;
		otherHash2 = 2;
		break;
	default:
		cout << "utilization() default state !" << endl;
	}

	int emptySlots = 0;
	for (int i = 0; i < size; i++)
	{
		if (hashTable[i].empty())
			emptySlots++;
	}

	float efficiency = 0.0;
	efficiency = (float)nodes / (float)emptySlots;	

	cout << "Efficiency of Hash" << hashType << " (main hash) is " << efficiency << endl;

	emptySlots = 0;

	list<struct student>* clone;
	clone = new list<struct student>[size];

	fillTable(hashTable, clone);

	list<struct student>* hashTable2;
	hashTable2 = new list<struct student>[size];
	
	for (int i = 0; i < size; i++)
	{	
		if (!hashTable[i].empty())
		{
			if (otherHash1 == 1)
				replaceWith1(hashTable, hashTable2, i);
			if(otherHash1 == 2)
				replaceWith2(hashTable, hashTable2, i);
			if(otherHash1 == 3)
				replaceWith3(hashTable, hashTable2, i);
		}		
	}
	for (int i = 0; i < size; i++)
	{
		if (hashTable2[i].empty())
			emptySlots++;
	}
	
	efficiency = (float)nodes / (float)emptySlots;	
	cout << "Efficiency of Hash" << otherHash1 << " is " << efficiency << endl;

	list<struct student>* hashTable3;
	hashTable3 = new list<struct student>[size];
	
	fillTable(clone, hashTable);

	emptySlots = 0;

	for (int i = 0; i < size; i++)
	{
		if (!hashTable[i].empty())
		{
			if (otherHash2 == 1)
				replaceWith1(hashTable, hashTable3, i);
			if (otherHash2 == 2)
				replaceWith2(hashTable, hashTable3, i);
			if (otherHash2 == 3)
				replaceWith3(hashTable, hashTable3, i);
		}
	}

	fillTable(clone, hashTable);

	for (int i = 0; i < size; i++)
	{
		if (hashTable3[i].empty())
			emptySlots++;
	}
	
	efficiency = (float)nodes / (float)emptySlots;
	cout << "Efficiency of Hash" << otherHash2 << " is " << efficiency << endl;
	cout << "Do you want to switch between hash functions ?\n" << endl;
	cout << "Press 'y' for Yes, 'n' for No" << endl;
	char choice = '-';
	cin >> choice;

	bool userInput = false;
	if (choice == 'y')
		userInput = true;

	while (userInput)
	{
		cout << "Which hash function you want to switch to ?" << endl;
		cout << "Press " << otherHash1 << " or " << otherHash2 << endl;
		int choiceNum = 0;
		cin >> choiceNum;

		if (choiceNum == otherHash1)
		{
			cout << "\nNew List :" << " (According to Hash" << otherHash1 << ")" << endl;

			hashTable = hashTable2;
			this->hashType = otherHash1;
			display();
		}
		if (choiceNum == otherHash2)
		{
			cout << "\nNew List :" << " (According to Hash" << otherHash2 << ")" << endl;

			hashTable = hashTable3;
			this->hashType = otherHash2;
			display();
		}	
		userInput = false;		
	}
	cout << "...utilization()... returned\n" << endl;
}

int Hash::numOfElements(list<struct student> std)
{
	int result = 0;
	for (auto itr = std.begin(); itr != std.end(); itr++)
		result++;

	return result;
}

void Hash::replaceWith1(list<struct student>* hashTable, list<struct student>* hashTableNew, int i)
{
	int newTableIndex = -1;	
	int j = 0;	

	while (j < numOfElements(hashTable[i]))
	{
		for (auto itr = hashTable[i].begin(); itr != hashTable[i].end(); itr++)
		{
			if (!hashTable[i].empty())
			{
				newTableIndex = hash1(hashTable[i].front());
				hashTableNew[newTableIndex].push_back(hashTable[i].front());				
				hashTable[i].pop_front();
				j++;
			}
			break;
		}
		j = 0;
	}	
}

void Hash::replaceWith2(list<struct student>* hashTable, list<struct student>* hashTableNew, int i)
{
	int newTableIndex = -1;	
	int j = 0;

	while (j < numOfElements(hashTable[i]))
	{
		for (auto itr = hashTable[i].begin(); itr != hashTable[i].end(); itr++)
		{
			if (!hashTable[i].empty())
			{				
				newTableIndex = hash2(hashTable[i].front());
				hashTableNew[newTableIndex].push_back(hashTable[i].front());				
				hashTable[i].pop_front();
				j++;
			}
			break;
		}
		j = 0;
	}		
}

void Hash::replaceWith3(list<struct student>* hashTable, list<struct student>* hashTableNew, int i)
{
	int newTableIndex = -1;	
	int j = 0;

	while (j < numOfElements(hashTable[i]))
	{
		for (auto itr = hashTable[i].begin(); itr != hashTable[i].end(); itr++)
		{
			if (!hashTable[i].empty())
			{
				newTableIndex = hash3(hashTable[i].front());
				hashTableNew[newTableIndex].push_back(hashTable[i].front());				
				hashTable[i].pop_front();
				j++;
			}
			break;
		}
		j = 0;
	}		
}

void Hash::fillTable(list<struct student>* hashTable, list<struct student>* hashTableNew)
{
	for (int i = 0; i < size; i++)
		hashTableNew[i] = hashTable[i];			
}