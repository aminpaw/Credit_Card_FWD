#include <server.h>
#include<stdio.h>

ST_accountsDB_t validAccounts[255];
ST_transaction_t transactions[255];
int acc_number;

int main(){
    ST_cardData_t card={"Amin","1001"};
    ST_terminalData_t Tdata = {100  ,1000};
    ST_transaction_t trans = {card,Tdata};
    ST_accountsDB_t acc1 = {101,"1001"};
    validAccounts[0] = acc1;
    printf("%d",recieveTransactionData(&trans));
    trans.transState = recieveTransactionData(&trans);
    for (int i =0; i <255; i++){
        if (&transactions[i].transactionSequenceNumber == 0){
                transactions[i] = trans;
                transactions[i].transactionSequenceNumber = i+1;
            break;
        }
    }
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
        if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND){return DECLINED_STOLEN_CARD;}
        else if (isAmountAvailable(&transData->terminalData)==LOW_BALANCE){return DECLINED_INSUFFECIENT_FUND;}
        else{return APPROVED;}
    }

EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    for(acc_number = 0; acc_number < 255; acc_number++)
        {
            if(strcmp(validAccounts[acc_number].primaryAccountNumber, cardData->primaryAccountNumber) != 0)
            {
                return ACCOUNT_NOT_FOUND;
            }
            else
            {return OK;}
        }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    if (termData->transAmount > validAccounts[acc_number].balance){
        return LOW_BALANCE;
    }else{return OK;}
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){

}

