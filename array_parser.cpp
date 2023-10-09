#include "parser.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

// Function to extract array components (name and index) from an array string
void Parser::extract_array_components(const std::string& arr_string, std::string& name, std::string& index) 
{
    size_t start = arr_string.find('[');
    size_t end = arr_string.find(']');

    if (start != std::string::npos && end != std::string::npos) {
        name = arr_string.substr(0, start);
        index = arr_string.substr(start + 1, end - start - 1);
    }
}

// Function to parse array manipulation statements (e.g., arr[i] = value;)
void Parser::parse_array_manipulation(const std::string& line) 
{
    std::string tmp_name_arr {};
    std::string index {};
    std::string assignment {};
    std::string value {};

    std::istringstream iss(line);

    iss >> tmp_name_arr >> assignment >> value;

    if (line.find("if") && line.find("while") && value[value.size() - 1] != ';') {
        throw std::runtime_error("You forgot the ; in the following line:");
    }

    // Extract array components
    std::string array_name;
    extract_array_components(tmp_name_arr, array_name, index);

    // std::cout << "array_name: " << array_name << std::endl;
    // std::cout << "index: " << index << std::endl;

    value.pop_back();
    execute_array_assignment_statement(array_name, index, assignment, value);
}

// Function to check if a line starts with std::cout
bool Parser::start_cout(const std::string& str)
{
    return !str.find("std::cout");
}

// Function to check if a line starts with std::cin
bool Parser::start_cin(const std::string& str)
{
    return !str.find("std::cin");
}

// Function to check if a line starts with if
bool Parser::start_if(const std::string& str)
{
    return !str.find("if");
}

// Function to check if a line starts with while
bool Parser::start_while(const std::string& str)
{
    return !str.find("while");
}

// Function to execute array assignment statements
void Parser::execute_array_assignment_statement(const std::string& array_name, const std::string& index, const std::string& assignment, const std::string& value)
{
    if (!defined_array(array_name) && !start_cout(array_name) && !start_cin(array_name)) {
        throw std::runtime_error("Not defined array: " + array_name);
    }

    // Convert index to size_t
    int array_index = get_value<int>(index);

    if (is_int_array(array_name)) {
        if (array_index < 0 || int_array[array_name].size() <= array_index) {
            throw std::runtime_error("invalid array_index");
        }
        int_array[array_name][array_index] = get_value<int>(value);
    } else if (is_double_array(array_name)) {
        if (array_index < 0 || double_array[array_name].size() <= array_index) {
            throw std::runtime_error("invalid array_index");
        }
        double_array[array_name][array_index] = get_value<double>(value);
    } else if (is_char_array(array_name)) {
        if (array_index < 0 || char_array[array_name].size() <= array_index) {
            throw std::runtime_error("invalid array_index");
        }
        char_array[array_name][array_index] = get_value<char>(value);   
    } else if (is_bool_array(array_name)) {
        if (array_index < 0 || bool_array[array_name].size() <= array_index) {
            throw std::runtime_error("invalid array_index");
        }
        bool_array[array_name][array_index] = get_value<bool>(value);      
    } else if (is_string_array(array_name)) {
        if (array_index < 0 || string_array[array_name].size() <= array_index) {
            throw std::runtime_error("invalid array_index");
        }
        if (is_string_variable(value)) {
            string_array[array_name][array_index] = string_variables[value];
        } else if (is_string_literal(value)) {
            string_array[array_name][array_index] = get_string(value);
        }      
    } else if (is_float_array(array_name)) {
        if (array_index < 0 || string_array[array_name].size() <= array_index) {
            throw std::runtime_error("invalid array_index");
        }
        float_array[array_name][array_index] = get_value<float>(value); 
    }
}

// Function to check if a line is an array declaration
bool Parser::is_array_declaration(const std::string& line)
{
    // Check if the line starts with one of the data types
    const std::vector<std::string> data_types = {"char", "bool", "int", "float", "double", "string"};

    int is_type = false;
    for (const std::string& data_type : data_types) {
        if (line.find(data_type) == 0) {
            is_type = true;

            size_t pos1 = line.find('[');
            size_t pos2 = line.find(']');

            if (pos1 == std::string::npos || pos2 == std::string::npos) {
                is_type = false;
            }
        }
    }

    // Check if the line ends with a semicolon
    if (is_type && line[line.size() - 1] != ';') {
        throw std::runtime_error("You forgot the ; in the following line:");
    }
    return is_type;
}

// Function to parse array declarations
void Parser::parse_array_statement(const std::string& line)
{
    if (line.find('{') != std::string::npos || line.find('}') != std::string::npos) {
        brace_init_array(line);
        return;
    }

    std::string op1 {};
    std::string op2 {};

    std::istringstream iss(line);
    iss >> op1 >> op2;

    // Remove the semicolon if necessary
    op2.erase(std::remove(op2.begin(), op2.end(), ';'), op2.end());
    
    std::string array_name {};
    std::string index {};
    extract_array_components(op2, array_name, index);

    // Check for redefinition
    if (defined_array(array_name) || defined_variable(array_name)) {
        throw std::runtime_error("Redefinition");
    }

    int size_array {};

    // Parse the size of the array
    if (is_number(index) || is_int_variable(index)) {
        size_array = get_value<int>(index);
    }

    // Validate array size
    if (size_array < 0) {
        throw std::runtime_error("Array size cannot be negative");
    }

    // Initialize the array with zeros
    if (op1 == "int") {
        int_array[array_name] = std::vector<int>(size_array, 0);
    } else if (op1 == "double") {
        double_array[array_name] = std::vector<double>(size_array, 0.0);
    } else if (op1 == "char") {
        char_array[array_name] = std::vector<char>(size_array, ' ');
    } else if (op1 == "bool") {
        bool_array[array_name] = std::vector<bool>(size_array, false);
    } else if (op1 == "string") {
        string_array[array_name] = std::vector<std::string>(size_array, "");
    } else if (op1 == "float") {
        float_array[array_name] = std::vector<float>(size_array, 0.0);
    }
}

// Function for brace initialization of arrays
void Parser::brace_init_array(const std::string& line)
{
    // Find the position of the opening and closing braces
    size_t openingBracePos = line.find('{');
    size_t closingBracePos = line.find('}');

    std::string op1 {};
    std::string op2 {};

    std::istringstream iss(line);
    iss >> op1 >> op2;

    std::string array_name {};
    std::string index {};
    extract_array_components(op2, array_name, index);

    if (openingBracePos == std::string::npos || closingBracePos == std::string::npos) {
        throw std::runtime_error("Missing opening or closing brace in array initialization");
    }

    // Extract the content between the braces
    std::string content = line.substr(openingBracePos + 1, closingBracePos - openingBracePos - 1);

    // Tokenize the content based on commas
    std::istringstream iss2(content);
    std::vector<std::string> elements;
    std::string element {};
    while (std::getline(iss2, element, ',')) {
        elements.push_back(trim(element));
    }

    if (op1 == "int") {
        std::vector<int> int_elements;
        for (const auto& elem : elements) {
            int_elements.push_back(std::stoi(elem));
        }
        int_array[array_name] = int_elements;
    } else if (op1 == "double") {
        std::vector<double> double_elements;
        for (const auto& elem : elements) {
            double_elements.push_back(std::stod(elem));
        }
        double_array[array_name] = double_elements;
    } else if (op1 == "char") {
        std::vector<char> char_elements;
        for (const auto& elem : elements) {

            char_elements.push_back(elem[1]);
        }
        char_array[array_name] = char_elements;  
    } else if (op1 == "string") {
        std::vector<std::string> string_elements;
        for (const auto& elem : elements) {
            std::string tmp = elem;
            tmp = tmp.substr(1);
            tmp.pop_back();
            string_elements.push_back(tmp);
        }
        string_array[array_name] = string_elements;
    } else if (op1 == "float") {
        std::vector<float> float_elements;
        for (const auto& elem : elements) {
            float_elements.push_back(std::stod(elem));
        }
        float_array[array_name] = float_elements;
    }
}