#include <iostream>
#include <fstream>

using namespace std;

class sudoku {
    public:
        int variables[9][9];
        int domain[81][8]; //9*9
        int row[9][9];
        int column[9][9];
        int box[9][9];
        int arcC[9][9];

    sudoku() {
        initialState();
    }

    void initialState(){
        int count=0, val=0;
        ifstream file("testing.txt");
        if (file.is_open()) { //this is to check if the file is open
            for (int i=0; i<9; i++) {
                for (int j=0; j<9; j++) {
                    file >> variables[i][j];
                    row[i][j] = variables[i][j];
                }
            }
        }
        
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                column[i][j] = variables[j][i];
            }
        }
        return;
    }
    

};

int main(int argc, char const *argv[]) {
    sudoku s;
    for (int i=0; i<9; i++){
        cout << s.row[2][i] << " ";
    }
    return 0;
}
