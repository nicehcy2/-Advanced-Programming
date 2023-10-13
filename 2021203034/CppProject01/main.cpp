#include "std_lib_facilities.h"
using namespace std;

void PrintMessage1();
void PrintMessage2();
void PrintMessage3();
int ChooseAnOption(void);
void PrintWords(vector<string>&);
string AddWord(vector<string>&);
vector<string> SaveEasyWords(vector<string>&, vector<string>&);
vector<string> SaveHardWords(vector<string>&, vector<string>&);
int SelRanEWord(vector<string>);
string SwapEWords(vector<string>, int);
int SelRanHWord(vector<string>);
string SwapHWords(vector<string>, int);
string CheckProblem(string, string, int*);
//string SaveEasyWords(vector<string>&, vector<string>&, int, int);
//string SaveEasyWords(vector<string>&, vector<string>&, int, int);


int main(void)
{	
	int num, numPW, numSP, chance, select, Tsize, cntE=0, cntH=0;
	string newWord, ranWord, userInp, temp;
	vector<string> words = { "drift","professional","midnight","scatter","relevance","visit","disaster","commerce",
		"coincide","progress","shift","spell","veil","desk","gown","umbrella","gregarious","craftsman","wriggle","score",
		"deliver","vote","dirty","chain","road","charter","feign","duck","highway","add","van","mutual","bang","table",
		"venture","deficiency","depend","dimension","holiday","scrap","unlike","coast","command","base","recommend",
		"spit","corner","huge","economic","sigh" };
	vector<string> Ewords, Hwords;
	int digit[100] = { 0, };

	SaveEasyWords(words, Ewords);
	SaveHardWords(words, Hwords);

	/*for (int i = 0; i < 10; i++) //A statement to check whether a word is properly initialized
	{
		cout << words[i] << '\n';
	}cout << '\n';*/
	
	while (true)
	{	
		PrintMessage1();
		num = ChooseAnOption();
		switch (num) {
		case 1:
			while (true) {
				PrintMessage2();
				numPW = ChooseAnOption(); 

				switch (numPW) {
				case 1:
					PrintWords(words);
					break;
				case 2:
					newWord = AddWord(words);
					if (newWord != "ERROR!") {
						words.push_back(newWord);
						if (newWord.length() <= 5)
							Ewords.push_back(newWord);
						else if (newWord.length() > 5)
							Hwords.push_back(newWord);
					}
						
					break;
				case 3:
					break;
				}
				if (numPW == 3)
					break;
			}
			break;
		case 2: //GAME ALGORITHM
			while (true) {
				PrintMessage3();
				numSP = ChooseAnOption();
				switch (numSP)
				{
				case 1:
					sort(Ewords);
					select = SelRanEWord(Ewords);
					ranWord = SwapEWords(Ewords, select);
					chance = 1;
					for (int i = 0; i < 100; i++)
						digit[i] = 0;
					while(true){
						if (chance > 3) {
							cout << "Oops! You failed to solve the puzzle...\n";
							cout << "The correct answer is '" << Ewords[select] << ".'\n\n";
							break;
						}
						cout << "[" << chance << "/3] " << "Guess the original word : ";
						cin >> userInp; 
						chance++;
						
						cout << ">> [ ";
						temp = CheckProblem(Ewords[select], userInp, digit);
						Tsize = temp.size();
						for (int i = 0; i < Ewords[select].size(); i++) {
							if (temp[i] != '-')
								digit[i] = 1;
						}
						//cout << temp << " ]\n";
						for (int i = 0; i < Ewords[select].size(); i++) {
							cout << temp[i];
						}cout << " ]\n";
						if (temp == Ewords[select] && userInp.size() == Ewords[select].size()) {
							cout << "Congratulation! You got the answer right!\n\n";
							break;
						}
					}
					break;
				case 2:
					sort(Hwords);
					select = SelRanHWord(Hwords);
					ranWord = SwapHWords(Hwords, select);
					chance = 1;
					for (int i = 0; i < 100; i++)
						digit[i] = 0;
					while (true) {
						
						if (chance > 5) {
							cout << "Oops! You failed to solve the puzzle...\n";
							cout << "The correct answer is '" << Hwords[select] << ".'\n\n";
							break;
						}
						cout << "[" << chance << "/5] " << "Guess the original word : ";
						cin >> userInp; 
						chance++;
						
						cout << ">> [ ";
						temp = CheckProblem(Hwords[select], userInp, digit);
						
						for (int i = 0; i < Hwords[select].size(); i++) {
							if (temp[i] != '-')
								digit[i] = 1;
						}

						//cout << temp << " ]\n";
						for (int i = 0; i < Hwords[select].size(); i++) {
							cout << temp[i];
						}cout << " ]\n";

						if (temp == Hwords[select] && userInp.size()==Hwords[select].size()) {
							cout << "Congratulation! You got the answer right!\n\n";
							break;
						}
					}
					break;
				case 3:
					break;
				}
				if (numSP == 3)
					break;
			}
			break;
		}
		if (num == 3) {
			cout << "Good Bye!!\n";
			break;
		}
	}
	return 0;
}

void PrintMessage1(void) //print Title Screen
{	
	cout << "<<< WORD JUMBLE >>>" << '\n';
	cout << "1. Manage List\n";
	cout << "2. Solve Puzzle\n";
	cout << "3. Exit\n\n";
}

void PrintMessage2(void) //print to confirm words
{
	cout << "[  MANAGE LIST  ]" << '\n';
	cout << "1. Print Words\n";
	cout << "2. Add word\n";
	cout << "3. Return\n\n";
}

void PrintMessage3(void) //print Game Option
{
	cout << "[  SOLVE PUZZLE  ]" << '\n';
	cout << "1. Easy Mode\n";
	cout << "2. Hard Mode\n";
	cout << "3. Return\n\n";
}

int ChooseAnOption(void)
{	
	int num;
	while (true) {
		cout << "Choose an option (1-3): ";
		cin >> num;
		if ((num >= 1) && (num <= 3)) {
			cout << '\n';
			break;
		}
	}
	return num;
}

/*vector<string> InitializeWords()
{
	vector<string> words = { "add", "bang", "base", "chain", "charter", "coast", "coincide", "command", "commerce", "corner"};
	return words;
}*/

void PrintWords(vector<string>& words) //print words initialized
{	
	cout << "A total of " << words.size() <<" words are available : \n";
	sort(words.begin(), words.end());
	for (const auto& word:words) {
		cout << word <<'\n';
	}cout << '\n';
}

string AddWord(vector<string>& words) //Add a new word in vector
{
	string newWord;
	int overlap = 0;
	cout << "Input a new word: ";
	cin >> newWord;
	if (!cin) {
		cout << "Failed to add new word\n";
		return "ERROR!";
	}
	else {
		for (int i = 0; i < words.size(); i++) {
			if (newWord == words[i])
				overlap = 1;
		}
		if (overlap == 1) {
			cout << "The word \"" << newWord << "\" already exists in the list.\n\n";
			return "ERROR!";
		}
		else
			cout << "The word \"" << newWord << "\" has been succesfully inserted in the list.\n\n";
	}

	return newWord;
}

vector<string>SaveEasyWords(vector<string>& words, vector<string>& Ewords)
{	
	for (int i = 0; i < words.size(); i++){ 
		if (words[i].length()<=5) {
			Ewords.push_back(words[i]);
		}
	}
	return Ewords;
}

vector<string>SaveHardWords(vector<string>& words, vector<string>& Hwords)
{
	for (int i = 0; i < words.size(); i++) {
		if (words[i].length() > 6) {
			Hwords.push_back(words[i]);
		}
	}
	return Hwords;
} 

int SelRanEWord(vector<string> Ewords)
{
	int select;
	srand((unsigned int)time(NULL));
	select = rand() % Ewords.size();
	return select;
}

string SwapEWords(vector<string> Ewords, int select) //a function randomly select a easy word and swap a word 
{	
	int swapNum1, swapNum2, swapNum3, swapNum4;
	srand((unsigned int)time(NULL));
	cout << "I give you a jumbled word '";
	swapNum1 = rand() % Ewords[select].size();
	swapNum2 = rand() % Ewords[select].size();
	swapNum3 = rand() % Ewords[select].size();
	swapNum4 = rand() % Ewords[select].size();
		
	swap(Ewords[select][swapNum1], Ewords[select][swapNum2]);
	swap(Ewords[select][swapNum3], Ewords[select][swapNum4]);
	cout << Ewords[select] << "'.\n";
	//cout << "Guess the original word : "<< Ewords[select] <<'\n';

	return Ewords[select];
}

int SelRanHWord(vector<string> Hwords)
{
	int select;
	srand((unsigned int)time(NULL));
	select = rand() % Hwords.size();
	return select;
}

string SwapHWords(vector<string> Hwords, int select) //a function randomly select a easy word and swap a word 
{
	int swapNum1, swapNum2, swapNum3, swapNum4, swapNum5, swapNum6;
	cout << "I give you a jumbled word '";
	swapNum1 = rand() % Hwords[select].size();
	swapNum2 = rand() % Hwords[select].size();
	swapNum3 = rand() % Hwords[select].size();
	swapNum4 = rand() % Hwords[select].size();
	swapNum5 = rand() % Hwords[select].size();
	swapNum6 = rand() % Hwords[select].size();
	/*while (true) {
		swapNum2 = rand() % Hwords.size();
		if (swapNum1 != swapNum2)
			break;
	}
	while (true) {
		swapNum3 = rand() % Hwords.size();
		if ((swapNum1 != swapNum3)&&(swapNum2 != swapNum3));
			break;
	}
	while (true) {
		swapNum4 = rand() % Hwords.size();
			if ((swapNum1 != swapNum4) && (swapNum2 != swapNum4)&&(swapNum3 != swapNum4));
				break;
	}*/
	swap(Hwords[select][swapNum1], Hwords[select][swapNum2]);
	swap(Hwords[select][swapNum3], Hwords[select][swapNum4]);
	swap(Hwords[select][swapNum5], Hwords[select][swapNum6]);
	cout << Hwords[select] << "'.\n";
	//cout << "Guess the original word : "<< Ewords[select] <<'\n';

	return Hwords[select];
}

string CheckProblem(string word, string user, int digit[])
{	
	string temp;
	int err=0;

	if (user.size() >= word.size())
	{	
		temp = user;
		//temp.erase(word.size(), user.size());
		for (int i = 0; i < word.size(); i++)
		{	
			if (digit[i] == 0) {
				if (user[i] == word[i]) {
					temp[i] = word[i];
				}
				else
					temp[i] = '-';
			}
			else {
				temp[i] = word[i];
				if (user[i] != word[i]) {
					err++;
				}
			}
		}
		
	}

	else if(user.size() < word.size()) {
		for (int i = 0; i < word.size(); ++i) {
			temp.insert(i, "-");
		}
		for (int i = user.size(); i < word.size(); ++i) {
			user.insert(i, "-");
		}
		for (int i = 0; i < word.size(); i++)
		{	
			if (digit[i] == 0) {
				if (user[i] == word[i]) {
					temp[i] = word[i];
				}
				else
					temp[i] = '-';
			}
			else {
					temp[i] = word[i];
					if (user[i] != word[i]) {
						err++;
					}
			}
		}
	}
	string Etemp = temp + '?';
	if (err > 0) return Etemp;
	else	return temp;
}

/*string SaveEasyWords(vector<string>& words, vector<string>& Ewords, int i, int j)
{
	if (sizeof(&words[i]) <= 1000) {
		Ewords[j] = words[i];
		return Ewords[j];
	}
	else
		return "-1";
}*/

