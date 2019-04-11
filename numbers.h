#include <list>
#include <string>
// using namespace std;

int gcd(int a,int b);
int char_to_int(char c);
int string_to_int(char* myString);
void trim_left_and_right(char* my_char);

class StringExpressionToList {
    public:
    StringExpressionToList(char* expression);
    std::list<std::string> get_listed_expression();
    
    private:
    std::list<std::string> messages;
};

class Number {
    public: 
    virtual Number* somma(Number* other) = 0;
    virtual Number* sottrai(Number* other) =0;
    virtual Number* moltiplica(Number* other) = 0;
    virtual Number* opposto() = 0;
    virtual Number* dividi(Number* other) = 0;
    virtual char* to_string() = 0;
};

Number* string_to_number(char* my_string);
Number* parse_expression(char* expression);


class Syntax_tree {
    public:
    virtual Number* eval() = 0;
};

Syntax_tree* expression_to_syntax_tree(char* expression);
char* chunk_delimiter(char* my_string);

class Number_node_tree: public Syntax_tree {
    public: 
    Number_node_tree(Number*);
    Number* eval();
    private: 
    Number* number;
};

class Expression_node_tree: public Syntax_tree {
    public:
    Expression_node_tree(Syntax_tree* left_expression, char operation, Syntax_tree* right_expression);
    Number* eval();
    private: 
    char operation;
    Syntax_tree* left_expression;
    Syntax_tree* right_expression;
};

Syntax_tree* expression_to_syntax_tree_iter(char* expression,Syntax_tree** tree, char my_operator );

class Integer_operations {
    private:
    virtual Number* somma_intero(Number* other) = 0;
    virtual Number* moltiplica_intero(Number* other) = 0;
    virtual Number* dividi_intero(Number* other) = 0;
};

class Integer: public Number,Integer_operations {
    friend class Rational;

    public:
    Integer(int number);
    Number* somma(Number* other);
    Number* sottrai(Number* other);
    Number* moltiplica(Number* other);
    Number* opposto();
    Number* dividi(Number* other);

    char* to_string();

    protected:
    char buffer[97];

    private:
    Integer();
    int get_value();
    int the_value;
    Number* somma_intero(Number* other);
    Number* moltiplica_intero(Number* other);
    Number* dividi_intero(Number* other);
};


class Rational_operations {
    public: 
    virtual Number* reciproco() = 0;

    private:
    virtual Number* somma_razionale(Number* other) = 0;
    virtual Number* moltiplica_razionale(Number* other) = 0;
    virtual Number* dividi_razionale(Number* other) = 0;
};

class Rational: public Integer,Rational_operations {
    public: 
    Rational (int numeratore,int denominatore);
    Number* somma(Number * other);
    Number* moltiplica(Number * other);
    Number* opposto();
    Number* reciproco();
    Number* dividi(Number* other);
    char* to_string();

    Number* down_cast(Number* other);

    protected: 
    Rational();
    Number* somma_intero(Number* other);

    private: 
    Number* somma_razionale(Number* other);
    Number* moltiplica_razionale(Number *other);
    Number* moltiplica_intero(Number *other);
    Number* dividi_razionale(Number *other);
    Number* dividi_intero(Number *other);
    int get_numeratore();
    int get_denominatore();
    int numeratore;
    int denominatore;
};

class Complex_operations {
    private:
    virtual Number* somma_complesso(Number* other) =0;
    virtual Number* moltiplica_complesso(Number* other) =0;
};

class Complex: public Rational, Complex_operations {
    public:
    Complex (Number* real_part, Number* imaginary_part);
    Number* somma(Number* other);
    Number* moltiplica(Number* other);

    char* to_string();

    private:
    Number* somma_complesso(Number* other);
    Number* somma_razionale(Number* other);
    Number* moltiplica_complesso(Number* other);
    Number* real_part;
    Number* imaginary_part;
    Number* get_real_part();
    Number* get_imaginary_part();
};



