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

void Parser::print_int_arrays()
{
    for (const auto& entry : int_array) {
        const std::string& array_name = entry.first;
        const std::vector<int>& values = entry.second;

        std::cout << "IArray " << array_name << ": [";

        if (!values.empty()) {
            // Print elements separated by commas
            for (int i = 0; i < values.size() - 1; ++i) {
                std::cout << values[i] << ", ";
            }

            // Print the last element
            std::cout << values.back();
        }

        std::cout << "]" << std::endl;
    }
}

void Parser::print_double_arrays()
{
    for (const auto& entry : double_array) {
        const std::string& array_name = entry.first;
        const std::vector<double>& values = entry.second;

        std::cout << "DArray " << array_name << ": [";

        if (!values.empty()) {
            // Print elements separated by commas
            for (int i = 0; i < values.size() - 1; ++i) {
                std::cout << values[i] << ", ";
            }

            // Print the last element
            std::cout << values.back();
        }

        std::cout << "]" << std::endl;
    }
}

void Parser::print_char_arrays()
{
    for (const auto& entry : char_array) {
        const std::string& array_name = entry.first;
        const std::vector<char>& values = entry.second;

        std::cout << "CArray " << array_name << ": [";

        if (!values.empty()) {
            // Print elements separated by commas
            for (int i = 0; i < values.size() - 1; ++i) {
                std::cout << values[i] << ", ";
            }

            // Print the last element
            std::cout << values.back();
        }

        std::cout << "]" << std::endl;
    }
}

void Parser::print_bool_arrays()
{
    for (const auto& entry : bool_array) {
        const std::string& array_name = entry.first;
        const std::vector<bool>& values = entry.second;

        std::cout << "BArray " << array_name << ": [";

        if (!values.empty()) {
            // Print elements separated by commas
            for (int i = 0; i < values.size() - 1; ++i) {
                std::cout << values[i] << ", ";
            }

            // Print the last element
            std::cout << values.back();
        }

        std::cout << "]" << std::endl;
    }
}

void Parser::print_string_arrays()
{
    for (const auto& entry : string_array) {
        const std::string& array_name = entry.first;
        const std::vector<std::string>& values = entry.second;

        std::cout << "SArray " << array_name << ": [";

        if (!values.empty()) {
            // Print elements separated by commas
            for (int i = 0; i < values.size() - 1; ++i) {
                std::cout << values[i] << ", ";
            }

            // Print the last element
            std::cout << values.back();
        }

        std::cout << "]" << std::endl;
    }
}

void Parser::print_float_arrays()
{
    for (const auto& entry : float_array) {
        const std::string& array_name = entry.first;
        const std::vector<float>& values = entry.second;

        std::cout << "FArray " << array_name << ": [";

        if (!values.empty()) {
            // Print elements separated by commas
            for (int i = 0; i < values.size() - 1; ++i) {
                std::cout << values[i] << ", ";
            }

            // Print the last element
            std::cout << values.back();
        }

        std::cout << "]" << std::endl;
    }
}