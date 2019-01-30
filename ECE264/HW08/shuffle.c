// Please edit this file as required.
// You may add more functions/variables/structures in this file (if needed).

#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef TEST_DIV
void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck)
{
	// Dividing the decks into the way mentioned in Readme - as lower and upper decks

	// starting from i = 0 -> size-1 copying into upper deck and lower decks
		// For example: strncpy((upper_deck[i]).cards, orig_deck.cards,i+1);
		// Update the size of the upper and lower decks after copying each element.
			// For example: upper_deck[i].size = i+1;
    for (int i=0; i<orig_deck.size-1; i++) {
        strncpy((upper_deck[i]).cards, orig_deck.cards,i+1);
        upper_deck[i].size = i+1;
        
        strncpy((lower_deck[i]).cards, orig_deck.cards+i+1,orig_deck.size-i-1);
        lower_deck[i].size = orig_deck.size -i - 1;
    }
		// Similarly perform the string copy, and size update operation on the lower deck.
			//For example: strncpy((lower_deck[i]).cards, orig_deck.cards+i+1,orig_deck.size-i-1);
		    // For example: lower_deck[i].size = orig_deck.size -i - 1;
}
#endif

#ifdef TEST_INTER
void interleave_Util(CardDeck*, CardDeck*, CardDeck*, int, int);

void interleave(CardDeck upper_deck, CardDeck lower_deck)
{
    // Follow instructions in the README, to understand the working of the recursive function.
    // Usinterleavee print_deck(…) to print each resulting order.
    // Tip: There should be no uncertainty in this function.
        //If you think a random number generator is needed, you are on the wrong track.
    // Tip: To copy the elements of one array from one array to another (e.g., the array of cards in a CardDeck),
        //you could use memcpy(…).
        //The = operator will simply copy the address, not the elements themselves.
//    printf("\ninterleave\n");
//    for (int i=0; i < upper_deck.size; i++) {
//        printf("UpperArray[%d]: %c \n", i, upper_deck.cards[i]);
//    }
//
//    for (int i=0; i < lower_deck.size; i++) {
//        printf("LowerArray[%d]: %c \n", i, lower_deck.cards[i]);
//    }
    CardDeck* handed = malloc(sizeof(CardDeck));
    handed->size = 1;
    interleave_Util(handed,&upper_deck,&lower_deck,0,0);
    free(handed);
    
}

void interleave_Util(CardDeck* handed, CardDeck* upper_deck, CardDeck* lower_deck, int upper_ind, int lower_ind)
{

    if (upper_ind >= upper_deck->size) {
        for (int i = lower_ind; i < lower_deck->size; i++) {
            handed->cards[handed->size -1+i-lower_ind] = lower_deck->cards[i];
        }
        lower_ind = lower_deck->size - 1;
        handed->size = lower_deck->size + upper_deck->size;
        print_deck(*handed);
        return;
    }
    
    if (lower_ind >= lower_deck->size) {
        for (int i = upper_ind; i < upper_deck->size; i++) {
            handed->cards[handed->size -1+i-upper_ind] = upper_deck->cards[i];
        }
        upper_ind = upper_deck->size - 1;
        handed->size = lower_deck->size + upper_deck->size;
        print_deck(*handed);
        return;
    }
    
    CardDeck* newHanded = malloc(sizeof(CardDeck));
    memcpy(newHanded,handed,sizeof(CardDeck));
    newHanded->cards[newHanded->size-1] = upper_deck->cards[upper_ind];
    newHanded->size++;
    upper_ind++;
    interleave_Util(newHanded,upper_deck,lower_deck,upper_ind,lower_ind);
    upper_ind--;
    
    memcpy(newHanded,handed,sizeof(CardDeck));
    newHanded->cards[newHanded->size-1] = lower_deck->cards[lower_ind];
    newHanded->size++;
    lower_ind++;
    interleave_Util(newHanded,upper_deck,lower_deck,upper_ind,lower_ind);
    lower_ind--;
    free(newHanded);
}

#endif

#ifdef TEST_SHUF
void shuffle(CardDeck orig_deck)
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
    // call divideDeck to fill upper_deck and lower_deck
    divide(orig_deck, upper_deck, lower_deck);
	//run a loop through all the pairs
		// for each pair of upper and lower deck call interleave()
		// For example: interleave(upper_deck[i],lower_deck[i]);
    for (int i = 0; i<numpairs; i++) {
        interleave(upper_deck[i],lower_deck[i]);
    }

    free(upper_deck);
    free(lower_deck);
    // free memory allocated to upper and lower deck.
}
#endif
