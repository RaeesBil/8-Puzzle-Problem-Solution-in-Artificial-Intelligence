#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 3;
struct State {
    vector<vector<char>> puzzle;
    int cost_h2;  // Misplaced tiles heuristic
    int level;
    bool operator>(const State &other) const {
        return cost_h2 > other.cost_h2;
    }	};
pair<int, int> findGoalPosition(char value, const vector<vector<char>> &goal) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (goal[i][j] == value) {
                return {i, j};
            }	}	}	
		return {-1, -1};
}
// Calculation of Heuristic function (H2)
int misplacedTilesHeuristic(const vector<vector<char>> &current, const vector<vector<char>> &goal) {
    int misplacedTiles = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (current[i][j] != goal[i][j] && current[i][j] != '-') {
                misplacedTiles++;
            }	}	}
		return misplacedTiles;
}
bool isGoalState(const State &state, const vector<vector<char>> &goal) {
    return state.puzzle == goal;
}
void printMatrix(const vector<vector<char>> &matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << " ";
        }	cout << endl;
    }		cout << endl;
}
// Function to solve H2
void solvePuzzle(const vector<vector<char>> &initial, const vector<vector<char>> &goal) {
    priority_queue<State, vector<State>, greater<State>> pq;
    State initialState = {initial, misplacedTilesHeuristic(initial, goal), 0};
    pq.push(initialState);
    vector<State> path;
    int step = 0;

    // Step Limit & Priority Queue: pq
    const int maxSteps = 100;
    while (!pq.empty() && step < maxSteps) {
        State current = pq.top();
        pq.pop();
        path.push_back(current);
        cout << "Phase " << ++step << ":" << endl;
        cout << "Depth: " << current.level << " | H2 Cost : " << current.cost_h2 << endl;
        printMatrix(current.puzzle);

        if (isGoalState(current, goal)) {
            cout << "WooHoo, Goal State Reached; You did it Raees!" << endl;
            return;
        }
        int zeroI, zeroJ;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (current.puzzle[i][j] == 'e') {
                    zeroI = i;
                    zeroJ = j;
                    break;
                }	}	}	const vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        // Move the declaration outside the loop
        State nextState = current;
        for (const auto &move : moves) {
            int newI = zeroI + move.first;
            int newJ = zeroJ + move.second;

            if (newI >= 0 && newI < N && newJ >= 0 && newJ < N) {
                swap(nextState.puzzle[zeroI][zeroJ], nextState.puzzle[newI][newJ]);
                nextState.level = current.level + 1;
                nextState.cost_h2 = nextState.level + misplacedTilesHeuristic(nextState.puzzle, goal);
                pq.push(nextState);
            }	}	}
    cout << "Oops! Goal State Remains Unreached within the allocated Steps; Raise the Step limit" << endl;
}
// Declaration of Main Function
vector<vector<char>> getMatrixFromUser(const string &prompt);
int main() {
    vector<vector<char>> inputMatrix = getMatrixFromUser("Please Initialize the Input Matrix :");
    vector<vector<char>> goalMatrix = getMatrixFromUser("Please Initialize the Goal Matrix :");

    cout << "Input Matrix:" << endl;
    printMatrix(inputMatrix);
    cout << "Goal Matrix:" << endl;
    printMatrix(goalMatrix);
    solvePuzzle(inputMatrix, goalMatrix);
    return 0;
}
// Definition of Function
vector<vector<char>> getMatrixFromUser(const string &prompt) {
    cout << prompt << endl;
    vector<vector<char>> matrix(N, vector<char>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "Assign value to Position(" << i + 1 << ", " << j + 1 << "): ";
            cin >> matrix[i][j];
        }	}	return matrix;	}

