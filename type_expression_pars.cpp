#include "parser.hpp"

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