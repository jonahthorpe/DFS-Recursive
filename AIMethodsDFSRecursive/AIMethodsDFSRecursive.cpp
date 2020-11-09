// aimethods.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <stack>
#include <chrono>

using namespace std;

enum Move {
	North,
	East,
	South,
	West,
	Null
};

class EightPuzzle {

public:

	string state1 = "";
	unordered_set<string> visitedStates;
	string vs = "";

	void getStartStates(void) {
		setupState();
		for (int i = 0; i < 9; i++)
		{
			if (i % 3 == 0) {
				cout << "\n";
			}
			cout << state1[i];
			cout << " ";

		}
		cout << "\n";
		visitedStates.insert(state1);
	}

	void generateStates(string startState) {
		string newState;

		vector<Move> validMoves = getValidMoves(startState);
		for (Move move : validMoves) {
			newState = makeMove(move, startState);
			if (visitedStates.find(newState) == visitedStates.end()) {
				visitedStates.insert(newState);
				vs.append(newState);
				vs.append("\n");
				generateStates(newState);
			}
		}
	}
	void generateStatesIt(string startState) {
		stack <string> path;
		path.push(startState);
		while (!path.empty()) {
			string currentState = path.top();
			path.pop();
			vector<Move> validMoves = getValidMoves(currentState);
			for (Move move : validMoves) {
				string newState = makeMove(move, currentState);
				if (visitedStates.find(newState) == visitedStates.end()) {
					visitedStates.insert(newState);
					path.push(newState);
				}
			}
		}
	}


private:

	void getTileMessage(int tile, string boardTiles) {
		cout << "Available tiles: ";
		cout << boardTiles;
		cout << "\nWhat tile would you like at ";
		cout << tile % 3;
		cout << ", ";
		cout << tile / 3;
		cout << "\n";
	}


	void setupState() {
		string boardTiles = "abcdefgh_";
		int tile = 0;
		string input = "";
		while (boardTiles.length() != 0) {
			getTileMessage(tile, boardTiles);
			cin >> input;
			if (input == "empty") {
				input = "_";
			}
			if (input.length() == 1 and boardTiles.find(input) != string::npos) {
				state1.append(input);

				boardTiles.erase(boardTiles.find(input), 1);
				tile++;
			}
			else {
				cout << "Choice not a valid tile, Please try again\n";
			}
		}
	}

vector <Move> getValidMoves(string currentState) {
		// get valid moves from current states
		vector<Move> validMoves;
		// get the posistion of the empty set
		int emptyTileIndex = currentState.find("_");
		switch (emptyTileIndex) {
			// top left
		case (0):
			validMoves = { East, South };
			break;
			// top middle
		case (1):
			validMoves = { East, South, West };
			break;
			//top right
		case (2):
			validMoves = { South, West };
			break;
			// middle left
		case (3):
			validMoves = { North, East, South };
			break;
			// middle middle
		case (4):
			validMoves = { North, East, South, West };
			break;
			//middle right
		case (5):
			validMoves = { North, South, West };
			break;
			// bottom left
		case (6):
			validMoves = { North, East };
			break;
			// bottom middle
		case (7):
			validMoves = { North, East, West };
			break;
			// bottom right
		case (8):
			validMoves = { North, West };
			break;
		}
		return validMoves;
	}

	string makeMove(Move move, string currentState) {
		int emptyTileIndex = currentState.find("_");
		int newEmptyTileIndex;
		// get position of empty tile after move
		switch (move) {
		case North:
			newEmptyTileIndex = emptyTileIndex - 3;
			break;
		case South:
			newEmptyTileIndex = emptyTileIndex + 3;
			break;
		case East:
			newEmptyTileIndex = emptyTileIndex + 1;
			break;
		case West:
			newEmptyTileIndex = emptyTileIndex - 1;
			break;

		}
		// get tile value of that position
		char tileValue = currentState[newEmptyTileIndex];
		currentState[emptyTileIndex] = tileValue;
		currentState.replace(newEmptyTileIndex, 1, "_");

		return currentState;
	}
};


int main()
{
	EightPuzzle puzzle1;
	cout << "State 1\n";
	puzzle1.getStartStates();
	cout << "Getting States.\n";
	auto t1 = std::chrono::high_resolution_clock::now();
	puzzle1.generateStates(puzzle1.state1);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * pow(10, -6);
	cout << duration;
	cout << "\n";

	bool answer = false;
	string input;
	while (!answer) {
		cout << "Do you want to ouput the states? (yes or no) \n";
		cin >> input;
		if (input == "yes") {
			answer = true;
			cout << puzzle1.vs;
			//for (string state : puzzle1.visitedStates) {
			//	cout << state << "\n";
			//}
		}
		else if (input == "no") {
			answer = true;
		}
		else {
			cout << "Not a valid input \n";
		}
	}


	EightPuzzle puzzle2;
	cout << "State 2\n";
	puzzle2.getStartStates();
	cout << "Getting States. May take upto a minute. \n";
	t1 = std::chrono::high_resolution_clock::now();
	puzzle2.generateStates(puzzle2.state1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * pow(10, -6);
	cout << duration;
	cout << "\n";

	answer = false;
	while (!answer) {
		cout << "Do you want to ouput the states? (yes or no) \n";
		cin >> input;
		if (input == "yes") {
			answer = true;
			cout << puzzle1.vs;
			//for (string state : puzzle1.visitedStates) {
			//	cout << state << "\n";
			//}
		}
		else if (input == "no") {
			answer = true;
		}
		else {
			cout << "Not a valid input \n";
		}
	}


	cout << "The size of R(S1) is ";
	cout << puzzle1.visitedStates.size();
	cout << "\n";
	cout << "The size of R(S2) is ";
	cout << puzzle2.visitedStates.size();
	cout << "\n";
	cout << "The size of R(S1)/R(S2) is ";
	if (puzzle1.visitedStates.find(puzzle2.state1) != puzzle1.visitedStates.end()) {
		cout << 0;
	}
	else {
		cout << puzzle1.visitedStates.size();
	}
	string end;
	cin >> end;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
