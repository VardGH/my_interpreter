#include "parser.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

// Parses a line of code to check for the presence of iostream
void Parser::parse_iostream(const std::string& line, bool& found_iostream)
{
    if (is_iostream(line)) {
        found_iostream = true;
    } else {
        throw std::runtime_error("Missing #include <iostream>");
    }
}

// Parses a line of code to identify the presence of the main function
void Parser::parse_main(const std::string& line, bool& found_main)
{
    if (is_main(line)) {
        found_main = true;
    } else {
        throw std::runtime_error("Line does not contain int main() {");
    }
}

// Parse expression x = y + z
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

// Parse and calculate 
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

// If variable id defined we can =, +=, -=, /=, *=
void Parser::parse_variable_definition(const std::string& line, int address)
{
    std::string op1;
    std::string assignment;
    std::string op2;

    std::istringstream iss(line);
    iss >> op1 >> assignment >> op2; 
    op2.erase(std::remove(op2.begin(), op2.end(), ';'), op2.end());

    if (assignment == "=") {
       assignment_operator_parse(op1, op2);
    } else if (assignment == "+=") {
        plus_assignment_operator_parse(op1, op2);
    } else if (assignment == "-=") {
        minus_assignment_operator_parse(op1, op2);
    } else if (assignment == "*=") {
        mul_assignment_operator_parse(op1, op2);
    } else if (assignment == "/=") {
        div_assignment_operator_parse(op1, op2);
    }
}

// Parses a variable declaration from the given code line
void Parser::parse_variable_declaration(std::string& line, int address)
{
    line.erase(std::remove(line.begin(), line.end(), ';'), line.end());

    std::istringstream iss(line);
    std::string type {};
    std::string name {};
    std::string assignment {};
    std::string expression {};

    iss >> type >> name >> assignment >> expression;

    // will be deleted
    // std::cout << "type: " << type << std::endl;
    // std::cout << "name: " << name << std::endl;
    // std::cout << "assignment: " << assignment << std::endl;
    // std::cout << "expression: " << expression << std::endl;
    // std::cout << std::endl;

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

void Parser::increment_expression_parse(std::string& expression)
{
    if (expression.back() != ';') {
        throw std::runtime_error("You forgot the ; in the following line:");
    }

    expression.erase(std::remove(expression.begin(), expression.end(), ';'), expression.end());

    if (is_int_variable(expression)) {
        ++int_variables[expression];
    } else if (is_bool_variable(expression)) {
        std::cout << "!" << std::endl;
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

// decrement expression
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