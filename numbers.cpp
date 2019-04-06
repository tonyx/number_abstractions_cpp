#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <string.h>
#include "numbers.h"
#include <math.h>


int char_to_int(char c) {
	return (int)c - 48;
}

Integer* meno_uno = new Integer(-1);

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
    Integer* iOther = (Integer*)other;
    return iOther->somma_intero(this);

    // Integer* iOther = dynamic_cast<Integer*> (other);
    // if (iOther!=NULL) {
    //     return iOther->somma_intero(this);
    // } else {
    //     return other->somma(this);
    // }

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
        (this->get_imaginary_part()->moltiplica(cOther->get_imaginary_part())->moltiplica(new Rational(-1,1)))));
    Number* im_part = ((this->get_real_part()->moltiplica(cOther->get_imaginary_part()))->somma(
        this->get_imaginary_part()->moltiplica(cOther->get_real_part())));
    return new Complex(real_part,im_part);
}

char* Complex::to_string() {
    sprintf(buffer,"%s+(%s)*i",get_real_part()->to_string(),get_imaginary_part()->to_string());
    return buffer;
}

