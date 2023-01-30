**Poker Hand Strength Calculator**

This repository contains the algorithm to be used to compute the Hand Strength of a Poker Hand during the game. 

**Refer to only "NLH.cpp" file for the Hand Strength Calculator right now.**

---

## No Limit Hold'em

The file "NLH.cpp" contains the algorithm for a game of No Limit Hold'em. 

---
## Pre Flop Analysis

Pre Flop analysis is done taking into account two cases: 

1. Having a pair in Pre-Flop: (for example: AA, 33)
2. Playing on High Card in Pre-Flop: (for example: Q9)

In both cases, we simply compute the number of cards better than the high card and the second ranked card. 

Formula- 
If we have a Q9, the number of cards better than or equal to a Queen are- Q, K, A => B=3
Card:   Q K A
Number: 3 4 4 => **Formula: k= 3 + 4*(Better-1)**

Let, k = k1 for Q, and k = k2 for 9

**Probability Calculation-
P = (k1/50) * (k2/49)**

Strength of the Hand = 1- P , Scale: [0, 1]

Now, to make sure the player makes a concrete decision pre-flop, the maximum possible strength has been capped to 60. 

For further improvements in judgements, since a Pair is always going to be having better strength. The scale has been broken down into: 

1. Pair in Pre-flop, Scale: [40,60]
2. High Card in Pre-flop, Scale: [0, 40]

Hence,

**Formula(1): 40 + (Strength*20) **

**Formula(2): (Strength*40)**

---

## Post Flop Analysis

To understand the Post Flop analysis, we need to understand the scale followed by the algorithm used to provide a Hand Strength in the required range. 

**Scale**

A standardised scale has been followed to compute the score taken from [https://en.wikipedia.org/wiki/Poker_probability]. On a brief note, the
scale contains the ranges of all the card combinations. 

	Card				Probability	 	 Range		Multiplying Factor
	High Card    		17.4%       	(0,17)		0.0833
	One Pair     		43.8%       	(17,62)		0.0833
	Two Pair     		23.5%       	(63,87)		0.0833
	Three of a Kind		4.83% 			(87,92)		0.41
	Straight			4.62%       	(92,96)		0.33
	Flush				3.03%			(96,99)		0.0833
	Full House			2.60%			(99,102)	0.24
	Four of a Kind		0.168%			(102,103)	0.08
	Straight Flush		0.0279%			(103,105)	0.16
	Royal Flush			0.0032%			105

The Multiplying Factor ensures that all calculations are within the range and is adjusted as per the probability.

**Algorithm**

1. Based on the flop, **the algorithm computes a minimum and maximum limit of score.** 

2. The **score** is computed based on a standardised scale explained above. 

3. Based on Flop, Turn, River - the Best 5 card combinations are computed from flop combined with the cards and all possible probabilities are calculated.

4. Now, we have- score, minimum, maximum. We scale this to a range of (0,100) using normalisation. **Formula: ((score-minimum)/(maximum-minimum))*100)**


---

## Nomenclature of Cards: 

The Cards are stored as *String* form, subsequently stored in the *hand* and *flop* vectors. 

Example: "Ac" represents an Ace of Clubs, "Td" represents a Ten of Diamonds. 
