#include <server.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char acc_data[256]="";

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
        if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND){
            transData->transState = DECLINED_STOLEN_CARD;
            saveTransaction(transData);
            printf("Declined Stolen Card");
            return DECLINED_STOLEN_CARD;
            }
        
        if (isAmountAvailable(&transData->terminalData)==LOW_BALANCE){
            transData->transState = DECLINED_INSUFFECIENT_FUND;
            saveTransaction(transData);
            printf("Declined Insuffecient Fund");
            return DECLINED_INSUFFECIENT_FUND;
        }
        transData->transState=APPROVED;
        if (saveTransaction(transData)==SAVING_FAILED){
            return INTERNAL_SERVER_ERROR;
            printf("Internal Server Error");
        }    
        printf("Approved");
        return APPROVED;
    }

EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    FILE* acc;
    FILE* temp;
    char line[256]="";
    acc = fopen("Accounts.txt","r");
    temp = fopen("temp.txt","a");
    int found = 0;
    while (fgets(line, sizeof(line), acc)) {
            char PAN_s[20]="\0";
            int space =300;
            for (int c = 0; c < 256; c++)
            {
                if(line[c]==' '){
                    if(c<space){space = c;}
                    else{break;}
                }
                if (space != 0 && line[c]!= '\0' && line[c+1]!='\n'){PAN_s[c-space]=line[c+1];}
            }
            if(strcmp(PAN_s, cardData->primaryAccountNumber) == 0)
            {
                found = 1;
                strcpy(acc_data,line);
            }else{
                fprintf(temp,"%s",line);
            }
        }
    fclose(acc);
    fclose(temp);
    if(found ==1)
        return OK;
    remove("temp.txt");
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    char balance_s[256]="\0";
    float balance;
    char* pan;
    FILE* temp;
    temp = fopen("temp.txt","a");
    char line[256];
        for(int i =0;i<256;i++) {
            if(line[i]==' '){
                break;
            }
            balance_s[i]=acc_data[i];
        }
        balance = atof(balance_s);
    float balance_new =balance - termData->transAmount;
    pan = strchr(acc_data,' ');
    fprintf(temp,"%f%s",balance_new,pan);
    fclose(temp);
    if (termData->transAmount > balance){
        remove("temp.txt");
        return LOW_BALANCE;
    }else{
    
    remove("Accounts.txt");
    rename("temp.txt","Accounts.txt");
    return OK;
    }
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    int transactionNumber = 0;
    char c;
    FILE* transactions;
    transactions = fopen("transactions.txt","a+");

    for (c = getc(transactions); c != EOF; c = getc(transactions))
        if (c == '\n') 
            transactionNumber ++;

    transData->transactionSequenceNumber = transactionNumber+1;
    fprintf(transactions, "%s %s %s ",transData->cardHolderData.cardHolderName,transData->cardHolderData.primaryAccountNumber,transData->cardHolderData.cardExpirationDate);
    fprintf(transactions, "%f %f %s ",transData->terminalData.transAmount,transData->terminalData.maxTransAmount,transData->terminalData.transactionDate);
    fprintf(transactions, "%i %i\n",transData->transState,transData->transactionSequenceNumber);
    fclose(transactions);
    return OK;
}



