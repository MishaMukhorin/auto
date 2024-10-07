//
// Created by Misha on 13.09.2024.
//
#include "machines/MealyMachine.h"
#include "machines/MooreMachine.h"
#include "machines/MachineReader.h"
#include <iostream>
#include <string>

void printUsage() {
    std::cout << "Usage: program.exe [mealy-to-moore|moore-to-mealy] input.csv output.csv\n";
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];
    std::string input_file = argv[2];
    std::string output_file = argv[3];
    std::string visual_file = output_file.substr(0, output_file.find(".csv"));  // Strip the '.csv'

    if (command == "mealy-to-moore") {
        MealyMachine mealy_machine = readMealyCSV(input_file);
        MooreMachine moore_machine = mealy_machine.ToMoore();
        moore_machine.WriteCsv(output_file);
        
        std::cout << "Conversion from Mealy to Moore completed.\n";
        std::cout << "Output CSV saved to " << output_file << "\n";

    } else if (command == "moore-to-mealy") {

        MooreMachine moore_machine = readMooreCSV(input_file);
        MealyMachine mealy_machine = moore_machine.ToMealy();
        mealy_machine.WriteCsv(output_file);

        std::cout << "Conversion from Moore to Mealy completed.\n";
        std::cout << "Output CSV saved to " << output_file << "\n";

    } else {
        std::cerr << "Unknown command. Use either 'mealy-to-moore' or 'moore-to-mealy'.\n";
        printUsage();
        return 1;
    }

    return 0;
}