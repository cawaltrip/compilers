/* 
 * File:   ant.h
 * Author: Joshua Rubini
 *
 * Created on October 25, 2011, 10:42 AM
 * 
 * ant class includes all basic movement methods,
 * energy handling, and a simple means of output
 * 
 * You may output an ant now using an output stream:
 * -- ant my_ant w/ x = 5, y = 6, energy = 40, facing north
 * -- the statement: cout << my_ant << endl;
 * -- will output: (5,6) ^ 40
 * -- to the screen
 */

#include <iostream>

using namespace std;

class ant {
    public:
        // Constructor:
        
        ant();          // init: x,y,energy = 0, dir = '^'

        // Accessors:
        
        int GetX();     
        int GetY();
        int GetEnergy();
        char Print();
        
        // Mutator:
        
        void ChangeEnergy(int);
        
        // Methods:
        
        bool Left();
        bool Right();
        bool Forward();
        
        friend ostream &operator<<(ostream &outs, ant &rhs) {
            outs << "(" << rhs.GetX() << "," 
                 << rhs.GetY() << ") " << rhs.Print() 
                 << " " << rhs.GetEnergy();
        }
    private:
        int x,y;
        char dir;
        int energy;
};
