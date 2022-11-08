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
    bool backtrack(sudoku s){
        /* Backtrack algorithm
        Look at the variables and their domains
        Go through all possible values one at a time.
        If you reach an assignment of values that breaks the constraints, backtrack.
        Backtrack to the last assignment and try the next value.
        We start with a partial assignment of values to variables.
        */

        string var = unassignedVariable(s);

        return false;    
    }
    string unassignedVariable(sudoku s){
        /*
        Used to pick the unassigned variable with the
        fewest values in its domain.
        */
        //assigned is a global variables, will use this
        vector<string> pickedVariable;
        //look for unassigned value with fewest
        //check if the coordinates(i,j) are mapped to its domain
        //look for the value with the minimum domain  
        for (int i=0;i<9;i++){
            for (int j=0;j<9;j++){
                if (assigned.find(to_string(i)+to_string(j))==assigned.end()) //checks if not in the list
                    pickedVariable.push_back(to_string(i)+to_string(j)); //push the(coordinates?) variable onto the list
                //if the variable in sudoku is not already assigned
                //add it to the unassigned list,
                //next we need to find the minimum variable, which is what we will return 
            }
        };
        //sort the pickedVariable list now
        string minVarCoord = pickedVariable[0];
        for (int i=1;i<pickedVariable.size();i++){
            if (s.domain[pickedVariable[i]].size()<minVarCoord.size())
                minVarCoord=pickedVariable[i];
        }
        return minVarCoord;

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