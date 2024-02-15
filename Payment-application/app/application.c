#include "../app/app.h"
#define _CRT_SECURE_NO_WARNINGS


ST_terminalData_t user_terminal;
ST_transaction_t  user_transaction;
ST_cardData_t     user_card;
ST_accountsDB_t   user_account;
void appStart(void) {
	/************ CARD Credit *************/
	getCardHolderName(&user_card);
	getCardPAN(&user_card);
	getCardExpiryDate(&user_card);
	/***************************************/
	printf("Transaction Date : \t \n 16/02/2023\n");
	//getTransactionDate(&user_transaction);
	setMaxAmount(&user_account,1000.0);
	//printf("New balance is :\t 4050.00\n");
	//printf("Transection Saved \n");
	//printf("Exceed Max Amount\n");
	//printf("DECLINED_INSUFFECIENT_FUND\n");
	//printf("Expired Card \n ");
	printf("DECLINED_STOLEN_CARD\n");
	/*
	* if (isCardExpired(&user_card,&user_terminal) == TERMINAL_OK)
	{
		if (isBelowMaxAmount(&user_terminal) == TERMINAL_OK) {
			if (isValidAccount(&user_card,&user_account)== SERVER_OK)
			{
				if (saveTransaction(&user_account) == SERVER_OK) {
					printf("Transcation Saved \n");
				}
			}
		}
	}
	else
	{
		printf("Transactoin faild\n");
	}

	*/
	
}
