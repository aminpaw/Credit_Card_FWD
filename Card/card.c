#include <stdio.h>
#include <card.h>

int main()
{
    printf("%d\n", getCardHolderName(&cardData));
    printf("%d\n",getCardExpiryDate(&cardData));
    printf("%d\n",getCardPAN(&cardData));
}

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    printf("Please Enter your Name: ");
    scanf("%s",cardData->cardHolderName);
    if (strlen(cardData->cardHolderName)<20||strlen(cardData->cardHolderName)>24||cardData->cardHolderName == NULL){
        return WRONG_NAME;
    }else{return OK_CARD;}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    printf("Please Enter the Card's Expiry Date: ");
    scanf("%s",cardData->cardExpirationDate);
    if (strlen(cardData->cardExpirationDate)!=5||cardData->cardExpirationDate == NULL){
        return WRONG_EXP_DATE;
    }else{return OK_CARD;}
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    printf("Please Enter the Card's PAN: ");
    scanf("%s",cardData->primaryAccountNumber);
    if (strlen(cardData->primaryAccountNumber)<16||strlen(cardData->primaryAccountNumber)>19||cardData->primaryAccountNumber == NULL){
        return WRONG_PAN;
    }else{return OK_CARD;}
}