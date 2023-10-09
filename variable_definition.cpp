#include "parser.hpp"

// parse operator+= 
void Parser::plus_assignment_operator_parse(const std::string& op1, const std::string& op2)
{
    if (is_int_variable(op1)) {
        int_variables[op1] += get_value<int>(op2);
    } else if (is_bool_variable(op1)) {
        bool_variables[op1] += get_value<bool>(op2);
    } else if (is_double_variable(op1)) {
        double_variables[op1] += get_value<double>(op2);
    } else if (is_float_variable(op1)) {
        double_variables[op1] += get_value<double>(op2);
    } else if (is_char_variable(op1)) {
        char_variables[op1] += get_value<char>(op2);
    } else {
        throw std::runtime_error("Not declare variable");
    }
}

// parse operator-= 
void Parser::minus_assignment_operator_parse(const std::string& op1, const std::string& op2)
{
    if (is_int_variable(op1)) {
        int_variables[op1] -= get_value<int>(op2);
    } else if (is_bool_variable(op1)) {
        bool_variables[op1] -= get_value<bool>(op2);
    } else if (is_double_variable(op1)) {
        double_variables[op1] -= get_value<double>(op2);
    } else if (is_float_variable(op1)) {
        double_variables[op1] -= get_value<double>(op2);
    } else if (is_char_variable(op1)) {
        char_variables[op1] -= get_value<char>(op2);
    } else {
        throw std::runtime_error("Not declare variable");
    }
}

// parse operator=
void Parser::assignment_operator_parse(const std::string& op1, const std::string& op2)
{
    if (is_int_variable(op1)) {
        int_variables[op1] = get_value<int>(op2);
    }  else if (is_bool_variable(op1)) {
        if (is_bool_variable(op2)) {
            bool_variables[op1] = bool_variables[op2];
        } else if (is_number(op2)) {
            bool_variables[op1] = 1;
        } else if (op2 == "true") {
            bool_variables[op1] = 1;
        } else if (op2 == "false") {
            bool_variables[op1] = 0;
        }
    } else if (is_double_variable(op1)) {
        double_variables[op1] = get_value<double>(op2);
    } else if (is_float_variable(op1)) {
        double_variables[op1] = get_value<double>(op2);
    } else if (is_char_variable(op1)) {
        char_variables[op1] = get_value<char>(op2);
    } else if (is_string_variable(op1)) {
        if (is_string_variable(op2)) {
            string_variables[op1] = string_variables[op2];
        } else if (is_string_literal(op2)) {
            string_variables[op1] = get_string(op2);
        }
    } else {
        throw std::runtime_error("Not declare variable");
    }
}

// parse operator *= 
void Parser::mul_assignment_operator_parse(const std::string& op1, const std::string& op2)
{
    if (is_int_variable(op1)) {
        int_variables[op1] *= get_value<int>(op2);
    } else if (is_bool_variable(op1)) {
        bool_variables[op1] *= get_value<bool>(op2);
    } else if (is_double_variable(op1)) {
        double_variables[op1] *= get_value<double>(op2);
    } else if (is_float_variable(op1)) {
        double_variables[op1] *= get_value<double>(op2);
    } else if (is_char_variable(op1)) {
        char_variables[op1] *= get_value<char>(op2);
    } else {
        throw std::runtime_error("Not declare variable");
    }
}

// parse operator /= 
void Parser::div_assignment_operator_parse(const std::string& op1, const std::string& op2)
{
    if (is_int_variable(op1)) {
        int_variables[op1] /= get_value<int>(op2);
    } else if (is_bool_variable(op1)) {
        bool_variables[op1] /= get_value<bool>(op2);
    } else if (is_double_variable(op1)) {
        double_variables[op1] /= get_value<double>(op2);
    } else if (is_float_variable(op1)) {
        double_variables[op1] /= get_value<double>(op2);
    } else if (is_char_variable(op1)) {
        char_variables[op1] /= get_value<char>(op2);
    } else {
        throw std::runtime_error("Not declare variable");
    }
}