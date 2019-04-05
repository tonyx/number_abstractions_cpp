

int char_to_int(char c);
int string_to_int(char* myString);

class Number {
    public: 
    virtual Number* somma(Number* other) = 0;
    virtual Number* sottrai(Number* other) =0;
    virtual Number* moltiplica(Number* other) = 0;
    virtual Number* opposto() = 0;
    virtual char* to_string() =0;
};


class Integer_operations {
    protected:
    virtual Number* somma_intero(Number* other) = 0;
    virtual Number* moltiplica_intero(Number* other) = 0;
};

class Integer: public Number,Integer_operations {
    public:
    Integer();
    Integer(int number);
    Number* somma(Number* other);
    Number* sottrai(Number* other);
    Number* moltiplica(Number* other);
    Number* opposto();
    char* to_string();
    int get_value();

    protected:
    Number* somma_intero(Number* other);
    Number* moltiplica_intero(Number* other);
    int the_value;
    char buffer[97];
};

class Rational_operations {
    protected:
    virtual Number* somma_razionale(Number* other) = 0;
    virtual Number* moltiplica_razionale(Number* other) = 0;
};

class Rational: public Integer,Rational_operations {
    public: 
    Rational (int numeratore,int denominatore);
    int get_numeratore();
    int get_denominatore();
    Number* somma(Number * other);
    Number* moltiplica(Number * other);
    Number* opposto();
    char* to_string();

    protected: 
    Number* somma_intero(Number* other);
    Number* somma_razionale(Number* other);
    Number* moltiplica_razionale(Number *other);
    int numeratore;
    int denominatore;
};


