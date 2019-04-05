#include "minunit.h"
#include "numbers.h"
#include <stdlib.h>
#include <string.h>

static int foo = 0;
static int bar = 0;
static double dbar = 0.1;
static const char* foostring = "Thisstring";

void test_setup(void) {
	foo = 7;
	bar = 4;
}

void test_teardown(void) {
	/* Nothing */
}

MU_TEST(sum_integers) {
	Number* first = new Integer(1);
	Number* second = new Integer(1);
	Number* result = (Number*)first->somma(second);
	mu_check(strcmp("2",result->to_string())==0);
}

MU_TEST(sum_integer_and_rational) {
	Number* first = new Integer(1);
	Number* second = new Rational(1,2);
	Number* result = (Number*)first->somma(second);
	mu_check(strcmp("3/2",result->to_string())==0);
}


MU_TEST(sum_rational_and_integer) {
	Number* first = new Rational(1,2);
	Number* second = new Integer(1);
	Number* result = (Number*)first->somma(second);
	mu_check(strcmp("3/2",result->to_string())==0);
}

MU_TEST(moltiplica_razionali) {
	Number* first = new Rational(1,2);
	Number* second = new Rational(1,2);
	Number* result = first->moltiplica(second);
	mu_check(strcmp("1/4",result->to_string())==0);

}

MU_TEST(sottrai_interi) {
	Number* first = new Integer(2);
	Number* second = new Integer(1);
	Number* result = first->sottrai(second);
	mu_check(strcmp("1",result->to_string())==0);
}

MU_TEST(sottrai_intero_razionale) {
	Number* first = new Integer(1);
	Number* second = new Rational(1,2);
	Number* result = first->sottrai(second);
	mu_check(strcmp("1/2",result->to_string())==0);
}

MU_TEST(sottrai_razionali) {
	Number* first = new Rational(1,1);
	Number* second = new Rational(1,2);
	Number* result = first->sottrai(second);
	mu_check(strcmp("1/2",result->to_string())==0);
}




// MU_TEST(explicit_sum_rationals) {
// 	Rational* first = new Rational(1,2);
// 	Rational* second = new Rational(1,2);
// 	Rational* result = (Rational*)first->somma_razionale(second);
// 	mu_check(result->get_numeratore()==1);
// 	mu_check(result->get_denominatore()==1);
// }


MU_TEST(implicit_sum_rationals) {
	Number* first = new Rational(1,2);
	Number* second = new Rational(1,2);
	Number* result = (Number*)first->somma(second);
	mu_check(strcmp("1/1",result->to_string())==0);
}

MU_TEST(dynamic_cast_test) {
	Number* first = new Rational(1,2);
	Number* second = new Rational(1,2);
	Rational* rational_op = dynamic_cast<Rational*>(second);
	mu_check(rational_op!=NULL);

}

MU_TEST(moltiplica_interi) {
	Number* first = new Integer(2);
	Number* second =  new Integer(2);
	Integer* prodotto = (Integer*)first->moltiplica(second);
	mu_check(4==prodotto->get_value());
}

MU_TEST(stampa_istanza_razionale) {
	Number* first = new Rational(1,2);
	mu_check(strcmp("1/2",first->to_string())==0);
}

MU_TEST(opposto_razional) {
	Number* number = new Rational(1,2);
	Number* opposite = number->opposto();
	printf ("%s\n",opposite->to_string());
	
	mu_check(strcmp("-1/2",opposite->to_string())==0);
}

MU_TEST(string_to_intger) {
	char* no_val = (char*)"";
	int actual = string_to_int(no_val);
	mu_check(actual==0);

	char* unoduetre = (char*)"1";
	actual = string_to_int(unoduetre);
	mu_check(actual==1);

	char* eleven = (char*)"11";
	actual = string_to_int(eleven);
	mu_check(actual==11);
}


MU_TEST(to_int_test) {
	int converted = char_to_int('1');
	char* unoduetre = (char*)"123";
	int actual = string_to_int(unoduetre);
	mu_check(converted==1);
}


MU_TEST(test_check) {
	mu_check(foo == 7);
}

MU_TEST(test_check_fail) {
	mu_check(foo != 7);
}

MU_TEST(test_assert) {
	mu_assert(foo == 7, "foo should be 7");
}

MU_TEST(test_assert_fail) {
	mu_assert(foo != 7, "foo should be <> 7");
}

MU_TEST(test_assert_int_eq) {
	mu_assert_int_eq(4, bar);
}

MU_TEST(test_assert_int_eq_fail) {
	mu_assert_int_eq(5, bar);
}

MU_TEST(test_assert_double_eq) {
	mu_assert_double_eq(0.1, dbar);
}

MU_TEST(test_assert_double_eq_fail) {
	mu_assert_double_eq(0.2, dbar);
}

MU_TEST(test_fail) {
	mu_fail("Fail now!");
}

MU_TEST(test_string_eq){
	mu_assert_string_eq("Thisstring", foostring);
}

MU_TEST(test_string_eq_fail){
	mu_assert_string_eq("Thatstring", foostring);
}


MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	// MU_RUN_TEST(test_check);
	// MU_RUN_TEST(test_assert);
	// MU_RUN_TEST(test_assert_int_eq);
	// MU_RUN_TEST(test_assert_double_eq);

	// MU_RUN_TEST(test_check_fail);
	// MU_RUN_TEST(test_assert_fail);
	// MU_RUN_TEST(test_assert_int_eq_fail);
	// MU_RUN_TEST(test_assert_double_eq_fail);
	
	// MU_RUN_TEST(test_string_eq);
	// MU_RUN_TEST(test_string_eq_fail);

	// MU_RUN_TEST(test_fail);


	MU_RUN_TEST(sum_integers);
	MU_RUN_TEST(sum_integer_and_rational);
	MU_RUN_TEST(sum_rational_and_integer);
	// MU_RUN_TEST(explicit_sum_rationals);

	MU_RUN_TEST(implicit_sum_rationals);
	MU_RUN_TEST(moltiplica_interi);
	MU_RUN_TEST(string_to_intger);
	MU_RUN_TEST(to_int_test);
	MU_RUN_TEST(stampa_istanza_razionale);
	MU_RUN_TEST(opposto_razional);
	MU_RUN_TEST(moltiplica_razionali);
	MU_RUN_TEST(sottrai_interi);
	MU_RUN_TEST(sottrai_intero_razionale);
	MU_RUN_TEST(sottrai_razionali);

}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}
