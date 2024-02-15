#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
typedef uint8_t;


/*
--------------------------------------------------------
THIS Define of DataType 
--------------------------------------------------------
*/
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/*
--------------------------------------------------------
THIS Function Define
--------------------------------------------------------
*/

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

/*
--------------------------------------------------------
THIS TEST FUNCTION
--------------------------------------------------------
*/
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);
/*
--------------------------------------------------------
THIS HELPFULL FUNCTION
--------------------------------------------------------
*/

void wait_second(void);
int check_date(const char* str);

