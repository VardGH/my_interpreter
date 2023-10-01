#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <unordered_map>
#include <stack>
#include <map>

class Parser
{
public:
    // Constructors and operator overloads
    Parser(const std::string& input);
    Parser(const Parser& other) = delete;
    Parser& operator=(const Parser& other) = delete;

    Parser(Parser&& other) = delete;
    Parser& operator=(Parser&& other) = delete;

public:
    void parse(); // Main parsing function

private:
    std::string trim(const std::string& str); // // Utility function for trimming whitespace from a string

     // Functions for identifying different types of lines
    bool is_variable_declaration(std::string& line, int address);
    bool is_valid_line(const std::string& line, int address);

    bool is_iostream(const std::string& line);
    bool is_main(const std::string& line, int address);
    
    // Functions for parsing specific line types
    void parse_variable_declaration(std::string& line, int address); // int x = 10;
    void parse_variable_definition(const std::string& line, int address); // x = y or x += 10
    void save_memory(const std::string& type, const std::string& type_name, const std::string& expression);
    void parse_main(const std::string& line, int address, bool& found_main);
    void parse_iostream(const std::string& line, bool& found_iostream);

    // Functions for parsing expressions of different data types
    void bool_expression_pars(const std::string& name, const std::string& expression);
    void char_expression_pars(const std::string& name, const std::string& expression);
    void int_expression_pars(const std::string& name, const std::string& expression);
    void float_expression_pars(const std::string& name, const std::string& expression);
    void double_expression_pars(const std::string& name, const std::string& expression);
    void string_expression_pars(const std::string& name, const std::string& expression);

    // Function for checking if a variable is defined
    bool defined_variable(const std::string& name);

    // Functions for checking the data type of an expression
    bool is_float_variable(const std::string& expression);
    bool is_char_variable(const std::string& expression);
    bool is_bool_variable(const std::string& expression);
    bool is_int_variable(const std::string& expression);
    bool is_double_variable(const std::string& expression);
    bool is_string_variable(const std::string& expression);

    bool is_double_literal(const std::string& expression);
    bool is_char_literal(const std::string& expression);
    bool is_number(const std::string& expression);

    // Functions for parsing assignment expressions
    void assignment_operator_pars(const std::string& op1, const std::string& op2);
    void plus_assignment_operator_pars(const std::string& op1, const std::string& op2);
    void minus_assignment_operator_pars(const std::string& op1, const std::string& op2);
    void mul_assignment_operator_pars(const std::string& op1, const std::string& op2);
    void div_assignment_operator_pars(const std::string& op1, const std::string& op2);
    bool is_assignment_expression(const std::string& line, int address);

    // example x = y + z
    void parse_assignment_expression(const std::string& op1, const std::string& op2, const std::string& some_operator, const std::string& op3);
    void parse_expression(const std::string& line, int address);

    // Functions for parsing cout expressions
    bool is_cout_expression(const std::string& op1, const std::string& assignment, const std::string& op2, const std::string& st1, const std::string& st2);
    void cout_expression_parse(std::string& expression);

    // Functions for parsing cin expressions
    bool is_cin_expression(const std::string& op1, const std::string& assignment, const std::string& op2, const std::string& st1, const std::string& st2);
    void cin_expression_parse(std::string& expression);

    // Functions for parsing increment expressions
    bool is_increment_expression(const std::string& op1, const std::string& op2, const std::string& op3, const std::string& op4, const std::string& op5);
    void increment_expression_parse(std::string& expression);

    // Functions for parsing cin expressions
    bool is_decrement_expression(const std::string& op1, const std::string& op2, const std::string& op3, const std::string& op4, const std::string& op5);
    void decrement_expression_parse(std::string& expression);

    // Functions for parsing "if" statements
    bool is_if_expression(const std::string& line);
    void parse_if_statement(int& address, const std::string& line);
    void execute_if_statement(int& address, const std::string& op1, const std::string& op2, const std::string& op3);

public:
    // Read and store in map
    void load_from_file(const std::string& filename);

private:
    // Template function for retrieving variable values
    template <typename T>
    T get_value(const std::string& name)
    {
        if (is_int_variable(name)) {
            return int_variables[name];
        } else if (is_double_variable(name)) {
            return double_variables[name];
        } else if (is_bool_variable(name)) {
            return bool_variables[name];
        } else if (is_char_variable(name)) {
            return char_variables[name];
        } else if (is_number(name)) {
            return std::stoi(name);
        } else if (is_double_literal(name)) {
            return std::stod(name);
        } else if (is_char_literal(name)) {
            return name[1];
        } else {
            throw std::runtime_error("Variable " + name + " is not defined.");
        }
    }
    
public:
    void print_bool_map();
    void print_char_map();
    void print_int_map();
    void print_float_map();
    void print_double_map();
    void print_string_map();
    void full_memory_print();

private:
    std::string m_input;
    std::unordered_map<std::string, bool> bool_variables;
    std::unordered_map<std::string, char> char_variables;
    std::unordered_map<std::string, int> int_variables;
    std::unordered_map<std::string, float> float_variables;
    std::unordered_map<std::string, double> double_variables;
    std::unordered_map<std::string, std::string> string_variables;

    std::map<int, std::string> full_memory;
    std::unordered_map<int, std::pair<int, int>> if_map;
    std::unordered_map<int, std::pair<int, int>> while_map;
};

#endif // PARSER_HPP_