#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

//detta program är en ordbok som innehåller möjligheten till att lägga till egna ord, ta bort ord, printa ut alla ord, söka efter ord standard och söka efter ord på ett avancerat sätt!! 

class ord {   //skapar en klass som innehåller funktioner som sätter och hämtar ord. ( tex för att senare skapa orden)
private:

	string word;
	string desc;

public:

	//konstruktor
	ord(string w, string d) {
		word = w;
		desc = d;

	}

	// en set funktion, i och med att den är en "set" så betyder det att det skapas ett samband som man sedan kan "get" för att hämta det som sätts.
	void setWord(string w) {
		word = w;
	}

	// samma som ovan, fast beskrivningen av ordet.
	void setDesc(string d) {
		desc = d;
	}

	//Här är en "get" funktion som man kan calla genom "getWord()" för att hämta ordet.
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
	bool operator==(string s) { // detta är en jämförande operator som ser att word är lika med s.
		return word == s;
	}
};

class ordBok {  //Här är ordboks klassen där allt från listan till alla funktioner som används för att t.ex lägga till ord.
public:
	string searchWord;    //stringen som används för att söka efter ord (cin)
	list<ord> ordbok;  //en "list" som lagrar alla ord i en array.
	list<ord>::iterator it; //en iterator, vilket är ett objekt som är lite som en pekare

	void add(ord o) {       // lägger till ord
		ordbok.push_back(o); //pushar in ett ord i listan
	}

	bool removeWord() { //tar bort ord, bool funktion pågrund av error handeling reasons. 
		for (it = ordbok.begin(); it != ordbok.end(); it++) { 
			if (it->getWord() == searchWord) {
				ordbok.erase(it);
				return true;
			}

		}
		return false;
	}


	void search() { // en sök funktion som innehåller en for loop som försöker hitta det ord du sökte på i ordboken, om det finns så visas det. annars inte.
		for (ord o : ordbok) {
			if (o == searchWord) {
				cout << "Description: " << o.getdesc() << endl;
				return;
			}
		}
		cout << "The word you entered does not exist, sorry bro" << endl;  // error handeling
	}

	void advancedSearch(string s1) {     // advanced search funktion
		//detta är if satsen för när man skriver till exempel pot* och output blir potatis
		if (s1[s1.size() - 1] == '*') {  // sätter att wildcardet "*" sist av ordet eftersom att s1.size(), hämtar längden på s1 stringen, och det räknas med index så - 1 för att det börjar på 0
			s1 = s1.substr(0, s1.size() - 1); // tar substringen av s1 från index 0 till index nummret längden av stringen - 1
			cout << s1 << endl;
			for (ord o : ordbok) { // for loop
				size_t index = o.getWord().find(s1);
				if (index == 0) {
					cout << o.getWord() << endl;
				}
			}

		}
		// if satsen för när wildcardet är i början, till exempel *is och output blir potatis och pingis
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
			cout << o.getWord() << endl; // output alla ord som är lagrade
		}
	}
};
int main()   // main funktionen
{
	ordBok dic;   // skapar en variabel för ordBok klassen
	bool run = false;
	string input;   // string som används för att välja option
	string word;
	string beskrivning;

	dic.add(ord("potatis", "potato"));  // manuellt skapade ord
	dic.add(ord("lukas", "noob"));
	dic.add(ord("phone", "a phone"));
	dic.add(ord("pingis", "table tennis"));

	while (run = true) {  //while loop som körs under hela programmet
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
			dic.search(); // callar sökfunktionen i ordBok klassen
		}
		else if (input == "add") {
			cout << "#################" << endl;
			cout << "Type in a word that you would like to add" << endl;
			cin >> word;
			cin.ignore(1000, '\n');
			cout << "#################" << endl;
			cout << "enter a description" << endl;
			getline(cin, beskrivning);  //fixar att mellanrum i stringen är möjligt
			dic.add(ord(word, beskrivning)); // callar add funktionen i ordBok och lägger till valda ordet + beskrivningen
			cout << "successfully added: " << word << endl; //confirmation
		}
		else if (input == "remove") {
			cout << "#################" << endl;
			cout << "Type in the word that you would like to remove" << endl;
			cout << "#################" << endl;
			cin >> dic.searchWord; // val av ord som ska borttttttt

			if (dic.removeWord() == true) { // om ordet finns så tas det bort här
				dic.removeWord();
				cout << "You successfully removed the word " << dic.searchWord << endl;
			}
			else { // error handeling, om ordet inte finns så får du detta
				cout << "The word you entered does not exist" << endl;
			}
		}

		else if (input == "exit") { //exit av programmet.... om du inte vill använda det längre.......
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