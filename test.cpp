#include"Interface.h"
#include<string>
#include<iostream>
#include<vector>

using namespace std;

int main() {
    int status = 0;
    Program::start( "// MANAGE PROGRAM //\n"
                    "1. statistical\n"
                    "1.1. by day\n"
                    "1.2. by month\n"
                    "1.3. by year\n"
                    "2. add data\n"
                    "2.1. by day\n"
                    "2.2. by month\n"
                    "2.3. by year\n"
                    "3. compare\n"
                    "3.1. by day\n"
                    "3.1.1. avg\n"
                    "3.1.2. sum\n"
                    "3.1.3. all\n"
                    "3.2. by month\n"
                    "3.2.1. avg\n"
                    "3.2.2. sum\n"
                    "3.2.3. all\n"
                    "3.3. by year\n"
                    "3.3.1. avg\n"
                    "3.3.2. sum\n"
                    "3.3.3. all\n"
                    "4. quit\n",
    [&status](){ // database push reference to [...]
        switch (Program::process()) {
            case 11:
            case 12:
            case 13: {
                string input = Program::getInput("DAY MONTH YEAR");
                cout << input << endl;
                Program::stopProgram();
                break;
            }
            case 21:
            case 22:
            case 23: {
                cout << "JUST PRINT SOMETHING" << endl;
                Program::stopProgram();
                break;
            }
            case 311:
            case 312:
            case 313:
            case 321:
            case 322:
            case 323:
            case 331:
            case 332:
            case 333: {
                cout << "status: " << status++ << endl;
                Program::stopProgram();
                break;
            }
            case 4: {
                Program::quitProgram();
                break;
            }
            default: {
                cout << "This is the announcement after the program ends." << endl; //must to make a default case if dont want endless loop when have some ERROR
            }
        }
    });


    return 0;
}


