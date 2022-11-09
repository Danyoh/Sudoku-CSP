#include <algorithm>
#include <sudoku.cpp>
#include <vector>

class ac3 {
private:
        unordered_map<string, vector<string>> assignedValues;
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
    vector<int> minConstraints(string var, sudoku s) {
        /*
        Chose the coordinate of the value with the fewest constraints.
        */
        if (s.domain[var].size() == 1) // if there is only one value in the domain, return it
            return s.domain[var];

        vector<int> minDomain;
        // if there are more than one value in the domain, find the value with the fewest constraints
        // sort the values in the domain of the variable by the number of constraints they have
        // return the domain with the fewest constraints
        // put all values in minDomain
        for (int i = 0; i < s.domain[var].size(); i++) {
            minDomain.push_back(s.domain[var][i]);
        }
        // sort the values in minDomain by the number of constraints they have
        sort(minDomain.begin(), minDomain.end(), countConstraints(var, s));

        return minDomain;
    }
    int countConstraints(string var, sudoku s) {
        /*
        Count the number of constraints for a given value.
        */
        int count = 0;
        // s.neighbours[var] is a vector of strings representing the coordinates of the neighbours of var
        for (string neighbour : s.neighbours[var]) {
            if (s.domain[neighbour].size() > 1 && s.domain.find(var) != s.domain.end()) // if the neighbour has more than one value in its domain, it is a constraint
                count++;
        }
        return count;
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

    bool consistent(string coord, int value) {
        bool consist = true;
        for (auto x: assignments) {
            if (assignments[x.first] == value) {
                if (assignments.find(x.first)!=assignments.end()) {
                    consist = false;
                }
            }
        }
        return consist;
    }

    void addAssigned(sudoku s, string coord, int value){
        assignments[coord]=value;

        for (string neighbour: s.neighbours[coord]){
            if (assignments.find(neighbour)==assignments.end()){
                for (int i=0;i<s.domain[neighbour].size();i++){
                    if (value == s.domain[neighbour][i]) {
                        s.domain[neighbour].erase(s.domain[neighbour].begin()+i);
                        vector<string> temp = {neighbour,coord};
                        assignedValues[coord]=temp;
                        break;
                    }
                }
            }
        }
    }

    void removeAssigned(){
        
    }

    bool isSolved(sudoku s) {
        // go through the domain and see if the domain at that value is empty
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (s.domain[to_string(i) + to_string(j)].size() == 0)
                    return false;
            }
        }
        return true;
    }
};