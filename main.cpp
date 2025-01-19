#include <iostream>
#include <iomanip>
#include <array>
using std::cout;
using std::cin;
using std::setw;
using std::array;
using std::setfill;

/* READ AND WRITE OPERATION VALUES */
const int read{10};
const int write{11};

/* LOAD AND STORE OPERATION VALUES */
const int load{20};
const int store{21};

/* ARITHMETIC OPERATION VALUES */
const int add{30};
const int subtract{31};
const int divide{32};
const int multiply{33};

/* TRANSFER-OF-CONTROL OPERATION VALUES */
const int branch{40};
const int branchneg{41};
const int branchzero{42};
const int halt{43};


/* MEMORY AND ACCUMULATOR */
const size_t capacity{100};
array<int, capacity> memory;


int main() {
    cout << "*** Welcome to Simpletron! ***\n\n";
    cout << "*** Please enter your program one instruction ***\n";
    cout << "*** (or data word) at a time. I will type the ***\n";
    cout << "*** location number and a question mark (?).  ***\n";
    cout << "*** You then type the word for that location. ***\n";
    cout << "*** Type the sentinel -99999 to stop entering ***\n";
    cout << "*** your program.                             ***\n\n";

    int instructionCounter{0};
    int instruction{0};
    int operationCode{0};
    int operand{0};

    // read instructions to memory
    while (instruction != -99999) {
        cout << setw(2) << setfill('0') << instructionCounter << " ? ";
        cin >> instruction;

        // Execute if sentinel value is entered
        if (instruction == -99999) {
            cout << "Terminating simulator....\n";
            exit(0);
        }

        memory[instructionCounter] = instruction;
        instructionCounter++;
    }  
    
     
}