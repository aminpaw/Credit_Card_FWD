#include <server.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

ST_accountsDB_t validAccounts[255];
ST_transaction_t transactions[255];
int acc_number;

int main(){
    ST_cardData_t card={"Amin ","19999997999","11/22"};
    ST_terminalData_t Tdata = {110  ,1000, "14/08/2022"};
    ST_transaction_t trans = {card,Tdata,APPROVED,223};
    ST_accountsDB_t acc1 = {101,"1001"};

    FILE *transT;
    transT = fopen("transactions.txt", "a");
    fprintf(transT,"%s %s %s ",trans.cardHolderData.cardHolderName,trans.cardHolderData.primaryAccountNumber,trans.cardHolderData.cardExpirationDate);
    fprintf(transT,"%f %f %s ",trans.terminalData.transAmount,trans.terminalData.maxTransAmount, trans.terminalData.transactionDate);
    fprintf(transT,"%d %d\n",trans.transState,trans.transactionSequenceNumber);
    fclose(transT);

    
    printf("%d %d",isValidAccount(&trans.cardHolderData),isAmountAvailable(&trans.terminalData));
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
        if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND){return DECLINED_STOLEN_CARD;}
        else if (isAmountAvailable(&transData->terminalData)==LOW_BALANCE){return DECLINED_INSUFFECIENT_FUND;}
        else{return APPROVED;}
    }

EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    FILE* file = fopen("acc.txt", "r"); /* should check the result */
    char line[256];
    while (fgets(line, sizeof(line), file)) {
            char PAN_s[20]="\0";
            int space =300;
            for (int c = 0; c < 256; c++)
            {
                if(line[c]==' '){
                    if(c<space){space = c;}
                    else{break;}
                }
                if (space != 0 && line[c]!= '\0'){PAN_s[c-space]=line[c+1];}
            }
            printf("%s ", PAN_s);
            if(strcmp(PAN_s, cardData->primaryAccountNumber) != 0)
            {
                return ACCOUNT_NOT_FOUND;
            }
            else
            {return OK;}
        }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    char balance_s[256]="\0";
    float balance;
    FILE* file = fopen("acc.txt", "r"); /* should check the result */
    char line[256];
          while (fgets(line, sizeof(line), file)) {
        int space = 300;
        for (int c =0;c<256;c++){
            if(line[c]==' '){
                if(c<space){space = c;}else{break;}}
            if (space == 300){
                balance_s[c] = line[c]; 
                //strcat(balance_s,line[c]);
            }
        }
         balance = atof(balance_s);
    }
    if (termData->transAmount > balance){
        return LOW_BALANCE;
    }else{return OK;}
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){

}

