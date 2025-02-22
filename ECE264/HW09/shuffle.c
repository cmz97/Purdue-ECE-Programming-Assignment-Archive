// Please modify this file as required

#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// You can add more functions, structures, and vairables to this file.  
	// Helper functions must start with '_'.

//This is an example of a helper function.
	//clean function whenever malloc fails in shuffle function
static void _error_clean()
{
	exit(EXIT_FAILURE);

}

#ifdef TEST_DIV
void divide(CardDeck orig_deck, CardDeck* upper_deck, CardDeck* lower_deck)
{
	//Dividing the desks into the way mentioned in the document - as lower and upper
	//Use a loop from index i to orig_deck.size - 1
		//starting from 1 -> size-1 copying into upper deck and lower decks
			//strncpy((upper_deck[i]).cards, orig_deck.cards,i+1);
		//update size of upper deck
			//For example: upper_deck[i].size = i+1;
		//update size of lower deck:
			//For example: lower_deck[i].size = orig_deck.size -i -1;
    for (int i=0; i<orig_deck.size-1; i++) {
        strncpy((upper_deck[i]).cards, orig_deck.cards,i+1);
        upper_deck[i].size = i+1;
        
        strncpy((lower_deck[i]).cards, orig_deck.cards+i+1,orig_deck.size-i-1);
        lower_deck[i].size = orig_deck.size -i - 1;
    }
}
#endif


#ifdef TEST_INTER
//repeat holds the number of shuffles yet to be performed.
//after the interleave operation has been completed, you will recursively call
	//repeat_shuffle(...) with a decremented value of repeat.
void interleave_Util(CardDeck*, CardDeck*, CardDeck*, int, int, int);
//CardDeck* combineDeck(CardDeck*,CardDeck*);

void interleave(CardDeck upper_deck, CardDeck lower_deck, int repeat)
{
    // Follow instructions in the README, to understand the working of the recursive function.
    
    // when the newly shuffled deck is complete:
    	//you will perform another k-1 rounds of shuffling with the new deck
    
    // Tip: There should be no uncertainty in this function.
        //If you think a random number generator is needed, you are on the wrong track.
    // Tip: To copy the elements of one array from one array to another (e.g., the array of cards in a CardDeck),
        //you could use memcpy(…).
        //The = operator will simply copy the address, not the elements themselves.

    
    CardDeck* handed = malloc(sizeof(CardDeck));
    if (handed == NULL) {
        fprintf(stderr, "maclloc fail\n");
        _error_clean();
    }
    handed->size = 1;
    interleave_Util(handed,&upper_deck,&lower_deck,0,0,repeat);
    
    //printf("Here is the resulting shuffle upper and lower deck: \n");
    //printDeck(*combineDeck(&upper_deck,&lower_deck));
    
    free(handed);
}



//CardDeck* combineDeck(CardDeck* upper,CardDeck* lower)
//{
//    int size = upper->size + lower->size;
//    CardDeck * newCardDeck = malloc(sizeof(CardDeck));
//    newCardDeck->size = size;
//    for (int i=0; i<upper->size; i++) {
//        newCardDeck->cards[i] = upper->cards[i];
//    }
//
//    for (int i=0; i<lower->size; i++) {
//        newCardDeck->cards[i+upper->size] = lower->cards[i];
//    }
//
//    return newCardDeck;
//
//}

void interleave_Util(CardDeck* handed, CardDeck* upper_deck, CardDeck* lower_deck, int upper_ind, int lower_ind, int repeat)
{
    
    if (upper_ind >= upper_deck->size) {
        for (int i = lower_ind; i < lower_deck->size; i++) {
            handed->cards[handed->size -1+i-lower_ind] = lower_deck->cards[i];
        }
        lower_ind = lower_deck->size - 1;
        handed->size = lower_deck->size + upper_deck->size;
        //printDeck(*handed);
        repeat_shuffle(*handed,repeat-1);
        //fprintf(stderr, "call\n");
        return;
    }
    
    if (lower_ind >= lower_deck->size) {
        for (int i = upper_ind; i < upper_deck->size; i++) {
            handed->cards[handed->size -1+i-upper_ind] = upper_deck->cards[i];
        }
        upper_ind = upper_deck->size - 1;
        handed->size = lower_deck->size + upper_deck->size;
        //printDeck(*handed);
        repeat_shuffle(*handed,repeat-1);
        //fprintf(stderr, "call\n");
        return;
    }
    
    CardDeck* newHanded = malloc(sizeof(CardDeck));
    if (newHanded == NULL) {
        fprintf(stderr, "maclloc fail\n");
        _error_clean();
    }
    memcpy(newHanded,handed,sizeof(CardDeck));
    newHanded->cards[newHanded->size-1] = upper_deck->cards[upper_ind];
    newHanded->size++;
    upper_ind++;
    interleave_Util(newHanded,upper_deck,lower_deck,upper_ind,lower_ind,repeat);
    upper_ind--;
    
    memcpy(newHanded,handed,sizeof(CardDeck));
    newHanded->cards[newHanded->size-1] = lower_deck->cards[lower_ind];
    newHanded->size++;
    lower_ind++;
    interleave_Util(newHanded,upper_deck,lower_deck,upper_ind,lower_ind,repeat);
    lower_ind--;
    free(newHanded);
}
#endif

#ifdef TEST_SHUF
//repeat holds the number of shuffles that are yet to be performed.
void shuffle(CardDeck orig_deck, int repeat)
{
    // declare a variable to hold the number of pairs
    // we can say that we have only size-1 possibility of pairs
    
    int numpairs = orig_deck.size - 1;
    
    // if number of pairs == 0; return;
    if (numpairs == 0) {
        return;
    }
    
    // instantiate pointers to hold both upper and lower decks (after division)
    // For example: CardDeck * upper_deck = NULL;
    CardDeck * upper_deck = NULL;
    CardDeck * lower_deck = NULL;
    
    // allocate memory based on number of pairs
    //For example: upper_deck = malloc(numpairs*sizeof(CardDeck));
    upper_deck = malloc(numpairs*sizeof(CardDeck));
    lower_deck = malloc(numpairs*sizeof(CardDeck));
    if (upper_deck == NULL || lower_deck == NULL) {
        fprintf(stderr, "maclloc fail\n");
        _error_clean();
    }
    // call divideDeck to fill upper_deck and lower_deck
    divide(orig_deck, upper_deck, lower_deck);
    //run a loop through all the pairs
    // for each pair of upper and lower deck call interleave()
    // For example: interleave(upper_deck[i],lower_deck[i]);
    for (int i = 0; i<numpairs; i++) {
        interleave(upper_deck[i],lower_deck[i],repeat);
    }
    
    free(upper_deck);
    free(lower_deck);
    // free memory allocated to upper and lower deck.
}
#endif

#ifdef TEST_RSHUF
void repeat_shuffle(CardDeck orig_deck, int k)
{
	//orig_deck contains a deck of cards, and it's size.
     //printf("Shuffle:(orig_deck,%d)\n",k);
	//If (k ≤ 0), no shuffling, print the only possible outcome.
    if (k<=0) {
        printDeck(orig_deck);
        return;
    }
		//printDeck(orig_deck); and return
		//TIP: Print only the results obtained after k rounds of shuffling
	// call shuffle(orig_deck);
    shuffle(orig_deck,k);
   
	// TIP: In interleave(…), when the newly shuffled deck is complete, 
		//you will perform another k-1 rounds of shuffling with the new deck.
}
#endif
