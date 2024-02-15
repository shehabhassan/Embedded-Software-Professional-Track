#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "../card/card.h"
#define _CRT_SECURE_NO_WARNINGS

/*
--------------------------------------------------------
THIS Define of DataType
--------------------------------------------------------
*/
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT

}EN_terminalError_t;
/*
--------------------------------------------------------

THIS Function Define

--------------------------------------------------------
*/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional

/*
--------------------------------------------------------
THIS TEST FUNCTION
--------------------------------------------------------
*/
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);

/*
--------------------------------------------------------

THIS HELPFULL FUNCTION

--------------------------------------------------------
*/

int check_date_term(const char* str);
int st_to_i(const char* string);
int st_toi_term(const char* string);
int st_to_i_mon(const char* string);