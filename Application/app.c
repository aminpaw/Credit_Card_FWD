#include<app.h>

 ST_cardData_t card={"","",""};
 ST_terminalData_t termData={0.0,10000.0,""};
 ST_transaction_t transaction = {};
 
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
    if (isBelowMaxAmount(&termData) ==EXCEED_MAX_AMOUNT){
        printf("Amount Exceeded Limit");
        exit(0);
    }

    //Server
    transaction.cardHolderData = card;
    transaction.terminalData = termData;
    recieveTransactionData(&transaction);

}