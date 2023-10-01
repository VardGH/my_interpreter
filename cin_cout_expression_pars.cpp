#include "parser.hpp"
#include <iostream>
#include <algorithm>

bool Parser::is_cout_expression(const std::string& op1, const std::string& assignment, const std::string& op2, const std::string& st1, const std::string& st2)
{
    if (op1 == "std::cout" && assignment == "<<" && !op2.empty() && st1.empty() && st2.empty()) {
        return true;
    } else if (op1 == "std::cout" && assignment != "<<" && !op2.empty() && st1.empty() && st2.empty()) {
        throw std::runtime_error("Wrong operator: " + m_input);
    }
    return false;
}

bool Parser::is_cin_expression(const std::string& op1, const std::string& assignment, const std::string& op2, const std::string& st1, const std::string& st2)
{
    if (op1 == "std::cin" && assignment == ">>" && !op2.empty() && st1.empty() && st2.empty()) {
        return true;
    } else if (op1 == "std::cin" && assignment != "<<" && !op2.empty() && st1.empty() && st2.empty()) {
        throw std::runtime_error("Wrong operator: " + m_input);
    }
    return false;
}

void Parser::cin_expression_parse(std::string& expression)
{
    if (expression.back() != ';') {
        throw std::runtime_error("You forgot the ; in the following line:");
    }

    expression.erase(std::remove(expression.begin(), expression.end(), ';'), expression.end());

    if (is_int_variable(expression)) {
        int a {};
        std::cin >> a;
        int_variables[expression] = a;
    } else if (is_char_variable(expression)) {
        char c {};
        std::cin >> c;
        char_variables[expression] = c;
    } else if (is_double_variable(expression)) {
        double d {};
        std::cin >> d;
        double_variables[expression] = d;
    } else if (is_float_variable(expression)) {
        float f {};
        std::cin >> f;
        float_variables[expression] = f;
    } else {
        throw std::runtime_error("Variable " + expression + " is not defined.");
    }
}

void Parser::cout_expression_parse(std::string& expression)
{
    if (expression.back() != ';') {
        throw std::runtime_error("You forgot the ; in the following line:");
    }

    expression.erase(std::remove(expression.begin(), expression.end(), ';'), expression.end());

    if (expression.front() == '\"' && expression.back() == '\"') {
        expression.erase(0, 1);
        expression.pop_back();
        std::cout << expression << std::endl;
    } else if (is_int_variable(expression)) {
        std::cout << int_variables[expression] << std::endl;
    } else if (is_bool_variable(expression)) {
        std::cout << bool_variables[expression] << std::endl;
    } else if (is_char_variable(expression)) {
        std::cout << char_variables[expression] << std::endl;
    } else if (is_double_variable(expression)) {
        std::cout << double_variables[expression] << std::endl;
    } else if (is_float_variable(expression)) {
        std::cout << float_variables[expression] << std::endl;
    } else if (is_string_variable(expression)) {
        std::cout << string_variables[expression] << std::endl;
    } else {
        throw std::runtime_error("Variable " + expression + " is not defined.");
    }
 }