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

/* FUNCTIONS */
void readInInstructions(int& instructionCount);
void readInstructionsFromMemory(const int& instructionCounter);

/* OPERATION FUNCTIONS */
void readToMem(const int& operandLoc);
void loadFromMem(const int& operandLoc);
void addToAccum(const int& operandLoc);
void subtractFromAccum(const int& operandLoc);
void divideAccumBy(const int& operandLoc);
void multiplyAccumBy(const int& operandLoc);
void branchTo(int& instructionLoc, const int& operandLoc);
void branchNegTo(int& instructionLoc, const int& operandLoc);
void branchZeroTo(int& instructionLoc, const int& operandLoc);
void haltProgram();

int main() {
    cout << "*** Welcome to Simpletron! ***\n\n";
    cout << "*** Please enter your program one instruction ***\n";
    cout << "*** (or data word) at a time. I will type the ***\n";
    cout << "*** location number and a question mark (?).  ***\n";
    cout << "*** You then type the word for that location. ***\n";
    cout << "*** Type the sentinel -99999 to stop entering ***\n";
    cout << "*** your program.                             ***\n\n";

    int instructionCounter{0};

    readInInstructions(instructionCounter);
    readInstructionsFromMemory(instructionCounter);
    
    
}

void readInInstructions(int& instructionCount) {
    /* READ IN THE INSTRUCTIONS TO MEMORY UNTIL SENTINEL VALUE ENTERED */

    int instruction{0}; // used for entering instructions to memory only
    int variables{0}; // keep track of how many variables are to be stored

    // read instructions to memory
    while (instruction != -99999) {
        cout << setw(2) << setfill('0') << instructionCount << " ? ";
        cin >> instruction;

        // Exit if sentinel value is entered
        if (instruction == -99999) {
            break;
        }

        if (instruction == 0000) {
            variables++;
        }

        memory[instructionCount] = instruction;
        instructionCount++;
    }

    cout << "\n\n*** Program loading completed ***\n";
    cout << "*** Program execution begins ***\n\n";

    instructionCount -= variables; // adjust instruction count for the number of variable slots saved
}

void readInstructionsFromMemory(const int& instructionCounter) {
    int operationCode{0}; // specifies the operation being performed with operand
    int operand{0}; // specifies the location to store operand
    int instructionRegister{0};

    for (int instr{0}; instr < instructionCounter; ++instr) {
        instructionRegister = memory[instr];

        operationCode = instructionRegister / 100;
        operand = instructionRegister % 100;

        switch (operationCode) {
            case read:
                break;
            case write:
                break;
            case load:
                break;
            case store:
                break;
            case add:
                break;
            case subtract:
                break;
            case divide:
                break;
            case multiply:
                break;
            case branch:
                break;
            case branchneg:
                break;
            case branchzero:
                break;
            case halt:
                break;
            default:
                cout << "ERROR! Invlaid Operation Code! Terminating....\n";
                exit(1);
        }
    }

}






















