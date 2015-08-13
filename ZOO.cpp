// ZOO.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include <stdio.h>
#include <iostream>
#include <istream>
#include <fstream>
using namespace std;
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cctype>

char name[16],
birthDate[11],
enterDate[11],
family[20],
type[20],
statusTemp[6],
reason[9];
char code2;

class Animals{
	char name[10],
		 birthDate[11],
	     enterDate[11],
	     reason[9],
	     family[20],
	     type[20];
	bool status = true;
public:
	Animals(char n[], char bDate[], char eDate[], char fam[], char typ[]){
		strcpy_s(name, n);
		strcpy_s(birthDate, bDate);
		strcpy_s(enterDate, eDate);
		strcpy_s(family, fam);
		strcpy_s(type, typ);
		strcpy_s(reason, "N/A");
	}
	Animals(char n[], char bDate[], char eDate[], char fam[], char typ[], char statusTemp[], char r[]){
		strcpy_s(name, n);
		strcpy_s(birthDate, bDate);
		strcpy_s(enterDate, eDate);
		strcpy_s(family, fam);
		strcpy_s(type, typ);
		strcpy_s(reason, r);
		if (!strcmp(statusTemp, "false")) status = false;
	}/*
	void get(){
		cout << "Name: " << name << "\n"
			<< "Birth date: " <<birthDate << "\n"
			<< "Enter date: "<< enterDate << "\n"
			<< "Family: " << family << "\n"
			<< "Type: " <<type << "\n";
		if (status == false) { 
			cout << "Status: Not available.\nReason: " << reason << endl;;
		}
		else { cout << "Status: Available" << endl; }
	}//get
	*/

	void get(){
		cout.fill(' ');
		cout.setf(ios::left);
		cout.width(10);
		cout << name;
		cout.fill(' ');
		cout.setf(ios::left);
		cout.width(11);
		cout << birthDate << " ";
		cout << enterDate << " ";
		cout.fill(' ');
		cout.setf(ios::left);
		cout.width(15);
		cout << family << " ";
		cout.fill(' ');
		cout.setf(ios::left);
		cout.width(15);
		cout << type << " ";
		if (status == false) {
			cout.fill(' ');
			cout.setf(ios::left);
			cout.width(15);
			cout << "Not available" << reason << endl;;
		}
		else {
			cout.fill(' ');
			cout.setf(ios::left);
			cout.width(15);
			cout << "Available" << reason << endl; }
	}
	char* getN(){ return name; }
	char* getBD(){ return birthDate; }
	char* getED(){ return enterDate; }
	char* getR(){ return reason; }
	char* getF(){ return family; }
	char* getT(){ return type; }
	char* getS(){
		if (!status){ return "false"; }
		else return "true";
	}
	bool disableByName(char disable[]){
		if (!strcmp(name, disable)) {
			status = false;
			return true;
		} else return false;
	}
	bool statusCheck(){return status;}
	bool setStatus(bool b){status = b;}
	void reasonCheck(char r[]){strcpy(reason, r);}
	
};//class Animals
vector<Animals> animals;
//Derived classes
class Herbivorous : public Animals{
public: Herbivorous(char n[], char bDate[], char eDate[], char fam[], char typ[]) : 
		Animals(n, bDate, eDate, fam, typ){}
};
class Primates : public Animals{
public:	Primates(char n[], char bDate[], char eDate[], char fam[], char typ[]) :
		Animals(n, bDate, eDate, fam, typ){}
};
class Predators : public Animals{
public:	Predators(char n[], char bDate[], char eDate[], char fam[], char typ[]) :
		Animals(n, bDate, eDate, fam, typ){}
};
class Birds : public Animals{
public:	Birds(char n[], char bDate[], char eDate[], char fam[], char typ[]) :
		Animals(n, bDate, eDate, fam, typ){}
};
class Terrarium : public Animals{
public:	Terrarium(char n[], char bDate[], char eDate[], char fam[], char typ[]) :
		Animals(n, bDate, eDate, fam, typ){}
};

void menu(){
	cout << "Menu" << endl;
	cout << "\t1 - Create file" << endl;
	cout << "\t2 - View all entries" << endl;
	cout << "\t3 - New entry" << endl;
	cout << "\t4 - Disable entry" << endl;
	cout << "\t5 - Find entry" << endl;
	cout << "\t6 - Export to CSV file" << endl;
	cout << "\t0 - Exit" << endl;
	cout << "Your choice: ";
}
void outputFormat(){
	cout.fill(' ');
	cout.setf(ios::left);
	cout.width(10);
	cout << "Name";
	cout.fill(' ');
	cout.setf(ios::left);
	cout.width(11);
	cout << "Birth Date" << " ";
	cout << "Enter Date" << " ";
	cout.fill(' ');
	cout.setf(ios::left);
	cout.width(15);
	cout << "Family" << " ";
	cout.fill(' ');
	cout.setf(ios::left);
	cout.width(15);
	cout << "Type" << " ";
	cout.fill(' ');
	cout.setf(ios::left);
	cout.width(15);
	cout << "Status";
	cout.fill(' ');
	cout.setf(ios::left);
	cout.width(9);
	cout << "Reason" << "\n\n";
}
void createFile(){
	ofstream existCheck("ZOO");
	existCheck.close();
	if (!existCheck){
		cout << "File ZOO exist" << endl;
	}
	else {
		ofstream create("ZOO", ios::out);
		create << "Name\t" << "BirthDate\t" << "EnterDate\t" << "Family\t" << "Type\t" << "Status\t" << "Reason";
		create.close();
	}
}
void readFile(){
	ifstream read("ZOO", ios::in);
	read.ignore(50); // Ignore first line with table labels

	while (!read.eof()) {
		read >> name >> birthDate >> enterDate >> family >> type >> statusTemp >> reason;
		animals.push_back(Animals(name, birthDate, enterDate, family, type, statusTemp, reason));
	}
	read.close();
}
void writeFile(){
	ofstream write("ZOO", ios::out);
	write << "Name\t" << "BirthDate\t" << "EnterDate\t" << "Family\t" << "Type\t" << "Status\t" << "Reason";
	for (unsigned int i = 0; i < animals.size(); i++) {
		write << "\n" << animals[i].getN() << "\t"
			<< animals[i].getBD() << "\t"
			<< animals[i].getED() << "\t"
			<< animals[i].getF() << "\t"
			<< animals[i].getT() << "\t"
			<< animals[i].getS() << "\t"
			<< animals[i].getR();
	}
	write.close();
	animals.clear();
}
void allEntries(){
	readFile();
	outputFormat();
	for (unsigned int i = 0; i < animals.size(); i++){
		animals[i].get();
		cout << endl;
	}; //for
	animals.clear();
}
void newEntry(){
	cout << "Enter animal name: "; scanf("%15s", name);
	cout << "Enter date of birth d/m/y: "; scanf("%10s", birthDate);
	cout << "Enter date of enter d/m/y: "; scanf("%10s", enterDate);
	cout << "\t1 - Herbivorous" << endl;
	cout << "\t2 - Primates" << endl;
	cout << "\t3 - Predators" << endl;
	cout << "\t4 - Birds" << endl;
	cout << "\t5 - Terrarium" << endl;
	cout << "\t0 - Exit" << endl;
	cout << "Enter family: "; cin >> code2;
	cout << "Enter type: "; scanf("%19s", type);
}
void disableEntry(){
	char disable[10];
	cout << "Enter name for disabling: "; scanf("%9s", disable);
	for (unsigned int i = 0; i < animals.size(); i++){
		if (animals[i].disableByName(disable)) {
			char code3;
			cout << "\t1 - Sold" << endl;
			cout << "\t2 - Donative" << endl;
			cout << "\t3 - Dead" << endl;
			cout << "\t0 - Exit" << endl;
			cout << "Enter reason: "; cin >> code3;
			switch (code3){
			case '1': {animals[i].reasonCheck("Sold"); break;	}
			case '2':	{animals[i].reasonCheck("Donative"); break;	}
			case '3':	{animals[i].reasonCheck("Dead"); break;	}
			default: { cout << "Wrong choice\n"; break; }
			}
			break;
		} //if
	}// for
}
void findEntry(){
	char search[20];
	cout << "Enter search type: "; scanf("%19s", search);
	outputFormat();
	for (unsigned int i = 0; i < animals.size(); i++){
		if (!strcmp(animals[i].getT(), search)) {
			animals[i].get();
			cout << endl;
		}//if			
	}//for 		
	animals.clear();
}
void herbivorous(){
	Herbivorous Herb(name, birthDate, enterDate, "Herbivorous", type);
	ofstream write("ZOO", ios::app);
	write << "\n" << Herb.getN() << "\t"
		<< Herb.getBD() << "\t"
		<< Herb.getED() << "\t"
		<< Herb.getF() << "\t"
		<< Herb.getT() << "\t"
		<< Herb.getS() << "\t"
		<< Herb.getR();
	write.close();
}
void primates(){
	Primates Prim(name, birthDate, enterDate, "Primates", type);
	ofstream write("ZOO", ios::app);
	write << "\n" << Prim.getN() << "\t"
		<< Prim.getBD() << "\t"
		<< Prim.getED() << "\t"
		<< Prim.getF() << "\t"
		<< Prim.getT() << "\t"
		<< Prim.getS() << "\t"
		<< Prim.getR();
	write.close();
}
void predators(){
	Predators Pred(name, birthDate, enterDate, "Predators", type);
	ofstream write("ZOO", ios::app);
	write << "\n" << Pred.getN() << "\t"
		<< Pred.getBD() << "\t"
		<< Pred.getED() << "\t"
		<< Pred.getF() << "\t"
		<< Pred.getT() << "\t"
		<< Pred.getS() << "\t"
		<< Pred.getR();
	write.close();
}
void birds(){
	Birds Bird(name, birthDate, enterDate, "Birds", type);
	ofstream write("ZOO", ios::app);
	write << "\n" << Bird.getN() << "\t"
		<< Bird.getBD() << "\t"
		<< Bird.getED() << "\t"
		<< Bird.getF() << "\t"
		<< Bird.getT() << "\t"
		<< Bird.getS() << "\t"
		<< Bird.getR();
	write.close();
}
void terrarium(){
	Terrarium Terr(name, birthDate, enterDate, "Terrarium", type);
	ofstream write("ZOO", ios::app);
	write << "\n" << Terr.getN() << "\t"
		<< Terr.getBD() << "\t"
		<< Terr.getED() << "\t"
		<< Terr.getF() << "\t"
		<< Terr.getT() << "\t"
		<< Terr.getS() << "\t"
		<< Terr.getR();
	write.close();
}
void exportCSV(){
	ofstream write("ZOO.csv", ios::out);
	write << "Name," << "BirthDate," << "EnterDate," << "Family," << "Type," << "Status," << "Reason";
	for (unsigned int i = 0; i < animals.size(); i++) {
		write << "\n" << animals[i].getN() << ","
			<< animals[i].getBD() << ","
			<< animals[i].getED() << ","
			<< animals[i].getF() << ","
			<< animals[i].getT() << ","
			<< animals[i].getS() << ","
			<< animals[i].getR();
	}
	animals.clear();
}

void main()
{
		
	char code;
	do {
		menu();
		cin >> code;
		switch (code){
		case '1': {	createFile(); break; }
		case '2': {	allEntries(); break; } 
		case '3': {	newEntry();					
					switch (code2){
					case '1': { herbivorous();  break; }
					case '2': { primates();  break; }
					case '3': { predators();  break; }
					case '4': { birds(); break; }
					case '5': { terrarium(); break; }
					case '0': {exit(0); break; }
					}
				}
		case '4': {					  									
					readFile();
					disableEntry();
					writeFile();
				  } break;
		case '5': {								
					readFile();
					findEntry();
					break; }
		case '6':{
					readFile();
					exportCSV();
					break; }
		case '0':	{exit(0); break; }
		default: { cout << "Wrong choice\n"; break; }
	}
} while (code != '0');
	system("pause");
}