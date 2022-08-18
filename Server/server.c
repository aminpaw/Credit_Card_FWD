#include <server.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char acc_data[256]="";

int main(){
    ST_cardData_t card={"Amin ","19999997999","11/22"};
    ST_terminalData_t Tdata = {800  ,1000, "14/08/2022"};
    ST_transaction_t trans = {card,Tdata,APPROVED,223};
    ST_accountsDB_t acc1 = {101,"1001"};
    
    isValidAccount(&card);
    isAmountAvailable(&Tdata);
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
        if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND){return DECLINED_STOLEN_CARD;}
        else if (isAmountAvailable(&transData->terminalData)==LOW_BALANCE){return DECLINED_INSUFFECIENT_FUND;}
        else{return APPROVED;}
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
    if(found =1)
        return OK;
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
    printf("\n%f%s",balance_new,pan);
    fprintf(temp,"%f%s",balance_new,pan);
    fclose(temp);
    if (termData->transAmount > balance){
        remove("temp.txt");
        printf("hehehehe");
        return LOW_BALANCE;
    }else{
    
    remove("Accounts.txt");
    rename("temp.txt","Accounts.txt");
    return OK;
    }
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){

}



