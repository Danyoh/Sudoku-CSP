#include <sudoku.cpp>
#include <vector>

class ac3 {
    public:
        unordered_map<string, int> assignments;
    ac3(sudoku& s){
        setAssigned(s);
    }

    bool solve(){
        /*
        */
       
       // make a queue of constraints 

        return true;
    }

    bool revise(){
        //use in solve
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
                if (assignments.find(to_string(i)+to_string(j))==assignments.end()) //checks if not in the list
                    pickedVariable.push_back(to_string(i)+to_string(j)); //push the(coordinates?) variable onto the list
                //if the variable in sudoku is not already assigned
                //add it to the unassigned list,
                //next we need to find the minimum variable, which is what we will return 
            }
        }
        //sort the pickedVariable list now
        string minVarCoord = pickedVariable[0];
        for (int i=1;i<pickedVariable.size();i++){
            if (s.domain[pickedVariable[i]].size()<minVarCoord.size())
                minVarCoord=pickedVariable[i];
        }
        return minVarCoord;

    }    

    void setAssigned(sudoku s){
        /*
        Fills the hashmap assigned with the current variables that have a domain of 1 value,
        therefore, variables that are already set.
        hashmap contains the coordinate of the assigned value as a key (string) and the value itself as an int
        */
        for (int i=0;i<9;++i){
            for (int j=0;j<9;++j){
                if (s.domain[to_string(i)+to_string(j)].size() == 1)    //if domain == 1
                    assignments[to_string(i)+to_string(j)]=s.domain[to_string(i)+to_string(j)][0]; //add element in domain to assigned
                
            }
        }
        return;
    }

    int countConstraints(){

    }

    bool consistent(){
    }

    void addAssigned(){

    }

    void removeAssigned(){

    }

    bool isSolved(){


    }


};