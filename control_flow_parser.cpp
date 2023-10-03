#include "parser.hpp"
#include <iostream>
#include <sstream>

// Checks if the given code line represents an 'if' statement or expression
bool Parser::is_if_expression(const std::string& line)
{
    return (line.find("if ") == 0);
}

// Checks if the given code line represents an 'while' statement or expression
bool Parser::is_while_expression(const std::string& line)
{
    return (line.find("while ") == 0);
}

void Parser::parse_if_statement(int& address,  const std::string& line)
{
    // Check if the line ends with an opening curly brace {
    if (line.back() != '{') {
        throw std::runtime_error("Missing opening curly brace {");
    }

    // Extract the condition part of the if statement
    std::string condition = line.substr(3);
    condition = condition.substr(0, condition.length() - 2);

    // Check if the condition is enclosed in parentheses
    if (condition.front() != '(' || condition.back() != ')') {
        throw std::runtime_error("Condition must be enclosed in parentheses");
    }

    std::istringstream iss(condition);
    std::string op1 {};
    std::string op2 {};
    std::string op3 {};
    iss >> op1 >> op2 >> op3;

    if (op1.front() != '(') {
        throw std::runtime_error("You miss (");
    }
    if (op3.back() != ')') {
        throw std::runtime_error("You miss )");
    }

    op1 = op1.substr(1);
    op3.pop_back();

    std::cout << "op1: " << op1 << std::endl;
    std::cout << "op2: " << op2 << std::endl;
    std::cout << "op3: " << op3 << std::endl;

    execute_if_statement(address, op1, op2, op3);
}

enum class ComparisonOperator 
{
    LESS_THAN,
    GREATER_THAN,
    EQUAL,
    NOT_EQUAL,
    LESS_EQUAL,
    GREATER_EQUAL
};

ComparisonOperator get_comparison_operator(const std::string& op) 
{
    if (op == "<") {
        return ComparisonOperator::LESS_THAN;
    } else if (op == ">") {
        return ComparisonOperator::GREATER_THAN;
    } else if (op == "==") {
        return ComparisonOperator::EQUAL;
    } else if (op == "!=") {
        return ComparisonOperator::NOT_EQUAL;
    } else if (op == "<=") {
        return ComparisonOperator::LESS_EQUAL;
    } else if (op == ">=") {
        return ComparisonOperator::GREATER_EQUAL;
    } else {
        throw std::runtime_error("Invalid comparison operator");
    }
}

void Parser::execute_if_statement(int& address, const std::string& op1, const std::string& op2, const std::string& op3)
{
    double tmp1 = get_value<double>(op1);
    double tmp2 = get_value<double>(op3);

    std::cout << "tmp1: " << tmp1 << std::endl;
    std::cout << "tmp2: " << tmp2 << std::endl;

    std::pair<int, int> address_range = if_map[address]; 

    int start_address = address_range.first;
    int end_address = address_range.second;

    ComparisonOperator comparison_operator = get_comparison_operator(op2);

    switch (comparison_operator) {
        case ComparisonOperator::LESS_THAN:
            address = (tmp1 < tmp2) ? start_address : end_address;
            break;
        case ComparisonOperator::GREATER_THAN:
            address = (tmp1 > tmp2) ? start_address : end_address;
            break;
        case ComparisonOperator::EQUAL:
            address = (tmp1 == tmp2) ? start_address : end_address;
            break;
        case ComparisonOperator::NOT_EQUAL:
            address = (tmp1 != tmp2) ? start_address : end_address;
            break;
        case ComparisonOperator::LESS_EQUAL:
            address = (tmp1 <= tmp2) ? start_address : end_address;
            break;
        case ComparisonOperator::GREATER_EQUAL:
            address = (tmp1 >= tmp2) ? start_address : end_address;
            break;
        default:
            throw std::runtime_error("Invalid comparison operator");
    }
}

std::tuple<std::string, std::string, std::string> Parser::parse_while_statement(const std::string& line)
{
    // Check if the line ends with an opening curly brace {
    if (line.back() != '{') {
        throw std::runtime_error("Missing opening curly brace {");
    }

    // Extract the condition part of the if statement
    std::string condition = line.substr(6);
    condition = condition.substr(0, condition.length() - 2);

    // Check if the condition is enclosed in parentheses
    if (condition.front() != '(' || condition.back() != ')') {
        throw std::runtime_error("Condition must be enclosed in parentheses");
    }

    std::istringstream iss(condition);
    std::string op1 {};
    std::string op2 {};
    std::string op3 {};
    iss >> op1 >> op2 >> op3;

    if (op1.front() != '(') {
        throw std::runtime_error("You miss (");
    }
    if (op3.back() != ')') {
        throw std::runtime_error("You miss )");
    }

    op1 = op1.substr(1);
    op3.pop_back();

    return std::make_tuple(op1, op2, op3);
}

std::pair<int, int> Parser::execute_while_statement(int& address, const std::string& op1, const std::string& op2, const std::string& op3, bool& flag)
{
    double tmp1 = get_value<double>(op1);
    double tmp2 = get_value<double>(op3);

    std::pair<int, int> address_range = while_map[address]; 

    int start_address = address_range.first;
    int end_address = address_range.second;

    ComparisonOperator comparison_operator = get_comparison_operator(op2);

    switch (comparison_operator) {
        case ComparisonOperator::LESS_THAN:
            flag = (tmp1 < tmp2);
            if (!flag) {
                address = end_address;
            }
            break;
        case ComparisonOperator::GREATER_THAN:
            flag = (tmp1 > tmp2);
            if (!flag) {
                address = end_address;
            }
            break;
        case ComparisonOperator::EQUAL:
            flag = (tmp1 == tmp2);
            if (!flag) {
                address = end_address;
            }
            break;
        case ComparisonOperator::NOT_EQUAL:
            flag = (tmp1 != tmp2);
            if (!flag) {
                address = end_address;
            }
            break;
        case ComparisonOperator::LESS_EQUAL:
            flag = (tmp1 <= tmp2);
            if (!flag) {
                address = end_address;
            }
            break;
        case ComparisonOperator::GREATER_EQUAL:
            flag = (tmp1 >= tmp2);
            if (!flag) {
                address = end_address;
            }
            break;
        default:
            throw std::runtime_error("Invalid comparison operator");
    }
    
    return {start_address, end_address};
}