#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class sudoku {
    public:
        int variables[9][9];
        int domain[81][8]; //9*9
        //int row[9][9];
        //int column[9][9];
        std::vector<vector<int>> row;
        std::vector<vector<int>> col;
        int box[9][9];
        int arcC[9][9];

    sudoku() {
        initialState();
    }

    void initialState(){
        int count=0, val=0;
        ifstream file("testing.txt");
        if (file.is_open()) { //this is to check if the file is open
            std::vector<int> rowList;// = new std::vector<int>();
            for (int i=0; i<9; i++) {
                for (int j=0; j<9; j++) {
                    file >> variables[i][j];
                    rowList.push_back(variables[i][j]);

                }
            row.push_back(rowList);
            rowList.clear();
            }
        }
        std::vector<int> colList;
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                colList.push_back(variables[j][i]);
            }
            col.push_back(colList);
            colList.clear();
        }
        return;
    }
    

};

int main(int argc, char const *argv[]) {
    sudoku s;
    //for (int i=0; i<9; i++){
     //   cout << s.row[2][i] << " ";
    //}
    //print the first row
    for (int i=0; i<9; i++){
        cout << s.row[0][i] << " ";
    }
    cout << endl;
    return 0;
}
