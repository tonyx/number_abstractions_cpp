#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <string.h>
#include "numbers.h"
#include <math.h>


int char_to_int(char c) {
	return (int)c - 48;
}


int string_to_int(char* my_string) {
	int base=10;
	int to_return = 0;
	int string_len = strlen(my_string);

	for(int index=string_len;index>0;index--) {
		to_return+=(char_to_int(*(my_string+(index-1))))*(pow(base,(index-1)));
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
    // Integer_operations* iOther = dynamic_cast<Integer*> (other);
    Integer* iOther = dynamic_cast<Integer*> (other);
    if (iOther!=NULL) {
        return iOther->somma_intero(this);
    } else {
        return other->somma(this);
    }
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

Number* Rational::opposto() {
    return new Rational(-this->get_numeratore(),this->get_denominatore());
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
    Integer* iOther = dynamic_cast<Integer*>(other);
    Rational* rOther = new Rational(iOther->get_value(),1);
    return this->somma_razionale(rOther);
}

Number* Rational::somma_razionale(Number* other) {
    Rational* rOther = dynamic_cast<Rational*>(other);
    int new_numerator = this->get_numeratore()*rOther->get_denominatore()+ rOther->get_numeratore()*this->get_denominatore();
    int new_denominator = this->get_denominatore()*rOther->get_denominatore();
    Rational* to_return = new Rational(new_numerator,new_denominator);
    return to_return;
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


#define NOMAIN

#ifndef NOMAIN 

int main() {
    printf("hello world");
}
#endif
