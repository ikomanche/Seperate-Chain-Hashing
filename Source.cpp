#include "Hash.h"

int main()
{	
	struct student ilker = {160002148,"Ilker Kilincarslan","Bahcesehir",2.44};
	struct student safa = {160003764,"Safa Orhan","Beylikduzu",2.5 };
	struct student isil = {160002106,"Isil Alici","Avcilar",1.9 };
	struct student yaren = {160001547,"Yaren Misirli","Basaksehir",2 };
	struct student tevfik = { 160003501,"Tevfik Tayyip Sarac","Fethiye",2.8 };
	struct student kamil = { 160001452,"Mahmut Kamil Aydin","Ankara",2 };
	struct student ugur = { 160002660,"Ugur Guler","Istanbul",2 };
	struct student safaU = { 160004213,"Safa Uysal","Basaksehir",2 };
	struct student aleyna = { 160006527,"Aleyna Erkisi","Istanbul",2.6 };
	struct student faruk = { 160001441,"Mehmet Faruk Koc","Istanbul",2.7 };
	struct student batu = { 160002046,"Batuhan Ucsu","Bahcelievler",2.2 };

	Hash h1(2, 11);

	h1.insert(ilker);
	h1.insert(safa);
	h1.insert(isil);
	h1.insert(yaren);
	h1.insert(tevfik);
	h1.insert(kamil);
	h1.insert(ugur);
	h1.insert(safaU);
	h1.insert(aleyna);
	h1.insert(faruk);
	h1.insert(faruk);
	h1.insert(batu);
	h1.insert(batu);
	h1.display();		
	h1.utilization();
	h1.remove(ilker);
	h1.destroy();

	return 0;
}