//main application
//made by:
// Habiba Gamal 900151007
// Mayada el Ghamry 900152853
// Farah Seif ElDin 900160195
//assignment 5

#include <iostream>
#include <string>
#include <fstream>
#include "BST.h"
using namespace std;

//const string dicname = "savedDictionary.txt";

int beginningMessage(); //outputs message at the start of the program
bool gotoMenu(); //returns true if user chooses to go back to menu
void handleMenu(BST <string, int> b[]); //processes the menu accroding to choices of the user
bool newDictionary(BST<string, int> b[]); //Generate a dictionary for an input text file
bool updateDictionary(BST<string, int> b[]); //Update a dictionary already stored on disk with the one obtained from a new text file
void saveDictionary(BST<string, int> b[]); //Save an updated dictionary to disk as a text file
void searchForFrequency(BST<string, int> b[]);  //Search and obtain the frequency of a given word in the dictionary
void maxFreq(BST<string, int> b[]);  //List the highest frequency word in each tree
void getMaxFreq(BST<string, int> b[]); //outputs the maximum frequency words in each BST
void produceListing(BST<string, int> b[]);  //Produce a listing of all dictionary words and their frequencies
bool generateDIC(BST<string, int>  dic[], string filename); //generate dictionary given an input file into an array of BSTs
bool loadDic(BST<string, int> b[36]); //loads a saved dictinary in a file into BSTs
bool isEmpty(BST <string, int> b[36]); //checks if array is empty/no loading
void exitProgram(BST <string, int> b[36]); //saves dictionary to disk according to choice of user
void queryRun(BST <string, int> b[36]); //query run assuming presence of an old dictionary


int main() {


	BST <string, int> dic[36]; //create array of type BST
	cout << endl;
	cout << "Welcome to our Text Concordance Program!" << endl;
	cout << endl;
	handleMenu(dic);

	system("pause");
	return 0;

}


int beginningMessage() //outputs message at the start of the program
{

	int n;

	
	cout << "MENU" << endl;
	cout << endl;
	cout << "1. Initial Run" << endl;
	cout << endl;
	cout << "2. Cumulative Run" << endl;
	cout << endl;
	cout << "3. Query Run" << endl;
	cout << endl;
	
	cout << endl;
	//cout << "Enter the number of the run you want." << endl;
	//dont forget to validate n
	do {
		cout << "Enter the number of the run you want." << endl;
		cin >> n;
	} while (n < 1 || n>3); //validation
	return n;
}

void handleMenu(BST <string, int> b[]) //processes the menu accroding to choices of the user
{

	int n = beginningMessage();

	switch (n)
    {
	case 1:
		if(newDictionary(b)) //generating dictionary of an input file
		exitProgram(b); //saves dictionary to disk according to choice of user
            
		if(gotoMenu()) //if user chooses to return back to menu
		handleMenu(b); //handle menu again

		break;
	case 2:
		if(updateDictionary(b)) //update an already saved dictionary
		exitProgram(b); //saves dictionary to disk according to choice of user
		if (gotoMenu()) //if user chooses to return back to menu
		handleMenu(b); //handle menu again

		break;
	case 3:
		queryRun(b); //query run assuming presence of an old dictionary
		if (gotoMenu()) //if user chooses to return back to menu
			handleMenu(b); //handle menu again
	

	default:
		break;
	}
	
}


//Generate a dictionary for an input text file
bool newDictionary(BST<string, int> b[])
{

	string s; //declares string
	cout << "File name of your new text: ";
	cin >> s; //gets filename

	return generateDIC(b, s); //generates dictionary using filename

}


//Update a dictionary already stored on disk with the one obtained from a new text file
bool updateDictionary(BST<string, int> b[])
{
	
	if (!loadDic(b))
    {
		return false;
	}
	
	string s;

	cout << "File name of the new text: ";
	cin >> s; //gets filename
	
	return generateDIC(b, s); //generate dictionary of new filename

}


//Save an updated dictionary to disk as a text file
void saveDictionary(BST<string, int> b[])
{

	cout << endl;
	string dicname;
	cout << "Name of file to save dictionary in: ";
	cin >> dicname; //gets filename
	b[0].preorderFile(dicname, false); //preorder traveral of BST into file
	for (int i = 1; i < 36; i++)
		b[i].preorderFile(dicname, true); //preorder traveral of BST into file
	if(!isEmpty(b)) //if array of BSTs is not empty
	cout << "Dictionary is saved successfully." << endl;
	else //if array of BSTs is empty
		cout << "Dictionary is empty. Did not save it." << endl;
}


//Search and obtain the frequency of a given word in the dictionary
void searchForFrequency(BST<string, int> b[]) {

	cout << endl;
	string w;
	if (!isEmpty(b)) //if array of BSTs is not empty
    {
		cout << "Please enter the word you want to get the frequency of:" << endl;
		cin >> w; //input word
		int f = -1;
		cout << endl;
		int i = (int)w[0]; //convert first character of word into ASCII
		if (i >= 97 && i <= 122) //if first char is a character from a to z
			if (!b[i - 97].isEmpty()) //if BST of this word is not empty
				b[i - 97].retrieve(w, f); //retrieve frequency of word

			else if (i >= 48 && i <= 57) //if first char is a number from 0 to 9
				if (!b[26 + i - 48].isEmpty()) //if BST of this word is not empty
					b[26 + i - 48].retrieve(w, f); //retrieve frequency of word
		if (f != -1)
			cout << "The word: " << w << " has frequency= " << f << "." << endl;
		else
			cout << "The word: " << w << " does not exist in the dictionary." << endl;
	}
	else cout << "Dictionary is empty." << endl;

}


//List the highest frequency word in each tree
void maxFreq(BST<string, int> b[]) {
	
	cout << endl;
	if (isEmpty(b))//if array of BSTs is empty
	{
		if (loadDic(b)) //if user is loading a dictionary
		getMaxFreq(b); //get max freq from new dictionary
		else
			cout << "No dictionary to search in. Please create a new one." << endl;
	}
	else //if array of BSTs is not empty
		getMaxFreq(b); //get max freq
	
	
	
}

//outputs the maximum frequency words in each BST
void getMaxFreq(BST<string, int> b[])
{
	if (!isEmpty(b)) //if array of BSTs is loaded
    {
		cout << "The words with the maximum frequency in the dictionary are the following." << endl;
		string w;
		int f;
		for (int i = 0; i < 36; i++) //loop over array of BSTs
			if (!b[i].isEmpty()) //if BST of this character is not empty
            {
				b[i].getMax(w, f); //get max frequency
				cout << w << " " << f << endl; //output word & frequency
			}
	}
	else cout << "Dictionary is empty." << endl;
}

//Produce a listing of all dictionary words and their frequencies
void produceListing(BST<string, int> b[])
{
	
	if (isEmpty(b)) //if array of BSTs is empty
		loadDic(b); //load dictionary
	cout << endl;
	for (int i = 0; i < 36; i++) //loop over indices of array
		b[i].traverse(); //traverse/output BST
}



//generate dictionary given an input file into an array of BSTs
bool generateDIC(BST<string, int>  dic[], string filename)
{

	ifstream inp; //declare input stream
	inp.open(filename.c_str()); //open file
	if (!inp.is_open()) //if file is not open
    {
		cout << "Failure to Open File\n";
		return false;
	}
	else //if file is open
	{
		string word;
		while (!inp.eof()) //while not end of file
		{
			inp >> word; //input word
		 
				for (int i = 0; i < word.length(); i++) //change all characters in word to lower case
					word[i] = (tolower(word[i]));
				while (word.size() != 0 && !isalnum(word[word.length() - 1])) //erase all characters that are not alpha numeric from the end of the string
                {
					word.erase(word.length() - 1);
				}
				if (((int)word[0] >= 97) && ((int)word[0] <= 122)) //if the first character is from a to z
				{
					if (dic[(int)word[0] - 97].search(word)) //if word is found in BST
					{
						int data;
						if (!dic[(int)word[0] - 97].retrieve(word, data))//retrieve frequency
							cout << "cannot retrieve data\n";
						if (!dic[(int)word[0] - 97].insert(word, ++data)) //add with incremented frequency
							cout << "cannot insert data\n";
					}
					else //if word is not found in BST
						if (!dic[(int)word[0] - 97].insert(word, 1)) //add with frequency 1
							cout << "cannot insert data\n";
				}
				if (((int)word[0] >= 48) && ((int)word[0] <= 57)) //if first character is a numeric from 0 to 9
				{
					if (dic[26 + (int)word[0] - 48].search(word)) //search for word in BST, if found
					{
						int data;
						if (!dic[26 + (int)word[0] - 48].retrieve(word, data)) //retrieve freq
							cout << "cannot retrieve data\n";
						if (!dic[26 + (int)word[0] - 48].insert(word, ++data)) //insert with incremented freq
							cout << "cannot insert data\n";
					}
					else //if not found in BST
						if (!dic[26 + (int)word[0] - 48].insert(word, 1)) //insert with frequency 1
							cout << "cannot insert data\n";
				}
			
		}
	}
	inp.close(); //close file
	return true;
}


//loads a saved dictinary in a file into BSTs
bool loadDic(BST<string, int> b[36])
{

	string dicname;
	cout << "File name of saved dictionary: ";
	cin >> dicname; //gets name of input file
	ifstream inp; //declare input file
	inp.open(dicname); //open input file
	//BST <string, int> b[36];
	for (int i = 0; i < 36; i++)
		b[i].empty();
	
	int cnt = 0; //declare count=0
	if (inp.is_open()) //if file is opened
    {

		string key;
		int data;
		inp >> key; //get key
		inp >> data; //get data
		while (!inp.eof()) //while not end of file
        {
			cnt++; //increment count
			if ((int)key[0] >= 97) //beginning charcter from a to z
            {

				b[(int)key[0] - 97].insert(key, data); //insert to BST of corresponding index
			}
			else //beginning character from 0 to 9
            {
				b[26 + (int)key[0] - 48].insert(key, data); //insert to BST of corresponding index
			}

			inp >> key; //get key
			inp >> data; //get data

		}
		//for (int i = 0; i < 36; i++)
		//	c[i] = b[i]; //put b[i] in c[i]
	}
	else //if file is not opened
    {
		cout << "Error opening file." << endl;
		inp.close();
		return false;
	}
		

	inp.close(); //close file
	if (cnt == 0) //if count is not incremented
		return false;

	return true;

}

bool gotoMenu() //returns true if user chooses to go back to menu
{

	cout << endl;
	int n;
	

	//dont forget validation
	do { cout << "Go back to the main menu. (0 for NO, 1 for YES)" << endl;
		cin >> n; } while (n != 0 && n != 1);//input command

	return n; //return command
}


bool isEmpty(BST <string, int> b[36]) //checks if array is empty/no loading
{

	for (int i = 0; i < 36; i++)
		if (!b[i].isEmpty()) //if not empty/if loaded
			return false;
	return true;
}

void exitProgram(BST <string, int> b[36]) //saves dictionary to disk according to choice of user
{
	int n;
	cout << "Do you want to save your dictionary? (0 for No, 1 for Yes)" << endl;
	cin >> n; //input command

	if (n == 1)
    {
	saveDictionary(b); //save dictionary to disk
	}
		
}

void queryRun(BST <string, int> b[36]) //query run assuming presence of an old dictionary
{

	int n;

	if (isEmpty(b)) //if BST is not loaded
    {
		cout << "Your dictionary is empty." << endl;
		cout << "1. Load saved dictionary from file." << endl;
		cout << "2. Generate new dictionary." << endl;
		cout << "3. Go back to main menu." << endl;
		cin >> n;
		if (n == 1)
			loadDic(b); //load a saved dictionary
		else if (n == 2)
			newDictionary(b); //load new dictionary
		else if (n == 3) //return to main menu
			return;
		else
		{
			cout << "invalid input" << endl; //validation
			return;
		}
	}

	cout << "1. Find frequency of word. (0 for NO, 1 for YES)" << endl;
	cin >> n; //input command
	if (n == 1)
		searchForFrequency(b); //search for frequency of a given word
	
		cout << "2. List highest frequency words. (0 for NO, 1 for YES)" << endl;
		cin >> n; //input command
		if (n == 1)
			getMaxFreq(b); //output max frequency word in each BST
		
			cout << "3. Display dictionary listings. (0 for NO, 1 for YES)" << endl;
			cin >> n; //input command
			if (n == 1)
				produceListing(b); //output list of words in dictionary with their frequencies
		
	
	
}
