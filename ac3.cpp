#include <algorithm>
#include "sudoku.cpp"
#include <vector>
#include <queue>

class ac3
{
private:
    unordered_map<string, vector<vector<string>>> assignedValues;

public:
    unordered_map<string, int> assignments;
    ac3(sudoku &s)
    {
        setAssigned(s);
        cout << solve(s) <<endl;
        setAssigned(s);
    }

    bool solve(sudoku& s)
    {
        /*

        */
        queue<vector<string>> arcQ;
        for (vector<string> e : s.constraints)
            arcQ.push(e); // fill arcQ
        vector<string> arc;
        while (!arcQ.empty())
        {
            cout << arcQ.size() << endl;    //TESTING
            arc = arcQ.front();             //pop an arbitrary arc (Xi,Xj)
            arcQ.pop(); 
            if (revise(s, arc[0], arc[1]))  //make Xi arc-consistent w.r.t Xj
            {   //Di was changed
                if (s.domain[arc[0]].size() == 0) // if domain is empty, CSP has no solution
                    return false;
                for (auto neighbour : s.neighbours[arc[0]]) //Di was made smaller, add all arcs (Xk,Xi)
                {
                    if (neighbour != arc[1])
                    {
                        vector<string> temp{neighbour,arc[0]};
                        arcQ.push(temp);
                        temp.clear();
                    }
                }
            }
        }

        return true;
    }

    bool revise(sudoku& s, string x1, string x2)
    {
        bool revised = false;
        int size = s.domain[x1].size(),count=0;
        for (int x: s.domain[x1])
        {
            for (int y : s.domain[x2])
            {
                if (x == y)
                {
                    if(s.domain[x1].size()==1){
                        s.domain[x1].clear();
                    }else{
                    s.domain[x1].erase(s.domain[x1].begin() + count);
                    }
                    revised= true;
                    if((s.domain[x1].size() <= count) || (s.domain[x1].size()==0)) return revised;

                }
            }
            count++;
        }
        return revised;
    }
    string unassignedVariable(sudoku& s)
    {
        /*
        Used to pick the unassigned variable with the
        fewest values in its domain.
        */
        // assigned is a global variables, will use this
        vector<string> pickedVariable;
        // look for unassigned value with fewest
        // check if the coordinates(i,j) are mapped to its domain
        // look for the value with the minimum domain
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (assignments.find(to_string(i) + to_string(j)) == assignments.end()) // checks if not in the list
                    pickedVariable.push_back(to_string(i) + to_string(j));              // push the(coordinates?) variable onto the list
                // if the variable in sudoku is not already assigned
                // add it to the unassigned list,
                // next we need to find the minimum variable, which is what we will return
            }
        }
        // sort the pickedVariable list now
        string minVarCoord = pickedVariable[0];
        for (int i = 1; i < pickedVariable.size(); i++)
        {
            if (s.domain[pickedVariable[i]].size() < s.domain[minVarCoord].size())
                minVarCoord = pickedVariable[i];
        }
        return minVarCoord;
    }
    bool backtrack(sudoku& s)
    {
        /* Backtrack algorithm
        Look at the variables and their domains
        Go through all possible values one at a time.
        If you reach an assignment of values that breaks the constraints, backtrack.
        Backtrack to the last assignment and try the next value.
        We start with a partial assignment of values to variables.
        */

        if (assignments.size() == 81)
            return true;

        string var = unassignedVariable(s);
        // convert var into i and j
        bool solved;
        for (int x : minConstraints(var, s))
        { // for each value in the ordered domain of var
            if (consistent(s, var, x))
            {
                addAssigned(s, var, x);
                solved = backtrack(s);

                if (solved == true)
                    return true;
            }
            removeAssigned(s, var);
        }

        return false;
    }
    vector<int> minConstraints(string var, sudoku& s)
    {
        /*
        Chose the coordinate of the value with the fewest constraints.
        */
        if (s.domain[var].size() == 1) // if there is only one value in the domain, return it
            return s.domain[var];

        vector<int> minDomain;
        vector<vector<int>> conValue;
        vector<int> temp;
        // if there are more than one value in the domain, find the value with the fewest constraints
        // sort the values in the domain of the variable by the number of constraints they have
        // return the domain with the fewest constraints
        // put all values in minDomain
        // sort the values in minDomain by the number of constraints they have
        for (int element : s.domain[var])
        {
            temp.push_back(element);
            temp.push_back(countConstraints(var, s, element));
            conValue.push_back(temp);
            temp.clear();
        }
        sort(conValue.begin(), conValue.end(),
             [](auto const &a, auto const &b)
             { return a[1] < b[1]; });

        for (auto x : conValue)
        {
            minDomain.push_back(x[0]);
        }

        return minDomain;
    }

    int countConstraints(string var, sudoku& s, int value)
    {
        /*
        Count the number of constraints for a given value.
        */
        int count = 0;
        // s.neighbours[var] is a vector of strings representing the coordinates of the neighbours of var
        for (string neighbour : s.neighbours[var])
        {
            if (s.domain[neighbour].size() > 1)
                for (int x : s.domain[neighbour])
                {
                    if (value == x)
                    {
                        count++;
                        break;
                    }
                }
        }
        return count;
    }

    void setAssigned(sudoku& s)
    {
        /*
        Fills the hashmap assigned with the current variables that have a domain of 1 value,
        therefore, variables that are already set.
        hashmap contains the coordinate of the assigned value as a key (string) and the value itself as an int
        */
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (s.domain[to_string(i) + to_string(j)].size() == 1)                                   // if domain == 1
                    assignments[to_string(i) + to_string(j)] = s.domain[to_string(i) + to_string(j)][0]; // add element in domain to assigned
            }
        }
        return;
    }

    bool consistent(sudoku& s, string coord, int value)
    {
        bool consist = true;
        for (auto x : assignments)
        {
            if (x.second == value)
            {
                // check if key in neighbours of coord
                if (find(s.neighbours[coord].begin(), s.neighbours[coord].end(), x.first) != s.neighbours[coord].end())
                    consist = false;
            }
        }
        return consist;
    }

    void addAssigned(sudoku& s, string coord, int value)
    {
        /*
        add value to assignments at index coord, update domains of the
        neighbours of coord
        */
        assignments[coord] = value;
        // update domains of neighbours
        for (string neighbour : s.neighbours[coord])
        {
            if (assignments.find(neighbour) == assignments.end())
            {
                for (int i = 0; i < s.domain[neighbour].size(); i++)
                {
                    if (value == s.domain[neighbour][i])
                    {
                        s.domain[neighbour].erase(s.domain[neighbour].begin() + i);
                        vector<string> temp = {neighbour, to_string(value)};
                        assignedValues[coord].push_back(temp);
                        break;
                    }
                }
            }
        }
    }

    void removeAssigned(sudoku& s, string coord)
    {
        /*
        unassign a previously assigned value (check assignedValues)
        */
        if (assignments.find(coord) != assignments.end())
        {
            for (vector<string> x : assignedValues[coord])
            {
                s.domain[x[0]].push_back(stoi(x[1]));
            }
            assignedValues[coord].clear();
            assignments.erase(coord);
        }
    }

    bool isSolved(sudoku& s)
    {
        // go through the domain and see if the domain at that value is empty
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (s.domain[to_string(i) + to_string(j)].size() == 0)
                    return false;
            }
        }
        return true;
    }
};

void testing(sudoku s)
{
    // print columns
    cout << "PRINT COLUMNS: \n";
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < s.col[i].size(); j++)
        {
            cout << s.col[i][j] << " ";
        }
        cout << endl;
    }
    cout << "PRINT ROWS: \n";
    // print rows
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < s.row[i].size(); j++)
        {
            cout << s.row[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "PRINT BOXES: \n";
    // print boxes
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < s.box[i].size(); j++)
        {
            cout << s.box[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "PRINT DOMAINS: \n";
    for (auto x : s.domain)
    {
        cout << x.first << " ";
        for (int val : x.second)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "PRINT NEIGHBOURS:\n";
    for (auto x : s.neighbours)
    {
        cout << x.first << " ";
        for (string val : x.second)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << "PRINT PERMS:\n";
    for (auto x : s.constraints)
    {
        for (string coord : x)
        {
            cout << coord << " ";
        }
        cout << endl;
    }

    cout << endl;

    return;
}

int main(int argc, char const *argv[])
{
    sudoku s;
    // TESTING:
    testing(s);
    ac3 solver(s);
    cout << solver.backtrack(s) << endl;
    cout << "done" << endl;
    // cout << (solver.backtrack(s)) << endl;

    // print puzzle from assignments

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << solver.assignments[to_string(i) + to_string(j)] << " ";
        }
        cout << endl;
    }

    return 0;
}