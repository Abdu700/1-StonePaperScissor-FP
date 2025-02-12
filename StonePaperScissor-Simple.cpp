#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

enum enChoices {Stone = 1, Paper = 2, Scissor = 3};

enum enWinner { Player = 1, Computer = 2, Tie = 3 };

struct stRoundInfo {

	int RoundNumber;
	enChoices PlayerChoice;
	enChoices ComputerChoice;
	enWinner RoundWinner;
	string WinnerName;
};

struct stGameResults {
	int GameRounds = 0, PlayerWins = 0, ComputerWins = 0, DrawTimes = 0;
	enWinner FinalWinner;

};

string Tabs(short NumberOfTabs) {
	string tab = "";
	for (short i = 1; i <= NumberOfTabs; i++)
		tab += "\t";
	return tab;

}

int ReadNumberInRange(int From, int To, string Message) {
	int Number = 0;
	do {
		cout << Message;
		cin >> Number;
	} while (Number < From || Number > To);

	return Number;
}

int generateRandomNumber(int From, int To) {
	return rand() % (To - From + 1) + From;
}

short HowManyRounds() {
	int Rounds = 1;
	do {
		cout << "How Many Rounds 1 to 10 ?\n";
		cin >> Rounds;
		cout << endl;

	} while (Rounds < 1 || Rounds > 10);

	return Rounds;

}

enChoices ReadPlayerChoice() {

	int Choice = ReadNumberInRange(1, 3, "Your Choice: [1]: Stone, [2]: Paper, [3]Scissor ?");
	switch (Choice) {
	case 1:
		return enChoices::Stone;
	case 2:
		return  enChoices::Paper;
	default:
		return  enChoices::Scissor;

	}

}

enChoices GetComputerChoice() {
	int Choice = generateRandomNumber(1, 3);
	switch (Choice) {
	case 1:
		return enChoices::Stone;
	case 2:
		return  enChoices::Paper;
	default:
		return  enChoices::Scissor;

	}
} 

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice) {
		return enWinner::Tie;
	}
	else if 
		(  (RoundInfo.PlayerChoice == enChoices::Stone && RoundInfo.ComputerChoice == enChoices::Scissor)
		|| (RoundInfo.PlayerChoice == enChoices::Paper && RoundInfo.ComputerChoice == enChoices::Stone)
		|| (RoundInfo.PlayerChoice == enChoices::Scissor && RoundInfo.ComputerChoice == enChoices::Paper) )
		return enWinner::Player;
	else
		return enWinner::Computer;
}

void SetScreenColor(enWinner RoundWinner) {
	if (RoundWinner == enWinner::Computer)
		system("color 4f");
	else if (RoundWinner == enWinner::Player)
		system("color 2f");
	else
		system("color 6f");
}

string ChoiceName(enChoices Choice) {
	string arrChoiceNames[3] = { "Stone","Paper","Scissor" };
	return arrChoiceNames[Choice - 1];
}

string WinnerName(enWinner WinnerName) {
	string arrWinnerNames[3] = { "Player", "Computer", "No Winner" };
	return arrWinnerNames[WinnerName - 1];
}

void PrintRoundInfo(stRoundInfo RoundInfo) {
	cout << "_______________Round[" << RoundInfo.RoundNumber << "]__________________\n\n";
	cout << "Player   Choice:" << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice:" << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   :" << WinnerName(RoundInfo.RoundWinner) << endl;
	cout << "__________________________________________________________\n";
	SetScreenColor(RoundInfo.RoundWinner);

}

enWinner WhoWonTheGame(stGameResults Results) {
	if (Results.ComputerWins == Results.PlayerWins)
		return enWinner::Tie;
	else if (Results.ComputerWins > Results.PlayerWins)
		return enWinner::Computer;
	else
		return enWinner::Player;
}

stGameResults FillGameResults(short HowManyRounds, short PlayerWinsCounts, short ComputerWinsCount, short DrawTimesCount) {

	stGameResults GameResults;

	GameResults.ComputerWins = ComputerWinsCount;
	GameResults.PlayerWins = PlayerWinsCounts;
	GameResults.DrawTimes = DrawTimesCount;
	GameResults.GameRounds = HowManyRounds;
	GameResults.FinalWinner = WhoWonTheGame(GameResults);

	return GameResults;

}

stGameResults PlayGame(short HowManyRounds) {
	stRoundInfo RoundInfo;
	short PlayerWinCount = 0, ComputerWinCount = 0, DrawTimesCount = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {

		cout << "Round [" << GameRound << "] begins:\n\n";
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);


		if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinCount++;
		else if (RoundInfo.RoundWinner == enWinner::Player)
			PlayerWinCount++;
		else
			DrawTimesCount++;

		PrintRoundInfo(RoundInfo);

	}
	return FillGameResults(HowManyRounds, PlayerWinCount, ComputerWinCount, DrawTimesCount);
}

void PrintGameResults(stGameResults Results) {

	cout << Tabs(2) << "___________________________[ Game Results ]________________________\n\n";
	cout << Tabs(2) << "Game Rounds              :" << Results.GameRounds << endl;
	cout << Tabs(2) << "Player Won Times         :" << Results.PlayerWins << endl;
	cout << Tabs(2) << "Computer Won Times       :" << Results.ComputerWins << endl;
	cout << Tabs(2) << "Draw Times               :" << Results.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner             :" << WinnerName(Results.FinalWinner) << endl;
	cout << Tabs(2) << "____________________________________________________________________\n\n";
}

void GameOverScreen() {
	cout << Tabs(2) << "____________________________________________________________________\n\n";
	cout << Tabs(5) << "+++ G a m e  O v e r +++\n";
	cout << Tabs(2) << "____________________________________________________________________\n\n";
}

void ResetScreen() {
		system("cls");
		system("color 07");
}

void StartGame() {
	
	char PlayAgain = 'Y';

	do {
		ResetScreen();
		stGameResults GameResults = PlayGame(HowManyRounds());
		GameOverScreen();
		PrintGameResults(GameResults);
		cout << "Do You Want To Play Again ? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');

}



int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;

}

