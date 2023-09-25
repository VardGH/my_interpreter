#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <unordered_map>

class Parser
{
public:
    Parser(const std::string& input);
    Parser(const Parser& other) = delete;
    Parser& operator=(const Parser& other) = delete;

    Parser(Parser&& other) = delete;
    Parser& operator=(Parser&& other) = delete;

public:
    void parse();

private:
    std::string trim(const std::string& str);

    bool is_variable_declaration(std::string& line, int address);
    bool is_variable_definition(const std::string& line, int address);

    bool is_iostream(const std::string& line);
    bool is_main(const std::string& line, int address);
    
    void parse_variable_declaration(std::string& line, int address); // int x = 10;
    void parse_variable_definition(const std::string& line, int address); // x = y or x += 10

    void save_memory(const std::string& type, const std::string& type_name, const std::string& expression);
    void parse_main(const std::string& line, int address, bool& found_main);
    void parse_iostream(const std::string& line, bool& found_iostream);
    bool is_number(const std::string& expression);

    void bool_expression_pars(const std::string& name, const std::string& expression);
    void char_expression_pars(const std::string& name, const std::string& expression);
    void int_expression_pars(const std::string& name, const std::string& expression);
    void float_expression_pars(const std::string& name, const std::string& expression);
    void double_expression_pars(const std::string& name, const std::string& expression);
    void string_expression_pars(const std::string& name, const std::string& expression);

    bool defined_variable(const std::string& name);

    bool is_float_variable(const std::string& expression);
    bool is_char_variable(const std::string& expression);
    bool is_bool_variable(const std::string& expression);
    bool is_int_variable(const std::string& expression);
    bool is_double_variable(const std::string& expression);
    bool is_string_variable(const std::string& expression);

    bool is_double_literal(const std::string& expression);
    void assignment_operator_pars(const std::string& op1, const std::string& op2);
    void plus_assignment_operator_pars(const std::string& op1, const std::string& op2);
    void minus_assignment_operator_pars(const std::string& op1, const std::string& op2);
    bool is_assignment_expression(const std::string& line, int address);

    // example x = y + z
    void parse_assignment_expression(const std::string& op1, const std::string& op2, const std::string& some_operator, const std::string& op3);
    void parse_expression(const std::string& line, int address);
    void handle_int_addition(const std::string& target, const std::string& operand1, const std::string& operand2);
    void handle_int_subtraction(const std::string& op1, const std::string& op2, const std::string& op3);
    void handle_int_multiplication(const std::string& op1, const std::string& op2, const std::string& op3);
    void handle_int_division(const std::string& op1, const std::string& op2, const std::string& op3);
    
public:
    void print_bool_map();
    void print_char_map();
    void print_int_map();
    void print_float_map();
    void print_double_map();
    void print_string_map();

private:
    std::string m_input;
    std::unordered_map<std::string, bool> bool_variables;
    std::unordered_map<std::string, char> char_variables;
    std::unordered_map<std::string, int> int_variables;
    std::unordered_map<std::string, float> float_variables;
    std::unordered_map<std::string, double> double_variables;
    std::unordered_map<std::string, std::string> string_variables;
};

#endif // PARSER_HPP_