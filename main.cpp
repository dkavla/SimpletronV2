#include <iostream>
#include <iomanip>
#include <array>
#include <cstdlib>
using std::cout;
using std::cin;
using std::cerr;
using std::setw;
using std::array;
using std::setfill;
using std::left;
using std::right;
using std::showpos;
using std::noshowpos;
using std::internal;
using std::fixed;
using std::setprecision;

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
double accumulator{0};

/* FUNCTIONS */
void readInInstructions(int& instructionCount);
void readInstructionsFromMemory(const int& instructionCounter);

/* OPERATION FUNCTIONS */
void readToMem(const int& operandLoc);
void writeFromMem(const int& operandLoc);
void loadFromMem(const int& operandLoc);
void storeToMem(const int& operandLoc);
void addToAccum(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operandLoc);
void subtractFromAccum(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operandLoc);
void divideAccumBy(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operandLoc);
void multiplyAccumBy(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operandLoc);
void branchTo(int& instructionLoc, const int& operandLoc);
void haltProgram(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operand);

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
    
    // cout << "\nTesting Successful!\n";
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

        if ( (instruction < -9999 || instruction > 9999) && instruction != -99999) {
            while (instruction < -9999 || instruction > 9999) {
                cout << "\tYour instruction is out of the accepted range. Enter a different instruction.\n";
                cout << "\t";
                cout << setw(2) << setfill('0') << instructionCount << " ? ";
                cin >> instruction;
            }
        }

        memory[instructionCount] = instruction;
        instructionCount++;
    }

    cout << "\n*** Program loading completed ***\n";
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
                readToMem(operand);
                break;
            case write:
                writeFromMem(operand);
                break;
            case load:
                loadFromMem(operand);
                break;
            case store:
                storeToMem(operand);
                break;
            case add:
                addToAccum(instr, instructionRegister, operationCode, operand);
                break;
            case subtract:
                subtractFromAccum(instr, instructionRegister, operationCode, operand);
                break;
            case divide:
                divideAccumBy(instr, instructionRegister, operationCode, operand);
                break;
            case multiply:
                multiplyAccumBy(instr, instructionRegister, operationCode, operand);
                break;
            case branch:
                branchTo(instr, operand);
                break;
            case branchneg:
                if (accumulator < 0) {
                    branchTo(instr, operand);
                }
                break;
            case branchzero:
                if (accumulator == 0) {
                    branchTo(instr, operand);
                }
                break;
            case halt:
                // cout << "Halting program execution\n";
                haltProgram(instr, instructionRegister, operationCode, operand);
                return;
                break;
            default:
                // cout << "ERROR! Invlaid Operation Code! Terminating....\n";
                exit(1);
        }
    }

}

void readToMem(const int& operandLoc) {
    cout << "? ";
    cin >> memory[operandLoc];
}

void writeFromMem(const int& operandLoc) {
    cout << "> " << memory[operandLoc] << "\n\n";
}

void loadFromMem(const int& operandLoc) {
    accumulator = memory[operandLoc];
}

void storeToMem(const int& operandLoc) {
    memory[operandLoc] = accumulator;
}

void addToAccum(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operandLoc) {
    accumulator += memory[operandLoc];

    if (accumulator < -9999 || accumulator > 9999) {
        cout << "*** Attempt to add a number resulted ***\n";
        cout << "*** in a value that is too large or  ***\n";
        cout << "*** too small.                       ***\n";
        cout << "*** Simpletron execution abnormally  ***\n";
        cout << "*** terminated.                      ***\n";
        haltProgram(instructionCounter, instructionRegister, operationCode, operandLoc);
        exit(1);
    }
}

void subtractFromAccum(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operandLoc) {
    accumulator -= memory[operandLoc];

    if (accumulator < -9999 || accumulator > 9999) {
        cout << "*** Attempt to subtract a number     ***\n";
        cout << "*** resulted in a value that is too  ***\n";
        cout << "*** large or too small.              ***\n";
        cout << "*** Simpletron execution abnormally  ***\n";
        cout << "*** terminated.                      ***\n";
        haltProgram(instructionCounter, instructionRegister, operationCode, operandLoc);
        exit(1);
    }
}

void divideAccumBy(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operandLoc) {
    if (memory[operandLoc] == 0) {
        cout << "*** Attempt to divide by zero ***\n";
        cout << "*** Simpletron execution abnormally terminated ***\n";
        exit(1);
    }

    accumulator /= memory[operandLoc];

    if (accumulator < -9999 || accumulator > 9999) {
        cout << "*** Attempt to divide a number ***\n";
        cout << "*** resulted in a value that   ***\n";
        cout << "*** is too large or too small. ***\n";
        cout << "*** Simpletron execution abnormally terminated. ***\n";
        haltProgram(instructionCounter, instructionRegister, operationCode, operandLoc);
        exit(1);
    }
}

void multiplyAccumBy(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operandLoc) {
    accumulator *= memory[operandLoc];

    if (accumulator < -9999 || accumulator > 9999) {
        cout << "*** Attempt to multiply a number resulted ***\n";
        cout << "*** in a number that is too large or too  ***\n";
        cout << "*** small.                                ***\n";
        cout << "*** Simpletron execution abnormally terminated. ***\n";
        haltProgram(instructionCounter, instructionRegister, operationCode, operandLoc);
        exit(1);
    }
}

void branchTo(int& instructionLoc, const int& operandLoc) {
    instructionLoc = operandLoc;
}

void haltProgram(const int& instructionCounter, const int& instructionRegister, const int& operationCode, const int& operand) {
    cout << fixed;
    cout << "REGISTERS:\n";
    cout << setfill(' ') << setw(23) << left << "accumulator";
    cout << setw(5) << setfill('0') << internal << showpos << setprecision(0) << accumulator;
    cout << '\n';

    cout << setfill(' ') << setw(26) << left << "instructionCounter";
    cout << setw(2) << setfill('0') << noshowpos << right << instructionCounter;
    cout << '\n';
    

    cout << setfill(' ') << setw(23) << left << "instructionRegister";
    cout << setw(5) << setfill('0') << internal << showpos << instructionRegister;
    cout << '\n';

    cout << setfill(' ') << setw(26) << left << "operationCode";
    cout << setw(2) << setfill('0') << noshowpos << right << operationCode;
    cout << '\n';

    cout << setfill(' ') << setw(26) << left << "operand";
    cout << setw(2) << setfill('0') << noshowpos << right << operand;
    cout << "\n\n";

    cout << "MEMORY:\n";

    // print the header of the memory dump table
    cout << setw(2) << "  ";
    cout << " ";
    for (int col{0}; col < 10; ++col) {
        cout << setw(5) << setfill(' ') << col;
        cout << " ";
    }
    cout << '\n';

    // print the rows of the memory dump table
    for (int row{0}; row < capacity; row += 10) {
        cout << setw(2) << right << row << " ";
        for (int col{0}; col < 10; ++col) {
            cout << setw(5) << setfill('0') << internal << showpos << memory[row + col] << " ";
        }
        cout << '\n';
        cout << noshowpos;
    }
    cout << '\n';
}





















