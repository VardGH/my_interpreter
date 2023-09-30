#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept> 

int main(int argc, char **argv)
{
    /*std::cout << "Interpreter" << std::endl;
    std::cout << "Usage: <executable> input_file_name" << std::endl;

    std::string input_file {};

    if (argc == 1) {
        throw std::runtime_error("Missing input argument, application expects to get an input file");
    } else if (argc == 2) {
        input_file = argv[1];
    } else {
        throw std::runtime_error("Input params are more than expected");
    }*/

    Parser parser("code.txt");
    parser.load_from_file("code.txt");

    parser.parse();

    parser.print_int_map();
    parser.print_bool_map();
    parser.print_double_map();
    parser.print_char_map();
    parser.print_float_map();
    parser.print_string_map();
    parser.full_memory_print();

    return 0;
}
