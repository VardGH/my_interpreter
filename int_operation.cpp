#include "parser.hpp"

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