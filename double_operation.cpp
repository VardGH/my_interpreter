#include "parser.hpp"

void Parser::handle_double_addition(const std::string& op1, const std::string& op2, const std::string& op3)
{
    if (is_double_variable(op2) && is_double_variable(op3)) {
        double_variables[op1] = double_variables[op2] + double_variables[op3];
    } else if (is_double_variable(op2) && is_double_literal(op3)) {
        double_variables[op1] = double_variables[op2] + std::stod(op3);
    } else if (is_double_literal(op2) && is_double_literal(op3)) {
        double_variables[op1] = std::stod(op2) + std::stod(op3);
    } else if (is_double_literal(op2) && is_double_variable(op3)) {
        double_variables[op1] = std::stod(op2) + double_variables[op3];
    } 
}

void Parser::handle_double_subtraction(const std::string& op1, const std::string& op2, const std::string& op3)
{
    if (is_double_variable(op2) && is_double_variable(op3)) {
        double_variables[op1] = double_variables[op2] - double_variables[op3];
    } else if (is_double_variable(op2) && is_double_literal(op3)) {
        double_variables[op1] = double_variables[op2] - std::stod(op3);
    } else if (is_double_literal(op2) && is_double_literal(op3)) {
        double_variables[op1] = std::stod(op2) - std::stod(op3);
    } else if (is_double_literal(op2) && is_double_variable(op3)) {
        double_variables[op1] = std::stod(op2) - double_variables[op3];
    }   
}

void Parser::handle_double_multiplication(const std::string& op1, const std::string& op2, const std::string& op3)
{
    if (is_double_variable(op2) && is_double_variable(op3)) {
        double_variables[op1] = double_variables[op2] * double_variables[op3];
    } else if (is_double_variable(op2) && is_double_literal(op3)) {
        double_variables[op1] = double_variables[op2] * std::stod(op3);
    } else if (is_double_literal(op2) && is_double_literal(op3)) {
        double_variables[op1] = std::stod(op2) * std::stod(op3);
    } else if (is_double_literal(op2) && is_double_variable(op3)) {
        double_variables[op1] = std::stod(op2) * double_variables[op3];
    }   
}

void Parser::handle_double_division(const std::string& op1, const std::string& op2, const std::string& op3)
{
    if (is_double_variable(op2) && is_double_variable(op3)) {
        double_variables[op1] = double_variables[op2] / double_variables[op3];
    } else if (is_double_variable(op2) && is_double_literal(op3)) {
        double_variables[op1] = double_variables[op2] / std::stod(op3);
    } else if (is_double_literal(op2) && is_double_literal(op3)) {
        double_variables[op1] = std::stod(op2) / std::stod(op3);
    } else if (is_double_literal(op2) && is_double_variable(op3)) {
        double_variables[op1] = std::stod(op2) / double_variables[op3];
    }   
}