#include "parser.hpp"

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
        } else if (op2 == "true") {
            bool_variables[op1] = 1;
        } else if (op2 == "false") {
            bool_variables[op1] = 0;
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