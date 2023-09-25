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
    std::string name {};
    std::string assignment {};
    std::string expression {};

    iss >> type >> name >> assignment >> expression;

    std::cout << "type: " << type << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "assignment: " << assignment << std::endl;
    std::cout << "expression: " << expression << std::endl;
    std::cout << std::endl;

    if (type != "" && name == "=") {
        std::cout << "You forgot the name: " << address << std::endl;
        return;
    }

    if (type != "" && name != "" && assignment == "=" && expression == "") {
        std::cout << "You have not provided a value after = " << address << std::endl;
        return;  
    }
    save_memory(type, name, expression);
}

void Parser::save_memory(const std::string& type, const std::string& name, const std::string& expression)
{
    std::string value {};
    if (expression != "") {
        value = expression;
    }

    // Handle variable declaration based on type
    if (type == "bool") {
        bool_expression_pars(name, expression);
    } else if (type == "char") {
        char_expression_pars(name, expression);
    } else if (type == "int") {
        int_expression_pars(name, expression);
    } else if (type == "float") {
        float_expression_pars(name, expression);
    } else if (type == "double") {
        double_expression_pars(name, expression);
    } else if (type == "string") {
        string_expression_pars(name, expression);
    }
}

void Parser::bool_expression_pars(const std::string& name, const std::string& expression)
{
    bool tmp{};
    if (expression.empty() || expression == "0" || expression == "false") {
        tmp = false;
    } else if (is_number(expression)) {
        tmp = true;
    } else if (expression == "true") {
        tmp = true;
    } else if (is_bool_variable(expression)) {
        auto bool_var_it = bool_variables.find(expression);
        if (bool_var_it != bool_variables.end()) {
            tmp = bool_var_it->second;
        }
    } else {
        throw std::invalid_argument("Invalid boolean expression: " + expression);
    }

    if (!defined_variable(name)) {
        bool_variables[name] = tmp;
    } else {
        throw std::runtime_error("Redefinition");
    }
}

bool Parser::is_bool_variable(const std::string& expression)
{
    return bool_variables.find(expression) != bool_variables.end();
}

void Parser::char_expression_pars(const std::string& name, const std::string& expression)
{
    char tmp{};
    if (expression.size() == 3 && expression.front() == '\'' && expression.back() == '\'') {
        tmp = expression[1];
    } else if (is_char_variable(expression)) {
        auto char_var_it = char_variables.find(expression);
        if (char_var_it != char_variables.end()) {
            tmp = char_var_it->second;
        }
    } else if (expression.empty()) {
        tmp = ' ';
    } else {
        throw std::invalid_argument("Invalid char expression: " + expression);
    }
    char_variables[name] = tmp;
}

bool Parser::is_char_variable(const std::string& expression)
{
    return char_variables.find(expression) != char_variables.end();
}

void Parser::int_expression_pars(const std::string& name, const std::string& expression)
{
    if (defined_variable(name)) {
        throw std::runtime_error("Redefinition");
    }

    if (is_int_variable(expression)) {
        auto int_var_it = int_variables.find(expression);
        if (int_var_it != int_variables.end()) {
            int_variables[name] = int_var_it->second;
            return;
        }
    } else if (expression.empty()) {
        int_variables[name] = 0;
        return;
    }

    try {
        int value = std::stoi(expression); // Attempt to convert the expression to an integer
        int_variables[name] = value;
    } catch (const std::invalid_argument& ex) {
        throw std::invalid_argument("Invalid integer expression: " + expression);
    } catch (const std::out_of_range& ex) {
        throw std::out_of_range("Integer value out of range: " + expression);
    }
}

bool Parser::is_int_variable(const std::string& expression)
{
    return int_variables.find(expression) != int_variables.end();
}

void Parser::float_expression_pars(const std::string& name, const std::string& expression)
{
    if (defined_variable(name)) {
        throw std::runtime_error("Redefinition");
    }

    if (is_float_variable(expression)) {
        auto float_var_it = float_variables.find(expression);
        if (float_var_it != float_variables.end()) {
            float_variables[name] = float_var_it->second;
            return;
        }
    } else if (expression.empty()) {
        float_variables[name] = 0.0;
        return;
    }

    try {
        int value = std::stof(expression); // Attempt to convert the expression to an float
        float_variables[name] = value;
    } catch (const std::invalid_argument& ex) {
        throw std::invalid_argument("Invalid float expression: " + expression);
    } catch (const std::out_of_range& ex) {
        throw std::out_of_range("Float value out of range: " + expression);
    }  
}

bool Parser::is_float_variable(const std::string& expression)
{
    return float_variables.find(expression) != float_variables.end();
}

void Parser::double_expression_pars(const std::string& name, const std::string& expression)
{
    if (defined_variable(name)) {
        throw std::runtime_error("Redefinition");
    }

    if (is_double_variable(expression)) {
        auto double_var_it = double_variables.find(expression);
        if (double_var_it != double_variables.end()) {
            double_variables[name] = double_var_it->second;
            return;
        }
    }  else if (expression.empty()) {
        double_variables[name] = 0.0;
        return;
    }

    try {
        int value = std::stod(expression); // Attempt to convert the expression to an double
        double_variables[name] = value;
    } catch (const std::invalid_argument& ex) {
        throw std::invalid_argument("Invalid double expression: " + expression);
    } catch (const std::out_of_range& ex) {
        throw std::out_of_range("double value out of range: " + expression);
    }  
}

bool Parser::is_double_variable(const std::string& expression)
{
    return double_variables.find(expression) != double_variables.end();
}

void Parser::string_expression_pars(const std::string& name, const std::string& expression)
{
    if (defined_variable(name)) {
        throw std::runtime_error("Redefinition");
    }

    if (expression.size() >= 2 && expression.front() == '"' && expression.back() == '"') {
        // Valid string expression enclosed in double quotes
        std::string value = expression.substr(1, expression.size() - 2);
        string_variables[name] = value;
    } else if (is_string_variable(expression)) {
        // Expression is a reference to an existing string variable
        auto string_var_it = string_variables.find(expression);
        if (string_var_it != string_variables.end()) {
            string_variables[name] = string_var_it->second;
        }
    } else if (expression.empty()) {
        string_variables[name] = " ";
    } else {
        // Invalid string expression
        throw std::invalid_argument("Invalid string expression: " + expression);
    }
}

bool Parser::is_string_variable(const std::string& expression)
{
    return string_variables.find(expression) != string_variables.end();
}

bool Parser::is_number(const std::string& expression)
{
    if (expression.empty()) {
        return false; // Empty string is not a number
    }

    for (char ch : expression) {
        if (ch < '0' || ch > '9') {
            return false; // Non-digit character found
        }
    }

    return true; // All characters are digits
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

            if (is_variable_definition(line, address)) {
                std::cout << "yes" << std::endl;
                parse_variable_definition(line, address);
            }

            if (is_assignment_expression(line, address)) {
                parse_expression(line, address);
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

bool Parser::is_variable_definition(const std::string& line, int address)
{
    std::string op1;
    std::string assignment;
    std::string op2;
    std::string st1;
    std::string st2;

    std::istringstream iss(line);
    iss >> op1 >> assignment >> op2 >> st1 >> st2;

    if (defined_variable(op1) && !assignment.empty() && !op2.empty() && st1.empty() && st2.empty()) {
        if (line[line.size() - 1] != ';') {
            throw std::runtime_error("You forgot the ; in the following line:");
        }
        return true;
    } else if (!defined_variable(op1) && !assignment.empty() && !op2.empty() && st1.empty() && st2.empty()) {
        throw std::runtime_error("Not declare variable " + op1);
    }
    return false;
}

bool Parser::is_assignment_expression(const std::string& line, int address)
{
    std::string op1;
    std::string assignment;
    std::string op2;
    std::string extra_token1;
    std::string extra_token2;

    std::istringstream iss(line);
    iss >> op1 >> assignment >> op2 >> extra_token1 >> extra_token2;

    if (defined_variable(op1) && !assignment.empty() && !op2.empty() && !extra_token1.empty() && !extra_token2.empty()) {
        if (line[line.size() - 1] != ';') {
            throw std::runtime_error("You forgot the ; in the following line: " + address);
        }
        return true;
    }
    return false;
}

// x = y + z, x += y + z, x -= y + z
void Parser::parse_expression(const std::string& line, int address)
{
    std::string op1;
    std::string some_operator1;
    std::string op2;
    std::string some_operator2;
    std::string op3;

    std::istringstream iss(line);
    iss >> op1 >> some_operator1 >> op2 >> some_operator2 >> op3;
    op3.erase(std::remove(op3.begin(), op3.end(), ';'), op3.end());
    
    if (some_operator1 == "=") {
        parse_assignment_expression(op1, op2, some_operator2, op3);
    }
}

void Parser::parse_assignment_expression(const std::string& op1, const std::string& op2, const std::string& some_operator, const std::string& op3)
{
    if (is_int_variable(op1)) {
        if (some_operator == "+") {
            handle_int_addition(op1, op2, op3);
        } else if (some_operator == "-") {
            handle_int_subtraction(op1, op2, op3);
        } else if (some_operator == "*") {
            handle_int_multiplication(op1, op2, op3);
        } else if (some_operator == "/") {
            handle_int_division(op1, op2, op3);
        }
    }
}

void Parser::handle_int_addition(const std::string& op1, const std::string& op2, const std::string& op3)
{
    if (is_int_variable(op2) && is_int_variable(op3)) {
        int_variables[op1] = int_variables[op2] + int_variables[op3];
    } else if (is_int_variable(op2) && is_number(op3)) {
        int_variables[op1] = int_variables[op2] + std::stoi(op3);
    } else if (is_number(op2) && is_number(op3)) {
        int_variables[op1] = std::stoi(op2) + std::stoi(op3);
    } else if (is_number(op2) && is_int_variable(op3)) {
        int_variables[op1] = std::stoi(op2) + int_variables[op3];
    } 
}

void Parser::handle_int_subtraction(const std::string& op1, const std::string& op2, const std::string& op3)
{
    if (is_int_variable(op2) && is_int_variable(op3)) {
        int_variables[op1] = int_variables[op2] - int_variables[op3];
    } else if (is_int_variable(op2) && is_number(op3)) {
        int_variables[op1] = int_variables[op2] - std::stoi(op3);
    } else if (is_number(op2) && is_number(op3)) {
        int_variables[op1] = std::stoi(op2) - std::stoi(op3);
    } else if (is_number(op2) && is_int_variable(op3)) {
        int_variables[op1] = std::stoi(op2) - int_variables[op3];
    } 
}

void Parser::handle_int_multiplication(const std::string& op1, const std::string& op2, const std::string& op3)
{
    if (is_int_variable(op2) && is_int_variable(op3)) {
        int_variables[op1] = int_variables[op2] * int_variables[op3];
    } else if (is_int_variable(op2) && is_number(op3)) {
        int_variables[op1] = int_variables[op2] * std::stoi(op3);
    } else if (is_number(op2) && is_number(op3)) {
        int_variables[op1] = std::stoi(op2) * std::stoi(op3);
    } else if (is_number(op2) && is_int_variable(op3)) {
        int_variables[op1] = std::stoi(op2) * int_variables[op3];
    } 
}

void Parser::handle_int_division(const std::string& op1, const std::string& op2, const std::string& op3)
{
    if (is_int_variable(op2) && is_int_variable(op3)) {
        int_variables[op1] = int_variables[op2] / int_variables[op3];
    } else if (is_int_variable(op2) && is_number(op3)) {
        int_variables[op1] = int_variables[op2] / std::stoi(op3);
    } else if (is_number(op2) && is_number(op3)) {
        int_variables[op1] = std::stoi(op2) / std::stoi(op3);
    } else if (is_number(op2) && is_int_variable(op3)) {
        int_variables[op1] = std::stoi(op2) / int_variables[op3];
    } 
}

void Parser::parse_variable_definition(const std::string& line, int address)
{
    std::string op1;
    std::string assignment;
    std::string op2;

    std::istringstream iss(line);
    iss >> op1 >> assignment >> op2; 
    op2.erase(std::remove(op2.begin(), op2.end(), ';'), op2.end());

    if (assignment == "=") {
       assignment_operator_pars(op1, op2);
    } else if (assignment == "+=") {
        plus_assignment_operator_pars(op1, op2);
    }
}

void Parser::plus_assignment_operator_pars(const std::string& op1, const std::string& op2)
{
    if (is_int_variable(op1)) {
        if (is_int_variable(op2)) {
            int_variables[op1] += int_variables[op2];
        } else if (is_number(op2)) {
            int_variables[op1] += std::stoi(op2);
        } else if (is_char_variable(op2)) {
            int_variables[op1] += char_variables[op2];
        }
    } else if (is_bool_variable(op1)) {
        if (is_bool_variable(op2)) {
            bool_variables[op1] = bool_variables[op2];
        } else if (is_number(op2)) {
            bool_variables[op1] = 1;
        }
    } else if (is_double_variable(op1)) {
        if (is_double_variable(op2)) {
            double_variables[op1] += double_variables[op2];
        } else if (is_number(op2)) {
            double_variables[op1] += std::stod(op2);
        } else if (is_double_literal(op2)) {
            double_variables[op1] += std::stod(op2);
        }
    } else if (is_float_variable(op1)) {
        if (is_float_variable(op2)) {
            float_variables[op1] += float_variables[op2];
        } else if (is_number(op2)) {
            float_variables[op1] += std::stof(op2);
        }
    } else if (is_char_variable(op1)) {
        if (is_char_variable(op2)) {
            char_variables[op1] += char_variables[op2];
        }
    } else {
        throw std::runtime_error("Not declare variable");
    }
}

void Parser::minus_assignment_operator_pars(const std::string& op1, const std::string& op2)
{
    if (is_int_variable(op1)) {
        if (is_int_variable(op2)) {
            int_variables[op1] -= int_variables[op2];
        } else if (is_number(op2)) {
            int_variables[op1] -= std::stoi(op2);
        } else if (is_char_variable(op2)) {
            int_variables[op1] -= char_variables[op2];
        }
    } else if (is_bool_variable(op1)) {
        if (is_bool_variable(op2)) {
            bool_variables[op1] = bool_variables[op2];
        } else if (is_number(op2)) {
            bool_variables[op1] = 1;
        }
    } else if (is_double_variable(op1)) {
        if (is_double_variable(op2)) {
            double_variables[op1] -= double_variables[op2];
        } else if (is_number(op2)) {
            double_variables[op1] -= std::stod(op2);
        } else if (is_double_literal(op2)) {
            double_variables[op1] -= std::stod(op2);
        }
    } else if (is_float_variable(op1)) {
        if (is_float_variable(op2)) {
            float_variables[op1] -= float_variables[op2];
        } else if (is_number(op2)) {
            float_variables[op1] -= std::stof(op2);
        }
    } else if (is_char_variable(op1)) {
        if (is_char_variable(op2)) {
            char_variables[op1] -= char_variables[op2];
        }
    } else {
        throw std::runtime_error("Not declare variable");
    }
}

void Parser::assignment_operator_pars(const std::string& op1, const std::string& op2)
{
    if (is_int_variable(op1)) {
        if (is_int_variable(op2)) {
            int_variables[op1] = int_variables[op2];
        } else if (is_number(op2)) {
            int_variables[op1] = std::stoi(op2);
        } else if (is_char_variable(op2)) {
            int_variables[op1] = char_variables[op2];
        }
    } else if (is_bool_variable(op1)) {
        if (is_bool_variable(op2)) {
            bool_variables[op1] = bool_variables[op2];
        } else if (is_number(op2)) {
            bool_variables[op1] = 1;
        }
    } else if (is_double_variable(op1)) {
        if (is_double_variable(op2)) {
            double_variables[op1] = double_variables[op2];
        } else if (is_number(op2)) {
            double_variables[op1] = std::stod(op2);
        } else if (is_double_literal(op2)) {
            double_variables[op1] = std::stod(op2);
        }
    } else if (is_float_variable(op1)) {
        if (is_float_variable(op2)) {
            float_variables[op1] = float_variables[op2];
        } else if (is_number(op2)) {
            float_variables[op1] = std::stof(op2);
        }
    } else if (is_char_variable(op1)) {
        if (is_char_variable(op2)) {
            char_variables[op1] = char_variables[op2];
        }
    } else {
        throw std::runtime_error("Not declare variable");
    }
}

bool Parser::is_double_literal(const std::string& expression)
{
    try {
        // Attempt to convert the string to a double
        double value = std::stod(expression);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

bool Parser::defined_variable(const std::string& name)
{
    return (is_bool_variable(name) || is_char_variable(name) || is_int_variable(name) || is_float_variable(name) || is_double_variable(name) || is_string_variable(name));
}