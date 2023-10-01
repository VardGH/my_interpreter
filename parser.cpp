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
        throw std::runtime_error("You forgot the ; in the following line:" + address);
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

bool Parser::is_bool_variable(const std::string& expression)
{
    return bool_variables.find(expression) != bool_variables.end();
}

bool Parser::is_char_variable(const std::string& expression)
{
    return char_variables.find(expression) != char_variables.end();
}

bool Parser::is_int_variable(const std::string& expression)
{
    return int_variables.find(expression) != int_variables.end();
}

bool Parser::is_float_variable(const std::string& expression)
{
    return float_variables.find(expression) != float_variables.end();
}

bool Parser::is_double_variable(const std::string& expression)
{
    return double_variables.find(expression) != double_variables.end();
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
            throw std::runtime_error("You forgot the ; in the following line:" + address);
        }
        return true;
    } 
    else if (!defined_variable(op1) && !assignment.empty() && !op2.empty() && st1.empty() && st2.empty()) {
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

// x = y + z
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
            int_variables[op1] = get_value<int>(op2) + get_value<int>(op3);
        } else if (some_operator == "-") {
            int_variables[op1] = get_value<int>(op2) - get_value<int>(op3);
        } else if (some_operator == "*") {
            int_variables[op1] = get_value<int>(op2) * get_value<int>(op3);
        } else if (some_operator == "/") {
            int_variables[op1] = get_value<int>(op2) / get_value<int>(op3);
        }
    } else if (is_double_variable(op1)) {
        if (some_operator == "+") {
            double_variables[op1] = get_value<double>(op2) + get_value<double>(op3);
        } else if (some_operator == "-") {
            double_variables[op1] = get_value<double>(op2) - get_value<double>(op3);
        } else if (some_operator == "*") {
            double_variables[op1] = get_value<double>(op2) * get_value<double>(op3);
        } else if (some_operator == "/") {
            double_variables[op1] = get_value<double>(op2) / get_value<double>(op3);
        }
    } else if (is_char_variable(op1)) {
        if (some_operator == "+") {
            char_variables[op1] = get_value<char>(op2) + get_value<char>(op3);
        } else if (some_operator == "-") {
            char_variables[op1] = get_value<char>(op2) - get_value<char>(op3);
        } else if (some_operator == "*") {
            char_variables[op1] = get_value<char>(op2) * get_value<char>(op3);
        } else if (some_operator == "/") {
            char_variables[op1] = get_value<char>(op2) / get_value<char>(op3);
        }
    } else if (is_float_variable(op1)) {
        if (some_operator == "+") {
            float_variables[op1] = get_value<float>(op2) + get_value<float>(op3);
        } else if (some_operator == "-") {
            float_variables[op1] = get_value<float>(op2) - get_value<float>(op3);
        } else if (some_operator == "*") {
            float_variables[op1] = get_value<float>(op2) * get_value<float>(op3);
        } else if (some_operator == "/") {
            float_variables[op1] = get_value<float>(op2) / get_value<float>(op3);
        }
    } 
    // else if (is_string_variable(op1)) {
    //     std::cout << "////////" << std::endl;
    //     if (some_operator == "+") {
    //         std::cout << "////////" << std::endl;
    //         string_variables[op1] = string_variables[op2] + string_variables[op3];
    //     }
    // }
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
    } else if (assignment == "-=") {
        minus_assignment_operator_pars(op1, op2);
    } else if (assignment == "*=") {
        mul_assignment_operator_pars(op1, op2);
    } else if (assignment == "/=") {
        div_assignment_operator_pars(op1, op2);
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

bool Parser::is_char_literal(const std::string& expression)
{
    return (expression.size() == 3 && expression.front() == '\'' && expression.back() == '\'');
}

void Parser::parse()
{
    int address = 1;
    bool found_iostream = false;
    bool found_main = false;

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
            }

            if (!found_main && found_iostream) {
                parse_main(trimmed_line, address, found_main);
                ++address;
                continue;
            }

            if (is_variable_declaration(trimmed_line, address)) {
                parse_variable_declaration(trimmed_line, address);
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
            std::cout << "address: " << address << std::endl;
    
            ++address;
        }
    } catch (const std::exception& e) {
        std::cerr << address << "-> Error: " << e.what() << std::endl;
        exit(0);
    }
}


 bool Parser::is_increment_expression(const std::string& op1, const std::string& op2, const std::string& op3, const std::string& op4, const std::string& op5)
 {
    if (op1 == "++" && !op2.empty() && op3.empty() && op4.empty() && op5.empty()) {
        return true;
    } else if (op1 == "++" && op2.empty() && op3.empty() && op4.empty() && op5.empty()) {
        throw std::runtime_error("Wrong increment_expression");
    }
    return false;
 }

 void Parser::increment_expression_parse(std::string& expression)
{
    if (expression.back() != ';') {
        throw std::runtime_error("You forgot the ; in the following line:");
    }

    expression.erase(std::remove(expression.begin(), expression.end(), ';'), expression.end());

    if (is_int_variable(expression)) {
        ++int_variables[expression];
    } else if (is_bool_variable(expression)) {
        std::cout << "lav ban ches anum" << std::endl;
    } else if (is_char_variable(expression)) {
        ++char_variables[expression];
    } else if (is_double_variable(expression)) {
        ++double_variables[expression];
    } else if (is_float_variable(expression)) {
        ++float_variables[expression];
    } else {
        throw std::runtime_error("Variable " + expression + " is not defined.");
    }
 }

  bool Parser::is_decrement_expression(const std::string& op1, const std::string& op2, const std::string& op3, const std::string& op4, const std::string& op5)
 {
    if (op1 == "--" && !op2.empty() && op3.empty() && op4.empty() && op5.empty()) {
        return true;
    } else if (op1 == "--" && op2.empty() && op3.empty() && op4.empty() && op5.empty()) {
        throw std::runtime_error("Wrong decrement_expression");
    }
    return false;
 }

 void Parser::decrement_expression_parse(std::string& expression)
{
    if (expression.back() != ';') {
        throw std::runtime_error("You forgot the ; in the following line:");
    }

    expression.erase(std::remove(expression.begin(), expression.end(), ';'), expression.end());

    if (is_int_variable(expression)) {
        --int_variables[expression];
    } else if (is_bool_variable(expression)) {
        throw std::runtime_error("You can't use the -- operator directly on a bool");
    } else if (is_char_variable(expression)) {
        --char_variables[expression];
    } else if (is_double_variable(expression)) {
        --double_variables[expression];
    } else if (is_float_variable(expression)) {
        --float_variables[expression];
    } else {
        throw std::runtime_error("Variable " + expression + " is not defined.");
    }
 }

 bool Parser::is_if_expression(const std::string& line)
 {
    return (line.find("if ") == 0);
 }

// read from file 
void Parser::load_from_file(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::string line {};
    int address = 0;
    std::stack<int> if_starts;  // Stack for "if" statements
    std::stack<int> while_starts;  // Stack for "while" statements

    while (std::getline(file, line)) {
        ++address;
        line = trim(line);

        // Check for "if" statements
        if (line.find("if ") == 0) {
            if_starts.push(address);
        }

        // Check for "while" statements
        if (line.find("while ") == 0) {
            while_starts.push(address);
        }

        // Process closing curly braces
        if (line == "}") {
            if (!if_starts.empty()) {
                int start_address = if_starts.top();
                if_starts.pop();
                if_map[start_address] = std::make_pair(start_address, address);
            }

            if (!while_starts.empty()) {
                int start_address = while_starts.top();
                while_starts.pop();
                while_map[start_address] = std::make_pair(start_address, address);
            }
        }

        full_memory[address] = line;
    }

    file.close();

    // Print the if_map for verification
    for (const auto& entry : if_map) {
        int if_id = entry.first;
        int start_address = entry.second.first;
        int end_address = entry.second.second;

        std::cout << "If statement " << if_id << ": Start Address = " << start_address
                  << ", End Address = " << end_address << std::endl;
    }

    // Print the while_map for verification
    for (const auto& entry : while_map) {
        int while_id = entry.first;
        int start_address = entry.second.first;
        int end_address = entry.second.second;

        std::cout << "While statement " << while_id << ": Start Address = " << start_address
                  << ", End Address = " << end_address << std::endl;
    }
}