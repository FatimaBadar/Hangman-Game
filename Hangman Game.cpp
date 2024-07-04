#include<iostream>
#include<fstream>
#include<time.h>
#include <conio.h>
#include<windows.h>
#include<process.h>
#include <unistd.h>
using namespace std;
#include<string.h>

class File{
	public:
		string word, wordList[99];
		
		File(){
		}
		
		void file(){
			int i;
			
			srand(time(0)); // initialise random number generators
		    fstream randWord;
			randWord.open("words.txt");
			
			cout << "\n\t\t\t\t\t\t";
		    for(i=0; i<99; i++){
			   randWord >> wordList[i];
		// randomWord == wordList[i];
		    }

			int randNum = rand() % 100; //random number
		    word = wordList[randNum];
		    
		    randWord.close();
		    cout << "\n\t\t\t\t\t\t";
		    string hiddenWord(word.length(), '*');
	    }
	    
};

class Word: public File{
	private:
		string secretWord;
	
	public:
		friend class Hangman;
		int wordLength;
		int blankLength;
		string blank;
				
		Word(){
		}
		
		void setWord(string s){
			secretWord = s;
		}

		bool check(string s){			
			int i;
			for(i=0; s[i]!='\0'; i++){
			
			if(isalpha(s[i])!=0){ //alphabet check
			   return true;
		    }
		    else
		    return false;
		}
	}
	
		string getWord(){
			return secretWord;
		}
		
		void length(string s){
			int i;
			secretWord = s;
			
			wordLength = secretWord.length();
			//cout << wordLength;
			blankLength = wordLength;
		//	cout << blankLength;
		}
		
		void setBlanks(){
			int i;		
				
			for(i=0; secretWord[i]!='\0'; i++){
				secretWord[i] = tolower(secretWord[i]); //uppercase alphabets to lowercase
			}
	    	
			for(i=0; secretWord[i]!='\0'; i++){
		       	blank[i] = '_';
		       	cout << blank[i] << " ";
			}	
	    }
	    
};

class Hangman:public Word{
	public:
		int tries, count, wrongLength;
		string wrongLetter;
		string guesses;
		char guess;
		bool gameEnded;
		
		Hangman(int t): Word(){
			tries = t;
			gameEnded = 0;
		}
		
		bool isCorrectGuess(char guess){
			guesses.push_back(guess);
			int i, count=0;
			// Check if word is fully guessed
			for(i=0; secretWord[i]!= '\0'; i++)
			{
				if(isAlreadyGuessed(secretWord[i]))
				{
					count++;
				}
			}

			if(count >= wordLength)
			{
				gameEnded = true;
			}
				
			if(secretWord.find(guess)<secretWord.length()){
			    return true;
			}
			else{
				return false;
            }
		}
				
		bool isAlreadyGuessed(char guess)
		{
			if(guesses.find(guess)<guesses.length()){ 
				return true;
			}
			else{
				return false;
		    }
	    }
	
     	bool addToWrongGuesses(char guess){
			if(secretWord.find(!guess)<secretWord.length()){ 
			    return true;
			}
			else{
			 	return false;
            }
	    }
	    
		void guessed(){
		    int i, c;
			fflush(stdin);	
		
		    while(!gameEnded && tries <=6)
			{
	//		while(tries <= 5){
			   	do
				   {
				   	cout << "\n\t\t\t\t\tEnter a guess letter: ";
                    cin >> guess;
            
                     if(!isalpha(guess)){
            	       cout << "\n\t\t\t\t\tInvalid input as " << guess << " isn't a letter" << endl;
            	       cout << "\n\t\t\t\t\tPress any key to guess further...";
				       getch();
				       system("cls");
				       cout << "\n\n\n\n\n";
			         }
                   }
				while (!isalpha(guess));
	
		    	guess = tolower(guess);
						
				if (isAlreadyGuessed(guess))
				{
					cout << "\n\t\t\t\t\tLetter is already guessed. Guess another letter." << endl;
					cout << "\n\t\t\t\t\tPress any key to guess further...";
				    getch();
				    system("cls");
				    cout << "\n\n\n\n\n";
				
					continue;
				}
				if (isCorrectGuess(guess))
				{
					cout << endl;
					cout << "\n\t\t\t\t\tYou guessed the correct word!";
				//	cout << "end: " << gameEnded;
					// Guess letter is correct (Exists in the secret word
				}
				else // Does not exist in secret word
				{
					// Add in WRONG GUESSES
					wrongLetter.push_back(guess);
					cout << "\n\t\t\t\t\tWrong Letters: " << wrongLetter;
					tries++;
					drawHangman(tries);
				}
				cout << "\n\t\t\t\t\t";
				printBlanks();
				cout << "\n\t\t\t\t\tPress any key to guess further...";
				getch();
				system("cls");
				cout << "\n\n\n\n\n";
				
		
				if (gameEnded && tries < 6)
				{
					cout << "\n\n\n\n\n";
					cout << "\n\t\t\t\t\t\tCONGRATULATIONS! YOU WON!!!\n\t\t\t\t\t\t\tGAME OVER!\n\n\n";
					cout << "\n\t\t\t\t\tPress any key to continue...";
					getch();
					system("cls");
					break;
				}
		    	else if (gameEnded && tries >5)
				{
		//			drawHangman(7);
					cout << "\n\n\n\n\n";
					cout << "\n\t\t\t\t\t\tYOU LOST!!!\n\t\t\t\t\t\t\tGAME OVER!\n\n\n";
					cout << "\n\t\t\t\t\tPress any key to continue...";
					getch();
					system("cls");
				}
			}
        }
		
        
		void printBlanks(void);

	   	
		void drawHangman(int t){
			cout<<endl<<endl;

			switch(tries)
			{
			case 1:
			{
			   cout <<"\t\t\t\t\t____________  " << endl;
			   cout <<"\t\t\t\t\t|       }     " << endl;
			   cout <<"\t\t\t\t\t|       o     " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;	
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|____________ " << endl;
				break;
			}

			case 2:
			{
		       cout <<"\t\t\t\t\t____________  " << endl;
			   cout <<"\t\t\t\t\t|       }     " << endl;
			   cout <<"\t\t\t\t\t|       o     " << endl;
			   cout <<"\t\t\t\t\t|       |     " << endl;
			   cout <<"\t\t\t\t\t|       |     " << endl;
			   cout <<"\t\t\t\t\t|       |     " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;	
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|____________ " << endl;
				
				break;	
			}
			case 3:
			{
			   cout <<"\t\t\t\t\t____________  " << endl;
			   cout <<"\t\t\t\t\t|       }     " << endl;
			   cout <<"\t\t\t\t\t|       o     " << endl;
			   cout <<"\t\t\t\t\t|       |     " << endl;
			   cout <<"\t\t\t\t\t|     / |     " << endl;
			   cout <<"\t\t\t\t\t|    /  |     " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;	
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|____________ " << endl;
				
				break;	
			}
			case 4:
			{
			   cout <<"\t\t\t\t\t____________  " << endl;
			   cout <<"\t\t\t\t\t|       }     " << endl;
			   cout <<"\t\t\t\t\t|       o     " << endl;
			   cout <<"\t\t\t\t\t|       |     " << endl;
			   cout <<"\t\t\t\t\t|     / | \\  " << endl;
			   cout <<"\t\t\t\t\t|    /  |  \\ " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|             " << endl;	
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|____________ " << endl;
				
				break;	
			}
			case 5:
			{
			   cout <<"\t\t\t\t\t____________  " << endl;
			   cout <<"\t\t\t\t\t|       }     " << endl;
			   cout <<"\t\t\t\t\t|       o     " << endl;
			   cout <<"\t\t\t\t\t|       |     " << endl;
			   cout <<"\t\t\t\t\t|     / | \\  " << endl;
			   cout <<"\t\t\t\t\t|    /  |  \\ " << endl;
			   cout <<"\t\t\t\t\t|      /      " << endl;
			   cout <<"\t\t\t\t\t|     /       " << endl;	
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|____________ " << endl;
				
				break;	
			}
			case 6:
			{
			   cout <<"\t\t\t\t\t____________  " << endl;
			   cout <<"\t\t\t\t\t|       }     " << endl;
			   cout <<"\t\t\t\t\t|       o     " << endl;
			   cout <<"\t\t\t\t\t|       |     " << endl;
			   cout <<"\t\t\t\t\t|     / | \\  " << endl;
			   cout <<"\t\t\t\t\t|    /  |  \\ " << endl;
			   cout <<"\t\t\t\t\t|      / \\   " << endl;
			   cout <<"\t\t\t\t\t|     /   \\  " << endl;	
			   cout <<"\t\t\t\t\t|             " << endl;
			   cout <<"\t\t\t\t\t|____________ " << endl;
				
				break;	
			}
			case 7:
	         cout << "\n\n\n\n\n";
			 cout << "\n\t\t\t\t\t\tYOU LOST!!!\n\t\t\t\t\t\t\tGAME OVER!\n\n\n";
			 cout << "\n\t\t\t\t\tThe word was: " << secretWord;
			 cout << "\n\t\t\t\t\tPress any key to continue...";
			 getch();
			 system("cls");	
			 break;
			}
			
	}

};

	void Hangman::printBlanks(){		
        	int i;
        	cout << "\n\t\t\t\t\t\t";
        	for(i=0; secretWord[i] !='\0'; i++){
        		// Check if the letter is guessed, print letter
        		if(isAlreadyGuessed(secretWord[i]))
        		{
        			cout << secretWord[i];
				}
				else
					cout << blank[i] << " ";
        		// Else print _
        		
			}
			cout << endl;
		}

int message()
{
	int i, j;
	
	for(i=1;i<=3;i++)
    {
    	for(j=1; j<=120; j++)
        {
        	if(i==2 && j==2)
            {
            	cout << "\n\t\t\t\t\t\t HANGMAN GAME  ";
                continue;
            }
            
            else if(i==2 && j>=2 || i == 2 && j<=2)
            cout << "  ";
   
            else
            cout << "*";

        }
        cout << "\n";
    }
}

void gotoxy(int x , int y){
	COORD coord; // coordinate system (x, y axis)
    
	coord.X=x;      
    coord.Y=y;
    
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void animation()
{
	int r,q;
    char c = 219; //ASCII code for a block type of character

    message();
    gotoxy(40,18);

    cout<<"STARTING GAME...";

    gotoxy(40,20);
	
	 for(r=1;r<=10;r++)
     {
     	for (q=0 ; q<=1; q++)
        {
        	cout<<c;
            usleep(95000); //slows loop
        }
    }

}

int main(){
	system("Color 80");
	animation();
	cout << endl;
	//clrscr();
	system("cls");
	
	cout << "\n\n\n\n";
	//message();
    Hangman h(0);
    
	int choice;
	char s[20];

	do
    {
    	cout << "\t\t\t\t HELLO, THIS IS BISMAH AND FATIMA! WELCOME TO OUR GAME HANGMAN!!!" << endl;
        cout << "\n\n\t\t\t\t\t\t\tINSTRUCTIONS" << endl;
        cout << "\n\n\t\t 1.This game has options whether you want to play 1 player or 2 players game." << endl;
        cout << "\n\n\t\t 2.The computer generates a word for the single player while the 2 player game option lets the \n\t\t  one of the player decide the word for the other player." << endl;
        cout << "\n\n\t\t 3.The player then starts guessing letter. If the letter appears in the word then the computer puts \n\t\t  the letter in its proper location. If not then the computer adds one more body part to the hangman." << endl;
        cout << "\n\n\t\t 4.If the entire body is completed then the player loses. If the player guesses the word before the \n\t\t  body is completed then the player wins." << endl;
        cout << "\n\n\t\t 5.You can not guess any letter more than once." << endl;
        cout << "\n\n\n\t\t\t\t\tPress any key to continue";
        getch();
	    system("cls");
	    
	    cout << "\n\n\n\t\t\t\t\tOptions:";
        cout << "\n\t\t\t\t 1. 1 Player Game";
		cout << "\n\t\t\t\t 2. 2 Player Game";
        cout << "\n\t\t\t\t 3. Reset Game";
		cout << "\n\t\t\t\t 4. End Game" << endl;
        cout << "\n\t\t\t\t Enter your choice here: ";
        cin  >> choice; 
    //	cout << "Continue playing. GOOD LUCK!" << endl;
        cout << "\n\t\t\t\t\tPress any key to continue...";
		getch();
		system("cls");	
		
		cout << "\n\n\n";
        switch(choice)
        {
        case 1:
        	h.file(); 
        	
        	do{       
	            if(h.check(h.word)){
	            	h.setWord(h.word);
					h.length(h.word);
	            }
	        }
	        while(!h.check(h.word));
	        
	        h.getWord();
			h.setBlanks();
			cout << "\n\t\t\t\t\t\t";
			h.guessed();
		//	main();
            break;
            
        case 2:
		{
			do{
					int i;
					char temp;
					
					cout << "\n\t\t\t\t\tEnter a word: ";
					fflush(stdin);
					
					while(1){
						fflush(stdin);
						temp = getch();
						if(temp == 13) //ASCII CODE of enter
						break;
						
						else{
							s[i] = temp;
							cout << "*";
							i++;
						}
					}

	            if(h.check(s)){
	            	h.setWord(s);
					h.length(s);
	            }
	        }
	        while(!h.check(s));
	        
			    h.getWord();
			    cout << "\n\t\t\t\t\t\t";
		    	h.setBlanks();
		    	cout << "\n";
			    h.guessed();
			//    main();
	        break;
	}	
	    case 3:
				main();
				break;
	  
      
        case 4:
 			 cout << "\n\t\t\t\t\t\t\t\tTHE END\n";	
			 break;
			 
        default:
            printf("\n\t\t\t\t\t\t\tINVALID INPUT");
	}
	
}
 while(choice!=0);
}   
