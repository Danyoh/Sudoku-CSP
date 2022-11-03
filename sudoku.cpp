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
        vector<vector<int>> row;
        vector<vector<int>> col;
        int box[9][9];
        int arcC[9][9];

    sudoku() {
        initialState();
    }

    void initialState(){
        int count=0, val=0;
        ifstream file("testing.txt");
        if (file.is_open()) { //this is to check if the file is open
            vector<int> rowList;// = new std::vector<int>();
            for (int i=0; i<9; i++) {
                for (int j=0; j<9; j++) {
                    file >> variables[i][j];
                    if (variables[i][j] !=0)
                        rowList.push_back(variables[i][j]);

                }
                row.push_back(rowList);
                rowList.clear();
            }
        }
        vector<int> colList;
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                if (variables[j][i] !=0)
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
    //TESTING:
    //print columns
    cout<<"PRINT COLUMNS: \n";
    for (int i=0; i<9; i++){
        for(int j=0;j<s.col[i].size();j++){
            cout << s.col[i][j] << " ";
        }
        cout << endl;
    }
    cout<<"PRINT ROWS: \n";
    //print rows
    for (int i=0; i<9; i++){
        for(int j=0;j<s.row[i].size();j++){
            cout << s.row[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}
