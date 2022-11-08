#include <sudoku.cpp>
#include <vector>

class ac3 {
    public:
        unordered_map<string, int> assigned;
    // make a queue of constraints 
    ac3(sudoku& s){
        setAssigned(s);
    }

    void updateNeighbours(){
        /* Update row, col., box for the updated var. 
        */
    }

    void updateDomains(){
        /* Update domain for every var. in the same row, col., box
        */
    }

    void setAssigned(sudoku s){
        for (int i=0;i<9;++i){
            for (int j=0;j<9;++j){
                if (s.domain[to_string(i)+to_string(j)].size() == 1) 
                    assigned[to_string(i)+to_string(j)]=s.domain[to_string(i)+to_string(j)][0];
                
            }
        }
        return;
    }
};