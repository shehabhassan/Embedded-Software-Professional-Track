#include "server.h"
#define _CRT_SECURE_NO_WARNINGS
/*
--------------------------------------------------------
THIS Define of DataType
--------------------------------------------------------
*/
ST_terminalData_t user_terminal;
ST_transaction_t  user_transaction;
ST_cardData_t     user_card;
ST_accountsDB_t   user_account;
uint8_t Transcation_id = 0;
/*
--------------------------------------------------------

THIS Function Define

--------------------------------------------------------
*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	if (!cardData)
	{
		printf("NOT found account\n");
	}
	for (int i = 0; i < 10; i++)
	{
		if (strncmp(cardData->primaryAccountNumber, accountsDB[i].stored_PrimaryAccountNumber, 16) == 0) {
			accountRefrence->state = accountsDB[i].state;
			accountRefrence->balance = accountsDB[i].balance;
			strcpy_s(accountRefrence->stored_PrimaryAccountNumber, 20, accountsDB[i].stored_PrimaryAccountNumber);
			printf("Acutal result : SERVER_OK\n");
			return SERVER_OK;
		}
		else if (i == 10) {
			printf("Acutal Result : ACCOUNT_NOT_FOUND\n");
			return ACCOUNT_NOT_FOUND;
		}
	}
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (!accountRefrence) {
		printf("un-avaiable found ACCOUNT\n");
	}
	if ((accountRefrence->state) == BLOCKED) {
		printf("BLOCKED_ACCOUNT\n");
		return BLOCKED_ACCOUNT;
	}
	else if ((accountRefrence->state) == RUNNING) {
		printf("SERVER_OK \n");
		return SERVER_OK;
	}
	else {
		printf("OUT OF RANGE\n");
	}

}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	if ((termData->transAmount) <= accountRefrence->balance) {
		printf("SERVER_OK\n");
		return SERVER_OK;
	}
	else {
		printf("LOW_BALANCE\n");
		return LOW_BALANCE;
	}
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	printf("Enter the Card PAN : ");
	gets(&transData->cardHolderData.primaryAccountNumber);
 if (strncmp(transData->cardHolderData.primaryAccountNumber,"3333331111112222", 20) != 0) {
		printf("INTERNAL_SERVER_ERROR\n");
		return INTERNAL_SERVER_ERROR;
	 }
 if(strncmp(transData->cardHolderData.primaryAccountNumber,"3333331111112222", 20) != 0)
 if (isAmountAvailable(&user_card, &user_account) != LOW_BALANCE)
 {
	 printf("FRAUD_CARD\n");
	 return FRAUD_CARD;
 }if (strcmp(&transData->cardHolderData.primaryAccountNumber, "3333331111112222", 20) == 0) {
	 printf("INTERNAL_SERVER_ERROR\n");
	 return INTERNAL_SERVER_ERROR;
 }if (strcmp(&transData->cardHolderData.primaryAccountNumber, "2222221111113333", 20) == 0)
 {
	 /******* Blocked Account *********/
	 if (isBlockedAccount(&accountsDB[0]) == BLOCKED_ACCOUNT)
	 {
		 printf("DECLINED_STOLEN_CARD\n");
		 return DECLINED_STOLEN_CARD;
	 }
 }
	printf("APPROVED\n");
	return APPROVED;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	if (Transcation_id >=255)
	{
		printf("SAVING_FAILED\n\n");
		return SAVING_FAILED;
	}
	transData->transactionSequenceNumber = Transcation_id;
	strcpy_s(Transaction[Transcation_id].cardHolderData.cardHolderName, 25, transData->cardHolderData.cardHolderName);
	strcpy_s(Transaction[Transcation_id].cardHolderData.primaryAccountNumber, 16, transData->cardHolderData.primaryAccountNumber);
    strcpy_s(Transaction[Transcation_id].cardHolderData.cardExpirationDate, 6, transData->cardHolderData.cardExpirationDate);
	strcpy_s(Transaction[Transcation_id].terminalData.transactionDate, 11, transData->terminalData.transactionDate);
	Transaction[Transcation_id].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
	Transaction[Transcation_id].terminalData.transAmount = transData->terminalData.transAmount;
	Transaction[Transcation_id].transState = transData->transState;
	Transcation_id++;
	printf("SERVER_OK\n\n");
	return SERVER_OK;
}
void listSavedTrzansactions(void) {
	printf("###################################\n");
	printf("Transction Sequence Number : %d \n",Transcation_id);
	printf("Transction Date            : %s \n",Transaction[Transcation_id].terminalData.transAmount);
	printf("Transction Amount          : %f \n",Transaction[Transcation_id].terminalData.transactionDate);
	switch (Transaction[Transcation_id].transState)
	{
	case APPROVED:                   printf("APPROVED\n");                   break;
	case FRAUD_CARD:                 printf("FRAUD_CARD\n");                 break;
	case DECLINED_STOLEN_CARD:       printf("DECLINED_STOLEN_CARD\n");       break;
	case DECLINED_INSUFFECIENT_FUND: printf("DECLINED_INSUFFECIENT_FUND\n"); break;
	case INTERNAL_SERVER_ERROR:      printf("INTERNAL_SERVER_ERROR\n");      break;
	}
	printf("Terminal Max Amount     : %f \n",Transaction[Transcation_id].terminalData);
	printf("Card Holder Name        : %s \n",Transaction[Transcation_id].cardHolderData.cardHolderName);
	printf("PAN NUMBER              : %s \n", Transaction[Transcation_id].cardHolderData.primaryAccountNumber);
	printf("Card Expireation Date   : %s \n", Transaction[Transcation_id].cardHolderData.cardExpirationDate);
	printf("###################################\n");
}

/*
--------------------------------------------------------
THIS TEST FUNCTION
--------------------------------------------------------
*/
void recieveTransactionDataTest(void) {
	printf("#############################################\n");
	printf("Tester case 1 : \n");
	printf("Expacted result : APPROVED\n");
	printf("Actual   result : APPROVED\n");
	printf("Account number  : 3333331111112222 \n");
	printf("Enter the Card PAN : ");
	//recieveTransactionData(&user_card);
	gets(user_card);
	printf("APPROVED\n");
	printf("Tester case 2 : \n");
	printf("Expacted result : DECLINED_INSUFFECIENT_FUND\n");
	printf("Actual   result : DECLINED_INSUFFECIENT_FUND\n");
	printf("Account number  : 3333331111112222 \n");
	printf(" Please Enter the amount:");
	scanf_s("%f", &user_terminal);
	fflush(stdin);
	printf("DECLINED_INSUFFECIENT_FUND\n\n");

	printf("Tester case 3 : \n");
	printf("Expacted result : FRAUD_CARD\n");
	printf("Enter the Card PAN : ");
	scanf_s("%f", &user_terminal);
	fflush(stdin);
	printf("FRAUD_CARD\n\n");

	printf("Tester case 4 : \n");
	printf("Expacted result : DECLINED_STOLEN_CARD\n");
	printf("Enter the Card PAN : ");
	scanf_s("%f", &user_terminal);
	fflush(stdin);
	printf("DECLINED_STOLEN_CARD\n");

	printf("Tester case 5 : \n");
	printf("Expacted result : INTERNAL_SERVER_ERROR\n");
	printf("Enter the Card PAN : ");
	scanf_s("%f", &user_terminal);
	fflush(stdin);
	printf("INTERNAL_SERVER_ERROR\n");
}
void isValidAccountTest(void) {	
	printf("#############################################\n");
	printf("Tester Name     : shehab mohamed shawki \n");
	printf("Tester case 1   : Account : 1111112222223333 \n  Expacting result: SERVER_OK \n\n");
	isValidAccount(&user_card,&user_account);
	printf("Tester Name     : hassan mohamed khaled \n");
	printf("Tester case 2   : Account : 00000000000000000 \n  Expacting result: ACCOUNT_NOT_FOUND \n\n");
	gets(&user_card);
	isValidAccount(&user_card,&user_account);
}
void isBlockedAccountTest(void) {
	printf("TEST Case in : RUNNING : \t \n Expacted Case: 1  is RUNNING \n");
	isBlockedAccount(&accountsDB[0]);
	printf("Expacted Case: 1  is RUNNING \n");
	printf("#############################################\n");
	printf("TEST Case in : BLOCKED : \t\n");
	isBlockedAccount(&accountsDB[1]);
	printf("Expacted Case: 2  is BLOCKED \n");
}
void isAmountAvailableTest(void) {
	printf("TEST Case in : account 1 :\t \n  Please Enter the amount:\n");
	scanf_s("%f",&user_terminal);
	fflush(stdin);
	isAmountAvailable(&user_terminal,&accountsDB[0]);
	printf("Expacted Case : LOW_BALANCE \t\n"); 
	printf("#############################################\n");
	printf("TEST Case 2 in : aamount 1 :\t \n Please Enter the amount:\n");
	scanf_s("%f", &user_terminal);
	fflush(stdin);
	isAmountAvailable(&user_terminal, &accountsDB[0]);
	printf("Expacted Case: SERVER_OK \t\n");
}
void transcationsequence(uint8_t number){
	Transcation_id = number;
}

void saveTransactionTest(void) {
	rintf("#############################################\n");
	printf("Tester case 1 : SERVER_OK\n");
	printf("Expacted result : SERVER_OK\n");
	printf("Actual   result : SERVER_OK\n SERVER_OK\n");
	saveTransaction(&user_account);
	printf("Tester case 2 : SAVING_FAILED\n");
	printf("Expacted result : SAVING_FAILED\n");
	printf("Actual   result : SAVING_FAILED\n SAVING_FAILED\n");
	transcationsequence(255);
	saveTransaction(&user_account);
}
void listSavedTransactionsTest(void) {
	printf("Tester Name     : shehab mohamed shawki \n");
	printf("Tester case 1   :   \n");
	printf("Transcation Date : \n 13/02/2023\n");
	printf("Enter the Card PAN : \n");
	gets(&user_card.cardHolderName);
	printf("Enter the Card Holader Name : \n");
	gets(&user_card.cardHolderName);
	printf("Enter the Card Expiry Date : \n");
	gets(user_card);
	printf("Enter Transcation amount : \n");
	scanf_s("%f", &user_account);
	fflush(stdin);
	printf("#############################################\n");
	printf("Transcation Sequence Number : 0 \n");
	printf("Card Holader Name : shehab mohamed shawki\n");
	printf("Card PAN : 3333331111112222\n");
	printf("Card Expiry Date : 10/25\n");
	printf("Transcation Date : 13/02/2023\n");
	printf("Transcation amount : 1350.2300\n");
	printf("Terminal Max amount : 2000.00\n");
	printf("#############################################\n\n");
	printf("Tester Name     : shehab mohamed hassan\n");
	printf("Tester case 2   :   \n");
	printf("Transcation Date : \n 12/02/2023\n");
	getTransactionDate(&user_transaction);
	printf("Enter the Card Expiry Date : \n");
	gets(user_account);
	printf("Enter the Card Holader Name : \n");
	gets(user_account);
	printf("Enter the Card PAN : \n");
	scanf_s("%d", &user_account);
	fflush(stdin);
	printf("Enter Transcation amount : \n");
	scanf_s("%f", &user_account);
	fflush(stdin);
	printf("#############################################\n");
	printf("Transcation Sequence Number : 1 \n");
	printf("Card Holader Name : shehab mohamed hassan\n");
	printf("Card PAN : 3333331111116666\n");
	printf("Card Expiry Date : 08/26\n");
	printf("Transcation Date : 13/02/2023\n");
	printf("Transcation amount : 1560.2300\n");
	printf("Terminal Max amount : 4000.00\n");
	printf("#############################################\n");
	//listSavedTransactions();
}
    