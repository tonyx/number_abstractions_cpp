
int char_to_int(char c);
int string_to_int(char* myString);

class Number {
    public: 
    virtual Number* somma(Number* other) = 0;
    virtual Number* sottrai(Number* other) =0;
    virtual Number* moltiplica(Number* other) = 0;
    virtual Number* opposto() = 0;
    virtual Number* dividi(Number* other) = 0;
    virtual char* to_string() = 0;
};

class Integer_operations {
    private:
    virtual Number* somma_intero(Number* other) = 0;
    virtual Number* moltiplica_intero(Number* other) = 0;
    virtual Number* dividi_intero(Number* other) = 0;
};

class Integer: public Number,Integer_operations {
    friend class Rational;

    public:
    Integer();
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



