#include "../card/card.h"
#define _CRT_SECURE_NO_WARNINGS


ST_cardData_t user;

/*
-----------------------------------------------------

funtion Check the CARD Holder Name from customer

-----------------------------------------------------
*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

    printf("Please Enter The Name of Card : \n");
    gets(cardData->cardHolderName);
    fflush(stdin);
    wait_second();   
    if ((cardData->cardHolderName) != NULL) {
        if (strlen(cardData->cardHolderName) < 25 && strlen(cardData->cardHolderName) >= 20)
        {
            return CARD_OK;
        }
        else {
            return WRONG_NAME;
        }
    }
}

/*
--------------------------------------------------------

THIS Function Card Expiry Date

--------------------------------------------------------
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
    printf("Please Enter The Expiry Date of Card :\t [MM/YY] :\n");
    gets((cardData->cardExpirationDate));
    fflush(stdin);
    wait_second();
    if (strlen(cardData->cardExpirationDate) == NULL || strlen((cardData->cardExpirationDate)) != 5)
        
            return WRONG_EXP_DATE;
    if (check_date((cardData->cardExpirationDate))==0) 
            return WRONG_EXP_DATE; 
   
    return CARD_OK;
}

/*
--------------------------------------------------------

THIS Function Card PAN

--------------------------------------------------------
*/

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {

    printf("Please Enter your Card PAN number  : \t \n");
    gets((cardData->primaryAccountNumber));
    fflush(stdin);
    wait_second();
    if(strlen(cardData->primaryAccountNumber) <= 19)
    if (strlen(cardData->primaryAccountNumber) != NULL 
        && strlen(cardData->primaryAccountNumber) >= 16 )
    {
        return CARD_OK;
    }
    else {
        return WRONG_PAN;
    }

}

/*
--------------------------------------------------------
THIS TEST FUNCTION
--------------------------------------------------------
*/ 

void getCardHolderNameTest(void) {
    if (getCardHolderName(&user) == CARD_OK) {
        printf("CARD OK \n\n");
    }
    else {
        printf("WRONG_NAME\n\n");
    }
}
void getCardExpiryDateTest(void) {
    if (getCardExpiryDate(&user) == CARD_OK) {
        printf("CARD OK \n\n");
    }
    else {
        printf("WRONG_EXP_DATE\n\n");
    }
}
void getCardPANTest(void) {
    if (getCardPAN(&user) == CARD_OK) {
        printf("CARD OK \n\n");
    }
    else {
        printf("WRONG_PAN\n\n");
    }
}
/*
--------------------------------------------------------
THIS HELPFULL FUNCTION
--------------------------------------------------------
*/
void wait_second(void) {
    printf("\t Waiting  \t");
    for (int i = 0; i < 5; i++)
    {
        printf(".");
        Sleep(200);
    }
    printf("\n");
}

int check_date(const char* str) {
    int len = strlen(str);
    if (len != 5 || str[2] != '/') {
        return 0;
    }
    for (int i = 0; i < 5; i++) {
        if(i==2) continue;
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}