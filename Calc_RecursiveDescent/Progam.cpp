/*
 *  �a���������. ������ �� �������� "�++ Programming Language" (������).
 *  ����������� �������� "����������� �����" (recursive descent).
 *  (����������: ����������� ����� �������� � �����������. ��������, ����
 *  �� ����� ������ r = 2.5; area = pi * r * r; �� �� ������ �����
 *  2.5; 19.635)
 */

#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

enum Token_value : char {
    NAME, NUMBER, END,
    PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
    PRINT = ';', ASSIGN = '=', LP = '(', RP = ')'
};

enum Number_value : char {
    NUM0 = '0', NUM1 = '1', NUM2 = '2',
    NUM3 = '3', NUM4 = '4', NUM5 = '5',
    NUM6 = '6', NUM7 = '7', NUM8 = '8',
    NUM9 = '9', NUMP = '.',
};

Token_value curr_tok = PRINT;        // ������ ��������� ������� ������� get_token().
double number_value;                 // ������ ����� ������� ��� ������� � ��������� �������.
std::string string_value;            // ������ ���.
std::map<std::string, double> table; // ������� ���.
int no_of_errors;                    // ������ ���������� ����������� ������.

double expr(std::istream*, bool);    // ������������ ����������.

/****************************************************************************/

// ������� error() ����� ����������� ��������: �������������� ������� ������.
double error(const std::string& error_message) {
    ++no_of_errors;
    std::cerr << "error: " << error_message << std::endl;
    return 1;
}

Token_value get_token(std::istream* input) {
    char ch;

    do {    // ���������� ��� ���������� ������� ����� '\n'.
        if (!input->get(ch)) {
            return curr_tok = END; // ��������� ������ ������������.
        }
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
    case 0: // ��� ����� ������� ����� �����, ��������� ������ ������������.
        return curr_tok = END;
    case PRINT:
    case '\n':
        return curr_tok = PRINT;
    case MUL:
    case DIV:
    case PLUS:
    case MINUS:
    case LP:
    case RP:
    case ASSIGN:
        return curr_tok = Token_value(ch); // ���������� � ������ � �������.
    case NUM0: case NUM1: case NUM2: case NUM3: case NUM4:
    case NUM5: case NUM6: case NUM7: case NUM8: case NUM9:
    case NUMP:
        input->putback(ch); // �������� ����� � �����...
        *input >> number_value; // � ������� ��� �������.
        return curr_tok = NUMBER;
    default:
        if (isalpha(ch)) {
            string_value = ch;
            while (input->get(ch) && isalnum(ch)) {
                string_value.push_back(ch);
            }
            input->putback(ch);
            return curr_tok = NAME;
        }
        error("Bad Token");
        return curr_tok = PRINT;
    }
}

/* ������ ������� ��������������� ������� ��������� �������� ���� bool
 * �����������, ������ �� ������� �������� get_token() ��� ���������
 * ��������� �������. */

 // prim() - ������������ ��������� ���������.
double prim(std::istream* input, bool get) {
    if (get) {
        get_token(input);
    }

    switch (curr_tok) {
    case NUMBER: {
        double v = number_value;
        get_token(input);
        return v;
    }
    case NAME: {
        double& v = table[string_value];
        if (get_token(input) == ASSIGN) {
            v = expr(input, true);
        }
        return v;
    }
    case MINUS:
        return -prim(input, true);
    case LP: {
        double e = expr(input, true);
        if (curr_tok != RP) {
            return error("')' expected");
        }
        get_token(input);
        return e;
    }
    default:
        return error("primary expected");
    }
}

// term() - ��������� � �������.
double term(std::istream* input, bool get) {
    double left = prim(input, get);

    for (; ; ) {
        switch (curr_tok) {
        case MUL:
            left *= prim(input, true);
            break;
        case DIV:
            if (double d = prim(input, true)) {
                left /= d;
                break;
            }
            return error("Divide by 0");
        default:
            return left;
        }
    }
}

// expr() - �������� � ���������.
double expr(std::istream* input, bool get) {
    double left = term(input, get);

    for (; ; ) {
        switch (curr_tok) {
        case PLUS:
            left += term(input, true);
            break;
        case MINUS:
            left -= term(input, true);
            break;
        default:
            return left;
        }
    }
}

int main(int argc, char* argv[]) {
    std::istream* input = nullptr; // ��������� �� �����.

    switch (argc) {
    case 1:
        input = &std::cin;
        break;
    case 2:
        input = new std::istringstream(argv[1]);
        break;
    default:
        error("Too many arguments");
        return 1;
    }

    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    while (*input) {
        get_token(input);
        if (curr_tok == END) {
            break;
        }

        // ������� ��������������� expr() �� ��������� ������ ���������.
        if (curr_tok == PRINT) {
            continue;
        }

        // expr() -> term() -> prim() -> expr() ...
        std::cout << expr(input, false) << std::endl;
    }

    if (input != &std::cin) {
        delete input;
    }

    return no_of_errors;
}