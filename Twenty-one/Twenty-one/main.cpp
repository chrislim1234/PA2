/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Chris Lim
 * USC email: chrislim@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] =
{"2","3","4","5","6","7",
    "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};
int fulldeck[52];

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
    for (int i=0; i<=NUM_CARDS-1; i++) {
        cards[i]=i;
    }
    /******** You complete ****************/
    
    // To shuffle an array a of n elements (indices 0..n-1):
    //for i from n−1 downto 1 do
      //  j ← random integer such that 0 ≤ j ≤ i
        //(i.e. use a modulus operation on the random number)
        //exchange a[j] and a[i]
    for (int i=NUM_CARDS-1; i>0; i--) {
        int j = (rand() %(i+1));
        int holder =cards[i];
        cards[i]=cards[j];
        cards[j] = holder;
    }
    
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
    /******** You complete ****************/
    int x = id/13;
    int y = id%13;
    cout << type[y] << "-"<<suit[x];
    
    
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
    /******** You complete ****************/
    
    return value[id%13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
    /******** You complete ****************/
    for (int i=0; i<numCards; i++) {
        printCard(hand[i]);
        cout << " ";
    }
}

/**
 * Should return the total score of the provided hand.
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    /******** You complete ****************/
    int sum=0;
    int acecounter = 0;
  for (int i=0; i<numCards; i++) {
      if (hand[i]%13==12) {
          acecounter=acecounter+1;
      }
      sum=sum+cardValue(hand[i]);
  }
    
    while(acecounter>0 && sum>21) {
        sum=sum-10;
        acecounter=acecounter-1;
    }
    return sum;
    
}

/**
  * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
    //---------------------------------------
    // Do not change this code -- Begin
    //---------------------------------------
    if(argc < 2){
        cout << "Error - Please provide the seed value." << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    srand(seed);
    
    int cards[52];
    int dhand[9];
    int phand[9];
    char yesorno;
    
    do {
        shuffle(cards);
        //for (int i=0; i<52; i++) {
          //  cout<<cards[i]<<" ";
        //}
        int handnum=1;
        int cardnum=0;
        for (int i=0; i<=handnum;i++) {
            phand[i]=cards[cardnum];
            cardnum++;
            dhand[i]=cards[cardnum];
            cardnum++;
        }
        
        cout << "Dealer: ? ";
        printCard(cards[3]);
        cout << endl<<"Player: ";
        printHand(phand, 2);
        cout<<endl;
        int n=2;
        
        char input;
        if (getBestScore(phand, int(n))!=21) {
            do {
            cout <<"Type 'h' to hit and 's' to stay:"<<endl;
            cin >> input;
            
            if (input=='h') {
                
                handnum=handnum+1;
                //cout<<cardnum<<endl;
                phand[handnum]=cards[cardnum];
                cardnum=cardnum+1;
                n++;
                cout <<"Player: ";
                printHand(phand, n);
                cout<<endl;
            }
            else if (input=='s') {
                cout <<"Player: ";
                printHand(phand, int(n));
                cout<<endl;
            }
            else {
                exit(0);
            }
            } while(input=='h' && getBestScore(phand, int(n))<21);
        }
        int handnum1=1;
        int x=2;
        while(getBestScore(dhand, int(x))<=16 && getBestScore(phand, int(n))<=21) {
            handnum1=handnum1+1;
            dhand[handnum1]=cards[cardnum];
            cardnum=cardnum+1;
            x++;
        }
        
        if(getBestScore(phand, int(n))>21) {
            cout << "Player busts"<<endl;
            cout<< "Lose" <<" "<<getBestScore(phand, int(n))<<" "<<getBestScore(dhand, int(x))<<endl;
        }
        else if (getBestScore(phand, int(n))<=21){
            cout<< "Dealer: ";
            printHand(dhand,int(x));
            cout<<endl;
        
        
        if (getBestScore(dhand, int(x))>21) {
            cout<< "Dealer busts"<<endl;
            cout<<"Win ";
            cout<<getBestScore(phand, int(n));
            cout<<" ";
            cout<< getBestScore(dhand, int(x))<<endl;
        }
        
        else if (getBestScore(phand, int(n))>getBestScore(dhand, int(x))) {
            cout<<"Win ";
            cout<<getBestScore(phand, int(n));
            cout<<" ";
            cout<< getBestScore(dhand, int(x))<<endl;
        }
        
        else if (getBestScore(phand, int(n))<getBestScore(dhand, int(x))) {
            cout<<"Lose ";
            cout<< getBestScore(phand, int(n));
            cout<<" ";
            cout<<getBestScore(dhand, int(x))<<endl;
        }
        else if (getBestScore(phand, int(n))==getBestScore(dhand, int(x))) {
            cout<<"Tie ";
            cout<<getBestScore(phand, int(n));
            cout<<" ";
            cout<<getBestScore(dhand, int(x))<<endl;
        }
    }
        
        cout << endl<<"Play again? [y/n]";
        cin >> yesorno;
        if (yesorno!='y') {
            exit(0);
        }
    } while (yesorno=='y');
        
        //---------------------------------------
        // Do not change this code -- End
        //---------------------------------------
        
        /******** You complete ****************/
        
        /*void shuffle(int cards[]);
        void printCard(int id);
        int cardValue(int id);
        void printHand(int hand[], int numCards);
        int getBestScore(int hand[], int numCards);*/
    return 0;
}

