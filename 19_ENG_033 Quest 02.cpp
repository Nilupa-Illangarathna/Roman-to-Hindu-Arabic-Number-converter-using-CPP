#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::reverse;

struct Characters  //structure to store the value of each character
{
	int char_value;
	char character;
};

int CharacterCompare(vector <Characters> char_vec , char character) //It returns the value of the input character (eg:X returns 10)
{
	int i=0;
	while(character!=char_vec[i].character)
	{
		i++;
	}
	return char_vec[i].char_value;
}


bool Validate_the_entry(string &str , vector <Characters> char_vec) //This function validates the string given to it. It checkes whether it follows the rules of roman numbers or not. 
{																	//If it follows rules of roman numbers this function will make all letters uppercase

	char previousChar=NULL; //Variable to store the previous character of the string
	int previousCount=1;	//variable to store the number of times the same character occurs again and again (eg:"Iii" has 3 I characters sor presiousCount is set to 3 at the end of this string)
	for(int i=0;i<str.size();i++)
	{
		if(str[i]=='I'||str[i]=='i')
		{
			if(previousChar==NULL && i==0)//
			{
				previousChar='I';
				previousCount=1;
				str[i]='I';
			}
			else if(previousChar=='I'&&i+2==str.size()&&(str[i+1]=='V'||str[i+1]=='X'))
			{
				previousChar='I';
				str[i]='I';
			}
			else if(previousChar=='I' && previousCount<3 && i+3>str.size())
			{
				previousCount++;
				str[i]='I';
			}
			else if(CharacterCompare(char_vec , previousChar) > CharacterCompare(char_vec , 'I'))
			{
				previousChar='I';
				previousCount=1;
				str[i]='I';
			}
			else
			{
				return false; 
			}
		}
		else if(str[i]=='V'||str[i]=='v')
		{
			if(previousChar==NULL && i==0)
			{
				previousChar='V';
				previousCount=1;
				str[i]='V';
			}
			else if(CharacterCompare(char_vec , previousChar) > CharacterCompare(char_vec , 'V'))
			{
				previousChar='V';
				previousCount=1;
				str[i]='V';
			}
			else if(previousChar=='I' && previousCount==1 && i+1==str.size() )
			{
				previousChar='V';
				previousCount=1;
				str[i]='V';
			}	
			else
			{
				return false; 
			}
			str[i]='V';
		}
		else if(str[i]=='X'||str[i]=='x')
		{
			if(previousChar==NULL && i==0)
			{
				previousChar='X';
				previousCount=1;
				str[i]='X';
			}
			else if(CharacterCompare(char_vec , previousChar) > CharacterCompare(char_vec , 'X'))
			{
				previousChar='X';
				previousCount=1;
				str[i]='X';
			}
			else if(previousChar=='I' && previousCount==1 && i+1==str.size() )
			{
				previousChar='X';
				previousCount=1;
				str[i]='X';
			}		
			if(previousChar=='X' && previousCount<=3)
			{
				previousCount++;
				str[i]='X';
			}
			else
			{
				return false; 
			}	
			str[i]='X';
		}
		else if(str[i]=='L'||str[i]=='l')
		{
			if(previousChar==NULL && i==0)
			{
				previousChar='L';
				previousCount=1;
				str[i]='L';
			}
			else if(previousChar=='X'&&i==1)
			{
				str[i]='L';
			}
			else
			{
				return false; 
			}
			str[i]='L';
		}
		else if(str[i]=='C'||str[i]=='c')
		{
			if(previousChar==NULL && i==0)
			{
				previousChar='C';
				previousCount=1;
				str[i]='C';
			}
			else if(previousChar=='X'&&i==1)
			{
				str[i]='C';
			}
			else
			{
				return false;
			}
			str[i]='C';
		}
		else
		{
			return false; 
		}
	}
	return true; //returns true only if the string follows rules of roman numbers
}

int Evaluate(string str , vector <Characters> char_vec)
{
	int Current_Summation=0;  //This variable stores the value of the number which is calculated this far
	char PreviousCharacter;  //Variable to store the previous character which is been considered
	
	reverse(str.begin(),str.end());	//set the string to reverse order
	
	for(int i=0;i<str.size();i++)
	{
		if(i==0)
		{
			Current_Summation+=CharacterCompare(char_vec , str[i]);
			PreviousCharacter=str[i];
		}
		else if(CharacterCompare(char_vec , str[i])>=CharacterCompare(char_vec , PreviousCharacter))
		{
			Current_Summation+=CharacterCompare(char_vec , str[i]);
			PreviousCharacter=str[i];
		}
		else if(CharacterCompare(char_vec , str[i])<CharacterCompare(char_vec , PreviousCharacter))
		{
			Current_Summation-=CharacterCompare(char_vec , str[i]);
			PreviousCharacter=str[i];	
		}
	}
	return Current_Summation;
}



int main()
{
	vector <Characters> char_vec={{ 1 , 'I' } , { 5 , 'V' } , { 10 , 'X' } , { 50 , 'L' } , { 100 , 'C' }};

	int ValidNumbers=0; //Number of valid roman numbers which are inputed from the txt file 
	int InvalidNumbers=0; //Number of invalid inputs which are inputted from the txt file
	int TotalNumbers=0; //the total number of inputs which are taken inside from the txt
	
	ifstream file;  //creating the file object
	file.open("numbers.txt"); //opening the numbers txt file
	
	while(!file.eof()) //read the txt untile the enf of the file
	{
		TotalNumbers++;
		string str;
		file>>str;
		string temp=str;

		if(Validate_the_entry(str,char_vec))
		{
			ValidNumbers++;
			if(str.size()<8)
				cout<<"\t"<<temp<<"\t\t\t: "<<Evaluate(str, char_vec)<<endl;
			else
				cout<<"\t"<<temp<<"\t\t: "<<Evaluate(str, char_vec)<<endl;
		}
		else
		{
			InvalidNumbers++;
			if(str.size()<9)
				cout<<"\t"<<temp<<" \t\t\t error"<<endl;
			else
				cout<<"\t"<<temp<<" \t\t\t error"<<endl;
		}	
		

	}
	
	
	cout<<endl<<endl<<endl<<endl;
	cout<<"\t\t"<<"Total number of inputs \t\t\t:"<<TotalNumbers<<endl;
	cout<<"\t\t"<<"Total number of valid inputs \t\t:"<<ValidNumbers<<endl;
	cout<<"\t\t"<<"Total number of invalid inputs\t\t:"<<InvalidNumbers<<endl<<endl;
	
	file.close(); //closing the opened resourse
	return 0;
}
