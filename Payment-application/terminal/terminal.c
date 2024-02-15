#include "terminal.h"
#define _CRT_SECURE_NO_WARNINGS

ST_terminalData_t user2;
ST_cardData_t user;
/*
--------------------------------------------------------

THIS Function Card PAN

--------------------------------------------------------
*/

float maxAmount = 20000;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	
	printf("Please Enter The Transcation date : [DD/MM/YYYY]\n");
	gets((termData->transactionDate));
	fflush(stdin);
	wait_second();
	//logic for check the transiction input is correct. 
	if (check_date_term(termData->transactionDate));   /*check the format is right */

	if ((termData->transactionDate) != NULL && strlen(termData->transactionDate) == 10) {
		return TERMINAL_OK;
	}
	else {
		return WRONG_DATE;  
	}
}

/*
--------------------------------------------------------

THIS Function Card PAN

--------------------------------------------------------
*/

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	printf("Please Enter The Expiry Date of Card :\t [MM/YY] :\n");
	gets((cardData->cardExpirationDate));
	fflush(stdin);
	wait_second();
	//logic to test the validation of card 
	//printf("%i\n",st_to_i(cardData->cardExpirationDate));
	//printf("%i\n",atoi(cardData->cardExpirationDate));

	if (st_to_i(cardData->cardExpirationDate) < st_toi_term(termData->transactionDate) 
	 || st_to_i(cardData->cardExpirationDate) == st_toi_term(termData->transactionDate))
	{	
	  if(st_to_i_mon(termData->transactionDate) > atoi(cardData->cardExpirationDate))
		return EXPIRED_CARD;
	}
	else
	{
	}
		return TERMINAL_OK;

}

/*
--------------------------------------------------------

THIS Function Card PAN

--------------------------------------------------------
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	
	printf("Please Enter The Transcation a mount : \n");
	scanf_s("%f",&(termData->transAmount));
	fflush(stdin);
	wait_second();
    if ((termData->transAmount) <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}
}



/*
--------------------------------------------------------

THIS Function set Max Amount

--------------------------------------------------------
*/

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
	printf("Please Enter The Max Amount   : \n");
	scanf_s("%f", &(termData->maxTransAmount));
	fflush(stdin);
	wait_second();
	if ((termData->maxTransAmount) <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else{ 
		termData->transAmount == maxAmount;
		return TERMINAL_OK;
	}

}
/*
--------------------------------------------------------

THIS Function is Below Max Amount

--------------------------------------------------------
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {

	printf("Please Enter The Amount Number : \n");

	scanf_s("%f", &(termData->transAmount));
	fflush(stdin);
	wait_second();
	if ((termData->transAmount) > termData->maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}
}
/*
--------------------------------------------------------
THIS TEST FUNCTION
--------------------------------------------------------
*/
void getTransactionDateTest(void) {
	if (getTransactionDate(&user2) == TERMINAL_OK) {
		printf("TERMINAL_OK\n");
	}
	else {
		printf("WRONG_DATE\n");
	}
}
void isCardExpriedTest(void) {

	if (isCardExpired(&user,&user2)==TERMINAL_OK){
		printf("TERMINAL_OK\n");
	}
	else {
		printf("EXPIRED_CARD\n");
	}

}
void getTransactionAmountTest(void) {
	if (getTransactionAmount(&user2) == TERMINAL_OK) {
		printf("TERMINAL_OK\n");
	}
	else {
		printf("INVALID_AMOUNT\n");
	}
}
void isBelowMaxAmountTest(void) {
	if (isBelowMaxAmount(&user2) == TERMINAL_OK) {
		printf("TERMINAL_OK\n");
	}
	else {
		printf("EXCEED_MAX_AMOUNT\n");
	}
}
void setMaxAmountTest(void) {
	if (setMaxAmount(&user2, maxAmount) == TERMINAL_OK) {
		printf("TERMINAL_OK\n");
	}
	else {
		printf("INVALID_MAX_AMOUNT\n");
	}
}

/*
--------------------------------------------------------

THIS HELPFULL FUNCTION

--------------------------------------------------------
*/

int check_date_term(const char* str1) {
	int len1 = strlen(str1);
	if (len1 != 5 || str1[2] != '/' || len1 != 10 || str1[5] != '/') {
		return 0;
	}
	for (int i = 0; i < 10; i++) {
		if (i == 2 || i==5) continue;
		if (isdigit(str1[i])) {
			return 0;
		}
	}
	return 1;
}
int st_to_i_mon(const char* string) {
	int result = 0;
	int negative = 1;
	int i = 3;

	if (string[0] == '/') {
		negative = -1;
		i++;
	}
	for (; string[i] != '\0'; i++) {
		result = result * 10 + (string[i] - '0');
	}
	return result * negative;
}
int st_to_i(const char* string) {
	int result = 0;
	int negative = 1;
	int i = 3;

	if (string[0] == '/') {
		negative = -1;
		i++;
	}
	for (; string[i] != '\0'; i++) {
		result = result * 10 + (string[i] - '0');
	}
	return result * negative;
}
int st_toi_term(const char* string) {
	int result = 0;
	int negative = 1;
	int i = 8;

	if (string[0] == '/') {
		negative = -1;
		i++;
	}
	for (; string[i] != '\0'; i++) {
		result = result * 10 + (string[i] - '0');
	}
	return result * negative;
}

