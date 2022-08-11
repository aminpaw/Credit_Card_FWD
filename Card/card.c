#include <stdio.h>
#include <card.h>

int main()
{
    ST_cardData_t card ;

    printf("%d\n", getCardHolderName(&card));
    printf("%d\n",getCardExpiryDate(&card));
    printf("%d\n",getCardPAN(&card));
}