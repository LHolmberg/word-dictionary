#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

//detta program �r en ordbok som inneh�ller m�jligheten till att l�gga till egna ord, ta bort ord, printa ut alla ord, s�ka efter ord standard och s�ka efter ord p� ett avancerat s�tt!! 

class ord {   //skapar en klass som inneh�ller funktioner som s�tter och h�mtar ord. ( tex f�r att senare skapa orden)
private:

	string word;
	string desc;

public:

	//konstruktor
	ord(string w, string d) {
		word = w;
		desc = d;

	}

	// en set funktion, i och med att den �r en "set" s� betyder det att det skapas ett samband som man sedan kan "get" f�r att h�mta det som s�tts.
	void setWord(string w) {
		word = w;
	}

	// samma som ovan, fast beskrivningen av ordet.
	void setDesc(string d) {
		desc = d;
	}

	//H�r �r en "get" funktion som man kan calla genom "getWord()" f�r att h�mta ordet.
	string getWord() {
		return word;
	}

	//samma som ovan, "gettar" description
	string getdesc() {
		return desc;

	}


	//en string funktion som returnerar ordet + beskrivningen
	string str() {
		return word + desc;
	}
	bool operator==(string s) { // detta �r en j�mf�rande operator som ser att word �r lika med s.
		return word == s;
	}
};

class ordBok {  //H�r �r ordboks klassen d�r allt fr�n listan till alla funktioner som anv�nds f�r att t.ex l�gga till ord.
public:
	string searchWord;    //stringen som anv�nds f�r att s�ka efter ord (cin)
	list<ord> ordbok;  //en "list" som lagrar alla ord i en array.
	list<ord>::iterator it; //en iterator, vilket �r ett objekt som �r lite som en pekare

	void add(ord o) {       // l�gger till ord
		ordbok.push_back(o); //pushar in ett ord i listan
	}

	bool removeWord() { //tar bort ord, bool funktion p�grund av error handeling reasons. 
		for (it = ordbok.begin(); it != ordbok.end(); it++) { 
			if (it->getWord() == searchWord) {
				ordbok.erase(it);
				return true;
			}

		}
		return false;
	}


	void search() { // en s�k funktion som inneh�ller en for loop som f�rs�ker hitta det ord du s�kte p� i ordboken, om det finns s� visas det. annars inte.
		for (ord o : ordbok) {
			if (o == searchWord) {
				cout << "Description: " << o.getdesc() << endl;
				return;
			}
		}
		cout << "The word you entered does not exist, sorry bro" << endl;  // error handeling
	}

	void advancedSearch(string s1) {     // advanced search funktion
		//detta �r if satsen f�r n�r man skriver till exempel pot* och output blir potatis
		if (s1[s1.size() - 1] == '*') {  // s�tter att wildcardet "*" sist av ordet eftersom att s1.size(), h�mtar l�ngden p� s1 stringen, och det r�knas med index s� - 1 f�r att det b�rjar p� 0
			s1 = s1.substr(0, s1.size() - 1); // tar substringen av s1 fr�n index 0 till index nummret l�ngden av stringen - 1
			cout << s1 << endl;
			for (ord o : ordbok) { // for loop
				size_t index = o.getWord().find(s1);
				if (index == 0) {
					cout << o.getWord() << endl;
				}
			}

		}
		// if satsen f�r n�r wildcardet �r i b�rjan, till exempel *is och output blir potatis och pingis
		else if (s1[0] == '*') {
			s1 = s1.substr(1, s1.size() - 1);
			for (ord o : ordbok) {

				string c = o.getWord();
				if (c.find(s1) == (c.length() - 1) - (s1.length() - 1)) {
					cout << o.getWord() << endl;
				}
			}
		}
	}

	void skrivut() {  // funktion som printar ut alla ord 
		for (ord o : ordbok) { // for loop
			cout << o.getWord() << endl; // output alla ord som �r lagrade
		}
	}
};
int main()   // main funktionen
{
	ordBok dic;   // skapar en variabel f�r ordBok klassen
	bool run = false;
	string input;   // string som anv�nds f�r att v�lja option
	string word;
	string beskrivning;

	dic.add(ord("potatis", "potato"));  // manuellt skapade ord
	dic.add(ord("lukas", "noob"));
	dic.add(ord("phone", "a phone"));
	dic.add(ord("pingis", "table tennis"));

	while (run = true) {  //while loop som k�rs under hela programmet
		cout << "######################" << endl;
		cout << "Options:" << endl;
		cout << "Type 'print' to print out all of your existing words." << endl;
		cout << "Type 'search' to search for an existing word, it will be displayed with a descripton." << endl;
		cout << "Type 'advsearch' to use the advanced search" << endl;
		cout << "Type 'add' to add a word" << endl;
		cout << "Type 'remove' to remove a word and its description" << endl;
		cout << "Type 'exit' to exit the application" << endl;
		cout << "#####################" << endl;
		cin >> input;
		if (input == "print") {
			dic.skrivut(); //callar funktionen skrivut() i klassen ordBok som printar ut alla ord som finns
		}
		else if (input == "search") {
			cin >> dic.searchWord;
			dic.search(); // callar s�kfunktionen i ordBok klassen
		}
		else if (input == "add") {
			cout << "#################" << endl;
			cout << "Type in a word that you would like to add" << endl;
			cin >> word;
			cin.ignore(1000, '\n');
			cout << "#################" << endl;
			cout << "enter a description" << endl;
			getline(cin, beskrivning);  //fixar att mellanrum i stringen �r m�jligt
			dic.add(ord(word, beskrivning)); // callar add funktionen i ordBok och l�gger till valda ordet + beskrivningen
			cout << "successfully added: " << word << endl; //confirmation
		}
		else if (input == "remove") {
			cout << "#################" << endl;
			cout << "Type in the word that you would like to remove" << endl;
			cout << "#################" << endl;
			cin >> dic.searchWord; // val av ord som ska borttttttt

			if (dic.removeWord() == true) { // om ordet finns s� tas det bort h�r
				dic.removeWord();
				cout << "You successfully removed the word " << dic.searchWord << endl;
			}
			else { // error handeling, om ordet inte finns s� f�r du detta
				cout << "The word you entered does not exist" << endl;
			}
		}

		else if (input == "exit") { //exit av programmet.... om du inte vill anv�nda det l�ngre.......
			return 0;

		}
		else if (input == "advsearch") {
			cout << "Search in an advanced way, for example, use po* to get potatis as output, or *is to get potatis and pingis as output" << endl;
			cin >> word;
			dic.advancedSearch(word);  // SAME SOM INNAN

		}

		else {
			cout << "This command does not exit" << endl; // ERROR HANDELING OM KOMMANDOT INTE FINNS

		}

	}

}