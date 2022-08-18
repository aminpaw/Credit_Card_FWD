#include<app.h>

extern ST_cardData_t card={};
extern ST_terminalData_t termData={};
ST_transaction_t trans = {};
int main(){
    appStart();
}

void appStart(){
    //Card
    getCardHolderName(&card);
    getCardExpiryDate(&card);
    getCardPAN(&card);

    //Terminal
    getTransactionDate(&termData);
    if(isCardExpired(card,termData) == EXPIRED_CARD){
        printf("Card is Expired");
        exit(0);
    }

    if(isValidCardPAN(&card)==INVALID_CARD){
        printf("Failed in Luhn Check");
        exit(0);    
    }

    printf("Please Enter the Transaction Amount: \n");
    getTransactionAmount(&termData);
    if (isBelowMaxAmount(&termData)==EXCEED_MAX_AMOUNT){
        printf("Amount Exceeded Limit");
        exit(0);
    }

    //Server
    trans.cardHolderData = card;
    trans.terminalData = termData;
    if(isValidAccount(&card) == ACCOUNT_NOT_FOUND){
        printf("Invalid Account");
        exit(0);
    }

    if(isAmountAvailable(&termData) == DECLINED_INSUFFECIENT_FUND){
        printf("Insuffecient Fund");
        exit(0);        
    }

    





    



}