#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <string.h>

#include "numbers.h"
#include <math.h>
#include <stdexcept>
using namespace std;

int char_to_int(char c) {
	return (int)c - 48;
}

Integer* meno_uno = new Integer(-1);
Rational* meno_uno_razionale = new Rational(-1,1);

Number* parse_expression(char* my_string) {
    return string_to_number(my_string);
}

Syntax_tree* expression_to_syntax_tree(char* my_string) {
    Syntax_tree* to_return;
    to_return = new Number_node_tree(string_to_number(my_string));
    return to_return;
}

int pointer_comparator(const void* a, const void* b) {
    return (char*)b - (char*)a;
}


char* chunk_delimiter(char* my_string) {
    char* endings[3];
    char* end_of_string = strchr(my_string,'\0');
    char* plus_operator_location  = (strchr(my_string,'+')!=NULL?strchr(my_string,'+'):NULL);
    char* times_operator_location = (strchr(my_string,'*')!=NULL?strchr(my_string,'*'):NULL);
    endings[0]=end_of_string;
    endings[1]=plus_operator_location;
    endings[2]=times_operator_location;

    qsort(endings,3,sizeof(char*),&pointer_comparator);
    int index=0;
    char* to_return=endings[index];
    while (to_return==NULL&&index++<3)  {
        to_return=endings[index];
    }
    return to_return;
}

Syntax_tree* expression_to_syntax_tree_iter(char* my_string,Syntax_tree** accumul,char my_operator) {
    char buffer[97];
    trim_left_and_right(my_string);
    if (strcmp("",my_string)==0) {
        return new Number_node_tree(new Integer(0));
    }
    char* end_of_current_chunk = chunk_delimiter(my_string);
    strncpy(buffer,my_string,end_of_current_chunk-my_string );
    buffer[end_of_current_chunk-my_string]='\0';
    Syntax_tree* to_return = new Number_node_tree(string_to_number(buffer));
    return to_return;
}

StringExpressionToList::StringExpressionToList(char* expression) {
    trim_left_and_right(expression);
    if (strcmp("",expression)==0) {
        return;
    }
    
    char buffer[29];
    this->messages = std::list<std::string>();

    char* begin_of_current_chunk = expression;
    char* end_of_current_chunk = expression;

    while(true) {
        while(*end_of_current_chunk++!='\0'&&*end_of_current_chunk!='+');
        strncpy(buffer,begin_of_current_chunk,end_of_current_chunk-begin_of_current_chunk);

        this->messages.push_back(buffer);

        if (*end_of_current_chunk=='\0') {
            break;
        } else {
            this->messages.push_back("+");
        }
        end_of_current_chunk++;
        begin_of_current_chunk=end_of_current_chunk;
    }
}

std::list<std::string> StringExpressionToList::get_listed_expression() {
    return this->messages;
}

void trim_left_and_right(char* my_char) {
    if (strchr(my_char,' ')==NULL) {
        return;
    }

    char buffer[37];
    char* chr_pointer = my_char;
    while(*chr_pointer==' ') {
        chr_pointer++;
    }

    strcpy(buffer,chr_pointer);

    char* first_right_space = strchr(buffer,' ');
    if (first_right_space!=NULL) {
        *first_right_space='\0';
    }

    strcpy(my_char,buffer);
}

Number* string_to_number(char* my_string) {
    trim_left_and_right(my_string);
    char buffer[97];
    char* slash_in_string = strchr(my_string,'/');
    if (slash_in_string==NULL) {
        return new Integer(string_to_int(my_string));
    } else {
        int position_of_slash = slash_in_string - my_string;
        strncpy(buffer,my_string,position_of_slash);
        buffer[position_of_slash]='\0';
        int numerator = string_to_int(buffer);
        int denominator = string_to_int(my_string+position_of_slash+1);
        return new Rational(numerator,denominator);
    }
}

int string_to_int(char* my_string) {
	int base=10;
	int to_return = 0;
	int string_len = strlen(my_string);

	for(int index=0;index<string_len;index++) {
		to_return+=(char_to_int(*(my_string+(index))))*(pow(base,(string_len-index-1)));
	}
	return to_return;
}

int gcd(int a,int b) {
    if (b==0) {
        return a;
    }  else
    {
       return gcd(b,a%b);
    }
}

Integer::Integer(int value) {
    the_value = value;
}

Integer::Integer() {
}

int Integer::get_value() {
    return the_value;
}

Number* Integer::somma(Number* other) {
    Integer* iOther = (Integer*)other;
    return iOther->somma_intero(this);
}

Number* Number_node_tree::eval() {
    return this->number;
};

Number_node_tree::Number_node_tree(Number* number) {
    this->number = number;
}

Expression_node_tree::Expression_node_tree(Syntax_tree* left_expression, char operation, Syntax_tree* right_expression) {
    this->operation = operation;
    this->left_expression = left_expression;
    this->right_expression= right_expression;
}

Number* Expression_node_tree::eval() {
    switch (this->operation) {
        case '+':
            return this->left_expression->eval()->somma(this->right_expression->eval());
        case '*':
            return this->left_expression->eval()->moltiplica(this->right_expression->eval());
    }

    char buffer[92];
    strcpy(buffer,"operazione 'X' non implementata");
    char* pointer_to_X = strchr(buffer,'X');
    *pointer_to_X = this->operation;
    throw new std::runtime_error(buffer);
}

Number* Rational::somma(Number* other) {
    Rational* rOther = dynamic_cast<Rational*>(other);
    if (rOther!=NULL)  {
        return rOther->somma_razionale(this);
    } else {
        return other->somma(this);
    }
}

Number* Integer::opposto() {
    return new Integer(-this->get_value());
}

Number* Integer::dividi_intero(Number* other) {
    if (typeid(other) != typeid(Integer)) {
        throw std::runtime_error("parametro diverso da intero non ammesso");
    }
    Integer* iOther = (Integer*)other;
    return new Integer(this->get_value()/iOther->get_value());
}


Number* Rational::down_cast(Number* other) {
    Integer* iOther = (Integer*) other;
    return new Rational(iOther->get_value(),1);
}

Number* Rational::dividi(Number* other) {
    Rational* rOther = dynamic_cast<Rational*>(other);
    if (rOther!=NULL) {
        return this->moltiplica(rOther->reciproco());
    } else {
        Rational* rOther = (Rational*)down_cast(other);
        return this->moltiplica(rOther->reciproco());
    }
}

Number* Integer::dividi(Number* other) {
    return this->dividi_intero(other);
}


Number* Rational::opposto() {
    return new Rational(-this->get_numeratore(),this->get_denominatore());
}

Number* Rational::reciproco() {
    return new Rational(this->get_denominatore(),this->get_numeratore());
}

Number* Integer::somma_intero(Number* other) {
    Integer* downcasted_other2 = (Integer*)other;
    return new Integer(this->get_value()+(downcasted_other2->get_value()));
}

Number* Rational::moltiplica(Number* other) {
    Rational* rOther = dynamic_cast<Rational*>(other);
    if (rOther!=NULL) {
        return rOther->moltiplica_razionale(this);
    } else {
        return other->moltiplica(this);
    }
}

Number* Integer::sottrai(Number* other) {
    Number* opposto = other->opposto();
    return opposto->somma(this);
}

Number* Integer::moltiplica(Number* other) {
    Integer* iOther = dynamic_cast<Integer*>(other);
    if (iOther!=NULL) {
        return iOther->moltiplica_intero(this);
    } else {
        return other->moltiplica(this);
    }
}

Number* Integer::moltiplica_intero(Number* other) {
    Integer* downcasted_other = dynamic_cast<Integer*>(other);
    return new Integer(this->get_value()*downcasted_other->get_value());
}


Rational::Rational() {

}

Number* Rational::dividi_intero(Number* other) {
    Integer* iOther = (Integer*)other;
    Rational* rOther = new Rational(1,iOther->get_value());
    return this->moltiplica_razionale(iOther);
}


Rational::Rational(int numeratore,int denominatore) {
    int greatest_common_divisor = gcd(numeratore,denominatore);
    this->numeratore=numeratore/greatest_common_divisor;
    this->denominatore=denominatore/greatest_common_divisor;

    if (this->get_denominatore()<0) {
        this->denominatore = this->denominatore*(-1);
        this->numeratore = this->numeratore*(-1);
    }
}

int Rational::get_numeratore() {
    return this->numeratore;
}
int Rational::get_denominatore() {
    return this->denominatore;
}

Number* Rational::somma_intero(Number* other) {
    Integer* iOther = (Integer*)(other);
    Rational* rOther = new Rational(iOther->get_value(),1);
    return this->somma_razionale(rOther);
}
Number* Rational::moltiplica_intero(Number* other) {
    Integer* iOther = (Integer*)(other);
    Rational* rOther = new Rational(iOther->get_value(),1);
    return this->moltiplica_razionale(rOther);
}


Number* Rational::somma_razionale(Number* other) {
    Rational* rOther = dynamic_cast<Rational*>(other);
    int new_numerator = this->get_numeratore()*rOther->get_denominatore()+ rOther->get_numeratore()*this->get_denominatore();
    int new_denominator = this->get_denominatore()*rOther->get_denominatore();
    Rational* to_return = new Rational(new_numerator,new_denominator);
    return to_return;
}

Number* Rational::dividi_razionale(Number* other) {
    Rational* rOther = (Rational*)rOther;
    return this->moltiplica_razionale(rOther->reciproco());
}

Number* Rational::moltiplica_razionale(Number* other) {
    Rational* rOther = dynamic_cast<Rational*>(other);
    int new_numerator = this->get_numeratore()*rOther->get_numeratore();
    int new_denominator = this->get_denominatore()*rOther->get_denominatore();
    return new Rational(new_numerator,new_denominator);
}


char* Integer::to_string() {
    sprintf(buffer,"%d",this->get_value());
    return buffer;
}


char* Rational::to_string() {
    sprintf(buffer, "%d/%d",this->get_numeratore(),this->get_denominatore());
    return buffer;
}

Complex::Complex(Number* real_part, Number* imaginary_part) {
    this->real_part = real_part;
    this->imaginary_part = imaginary_part;
}

Number* Complex::get_real_part() {
    return this->real_part;
}

Number* Complex::get_imaginary_part() {
    return this->imaginary_part;
}

Number* Complex::somma(Number *other) {
    Complex* cOther = dynamic_cast<Complex*>(other);
    if (cOther !=NULL) {
        return cOther->somma_complesso(this);
    } else
    {
        return other->somma(this);
    }
}

Number* Complex::somma_complesso(Number* other) {
    Complex* cOther = (Complex*)other;
    return new Complex(this->get_real_part()->somma(cOther->get_real_part()), 
        this->get_imaginary_part()->somma(cOther->get_imaginary_part()));
}

Number* Complex::somma_razionale(Number* other) {
    Rational* rOther = (Rational*)other;
    Complex* downcastedOther = new Complex(rOther,new Integer(0));
    return this->somma_complesso(downcastedOther);
}


Number* Complex::moltiplica(Number* other) {
    Complex* cOther = dynamic_cast<Complex*>(other);
    if (cOther != NULL) {
        return cOther->moltiplica_complesso(this);
    } else {
        return other->moltiplica(this);
    }
}

Number* Complex::moltiplica_complesso(Number* other) {
    Complex* cOther = (Complex*)other;
    Number* real_part = (this->get_real_part()->moltiplica(cOther->get_real_part())->somma(
        (this->get_imaginary_part()->moltiplica(cOther->get_imaginary_part())->moltiplica(meno_uno))));
    Number* im_part = ((this->get_real_part()->moltiplica(cOther->get_imaginary_part()))->somma(
        this->get_imaginary_part()->moltiplica(cOther->get_real_part())));
    return new Complex(real_part,im_part);
}

char* Complex::to_string() {
    sprintf(buffer,"%s+(%s)*i",get_real_part()->to_string(),get_imaginary_part()->to_string());
    return buffer;
}

