#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <card.h>

int main()
{   
    
    ST_cardData_t card = {};
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
    luhnCardGenerator(cardData);
    printf("Generated Luhn Card Number: %s\n",cardData->primaryAccountNumber);
    if (strlen(cardData->primaryAccountNumber)<16||strlen(cardData->primaryAccountNumber)>19||cardData->primaryAccountNumber == NULL){
        return WRONG_PAN;
    }else{return OK_CARD;}
}

void luhnCardGenerator(ST_cardData_t *cardData){
    int length = 18;
    int num[length];

    time_t t;
    srand(time(&t));

    num[0] = (rand()%9)+1;
    for (int i =1;i<length-1;i++){
        num[i] = rand()%10;
    }
    num[length-1]=0;

    int nDigits = length;
    int nSum = 0,isSecond = false;
    for (int i = nDigits - 1; i >= 0; i--) {
        int d = num[i] ;
        if (isSecond == 1)
            d = d * 2;
        nSum += d / 10;
        nSum += d % 10;
        isSecond = !isSecond;
    }
    num[length-1] = 10-(nSum%10);

    for (int i =0;i<length;i++){
        cardData->primaryAccountNumber[i] = num[i] + '0';
    }
}