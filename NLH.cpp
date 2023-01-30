#include<bits/stdc++.h>
#include<iostream>

using namespace std;

/*
Suits: c, d, h, s -> Clubs, Diamonds, Hearts, Spades
*/

/*

Flush - (T1, T2, T3, T4, T5)
Range= [2,14] = [0,12] 

Formula= 59 + (T1-2)*1 + (T2-2)*(1/12) + (T3-2)*(1/12)^2 + ....
71.....

How will we get Real-time information? 

*/

vector<string> deck = {
    "2c", "3c", "4c", "5c","6c", "7c", "8c", "9c", "Tc", "Jc", "Qc", "Kc", "Ac", 
    "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "Td", "Jd", "Qd", "Kd", "Ad",
    "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "Th", "Jh", "Qh", "Kh", "Ah",
    "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "Ts", "Js", "Qs", "Ks", "As",
};


//Scale based on: https://en.wikipedia.org/wiki/Poker_probability

double HandStrengthCalc(int type, vector<int> extra)
{
    double val= 0;
    
    switch(type){
        
        case 1: //Royal-Flush (105)
            {
           val = 105;
            break;
            }
        case 2: //Straight-Flush (103, 105)
            {
           val= 103 + (double)(extra[0]-5)*(0.16); //{Top=6, A= 14}, 108 
            break;
            }
        case 3: //Four of a Kind (102, 103)
            {
           val= 102 + (double)(extra[0]-2)*(0.08); //{Top= 2, 14} [85, 97]
            break;
            }
        case 4: //Full House (99, 102)
            {
           val= 99 + (double)(extra[0]-2)*(0.24); //{Top=2, 14} [72, 84]
            break;
            }
        case 5:  //Flush (96, 99)
            {
            val= 96;
            double multi = 0.23;
            
            for(auto &e: extra)
            {
                val+= (double)e*(double)multi;
                multi= (double)multi*(0.0833);
            }
            break;
            }
        case 6: //Straight => (92, 96)
            {
            val = 92 + (double)(extra[0]-2)*(0.33);
            break;
            }
        case 7: //Three of a Kind (87, 92) -> range= 5 
            {
            val = 87 + (double)(extra[0]-2)*(0.41);
            break;
            }
        case 8: //Two Pair -> (1stP, 2nd P, Side) (63, 87)
            {
            val = 63;
            double multi = 1;
            
            for(auto &e: extra)
            {
                val+= (double)(e-2)*(double)multi;
                multi= (double)multi*(0.0833);
            }
            break;
            }
        case 9: //One-Pair -> (1stP, S1, S2, S3) (17, 62)
            {
            val = 17;
            double multi = 3.4;
            
            for(auto &e: extra)
            {
                val+= (double)(e-2)*(double)multi;
                multi= (double)multi*(0.0833);
            }
            break;
            }
        case 10: //High Card (1, 17)
            {
            val= 1;
            double multi = 1.2;
            
            for(auto &e: extra)
            {
                val+= (double)(e-2)*(double)multi;
                
                multi= (double)multi*(0.0833);
            }
            break;
        }
    }
    
    val= (double)val/(105);
    val = (double)val*100;
    
    return val;
}

unordered_map<char, int> mp; //{A-14, K-13, ....and so on}
string take = "23456789TJQKA";

void func1()
{
    int var = 2;
    
    for(auto &e: take)
    {
        mp[e]= var;
        var++;
    }
    return;
}

static bool mysort (string &a, string &b){
    
    return mp[a[0]] < mp[b[0]];
}

double getRank(vector<string>& hand)
{
    sort(hand.begin(), hand.end(), mysort);
    
    //checking for a royal-flush
    double rank;
    
    bool check= true;
    
    vector<int> extra;
    
    for(int i=0;i<4;i++)
    {
        if((hand[i][1]!=hand[i+1][1])||(mp[hand[i][0]]+1 != mp[hand[i+1][0]])) 
        {
            check= false;
            break;
        }
    }
    if(check)
    {
        if(mp[hand[4][0]]==14) //last one is Ace
        {
            return HandStrengthCalc(1, {});
        }else{
            return HandStrengthCalc(2, {mp[hand[4][0]]});
        }
    }
    
    //checking for Four of a Kind
    check= false;
    
    int top; 
    
    for(int start=0;start<2;start++)
    {
        int count=1;
        for(int i=start+1;i<5;i++)
        {
            if(mp[hand[i][0]]==mp[hand[start][0]])
            {
                count++;
            }
        }

        if(count==4)
        {
            check= true;
            top = mp[hand[start][0]];
            break;
        }
    }
    if(check)
    {
        return HandStrengthCalc(3, {top});
    }
        
    //Full House- 3 of a Kind + a Pair
    // check for full house
      
      bool fullHouse = false;
      bool threeOfAKind = false;
      bool pair = false;
        
      int three;
      
      unordered_map<char, int> ch;
    
      for(int i=0;i<5;i++)
      {
          ch[hand[i][0]]++;
      }
      
      for(auto it: ch)
      {
          if(it.second==3)
          {
              three= mp[it.first];
              threeOfAKind= true;
          }else if(it.second==2)
          {
              pair= true;
          }
      }
      if (threeOfAKind && pair) {
        fullHouse = true;
      }
      if (fullHouse) {
        return HandStrengthCalc(4, {three});
      }
      
      // check for flush
      bool flush = true;
      for (int i = 0; i < 4; i++) {
        if (hand[i][1] != hand[i + 1][1]) {
          flush = false;
          break;
        }
      }
    if(flush)
    {
        vector<int> send;
        for(int i=4;i>=0;i--)
        {
            send.push_back(mp[hand[i][0]]);
        }
        return HandStrengthCalc(5, send);
    }
    
    //Check for straight
    bool straight= true;
    
    for(int i=0;i<4;i++)
    {
        if(mp[hand[i][0]]!=mp[hand[i+1][0]]-1)
        {
            straight= false;
            break;
        }
    }
    if(straight)
    {
        return HandStrengthCalc(6, {mp[hand[4][0]]});
    }
    
    //check for a three of a kind
    
    if(threeOfAKind)
    {
        return HandStrengthCalc(7, {three});
    }
    
    //Two-Pair check
    bool twoPair = false;
    int pairCount=0;
    
    unordered_map<char, int> freq;
    
    for(int i=0;i<5;i++)
    {
        freq[hand[i][0]]++;
        
    }
    vector<int> pp, side;
    
    for(auto it: freq)
    {
        if(it.second==2)
        {
            pp.push_back(mp[it.first]);
            pairCount++;
        }else{
            side.push_back(mp[it.first]);
        }
    }
    
    if (pairCount == 2) {  
      twoPair = true;
    }
    
    if (twoPair) {
        vector<int> c;
        
        sort(pp.begin(), pp.end());
        c.push_back(pp[1]);
        c.push_back(pp[0]);
        c.push_back(side[0]);
        
      return HandStrengthCalc(8, c);
    }

    // check for one pair
        
    if (pairCount==1) {
        
        vector<int> c;
        
        sort(side.begin(), side.end());
        c.push_back(pp[0]);
        c.push_back(side[2]);
        c.push_back(side[1]);
        c.push_back(side[0]);
        
        return HandStrengthCalc(9, c);
    }
    
    vector<int> fin;
    
    for(int i=4;i>=0;i--)
    {
        fin.push_back(mp[hand[i][0]]);
    }
    return HandStrengthCalc(10, fin);
}

typedef pair<double, double> pdd;

unordered_map<string, int> consider;


pdd combi(vector<string>& flop)
{
    //Find combinations of two in the remaining deck and get an upper & lower limit on a flop size of 3
    double low= 100, high= 0;
    
    for(int i=0;i<51;i++)
    {
        if(consider[deck[i]]==1)
        {
            continue;
        }
        for(int j=i+1;j<52;j++)
        {
            if(consider[deck[j]]==1)
            {
                continue; 
            }
            vector<string> temp(flop);

            temp.push_back(deck[i]);
            temp.push_back(deck[j]);

            double score= getRank(temp);
            low= min(low, score);
            high= max(high, score);
        }
    }
    return {low, high};
}

pdd combi2(vector<string>& flop)
{
    //Given a flop of 4, find all possible one cards in the remaining deck and get the min, low
    double low= 100, high= 0;
    
    for(int i=0;i<52;i++)
    {
        if(consider[deck[i]]==1)
        {
            continue;
        }
        vector<string> temp(flop);
        temp.push_back(deck[i]);
        double score= getRank(temp);

        low= min(low, score);
        high= max(high, score);
    }
    
    return {low, high};
}

pdd analyse(vector<string>& flop, int turn)
{
    
    
    for(auto &e: flop)
    {
        consider[e]++;
    }
    
    //Analysing turn= 0 ----> At Flop
    
    if(turn==0)
    {
        
        return combi(flop);
        
    }else if(turn==1)
    {
        //at Turn, find combinations of three + 2 across remaining deck
        
        double low= 100, high= 0;
        
        //find triplets in current flop at turn
        
        for(int i=0;i<2;i++)
        {
            for(int j=i+1;j<3;j++)
            {
                for(int k=j+1;k<4;k++)
                {
                    vector<string> temp= {flop[i], flop[j], flop[k]};
                    
                    pdd tmp = combi(temp);
                    low= min(low, tmp.first);
                    high= max(high, tmp.second);
                }
            }
        }
        
        //consider the turn as best and find one best
        
        for(int i=0;i<52;i++)
        {
            if(consider[deck[i]]==1)
            {
                continue;
            }
            vector<string> temp(flop);
            temp.push_back(deck[i]);
            double score= getRank(temp);
            
            low= min(low, score);
            high= max(high, score);
        }
        
        return {low, high};
        
    }else{
        
        double low= 100, high= 0;
        
        //find triplets in current flop at river
        for(int i=0;i<3;i++)
        {
            for(int j=i+1;j<4;j++)
            {
                for(int k=j+1;k<5;k++)
                {
                    vector<string> temp= {flop[i], flop[j], flop[k]};
                    
                    pdd tmp = combi(temp);
                    low= min(low, tmp.first);
                    high= max(high, tmp.second);
                }
            }
        }
        
        //find combinations of four in the current flop at river
        
        for(int i=0;i<2;i++)
        {
            for(int j=i+1;j<3;j++)
            {
                for(int k=j+1;k<4;k++)
                {
                    for(int l=k+1;l<5;l++)
                    {
                        vector<string> temp= {flop[i], flop[j], flop[k], flop[l]};
                        
                        pdd tmp = combi2(temp);
                        
                        low= min(low, tmp.first);
                        high= max(high, tmp.second);
                    }
                }
            }
        }
        double score= getRank(flop);
        
        low= min(low, score);
        high= max(high, score);
        
        return {low, high};
    }
    return {0,0};
}

double getBest(vector<string>& hand, vector<string>& flop)
{
    vector<string> all(hand);
    for(auto &e: flop)
    {
        all.push_back(e);
    }
    
    int n = all.size();
    
    double score= 0;
    
    for(int i=0;i<(n-4);i++)
    {
        for(int j=i+1;j<(n-3);j++)
        {
            for(int k=j+1;k<(n-2);k++)
            {
                for(int l=k+1;l<(n-1);l++)
                {
                    for(int m=l+1;m<n;m++)
                    {
                        vector<string> make= {all[i], all[j], all[k], all[l], all[m]};
                        double get= getRank(make);
                        score= max(get, score);
                    }
                }
            }
        }
    }
    return score;
}

double preFlopProb(vector<string>& hand)
{
    sort(hand.begin(), hand.end(), mysort);
    
    double prob, score;
    
    if(hand[0][0] == hand[1][0])
    {
        //pair of cards
        
        int better= 15-mp[hand[0][0]];
        
        int first = 2 + 4*(better-1);
        int second= 1 + 3*(better-1);
        
        prob = ((double)(first*second))/(50*49*1.0);
        prob = 1 - prob; //strength
        
        score= 50 + prob*10; //range from [50, 60];
        
    }else{
        
        int f = 15- mp[hand[1][0]]; //get better cards than the higher ranked card
        f= 3 + 4*(f-1); //playing on high card
        int s = 15- mp[hand[0][0]]; //get better cards than second ranked card
        s = 3 + 4*(s-1);
        
        if(hand[1][1]==hand[0][1])
        {
            f--;
            s--;
        }
        prob = ((double)(f*s))/(50*49*1.0);
        prob = 1 - prob; //strength
        
        score= prob*50; 
        
        
    }
    return score;
}
int main()
{
    func1();
    vector<string> hand= {"Ad", "Jd"};  
    
    vector<string> flop = {"Ac", "Jc", "As", "2c", "3d"};
    
    
    double pre_flop= -1;
    
    if(flop.size()==0)
    {
        cout<< preFlopProb(hand) <<endl;
        
    }else{
        int k = flop.size()-3;
    
        pdd score= analyse(flop, k);  //k=0, at flop, k=1, at turn, k=2-> at river

        double mini = score.first;
        double maxi = score.second;

        double best = getBest(hand, flop);

        double normalised= ((best-mini)/(double)(maxi-mini))*100;
        cout<<normalised<<endl;
    }
//     cout<<getRank(flop);
    
    // cout<<getRank(hand);
    // cout<<HandStrengthCalc(1, {})<<endl;
    return 0;
}

/*
High-Card, One-Pair -> (0,40)

Two-Pair and so on.. -> ()

*/

/*
    find low, high -> score= k
    
    scaled score= 
*/

/*
At flop, {Ac, Kc, 3d}

Left= 49

Best Combination - 
49C2 ways check - to find out the one with max strength

At Turn, 

Left= 48
48C2 
*/
