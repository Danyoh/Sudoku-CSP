#include "sudoku.h"
using namespace std;

class sudoku {
    public:
        int domain[9*9];

    sudoku(int* board) {
        int c = 1;
    }

};

int main(int argc, char const *argv[]) {
    ifstream file;
    string fileName;
    int grid[9][9];
    cout << "Please input the puzzle text file name: " << endl;
    cin >> fileName;
    file.open(fileName);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            file >> grid[i][j];
        }
    }
    file.close();
    cout << "Complete." << endl;
    
    return 0;
}
