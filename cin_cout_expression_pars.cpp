#include "parser.hpp"
#include <iostream>
#include <algorithm>

// Checks if the given expression is a valid std::cout expression
bool Parser::is_cout_expression(const std::string& op1, const std::string& assignment, const std::string& op2, const std::string& st1, const std::string& st2)
{
    if (op1 == "std::cout" && assignment == "<<" && !op2.empty() && st1.empty() && st2.empty()) {
        return true;
    } else if (op1 == "std::cout" && assignment != "<<" && !op2.empty() && st1.empty() && st2.empty()) {
        throw std::runtime_error("Wrong operator: " + m_input);
    }
    return false;
}

// Checks if the given expression is a valid std::cin expression
bool Parser::is_cin_expression(const std::string& op1, const std::string& assignment, const std::string& op2, const std::string& st1, const std::string& st2)
{
    if (op1 == "std::cin" && assignment == ">>" && !op2.empty() && st1.empty() && st2.empty()) {
        return true;
    } else if (op1 == "std::cin" && assignment != "<<" && !op2.empty() && st1.empty() && st2.empty()) {
        throw std::runtime_error("Wrong operator: " + m_input);
    }
    return false;
}

// Parses and handles std::cin expressions
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
    }
    else if (is_array_manipulation(expression)) {
        //std::cout << "expression| " << std::endl;
        std::string array_name {};
        std::string index {};
        extract_array_components(expression, array_name, index);

        int id = get_value<int>(index);
        if (is_int_array(array_name)) {
            int i {};
            std::cin >> i;
            const auto array = int_array[array_name];
            int_array[array_name][id] = i;
        } else if (is_double_array(array_name)) {
            double i {};
            std::cin >> i;
            const auto array = double_array[array_name];
            double_array[array_name][id] = i;
        } else if (is_char_array(array_name)) {
            char i {};
            std::cin >> i;
            const auto array = char_array[array_name];
            char_array[array_name][id] = i;
        } else if (is_bool_array(array_name)) {
            bool i {};
            std::cin >> i;
            const auto array = bool_array[array_name];
            bool_array[array_name][id] = i;
        } else if (is_string_array(array_name)) {
            std::string i {};
            std::cin >> i;
            const auto array = string_array[array_name];
            string_array[array_name][id] = i;
        } else if (is_float_array(array_name)) {
            float i {};
            std::cin >> i;
            const auto array = float_array[array_name];
            float_array[array_name][id] = i;
        }
    } 
    else {
        throw std::runtime_error("Variable " + expression + " is not defined.");
    }
}

// Parses and handles std::cout expressions
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
    } else if (is_array_manipulation(expression)) {
        std::string array_name {};
        std::string index {};
        extract_array_components(expression, array_name, index);

        int id = get_value<int>(index);
        if (is_int_array(array_name)) {
            const auto array = int_array[array_name];
            std::cout << array[id] << std::endl;
        } else if (is_double_array(array_name)) {
            const auto array = double_array[array_name];
            std::cout << array[id] << std::endl;
        } else if (is_char_array(array_name)) {
            const auto array = char_array[array_name];
            std::cout << array[id] << std::endl;
        } else if (is_bool_array(array_name)) {
            const auto array = bool_array[array_name];
            std::cout << array[id] << std::endl;
        } else if (is_string_array(array_name)) {
            const auto array = string_array[array_name];
            std::cout << array[id] << std::endl;
        }
    } 
    else {
        throw std::runtime_error("Variable " + expression + " is not defined.");
    }
 }