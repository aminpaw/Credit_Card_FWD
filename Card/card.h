#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;

typedef struct ST_cardData_t
{
uint8_t cardHolderName[25];
uint8_t primaryAccountNumber[20];
uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    printf("Please Enter your Name: ");
    scanf("%s",cardData->cardHolderName);
    if (strlen(cardData->cardHolderName)<20||strlen(cardData->cardHolderName)>24||cardData->cardHolderName == NULL){
        return WRONG_NAME;
    }else{return OK;}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    printf("Please Enter the Card's Expiry Date: ");
    scanf("%s",cardData->cardExpirationDate);
    if (strlen(cardData->cardExpirationDate)!=5||cardData->cardExpirationDate == NULL){
        return WRONG_EXP_DATE;
    }else{return OK;}
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    printf("Please Enter the Card's PAN: ");
    scanf("%s",cardData->primaryAccountNumber);
    if (strlen(cardData->primaryAccountNumber)<16||strlen(cardData->primaryAccountNumber)>19||cardData->primaryAccountNumber == NULL){
        return WRONG_PAN;
    }else{return OK;}
}
#endif