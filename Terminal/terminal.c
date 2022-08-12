#include <terminal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(){


scanf("%s",cardData.cardExpirationDate);
printf("%d", getTransactionDate(&termData));
printf("\n%s", termData.transactionDate);
printf("\n%d", isCardExpired(cardData,termData));
}

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    time_t Time = time(&Time);
    struct tm *currentTime = localtime(&Time);
    int day = currentTime->tm_mday;
    int month = currentTime->tm_mon + 1;
    int year = currentTime->tm_year + 1900;
    if (month < 10){sprintf(termData->transactionDate, "%d/0%d/%d", day,month,year);}else{sprintf(termData->transactionDate, "%d/%d/%d", day,month,year);}
    if (strlen(termData->transactionDate) < 10 || termData->transactionDate == NULL){
        return WRONG_DATE;
    }else{return OK_TERMINAL;}
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    int card_month = cardtoint(cardData,0);
    int card_year = cardtoint(cardData,3);
    int trans_month = transtoint(termData,3);
    int trans_year = transtoint(termData,8);

    if (trans_year>card_year || (trans_year == card_year && trans_month >> card_month)){
        return EXPIRED_CARD;
    }else{return OK_TERMINAL;}

}

int cardtoint(ST_cardData_t cardData, int start){
    char s_date[3];
    sprintf(s_date,"%c%c",cardData.cardExpirationDate[start],cardData.cardExpirationDate[start+1]);
    return (atoi(s_date));
}

int transtoint(ST_terminalData_t termData, int start){
    char s_date[3];
    sprintf(s_date,"%c%c",termData.transactionDate[start],termData.transactionDate[start+1]);
    return (atoi(s_date));
}
    
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    scanf("%f", termData->transAmount);
    if (termData->transAmount <= 0){
        return INVALID_AMOUNT;
    }else{return OK_TERMINAL;}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if (termData->transAmount > termData->maxTransAmount){
        return EXCEED_MAX_AMOUNT;
    }else{return OK_TERMINAL;}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    scanf("%f", termData->maxTransAmount);
    if (termData->maxTransAmount <= 0){return INVALID_MAX_AMOUNT;}else{return OK_TERMINAL;}
}


