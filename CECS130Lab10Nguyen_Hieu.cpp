#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <ctype.h> // this library was included to enable the use of isdigit()
// which checks if a char is a digit or not. Although it could have been done with
// only the standard libs, utulizing this lib makes the code more readable and descriptive
// However, some could say that wouldn't be an issue with coding it manually and using
// comment to decribe what it does. Is this acceptable for this lab?

//CECS 130 Lab 10
//Hieu Nguyen
// Tic-Tac-Toe Game
using namespace std;

//Defining Class
// the Player class is a sub-class of the Board class
class Player{
	//Private members
	char* name;
	int score, wins;
	public:
	Player(){ // initializing member variables to empty string or 0;
		this->wins = 0;
		this->name = "";
		this->score = 0;
	}
	Player(char name[10]){// if the constructor is provided a string
		this->wins = 0;
		this->score = 0;
		this->name = name;
	}
	char* getName(){
		return this->name;
	}
	void updateScore(){
		this->score++;// increasing score by one
	}
	void printScore(){
		cout<< this->score<< endl;
	}	
	int getScore(){
		return this->score;
	}
	void resetScore(){
		this->score = 0;
	}
	void updateWin(){
		this->wins++; 
	}
	void displayWins(){
		cout << this->wins<< endl;
	}
	
};
class Board: public Player{
	char cells[3][3];
	public:
		Board(){  // constructor initializes the cells.
			char temp[9] = { '1','2','3','4','5','6','7','8','9' };
			int i, k, j = 0;
			for (i = 0; i < 3; i++) {
				for (k = 0; k < 3; k++) {
					cells[i][k] = temp[j];
					j++;
				}
			}
		}
		char getCell(int i, int k){// getting the content of the cell
			return this->cells[i][k];
		}
		// member function prototypes(to be defined explicitly)
		void displayBoard();
		int findCellAndUpdate(char userInput, int boardChoice);
		bool randomCell();
		bool checkGameStatus();
		void resetBoard();
		void checkDiagonal( Player players[2]);	
};

//Main Function prototypes
void displayBoard(Board boards[3]);
bool findCell(char userInput, char cells[3][3]);
void updateCell(char userInput,  char cells[3][3]);
bool checkGameStatus(Board boards[3]);
void updateScore(Board boards[3], Player players[2]);
void resetGame(Board boards[3], Player players[3]);
void displayScore(Player players[2]);
void findWinner(Player players[2]);
void checkColumn(Board boards[3], Player players[2]);
void checkHorizontal(Board boards[3], Player players[2]);
void checkVertical(Board boards[3], Player players[2]);
		

// Main program
int main(){
	//set up
	srand(time(NULL));
	Board boards[3]; 
	char userInput;
	char name[10];
	int boardChoice;
	int currentPlayer = rand()%2;
	Player players[2]; // player[0] is the computer and player[1] is the use
	bool gameOver = false;
	int exitOrReset = 1;
	cout<< "Welcome to Tic-Tac-Toe"<< endl;
	cout<< "Enter your Name: ";
	cin>> name;
	Player temp(name);
	players[1] =  temp;
	

//Game Loop:
while(exitOrReset){ // true is associated with reset and false is associated with exit
		if(currentPlayer){ 
		// if the current player is 1(user)
		cout<< "You get to go first"<< endl;
		//if the current player is 0(computer)
		}else cout<< "the computer will go first"<< endl;
		
		//Loop for one Round
		while(!gameOver){
		//Code to be executed while the game is NOT over.
			if(currentPlayer){
				// code to be executed during the user's turn
				displayBoard(boards);
				cout<< "it's your turn"<< endl;
				cin>>boardChoice>> userInput;
				if(boards[boardChoice].findCellAndUpdate(userInput, boardChoice)){
					// if cell updated successfully
					currentPlayer = 0;
				}
				else currentPlayer = 1; // if cell update failed, the currentPlayer will remain the user
			 // until the cell is updated successfully
			 		
				
			}
			else{// code to be executed during the computer's turn
				boardChoice = rand()%3;
				while(!boards[boardChoice].randomCell()){// while updating a random cell is unsuccessful.
				 	boardChoice = rand()%3;
				}
			currentPlayer = 1;
			}
	
		//Checking Game status
		 	if(checkGameStatus(boards)){
				//code to be executed if there is no cell left.
		 		gameOver = true;	// exit the loop for the round
		 	}
		 	
		}
	//code to be executed when the game is over
	displayBoard(boards);
	cout<<"the round is over"<<endl;
	
	// Getting results
	updateScore(boards, players);// finding the number of TTT's for the user and the computer
	displayScore(players);
	findWinner(players); // checking which player has more TTT's
	cout<< "Computer's wins: ";
	players[0].displayWins();
	cout<<players[1].getName()<< "'s wins: "; 
	players[1].displayWins();
	
	// asking the user if they want to reset or exit the game
	cout << "Type (0) to Exit or (1) to Reset"<< endl;
	cin>> exitOrReset;
	if(exitOrReset){
	// code to be executed if the user enter 1(reset the game)
		resetGame(boards, players);
		gameOver = false;// starting the loop again
		currentPlayer = rand()%2; // randomly selecting who goes first again.
   }
}
//Program Exit
	return 0;
}

// displaying the board
void displayBoard(Board boards[3]){
		int i;
		char* boardLabels[3]= {"Top", "Middle", "Bottom"};
		for(i = 0; i < 3; i++){
			cout<< boardLabels[i]<<" board # " << i<< endl;
			boards[i].displayBoard();	
			cout<< endl;
		}
	cout<< "Enter a Board Number-a space - A Cell Number"<< endl;
}
void Board::displayBoard(){
	int i,k;
	for(i = 0 ; i < 3; i++){
		for(k= 0; k<3;k++){
			cout<<this->cells[i][k]<<"  |  ";
		}
		cout<<endl;
		cout<<endl;
	}
}		

// check if the cell is occupied or not
bool findCell(char userInput, char cells[3][3]){
	int i, k;
	bool takenOrNot=true;
	for(i = 0; i < 3; i++){
		for(k = 0 ; k <3; k++){
			if(userInput == cells[i][k]) takenOrNot = false;	
		}	
	}
	return takenOrNot; 
}
// picking a random cell for the computer
bool Board::randomCell(){
	bool successOrFail= true;
	int loop;
	int	i=rand()%3;
	int k= rand()%3;  
	
	while(!isdigit(this->cells[i][k])){
		i = rand()%3;
		k = rand()%3;
		loop++;
		if(loop>50){ /*to prevent an ifinite loop from occurring when all of the cells are occupied, 
		the condtions if the loop is run more than 50 times(arbitary value could be higher for better accuracy,
		 but might take longer)
		*/ 
			successOrFail = false;
			break;
		}
	}
	if(successOrFail) this->cells[i][k] = 'o';	
	return successOrFail;
}
// updating the cell
void updateCell(char userInput,  char cells[3][3]){
	int i, k;
	for(i = 0; i < 3; i++){
		for(k = 0 ; k <3; k++){
			if(userInput == cells[i][k]) {
				// code to be executed if the cell is available 
				//and the current player is 1 (User)
				cells[i][k] = 'x';	
			}	
		}	
	}
}
// calls both the findCell and updateCell for the specified board choice
int Board::findCellAndUpdate(char userInput, int boardChoice){
	int successOrFail;
		if(findCell(userInput,this->cells)){
			cout<< "the cell is not available"<< endl;
			successOrFail = 0;
		}else{
			updateCell(userInput, this->cells);
			successOrFail = 1;
		}
	return successOrFail;
}
// checks the game status, it returns false if the game is not over and true if the game is over
bool Board::checkGameStatus(){
	bool gameOver = true;
	int i , k;
	for(i = 0; i< 3; i++){
		for(k = 0; k < 3; k++){
			if(isdigit(this->cells[i][k])){
				gameOver = false;
				break;	
			}
		}
	}
	return gameOver;
}
bool checkGameStatus(Board boards[3]){
	bool gameOver = true;
	int i;
	for(i = 0; i <3 ; i++){
		if(!boards[i].checkGameStatus()){
			gameOver = false;
			break;
		}
	}
	return gameOver;
}
// finding TTT's horizontally
void checkHorizontal(Board boards[3], Player players[2]){
	int i,k=0;
	while(k<3){
		for(i = 0 ; i < 3; i++){
			if(boards[k].getCell(i,0)== boards[k].getCell(i,1)&& boards[k].getCell(i,0)==boards[k].getCell(i,2)){
				if(boards[k].getCell(i,0)=='x') players[1].updateScore();
				else players[0].updateScore();	
			}
		}
		k++;
	}
		
}
// finding TTT's vertically
void checkVertical(Board boards[3], Player players[2]){
	int k,i=0;
	while(i<3){
		for(k = 0; k< 3; k++){
			if(boards[i].getCell(0,k)==boards[i].getCell(1,k)&& boards[i].getCell(0,k)== boards[i].getCell(2,k)){
				if(boards[i].getCell(0,k)== 'x') players[1].updateScore();
				else players[0].updateScore();
			}
		}
		i++;
	}
	
}
// finding TTT's diagonally
void Board:: checkDiagonal(Player players[2]){
	
	if(this->cells[0][0] == this->cells[1][1]&& this->cells[0][0] == this->cells[2][2] ){
		if(this->cells[0][0]== 'x' || this->cells[0][2] == 'x' ){
			players[1].updateScore();
		}
		else if(this->cells[0][0] == 'o' || this->cells[0][2] == 'o'){
			players[0].updateScore();
		}
	}
	
	else if(this->cells[0][2] == this->cells[1][1]&& this->cells[0][2] == this->cells[2][0]){
			
		if(this->cells[0][0]== 'x' || this->cells[0][2] == 'x' ){
			players[1].updateScore();
		}
		else if(this->cells[0][0] == 'o' || this->cells[0][2] == 'o'){
			players[0].updateScore();
		}
	}
}
// checking the vertical columns and diagonal columns
void checkColumn(Board boards[3], Player players[2]){
	int i,k;
	for(i = 0 ; i <3; i ++){
		for(k = 0 ; k < 3; k++){
			if(boards[0].getCell(i, k)== boards[1].getCell(i,k)&& boards[0].getCell(i, k)== boards[2].getCell(i,k)){
				if(boards[0].getCell(i,k)=='x') players[1].updateScore();
				else players[0].updateScore();
			}
		}
		
	}
	if(boards[0].getCell(0,0) == boards[1].getCell(1,1)&& boards[0].getCell(0,0)== boards[2].getCell(2,2)){
		if(boards[0].getCell(0,0)=='x') players[1].updateScore();
		else players[0].updateScore();
	}
	else if(boards[0].getCell(0,2) == boards[1].getCell(1,1)&& boards[0].getCell(0,2)== boards[2].getCell(2,0)){
		if(boards[0].getCell(0,2)=='x') players[1].updateScore();
		else players[0].updateScore();
	}
	
}
// Updating the number of TTT's to the player's instances.
void updateScore(Board boards[3], Player players[2]){
	int m;	
	//checking horizontally
		checkHorizontal(boards,players);
		
	// check vertically
		checkVertical(boards, players);
		
	// checking diagonally
		for(m= 0; m< 3; m++){
			boards[m].checkDiagonal(players);
		}
	// checking column
	checkColumn(boards, players);
	
}

// displaying the number of TTT's for the players
void displayScore(Player players[2]){
	cout<< "Computer: ";
	players[0].printScore();
	cout<< players[1].getName()<<": ";
	players[1].printScore();
}
// determine if there was a winner or a draw
void findWinner(Player players[2]){
	if(players[0].getScore()>players[1].getScore()){
		cout<< "the computer won!"<< endl;
		players[0].updateWin();
	}
	else if(players[0].getScore()<players[1].getScore()){
		cout<< "the user won!"<< endl;
		players[1].updateWin();
	}
	else{
		cout << "draw" << endl;
	}
}
// reset the game
void resetGame(Board boards[3], Player players[3]){
	int n;
	while(n<3){
		boards[n].resetBoard();
		players[n].resetScore();
		n++;
	}	
}
// setting each cell back to the orignal elements.
void Board:: resetBoard(){
	char temp[9] = { '1','2','3','4','5','6','7','8','9' };
		int i, k, j = 0;
		for (i = 0; i < 3; i++) {
			for (k = 0; k < 3; k++) {
				this->cells[i][k] = temp[j];
				j++;
			}
		}
}

