#pragma once
#include "../card/card.h"
#include "../terminal/terminal.h"
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS

/*
--------------------------------------------------------
THIS input from user.
--------------------------------------------------------
*/

typedef uint32_t;

/*
--------------------------------------------------------

THIS Define of DataType

--------------------------------------------------------
*/
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;


typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;


typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t *stored_PrimaryAccountNumber;
}ST_accountsDB_t;

ST_accountsDB_t  accountsDB[255] = {
  {2000.0,   RUNNING, "3333331111112222"},
  {4000.0,   BLOCKED, "2222221111113333"},
  {6000.0,   RUNNING, "1234567890654321"},
  {8000.0,   RUNNING, "0000001111112222"},
  {10000.0,  RUNNING, "1111112222223333"},
  {3000.0,   BLOCKED, "3333331111116666"},
  {5000.0,   BLOCKED, "2222221111114444"},
  {7000.0,   BLOCKED, "1111112222228888"},
  {9000.0,   BLOCKED, "0000001111112323"},
  {110000.0, BLOCKED, "1111112222225555"}
};

ST_transaction_t Transaction[255] = { 0 };
/*
--------------------------------------------------------

THIS Function Define

--------------------------------------------------------
*/

EN_transState_t  recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t* transData);

/*
--------------------------------------------------------

THIS TEST FUNCTION

--------------------------------------------------------
*/

void listSavedTransactions(void);
void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);

