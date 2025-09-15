#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

//struct for positions by {row,col}
struct Pos { 
	int r, c; 
};

class Maze {
public:
	bool loadFromFile(const std::string& path) {
		std::ifstream fin(path);
		//check if file path exists
		if (!fin) {
			std::cerr << "Error: file path does not Exist. \n";
			return false;
		}
		//clear grid object for safety
		grid.clear();
		std::string line;

		while (std::getline(fin, line)) {
			grid.push_back(line);
		}
		//record max row and col size
		R = (int)grid.size();
		C = (int)grid[0].size();

		return true;
	}

	void print() const{
		//print maze by row
		for (const auto& row : grid) {
			std::cout << row << '\n';
		}
	}
	bool findEntrances() {
		std::vector<Pos> openings;

		//check for openings on left and right sides
		for (int c = 0; c < C; c++) {
			if (grid[0][c] == '0') {
				openings.push_back({ 0, c });
			}

			if (R > 1 && grid[R - 1][c] == '0') {
				openings.push_back({ R - 1, c });
			}
        }
		//check for openings on top or bottom sides
		for (int r = 1; r < R - 1; r++) {
			if (grid[r][0] == '0') {
				openings.push_back({ r, 0 });
			}
			if (C > 1 && grid[r][C - 1] == '0') {
				openings.push_back({ r, C - 1 });
			}
		}

		//record points if all is well
		start = openings[0];
		finish = openings[1];
		return true;
	}

	//safety check to see if we are within bounds
	bool inBounds(int r, int c) const { 
		return r >= 0 && r < R && c >= 0 && c < C; 
	}

	//search for and output available moves
	std::vector<Pos> neighbors(const Pos& p) const {
		//look up tables that contain difference needed for up, right, down, and left
		const int diffR[4] = { -1, 0, 1, 0 };
		const int diffC[4] = { 0, 1, 0, -1 };

		std::vector<Pos> moves;

		for (int i = 0; i < 4; i++) {
			int checkR = p.r + diffR[i];
			int checkC = p.c + diffC[i];
			if (inBounds(checkR, checkC) && grid[checkR][checkC] == '0') {
				moves.push_back({ checkR, checkC});
			}
		}

		return moves;
	}

	//backtracking algorithm solution
	bool solve(char markChar = ' ') {
		if (!findEntrances()) {
			return false;
		}

		//tracker for visited points utilizing just marked chars
		std::vector<std::vector<char>> visited(R, std::vector<char>(C, 0));

		//tracker for current path
		std::stack<Pos> search;
		search.push(start);
		visited[start.r][start.c] = 1;

		bool found = false;

		while (!search.empty()) {
			Pos curr = search.top();

			if (curr.r == finish.r && curr.c == finish.c) {
				found = true;
				break;
			}

			//check available neiboring paths and track advancement
			auto nbrs = neighbors(curr);
			bool advanced = false;

			for (const auto &n : nbrs) {
				if (!visited[n.r][n.c]) {
					visited[n.r][n.c] = 1;
					search.push(n);
					advanced = true;
					break;
				}
			}

			//if no movement occurs, start backtracking
			if (!advanced) {
				search.pop();
			}
		}

		//if no solution is found
		if (!found) {
			return false;
		}

		//if a path is found, mark it on the grid
		while (!search.empty()) {
			Pos p = search.top();
			search.pop();
			if (grid[p.r][p.c] == '0') {
				grid[p.r][p.c] = markChar;
			}
		}
		return true;
	}
private:
	std::vector<std::string> grid;
	int R = 0, C = 0;
	Pos start{ -1, -1 }, finish{-1, -1};
};

int main(int argc, char* argv[]) {
	Maze mz;

	if (!mz.loadFromFile(argv[1])) {
		return 1;
	}

	std::cout << "Echoing read file: \n";
	mz.print();

	std::cout << "Solving... \n";
	if (!mz.solve(' ')) {
		std::cout << "No solution possible\n";
		return 0;
	}
	
	mz.print(std::cout);
	return 0;
}