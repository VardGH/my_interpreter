#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

Parser::Parser(const std::string& input)
    : m_input{input}
{
}

std::string Parser::trim(const std::string& str) 
{
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}


bool Parser::is_variable_declaration(std::string& line, int address)
{
    std::cout << line << std::endl;
    // Check if the line starts with one of the data types
    const std::vector<std::string> data_types = {"char", "bool", "int", "float", "double", "string"};

    int is_type = false;
    for (const std::string& data_type : data_types) {
        if (line.find(data_type) == 0) {
            is_type = true;
        }
    }

    // Check if the line ends with a semicolon
    if (is_type && line[line.size() - 1] != ';') {
        throw std::runtime_error("You forgot the ; in the following line:");
    }
    return is_type;
}

void Parser::parse_variable_declaration(std::string& line, int address)
{
    line.erase(std::remove(line.begin(), line.end(), ';'), line.end());

    std::istringstream iss(line);
    std::string type {};
    std::string type_name {};
    std::string assignment {};
    std::string expression {};

    iss >> type >> type_name >> assignment >> expression;

    std::cout << "type: " << type << std::endl;
    std::cout << "type_name: " << type_name << std::endl;
    std::cout << "assignment: " << assignment << std::endl;
    std::cout << "expression: " << expression << std::endl;
    std::cout << std::endl;

    if (type != "" && type_name == "=") {
        std::cout << "You forgot the type_name: " << address << std::endl;
        return;
    }

    if (type != "" && type_name != "" && assignment == "=" && expression == "") {
        std::cout << "You have not provided a value after = " << address << std::endl;
        return;  
    }
    save_memory(type, type_name, expression);
}

void Parser::save_memory(const std::string& type, const std::string& type_name, const std::string& expression)
{
    std::string value {};
    if (expression != "") {
        value = expression;
    }

    if (type == "bool") {
        bool_expression_pars(type_name, expression);
    } else if (type == "char") {
        char_expression_pars(type_name, expression);
    } else if (type == "int") {
        int_expression_pars(type_name, expression);
    } else if (type == "float") {
        float_variables[type_name] = value;
    } else if (type == "double") {
        double_variables[type_name] = value;
    } else if (type == "string") {
        string_variables[type_name] = value;
    }
}

void Parser::bool_expression_pars(const std::string& type_name, const std::string& expression)
{
    bool tmp{};
    if (expression.empty() || expression == "0" || expression == "false") {
        tmp = false;
    } else if (is_number(expression)) {
        tmp = true;
    } else if (expression == "true") {
        tmp = true;
    } else {
        throw std::invalid_argument("Invalid boolean expression: " + expression);
    }
    bool_variables[type_name] = tmp;
}

void Parser::char_expression_pars(const std::string& type_name, const std::string& expression)
{
    char tmp {};
    if (expression.size() == 3 && expression[0] == '\'' && expression[2] == '\'') {
        tmp = expression[1];
    } else {
        throw std::invalid_argument("Invalid char expression: " + expression);
    }
    char_variables[type_name] = tmp;
}

void Parser::int_expression_pars(const std::string& type_name, const std::string& expression)
{
    try {
        int value = std::stoi(expression); // Attempt to convert the expression to an integer
        int_variables[type_name] = value;
    } catch (const std::invalid_argument& ex) {
        throw std::invalid_argument("Invalid integer expression: " + expression);
    } catch (const std::out_of_range& ex) {
        throw std::out_of_range("Integer value out of range: " + expression);
    }
}

bool Parser::is_number(const std::string& expression)
{
    if (expression.size() > 1 && expression[0] == '0') {
        return false;
    }

    for (int i = 1; i < expression.size(); ++i) {
        if ('0' > expression[i] || expression[i] > '9') {
            return false;
        }
    }
    return true;
}

void Parser::parse()
{
    std::ifstream file(m_input);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + m_input);
    }

    std::string line {};
    int address = 1;
    bool found_iostream = false;
    bool found_main = false;

    try {
        while (std::getline(file, line)) {
            // skip empty lines
            if (line.empty()) {
                ++address;
                continue;
            }

            // remove whitespace
            line = trim(line);

            if (!found_iostream) {
                parse_iostream(line, found_iostream);
                ++address;
                continue;
            }

            if (!found_main && found_iostream) {
                parse_main(line, address, found_main);
                ++address;
                continue;
            }

            if (is_variable_declaration(line, address)) {
                parse_variable_declaration(line, address);
            }
            ++address;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    file.close();
}

void Parser::print_int_map()
{
    std::cout << "int" << std::endl;
    for(auto& elem : int_variables) {
        std::cout << "Key: " << elem.first << " " << ", val: " << elem.second << std::endl;
    }
}

void Parser::print_char_map()
{
    std::cout << "char" << std::endl;
    for(auto& elem : char_variables) {
        std::cout << "Key: " << elem.first << " " << ", val: " << elem.second << std::endl;
    }
}

void Parser::print_bool_map()
{
    std::cout << "bool" << std::endl;
    for(auto& elem : bool_variables) {
        std::cout << "Key: " << elem.first << " " << ", val: " << elem.second << std::endl;
    }
}

void Parser::print_float_map()
{
    std::cout << "float" << std::endl;
    for(auto& elem : float_variables) {
        std::cout << "Key: " << elem.first << " " << ", val: " << elem.second << std::endl;
    }
}

void Parser::print_double_map()
{
    std::cout << "double" << std::endl;
    for(auto& elem : double_variables) {
        std::cout << "Key: " << elem.first << " " << ", val: " << elem.second << std::endl;
    }
}

void Parser::print_string_map()
{
    std::cout << "String" << std::endl;
    for(auto& elem : string_variables) {
        std::cout << "Key: " << elem.first << " " << ", val: " << elem.second << std::endl;
    }
}

void Parser::parse_iostream(const std::string& line, bool& found_iostream)
{
    if (is_iostream(line)) {
        found_iostream = true;
    } else {
        throw std::runtime_error("Missing #include <iostream>");
    }
}

void Parser::parse_main(const std::string& line, int address, bool& found_main)
{
    if (is_main(line, address)) {
        found_main = true;
    } else {
        throw std::runtime_error("Line does not contain int main() {");
    }
}

bool Parser::is_iostream(const std::string& line)
{
    std::string st1;
    std::string st2;
    std::istringstream iss(line);
    iss >> st1 >> st2;

    if (st1 == "#include" && st2 == "<iostream>") {
        return true;  // Correct
    } else if (st1 == "#include" && st2 != "<iostream>") {
        std::cout << "Error: Incorrect library name after #include" << std::endl;
    } else if (st1 != "#include" && st2 == "<iostream>") {
        std::cout << "Error: Missing #include before <iostream>" << std::endl;
    } else {
        std::cout << "Error: Line does not contain #include <iostream>" << std::endl;
    }

    return false;  // Not the correct directive
}

bool Parser::is_main(const std::string& line, int address)
{
    std::string st1;
    std::string st2;
    std::string st3;
    std::istringstream iss(line);
    iss >> st1 >> st2 >> st3;

    if (st1 == "int" && st2 == "main()" && st3 == "{") {
        return true;  // Correct start of main function
    } else if (st1.empty() && st2.empty() && st3 == "}") {
        return true;  // Correct end of main function
    }
    return false;
}