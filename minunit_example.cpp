#include "minunit.h"
#include "numbers.h"
#include <stdlib.h>
#include <stdexcept>
#include <list>
// using namespace std;

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

int int_comparator(const void* a, const void* b ) {
	return *(int*)a - *(int*)b;
}


MU_TEST(chunk_delimiter_test) {
	char buffer[97];
	strcpy(buffer,"ciao+ok");
	char* end_of_current_string = chunk_delimiter(buffer);
	mu_check(end_of_current_string==&buffer[4]);
}

MU_TEST(int_comparer_test) {
	int my_int_array[2] = {1,2};
	int your_int_array[2] = {2,1};
	int his_int_array[6] = {4,1,2,6,99,8};
	qsort(my_int_array,2,sizeof(int),&int_comparator);
	mu_check(my_int_array[0]==1);

	qsort(your_int_array,2,sizeof(int),&int_comparator);
	mu_check(your_int_array[0]==1);

	qsort(his_int_array,6,sizeof(int),&int_comparator);
	mu_check(his_int_array[0]==1);
	mu_check(his_int_array[1]==2);
	mu_check(his_int_array[2]==4);
	mu_check(his_int_array[5]==99);

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
	Number* result = first->somma(second);
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

MU_TEST(somma_intero_razionale) { 
	Number* first = new Integer(1);
	Number* second = new Rational(1,2);
	Number* result = first->somma(second);
	mu_check(strcmp("3/2",result->to_string())==0);
}

MU_TEST(somma_razionale_intero) { 
	Number* second = new Integer(1);
	Number* first = new Rational(1,2);
	Number* result = first->somma(second);
	mu_check(strcmp("3/2",result->to_string())==0);
}


MU_TEST(prodotto_razionale_intero) {
	Number*  uno_intero = new Integer(1);
	Number*  uno_razionale = new Rational(1,1);
	Number* result = uno_intero->moltiplica(uno_razionale);
	mu_check(strcmp("1/1",result->to_string())==0);
}

MU_TEST(prodotto_intero_razional) {
	Number*  uno_intero = new Integer(1);
	Number*  uno_razionale = new Rational(1,1);
	Number* result = uno_razionale->moltiplica(uno_intero);
	mu_check(strcmp("1/1",result->to_string())==0);
}

MU_TEST(divisione_intero_razionale) {
	Number*  uno_intero = new Integer(1);
	Number*  uno_razionale = new Rational(2,1);
	Number* result = uno_razionale->dividi(uno_intero);
	mu_check(strcmp("2/1",result->to_string())==0);
}

MU_TEST(divisione_intero_raz_va_in_errore) {
	Number*  uno_intero = new Integer(1);
	Number*  uno_razionale = new Rational(2,1);
	Number* result;
	bool success=false;
	try {
		result = uno_intero->dividi(uno_razionale);
	}
	catch (std::runtime_error me) {
		success=true;
	}
	mu_check(success);
}

MU_TEST(sottrai_razionali) {
	Number* first = new Rational(1,1);
	Number* second = new Rational(1,2);
	Number* result = first->sottrai(second);
	mu_check(strcmp("1/2",result->to_string())==0);
}

MU_TEST(reciproco_di_razionale) {
	Rational* first = new Rational(2,1);
	Number* reciprocal = first->reciproco();
	mu_check(strcmp("1/2",reciprocal->to_string())==0);
}

MU_TEST(divide_integer_by_another_integer_gives_an_integer) {
	Number* first = new Integer(2);
	Number* second = new Integer(3);
	Number* result = first->dividi(second);
	mu_check(strcmp("1",result->to_string())==0);
}

MU_TEST(divide_rationals) {
	Number* first = new Rational(2,1);
	Number* second = new Rational(2,1);
	Number* result = first->dividi(second);
	mu_check(strcmp("1/1",result->to_string())==0);
}

MU_TEST(divide_rationals_2) {
	Number* first = new Rational(1,1);
	Number* second = new Rational(3,1);
	Number* result = first->dividi(second);
	mu_check(strcmp("1/3",result->to_string())==0);
}

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
	mu_check(strcmp("4",prodotto->to_string())==0);
}

MU_TEST(stampa_istanza_razionale) {
	Number* first = new Rational(1,2);
	mu_check(strcmp("1/2",first->to_string())==0);
}

MU_TEST(opposto_razional) {
	Rational* number = new Rational(1,2);
	Number* opposite = number->opposto();
	mu_check(strcmp("-1/2",opposite->to_string())==0);
}

MU_TEST(dividi_razionale_intero) {
	Number* number = new Rational(2,1);
	Number* second = new Integer(2);
	Number* result = number->dividi(second);
	mu_check(strcmp("1/1",result->to_string())==0);
}

MU_TEST(dividi_razionali) {
	Number* number = new Rational(3,2);
	Number* second = new Rational(2,4);
	Number* result = number->dividi(second);
	mu_check(strcmp("3/1",result->to_string())==0);
}


MU_TEST(istanzia_complesso) {
	Number* number = new Complex(new Rational(1,1),new Rational(1,1));
	mu_check(strcmp("1/1+(1/1)*i",number->to_string())==0);
}

MU_TEST(somma_complessi) {
	Number* number = new Complex(new Rational(1,1),new Rational(1,1));
	Number* number2 = new Complex(new Rational(1,1),new Rational(1,1));
	Number* result  = number->somma(number2);
	mu_check(strcmp("2/1+(2/1)*i",result->to_string())==0);
}


MU_TEST(somma_complesso_razionale) {
	Number* number = new Complex(new Rational(1,1),new Rational(1,1));
	Number* number2 = new Rational(1,1);
	Number* result  = number->somma(number2);
	mu_check(strcmp("2/1+(1/1)*i",result->to_string())==0);
}

MU_TEST(somma_razionale_complesso) {

	Number* number = new Rational(1,1);
	Number* number2 = new Complex(new Rational(1,1),new Rational(1,1));
	Number* result  = number->somma(number2);
	mu_check(strcmp("2/1+(1/1)*i",result->to_string())==0);
}

MU_TEST(somma_complesso_intero) {
	Number* number = new Complex(new Rational(1,1),new Rational(1,1));
	Number* number2 = new Integer(1);
	Number* result  = number->somma(number2);
	mu_check(strcmp("2/1+(1/1)*i",result->to_string())==0);
}

MU_TEST(somma_intero_complesso) {
	Number* number = new Integer(1);
	Number* number2 = new Complex(new Rational(1,1),new Rational(1,1));
	Number* result  = number->somma(number2);
	mu_check(strcmp("2/1+(1/1)*i",result->to_string())==0);
}

MU_TEST(prodotto_complessi) {
	Number* number = new Complex(new Rational(1,1),new Rational(0,1));
	Number* second = new Complex(new Rational(1,1),new Rational(0,1));
	Number* result = number->moltiplica(second);
	mu_check(strcmp("1/1+(0/1)*i",result->to_string())==0);
}

// ignored
MU_TEST(prodotto_complessi_2) {
	Number* number = new Complex(new Rational(1,1),new Rational(1,1));
	Number* second = new Complex(new Rational(1,1),new Rational(1,1));
	Number* result = number->moltiplica(second);
	mu_check(strcmp("0/1+(2/1)*i",result->to_string())==0);
}

MU_TEST(prodotto_complessi_3) {
	Number* number = new Complex(new Rational(1,1),new Rational(1,1));
	Number* second = new Complex(new Rational(1,1),new Rational(0,1));
	Number* result = number->moltiplica(second);
	mu_check(strcmp("1/1+(1/1)*i",result->to_string())==0);
}

MU_TEST(prodotto_complessi_4) {
	Number* number = new Complex(new Rational(1,1),new Rational(1,1));
	Number* second = new Complex(new Rational(1,1),new Rational(0,1));
	Number* result = number->moltiplica(second);
	mu_check(strcmp("1/1+(1/1)*i",result->to_string())==0);
}


MU_TEST(costruzione_numero_da_stringa_vuota) {
	Integer* zero = (Integer*)(string_to_number((char*)""));
	mu_check(strcmp("0",zero->to_string())==0);
}

MU_TEST(costruzione_numero_da_stringa_1) {
	Integer* zero = (Integer*)(string_to_number((char*)"1"));
	mu_check(strcmp("1",zero->to_string())==0);
}

MU_TEST(costruzione_numero_da_stringa_errata_non_porta_ad_alcuna_eccezione) {
	bool got_exception=false;
	Integer* aNumber;
	try {
		aNumber = (Integer*)string_to_number((char*)"abcde");
	} catch (std::runtime_error my_error) {
		got_exception=true;
	}
	mu_check(got_exception==false);
}

MU_TEST(costruzione_di_numero_razionale) {
	Number* number = string_to_number((char*)"1/2");
	mu_check(strcmp("1/2",number->to_string())==0);
}

MU_TEST(string_to_int_test_1) {
	int actual = string_to_int((char*)"1234");
	int expected = 1234;
	mu_check(expected==actual);
}

MU_TEST(string_to_int_test_2) {
	int actual = string_to_int((char*)"341");
	int expected = 341;
	mu_check(expected==actual);
}

MU_TEST(costruzione_di_numero_razionale_2) {
	Number* number = string_to_number((char*)"341/267");
	printf ("%s\n",number->to_string());
	mu_check(strcmp("341/267",number->to_string())==0);
}

MU_TEST(costruzione_di_numero_razionale_2_test) {
	Number* number = string_to_number((char*)"341/1");
	Rational* rational = new Rational(341,1);
	mu_check(strcmp("341/1",number->to_string())==0);
}

MU_TEST(costruzione_di_numero_razionale_2_test_2) {
	Number* number = string_to_number((char*)"341/11");
	Rational* rational = new Rational(341,11);
	mu_check(strcmp("31/1",number->to_string())==0);
}

MU_TEST(costruzione_di_numero_razionale_2_test_2_con_spazi) {
	char buffer[97];
	strcpy(buffer," 341/11  ");
	Number* number = string_to_number(buffer);
	Rational* rational = new Rational(341,11);
	mu_check(strcmp("31/1",number->to_string())==0);
}

MU_TEST(costruzione_di_numero_razionale_2_test_2_con_spazi_prima) {
	char buffer[97];
	strcpy(buffer," 341/11");
	Number* number = string_to_number(buffer);
	Rational* rational = new Rational(341,11);
	mu_check(strcmp("31/1",number->to_string())==0);
}

MU_TEST(costruzione_di_numero_razionale_2_test_2_con_spazi_dopo) {
	char buffer[97];
	strcpy(buffer,"341/11 ");
	Number* number = string_to_number(buffer);
	Rational* rational = new Rational(341,11);
	mu_check(strcmp("31/1",number->to_string())==0);
}

MU_TEST(costruzione_numero_da_stringa_0) {
	Integer* zero = new Integer(0);
	mu_check(strcmp("0",zero->to_string())==0);
}

MU_TEST(costruzione_numero_da_stringa_nulla) {
	Number* actual= string_to_number((char*)"");
	mu_check(strcmp("0",actual->to_string())==0);
}


MU_TEST(parse_expression_null_string) {
	Number* actual= parse_expression((char*)"");
	mu_check(strcmp("0",actual->to_string())==0);
}

MU_TEST(parse_plain_integer_string_expression) {
	Number* actual= parse_expression((char*)"1");
	mu_check(strcmp("1",actual->to_string())==0);
}

MU_TEST(parse_plain_rational_string_expression) {
	Number* actual= parse_expression((char*)"1/2");
	mu_check(strcmp("1/2",actual->to_string())==0);
}

MU_TEST(parse_expression_by_with_spaces) {
	Number* actual= parse_expression((char*)" 1/2 ");
	printf ("%s\n",actual->to_string());
	mu_check(strcmp("1/2",actual->to_string())==0);
}


MU_TEST(parse_sum_expression_between_integer) {
	Number* actual= parse_expression((char*)"1+1");
	mu_check(strcmp("2",actual->to_string())==0);
}

MU_TEST(syntax_tree_composed_by_single_integer) {
	Syntax_tree* node = new Number_node_tree(new Integer(1));
	mu_check(strcmp("1",node->eval()->to_string())==0);
}

MU_TEST(syntax_tree_sum_composed_by_binary_expression) {
	Syntax_tree* node = new Expression_node_tree(new Number_node_tree(new Integer(1)),'+',new Number_node_tree(new Integer(1)));
	mu_check(strcmp("2",node->eval()->to_string())==0);
}

MU_TEST(syntax_tree_product_composed_by_binary_expression) {
	Syntax_tree* node = new Expression_node_tree(new Number_node_tree(new Integer(1)),'*',new Number_node_tree(new Integer(1)));
	mu_check(strcmp("1",node->eval()->to_string())==0);
}

MU_TEST(syntax_tree_product_composed_by_binary_expression_2) {
	Syntax_tree* node = new Expression_node_tree(new Number_node_tree(new Integer(2)),'*',new Number_node_tree(new Integer(2)));
	mu_check(strcmp("4",node->eval()->to_string())==0);
}

MU_TEST(build_node_by_string_expression_of_single_integer_number) {
	Syntax_tree* actual_syntax_tree	= expression_to_syntax_tree((char*)"");
	mu_check(strcmp("0",actual_syntax_tree->eval()->to_string())==0);
}

MU_TEST(build_node_by_string_expression_of_single_integer_number_zero) {
	Syntax_tree* actual_syntax_tree	= expression_to_syntax_tree((char*)"0");
	mu_check(strcmp("0",actual_syntax_tree->eval()->to_string())==0);
}

MU_TEST(build_node_by_string_expression_of_sum_of_integers) {
	Syntax_tree* actual_syntax_tree	= expression_to_syntax_tree((char*)"1+1");
	mu_check(strcmp("1",actual_syntax_tree->eval()->to_string())==0);
}


MU_TEST(split_mesages_to_string_list_empty_string_is_empty_list) {
	StringExpressionToList* expression_manager = new StringExpressionToList((char*)"");
	std::list<std::string> converted_to_list = expression_manager->get_listed_expression();
	mu_check(converted_to_list.size() == 0);
}

MU_TEST(split_mesages_to_string_list_for_list_of_one_element) {
	StringExpressionToList* expression_manager = new StringExpressionToList((char*)"1");
	std::list<std::string> converted_to_list = expression_manager->get_listed_expression();
	mu_check(converted_to_list.size() == 1);
}

MU_TEST(expression_manager_test) {
	char buffer[97];
	strcpy(buffer,"1+1");
	StringExpressionToList* stringExpressionManager = new StringExpressionToList(buffer);
	mu_check(3==stringExpressionManager->get_listed_expression().size());
}

MU_TEST(expression_manager_test2) {
	char buffer[97];
	strcpy(buffer,"11+1");

	StringExpressionToList* stringExpressionManager = new StringExpressionToList(buffer);
	printf("size: %d",(int)stringExpressionManager->get_listed_expression().size());

	std::list<std::string> msg = stringExpressionManager->get_listed_expression();

	int n = msg.size();
	printf ("mysize: %d\n",n);

	mu_check(4==(int)msg.size());
	
	int i=0;
	for (auto it = msg.begin();i<n;it++,i++) {
		printf("eccolo: %s\n",(*it).c_str());
	}

	// mu_check(3==msg.sizestringExpressionManager->get_listed_expression().size());

    // int i=0;
    // for (auto it = previous_messages.begin();i<n;it++,i++) {
    //     update((char*)(*it).c_str());
    // }
    // previous_messages.clear();

}

MU_TEST(expression_to_tree_empty_expession_is_zero) {
	char expression[97];
	strcpy(expression,"");
	Syntax_tree* from_expression = expression_to_syntax_tree(expression);
	mu_check(strcmp("0",from_expression->eval()->to_string())==0);
}

MU_TEST(expression_to_tree_for_zero_number_is_zeroe) {
	char expression[97];
	strcpy(expression,"0");
	Syntax_tree* from_expression = expression_to_syntax_tree(expression);
	mu_check(strcmp("0",from_expression->eval()->to_string())==0);
}

MU_TEST(expression_to_tree_for_number_one_is_one) {
	char expression[97];
	strcpy(expression,"1");
	Syntax_tree* from_expression = expression_to_syntax_tree(expression);
	mu_check(strcmp("1",from_expression->eval()->to_string())==0);
}

MU_TEST(expression_to_tree_for_any_rational_is_the_rational) {
	char expression[97];
	strcpy(expression,"1/1");
	Syntax_tree* from_expression = expression_to_syntax_tree(expression);
	mu_check(strcmp("1/1",from_expression->eval()->to_string())==0);
}

MU_TEST(expression_to_tree_for_sum_expression) {
	char expression[97];
	strcpy(expression,"1+1");
	Syntax_tree* from_expression = expression_to_syntax_tree(expression);
	mu_check(strcmp("2",from_expression->eval()->to_string())==0);
}

MU_TEST(empty_expression_leads_to_zero_tree) {
	Syntax_tree* iter_tree = NULL;
	char expression[97];
	strcpy(expression,"");
	Syntax_tree* from_expression = expression_to_syntax_tree_iter(expression,&iter_tree,'\0');
	mu_check(strcmp("0",from_expression->eval()->to_string())==0);
}

MU_TEST(zero_expression_leads_to_zero_tree) {
	Syntax_tree* iter_tree = NULL;
	char expression[97];
	strcpy(expression,"0");
	Syntax_tree* from_expression = expression_to_syntax_tree_iter(expression,&iter_tree,'\0');
	mu_check(strcmp("0",from_expression->eval()->to_string())==0);
}



MU_TEST(test_trim_before) {
	char to_trim[10];

	strcpy(to_trim,"    trim" );
	trim_left_and_right(to_trim);

	mu_check(strcmp(to_trim,"trim")==0);

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
	MU_RUN_TEST(reciproco_di_razionale);
	MU_RUN_TEST(divide_rationals);
	MU_RUN_TEST(divide_rationals_2);
	MU_RUN_TEST(dividi_razionale_intero);
	MU_RUN_TEST(somma_intero_razionale);
	MU_RUN_TEST(somma_razionale_intero);
	MU_RUN_TEST(istanzia_complesso);
	MU_RUN_TEST(somma_complessi);
	MU_RUN_TEST(somma_complesso_razionale);
	MU_RUN_TEST(somma_complesso_intero);
	MU_RUN_TEST(somma_intero_complesso);
	MU_RUN_TEST(somma_razionale_complesso);
	MU_RUN_TEST(prodotto_complessi);
	MU_RUN_TEST(prodotto_complessi_2);
	MU_RUN_TEST(prodotto_complessi_3);
	MU_RUN_TEST(prodotto_complessi_4);
	MU_RUN_TEST(prodotto_razionale_intero);
	MU_RUN_TEST(prodotto_intero_razional);
	MU_RUN_TEST(divisione_intero_razionale);
	MU_RUN_TEST(divisione_intero_raz_va_in_errore);
	MU_RUN_TEST(dividi_razionali);
	MU_RUN_TEST(costruzione_numero_da_stringa_vuota);
	MU_RUN_TEST(costruzione_numero_da_stringa_1);
	MU_RUN_TEST(costruzione_numero_da_stringa_0);
	MU_RUN_TEST(costruzione_numero_da_stringa_errata_non_porta_ad_alcuna_eccezione);
	MU_RUN_TEST(costruzione_di_numero_razionale);
	MU_RUN_TEST(costruzione_di_numero_razionale_2);
	MU_RUN_TEST(costruzione_di_numero_razionale_2_test_2);
	MU_RUN_TEST(string_to_int_test_2);
	MU_RUN_TEST(costruzione_numero_da_stringa_nulla);
	MU_RUN_TEST(parse_expression_null_string);
	MU_RUN_TEST(parse_plain_integer_string_expression);
	MU_RUN_TEST(parse_plain_rational_string_expression);


	// MU_RUN_TEST(parse_expression_by_with_spaces);
	// MU_RUN_TEST(parse_sum_expression_between_integer);

	MU_RUN_TEST(syntax_tree_composed_by_single_integer);
	MU_RUN_TEST(syntax_tree_sum_composed_by_binary_expression);

	MU_RUN_TEST(syntax_tree_product_composed_by_binary_expression);
	MU_RUN_TEST(syntax_tree_product_composed_by_binary_expression_2);
	MU_RUN_TEST(build_node_by_string_expression_of_single_integer_number);
	MU_RUN_TEST(build_node_by_string_expression_of_single_integer_number_zero);

	 MU_RUN_TEST(split_mesages_to_string_list_empty_string_is_empty_list);

	 MU_RUN_TEST(test_trim_before);
	 MU_RUN_TEST(costruzione_di_numero_razionale_2_test_2_con_spazi);
	 MU_RUN_TEST(costruzione_di_numero_razionale_2_test_2_con_spazi_prima);
	 MU_RUN_TEST(costruzione_di_numero_razionale_2_test_2_con_spazi_dopo);
	 MU_RUN_TEST(expression_to_tree_empty_expession_is_zero);
	 MU_RUN_TEST(expression_to_tree_for_zero_number_is_zeroe);
	 MU_RUN_TEST(expression_to_tree_for_number_one_is_one);
	 MU_RUN_TEST(expression_to_tree_for_any_rational_is_the_rational);
	//  MU_RUN_TEST(expression_to_tree_for_sum_expression);
	 MU_RUN_TEST(empty_expression_leads_to_zero_tree);
	 MU_RUN_TEST(zero_expression_leads_to_zero_tree);

	//  MU_RUN_TEST(expression_manager_test);
	//  MU_RUN_TEST(expression_manager_test2);

	 MU_RUN_TEST(int_comparer_test);
	 MU_RUN_TEST(chunk_delimiter_test);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}

