#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

class sudoku {
    private:
        unordered_map<string,int> grid = {{"00",0},{"03",1},{"06",2},{"30",3},{"33",4},{"36",5},{"60",6},{"63",7},{"66",8}}; // map for box number
        vector<vector<string>> tempRows;
        vector<vector<string>> tempCols;
        vector<vector<string>> tempBoxes;
    public:
        int variables[9][9];
        unordered_map<string, vector<int>> domain;
        vector<vector<int>> row;
        vector<vector<int>> col;
        vector<vector<int>> box;
        unordered_map<string, vector<string>> neighbours;

    sudoku() {
        initialState();
        setDomain();
        buildNeighbour();
        grid.clear();
        tempBoxes.clear();
        tempRows.clear();
        tempCols.clear();
    }

    void initialState(){
        int count=0, val=0;
        ifstream file("input.txt");
        // fill variables and rows matrix
        if (file.is_open()) { 
            vector<int> rowList;
            for (int i=0; i<9; i++) {
                for (int j=0; j<9; j++) {
                    file >> variables[i][j];
                    if (variables[i][j] !=0) rowList.push_back(variables[i][j]);
                }
                row.push_back(rowList);
                rowList.clear();
            }
        }
        // fill columns matrix
        vector<int> colList;
        vector<string> colC;
        vector<string> rowC;
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++){
                if (!(i==0 && j==0)) colC.push_back(to_string(j)+to_string(i));
                rowC.push_back(to_string(i)+to_string(j));
                if (variables[j][i] !=0) colList.push_back(variables[j][i]);
            }
            tempCols.push_back(colC);
            tempRows.push_back(rowC);
            col.push_back(colList);
            colList.clear();
            colC.clear();
            rowC.clear();
        }
        // fill boxes matrix
        vector<int> boxList;
        vector<string> boxC;
        for (int y=0;y<=6;y+=3){
            for (int x=0;x<=6;x+=3){
                for (int i=0; i<3;i++){
                    for (int j=0;j<3;j++){
                        boxC.push_back(to_string(i+y)+to_string(j+x));
                        if(variables[y+i][x+j] != 0) boxList.push_back(variables[y+i][x+j]);

                    }
                }
                tempBoxes.push_back(boxC);
                box.push_back(boxList);
                boxList.clear();
                boxC.clear();
            }
        }
        return;
    }
    void setDomain(){ // set domain for each variable
        for (int i=0; i<9; i++) { 
            for (int j=0; j<9; j++) {
                if (variables[i][j] == 0){ // if variable is empty
                    vector<int> temp = {1,2,3,4,5,6,7,8,9};      //define inital domain
                    //remove elements from the domain if they appear in the same row
                    for (int val: row[i]){
                        for (int k=0;k<temp.size();++k){
                            if (val == temp[k]) {
                                temp.erase (temp.begin()+k);    //erase kth element from doamin
                                break;
                            }
                        }
                    }
                    //remove elements in the same column
                    for (int val: col[j]){
                        for (int k=0;k<temp.size();++k){
                            if (val == temp[k]) {
                                temp.erase (temp.begin()+k);
                                break;
                            }
                        }
                    }
                    //remove elements in the same box
                    string index=to_string(int(floor(i/3)*3))+to_string(int(floor(j/3)*3));
                    for (int val: box[grid[index]]){        // find correct box
                        for (int k=0;k<temp.size();++k){
                            if (val == temp[k]) {
                                temp.erase (temp.begin()+k);
                                break;
                            }
                        }
                    }
                    domain[to_string(i)+to_string(j)]=temp;
                    temp.clear();
                }else{
                    domain[to_string(i)+to_string(j)]=vector<int>{variables[i][j]};
                }
            }
        }
    }
    void buildNeighbour(){
        for (int i=0;i<9;i++){
            for (int j=0;j<9;j++){
                for (string coords: tempRows[i]){
                    neighbours[to_string(i)+to_string(j)].push_back(coords);
                }
                for(string coords: tempCols[j]){
                    neighbours[to_string(i)+to_string(j)].push_back(coords);
                }
                for(string coords: tempBoxes[j]){
                    bool flag=false;
                    for (string x: neighbours[to_string(i)+to_string(j)]){
                        if(coords.compare(x) == 0) {
                            flag = true;
                            break;
                        }
                    }
                    if (!flag) neighbours[to_string(i)+to_string(j)].push_back(coords);
                }
            }
        }
        
    }

};

void testing(sudoku s){
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

    cout<<"PRINT BOXES: \n";
    //print boxes
    for (int i=0; i<9; i++){
        for(int j=0;j<s.box[i].size();j++){
            cout << s.box[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout<<"PRINT DOMAINS: \n";
    for(auto x : s.domain){
        cout << x.first << " ";
        for (int val : x.second){
            cout<< val << " ";
        }
        cout << endl;
    }
    cout << "PRINT NEIGHBOURS:\n";
    for (auto x: s.neighbours){
        cout << x.first << " ";
        for (string val : x.second){
            cout<< val << " ";
        }
        cout << endl;
    }

    cout << endl; 

    return;
}

int main(int argc, char const *argv[]) {
    sudoku s;
    //TESTING:
    testing(s);
    return 0;
}
