#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <card.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    printf("Please Enter your Name: ");
    fgets(cardData->cardHolderName,25,stdin);
    if (strlen(cardData->cardHolderName)<20||strlen(cardData->cardHolderName)>24||cardData->cardHolderName == NULL){
        return WRONG_NAME;
    }else{
        
        return OK_CARD;}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    printf("Please Enter the Card's Expiry Date: ");
    fflush(stdin);
    scanf("%s",cardData->cardExpirationDate);
    if (strlen(cardData->cardExpirationDate)!=5||cardData->cardExpirationDate == NULL){
        return WRONG_EXP_DATE;
    }else{return OK_CARD;}
}


EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    char PAN_s[20] =""; 
    luhnCardGenerator(cardData);
    printf("Generated Luhn Card Number: %s\n",cardData->primaryAccountNumber);
    printf("Please Enter your Card's PAN (PRESS ENTER TO USE GENERATED NUMBER):");
    fflush(stdin);
    fgets(PAN_s,20,stdin);
    if (PAN_s[0]!='\n'){
        strcpy(cardData->primaryAccountNumber,PAN_s);
    }
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
    if ((nSum%10)==0){
        num[length-1] = 1;
    }else{num[length-1] = 10-(nSum%10);}
    for (int i =0;i<length;i++){
        cardData->primaryAccountNumber[i] = num[i] + '0';
    }
}