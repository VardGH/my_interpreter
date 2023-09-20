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
    bool is_iostream(const std::string& line);
    bool is_main(const std::string& line, int address);
    void parse_variable_declaration( std::string& line, int address);
    void save_memory(const std::string& type, const std::string& type_name, const std::string& expression);
    void parse_main(const std::string& line, int address, bool& found_main);
    void parse_iostream(const std::string& line, bool& found_iostream);
    bool is_number(const std::string& expression);
    void bool_expression_pars(const std::string& type_name, const std::string& expression);
    void char_expression_pars(const std::string& type_name, const std::string& expression);
    void int_expression_pars(const std::string& type_name, const std::string& expression);

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
    std::unordered_map<std::string, std::string> int_variables;
    std::unordered_map<std::string, std::string> float_variables;
    std::unordered_map<std::string, std::string> double_variables;
    std::unordered_map<std::string, std::string> string_variables;
};

#endif // PARSER_HPP_