#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Ctor
Parser::Parser(const std::string& input)
    : m_input{input}
{
}

// Trimming whitespace
std::string Parser::trim(const std::string& str) 
{
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

// Checks if the given line of code represents a variable declaration
bool Parser::is_variable_declaration(std::string& line, int address)
{
    //std::cout << "declaration" << std::endl;
    // std::cout << line << std::endl;
    // Check if the line starts with one of the data types
    const std::vector<std::string> data_types = {"char", "bool", "int", "float", "double", "string"};

    int is_type = false;
    for (const std::string& data_type : data_types) {
        if (line.find(data_type) == 0) {
            is_type = true;

            size_t pos1 = line.find('[');
            size_t pos2 = line.find(']');

            if (pos1 != std::string::npos || pos2 != std::string::npos) {
                is_type = false;
            }
        }
    }

    // Check if the line ends with a semicolon
    if (is_type && line[line.size() - 1] != ';') {
        throw std::runtime_error("You forgot the ; in the following linee:" + address);
    }
    return is_type;
}

// Saves a variable or expression to memory(maps)
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

// Checks if the given expression represents a boolean variable
bool Parser::is_bool_variable(const std::string& expression)
{
    return bool_variables.find(expression) != bool_variables.end();
}

// Checks if the given expression represents a char variable
bool Parser::is_char_variable(const std::string& expression)
{
    return char_variables.find(expression) != char_variables.end();
}

// Checks if the given expression represents an int variable
bool Parser::is_int_variable(const std::string& expression)
{
    return int_variables.find(expression) != int_variables.end();
}

// Checks if the given expression represents a float variable
bool Parser::is_float_variable(const std::string& expression)
{
    return float_variables.find(expression) != float_variables.end();
}

// Checks if the given expression represents a double variable
bool Parser::is_double_variable(const std::string& expression)
{
    return double_variables.find(expression) != double_variables.end();
}

// Checks if the given expression represents a string variable
bool Parser::is_string_variable(const std::string& expression)
{
    return string_variables.find(expression) != string_variables.end();
}

// Checks if the given expression represents a number(literal)
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

std::string Parser::get_string(const std::string& expression)
{
    std::string tmp = expression;
    tmp = tmp.substr(1);
    tmp.pop_back();
    return tmp;
}

// Checks if the given expression represents a bool literal
bool Parser::is_bool_literal(const std::string& expression)
{
    if (expression == "true" || expression == "false") {
        return true;
    }
    return false;
}

// Checks if the given expression represents a bool literal
bool Parser::is_string_literal(const std::string& expression) 
{
    // Check if the string is enclosed in double quotes
    if (expression.size() >= 2 && expression.front() == '"' && expression.back() == '"') {
        return true;
    } else if (expression.size() >= 2 && expression.front() == '"' && expression.back() != '"') {
        throw std::runtime_error("You forgot the '\"'");
    } else if (expression.size() >= 2 && expression.front() != '"' && expression.back() == '"') {
        throw std::runtime_error("You forgot the '\"'");
    }
    return false;
}

// Checks if the given code line contains references to the iostream library
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

// Checks if the given code line contains the main function.
bool Parser::is_main(const std::string& line)
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

// Check lines
bool Parser::is_valid_line(const std::string& line, int address)
{
    std::string op1 {};
    std::string assignment {};
    std::string op2 {};
    std::string st1 {};
    std::string st2 {};

    std::istringstream iss(line);
    iss >> op1 >> assignment >> op2 >> st1 >> st2;

    if (is_cout_expression(op1, assignment, op2, st1, st2)) {
        cout_expression_parse(op2);
    } else if (is_cin_expression(op1, assignment, op2, st1, st2)) {
        cin_expression_parse(op2);
    } else if (is_increment_expression(op1, assignment, op2, st1, st2)) {
        increment_expression_parse(assignment);
    } else if (is_decrement_expression(op1, assignment, op2, st1, st2)) {
        decrement_expression_parse(assignment);
    } else if (defined_variable(op1) && !assignment.empty() && !op2.empty() && st1.empty() && st2.empty()) {
        if (line[line.size() - 1] != ';') {
            throw std::runtime_error("You forgot the ; in the following linel:" + address);
        }
        return true;
    } else if (!defined_variable(op1) && !assignment.empty() && !op2.empty() && st1.empty() && st2.empty()) {
        throw std::runtime_error("Not declare variable " + op1);
    }
    return false;
}

// Check 
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

// // Checks if the given expression represents a double literal
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

// Checks if the given variable name is defined
bool Parser::defined_variable(const std::string& name)
{
    return (is_bool_variable(name) || is_char_variable(name) || is_int_variable(name) || is_float_variable(name) || is_double_variable(name) || is_string_variable(name));
}

// Checks if the given variable name is defined array
bool Parser::defined_array(const std::string& name)
{
    return is_int_array(name) || is_double_array(name) || is_char_array(name) || is_bool_array(name) || is_string_array(name) || is_float_array(name);
}

// Checks if the given expression represents an int array
bool Parser::is_int_array(const std::string& expression)
{
    return int_array.find(expression) != int_array.end();
}

// Checks if the given expression represents an double array
bool Parser::is_double_array(const std::string& expression)
{
    return double_array.find(expression) != double_array.end();
}

// Checks if the given expression represents an double array
bool Parser::is_char_array(const std::string& expression)
{
    return char_array.find(expression) != char_array.end();
}

// Checks if the given expression represents an bool array
bool Parser::is_bool_array(const std::string& expression)
{
    return bool_array.find(expression) != bool_array.end();
}

// Checks if the given expression represents an string array
bool Parser::is_string_array(const std::string& expression)
{
    return string_array.find(expression) != string_array.end();
}

// Checks if the given expression represents an float array
bool Parser::is_float_array(const std::string& expression)
{
    return float_array.find(expression) != float_array.end();
}

// Checks if the given expression represents a character literal
bool Parser::is_char_literal(const std::string& expression)
{
    return (expression.size() == 3 && expression.front() == '\'' && expression.back() == '\'');
}

// Checks if the given code line represents increment expression
bool Parser::is_increment_expression(const std::string& op1, const std::string& op2, const std::string& op3, const std::string& op4, const std::string& op5)
{
    if (op1 == "++" && !op2.empty() && op3.empty() && op4.empty() && op5.empty()) {
        return true;
    } else if (op1 == "++" && op2.empty() && op3.empty() && op4.empty() && op5.empty()) {
        throw std::runtime_error("Wrong increment_expression");
    }
    return false;
}

// Checks if the given code line represents decrement expression
bool Parser::is_decrement_expression(const std::string& op1, const std::string& op2, const std::string& op3, const std::string& op4, const std::string& op5)
{
    if (op1 == "--" && !op2.empty() && op3.empty() && op4.empty() && op5.empty()) {
        return true;
    } else if (op1 == "--" && op2.empty() && op3.empty() && op4.empty() && op5.empty()) {
        throw std::runtime_error("Wrong decrement_expression");
    }
    return false;
}

bool Parser::is_array_manipulation(const std::string& line)
{
    //std::cout << "line: "  << line << std::endl;
    size_t pos1 = line.find('[');
    size_t pos2 = line.find(']');

    // std::cout << std::boolalpha << start_cout(line) << std::endl;

    if (pos1 == std::string::npos || pos2 == std::string::npos || start_cout(line) || start_cin(line) || start_if(line) | start_while(line)) {
        return false;
    }
    return true;
}

// main parse function
void Parser::parse()
{
    int address = 1;
    bool found_iostream = false;
    bool found_main = false;
    bool flag = false; // for the while condition
    std::pair<int, int> while_range;

    try {
        while (address < full_memory.size()) {
            const std::string& line = full_memory[address]; // Access the second element of the pair

            // skip empty lines
            if (line.empty()) {
                ++address;
                continue;
            }

            // remove whitespace
            std::string trimmed_line = trim(line);

            if (!found_iostream) {
                parse_iostream(trimmed_line, found_iostream);
                ++address;
                continue;
            } else if (!found_main && found_iostream) {
                parse_main(trimmed_line, found_main);
                ++address;
                continue;
            }

            if (is_variable_declaration(trimmed_line, address)) {
                parse_variable_declaration(trimmed_line, address);
                // ++address;
                // continue;
            }

            if (is_array_declaration(trimmed_line)) {
                parse_array_statement(trimmed_line);
                ++address;
                continue;
            }

            if (is_array_manipulation(trimmed_line)) {
                parse_array_manipulation(trimmed_line);
                ++address;
                continue;
            }

            if (is_valid_line(trimmed_line, address)) {
                parse_variable_definition(trimmed_line, address);
            } 

            if (is_assignment_expression(trimmed_line, address)) {
                parse_expression(trimmed_line, address);
            } 

            if (is_if_expression(trimmed_line)) {
                parse_if_statement(address, trimmed_line);
            }

            if (is_while_expression(trimmed_line)) {
                std::tuple<std::string, std::string, std::string> operands = parse_while_statement(trimmed_line);
                while_range = execute_while_statement(address, std::get<0>(operands), std::get<1>(operands), std::get<2>(operands), flag);
            }

            if (flag && address == while_range.second) {
                address  = while_range.first - 1;
            }

            if (trimmed_line == "break;") {
                address = while_range.second + 1;
            }

            if (trimmed_line == "continue;") {
                address = while_range.first - 1;
            }
    
            ++address;
        }
    } catch (const std::exception& e) {
        std::cerr << address << "-> Error: " << e.what() << std::endl;
        exit(0);
    }
}