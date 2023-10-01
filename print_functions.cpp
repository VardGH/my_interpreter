#include "parser.hpp"
#include <iostream>

void Parser::print_int_map()
{
    std::cout << "\nint" << std::endl;
    for(auto& elem : int_variables) {
        std::cout << "Key: " << elem.first << ", val: " << elem.second << std::endl;
    }
    std::cout << std::endl;
}

void Parser::print_char_map()
{
    std::cout << "char" << std::endl;
    for(auto& elem : char_variables) {
        std::cout << "Key: " << elem.first << ", val: " << elem.second << std::endl;
    }
    std::cout << std::endl;
}

void Parser::print_bool_map()
{
    std::cout << "bool" << std::endl;
    for(auto& elem : bool_variables) {
        std::cout << "Key: " << elem.first << ", val: " << elem.second << std::endl;
    }
    std::cout << std::endl;
}

void Parser::print_float_map()
{
    std::cout << "float" << std::endl;
    for(auto& elem : float_variables) {
        std::cout << "Key: " << elem.first << ", val: " << elem.second << std::endl;
    }
    std::cout << std::endl;
}

void Parser::print_double_map()
{
    std::cout << "double" << std::endl;
    for(auto& elem : double_variables) {
        std::cout << "Key: " << elem.first << ", val: " << elem.second << std::endl;
    }
    std::cout << std::endl;
}

void Parser::print_string_map()
{
    std::cout << "String" << std::endl;
    for(auto& elem : string_variables) {
        std::cout << "Key: " << elem.first << " " << ", val: " << elem.second << std::endl;
    }
    std::cout << std::endl;
}

void Parser::full_memory_print()
{
    std::cout << "full memory" << std::endl;
    for (auto it = full_memory.begin(); it != full_memory.end(); ++it) {
        std::cout << "Key: " << it->first << ", val: " << it->second << std::endl;
    }
    std::cout << std::endl;
}