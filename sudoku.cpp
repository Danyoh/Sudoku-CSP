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

    }

    void initialState(){
        int count=0, val=0;
        ifstream file;
        string fileName;
        cout << "Please input the puzzle text file name: " << endl;
        //open the file and read the data
        cin >> fileName;
        file.open(fileName.c_str()); //c_str converts string to char array
        if (file.is_open()) { //this is to check if the file is open
            for (int i=0; i<9; i++) {
                for (int j=0; j<9; j++) {
                    file >> val;
                    variables[i][j] = val;
                }
            }
        }
        //put the row values into the row array
        //store the enumeration of the row, with the whole row as a list
        int rowList[9];
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                rowList[j] = variables[i][j];
            }
            for (int j=0; j<9; j++) {
                row[i][j] = rowList[j];
            }
        }
        
        for (int i=0; i<9; i++) {
            int colList[9];
            for (int j=0; j<9; j++) {
                colList[j] = variables[j][i];
            }
            for (int j=0; j<9; j++) {
                column[i][j] = colList[j];
            }
        }
        //print column 3
        for (int i=0; i<9; i++) {
            cout << column[2][i] << " ";
        }



        file.close();
        return;
    }
    

};

int main(int argc, char const *argv[]) {
    sudoku s;
    s.initialState();

    return 0;
}
