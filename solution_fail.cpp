#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#include <tuple>
#include <algorithm>

typedef std::pair<int, int> Pair;

struct ValueCompare{
public:
    bool operator()(const Pair &p1, const Pair &p2) const{
        return p1.second < p2.second;
    }
};

struct KeyCompare{
public:
    bool operator()(const Pair &p1, const Pair &p2) const{
        return p1.first > p2.first;
    }
};

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.size() <= 0) {
            return 0;
        }
        int min_price = prices[0];
        int min_price_index = 0;
        int max_profix = 0;

        std::vector< std::pair<int, int> > profit_recorder; // (profit, min_index)
        profit_recorder.push_back ( Pair(0, 0) );

        /*
        ======= 
        get all possible profits 
        =======
        */
        for ( int i = 1; i < prices.size(); i++) {
            printf("[%d] prices[%d]:%d, min_price:%d, ", i, i, prices[i], min_price);

            if (prices[i] < min_price) {
                min_price = prices[i];
                min_price_index = i;
                
            } else {
                if(prices[i] - min_price > 0) {
                    int cur_profit = prices[i] - min_price;
                    profit_recorder.push_back( Pair(cur_profit, min_price_index) );
                    /*
                        1                  2                  3                  4                  5
                        ^                                                                           ^
                        min_price:1                                                                 cur_profit = 5-1
                        min_price_index:0                                                           min_price_index:0

                        profit_recorder[x] = (cur_profit:5-1, min_price_index:0)

                    */
                    printf("cur_profit:%d, new min_price:%d, min_price_index:%d",cur_profit , min_price, min_price_index);
                }
            }
            printf("\n");
        }

        /*
        ======= 
        Then, get 2 maximum profits from the profit_recorder
        and make sure they have different min_price_index
        =======
        */

        // large -> small (sort the min_price_index)
        std::sort(profit_recorder.begin(), profit_recorder.end(), ValueCompare());

        // get maximum value from different min_price_index and push into max_candidate vector
        std::vector<int> tmp_vector;
        std::vector<int> max_candidate;
        int tmp_max = INT_MAX;
        int current_min_idx = -1;
        for (int i = 0 ; i < profit_recorder.size(); i++) {
            Pair tmp_pair = profit_recorder[i];

            printf("record_profit:%d, record_min_price_index:%d, current_min_idx:%d\n", tmp_pair.first, tmp_pair.second, current_min_idx);
            
            if ( (tmp_pair.second != current_min_idx && current_min_idx != -1)) {
                std::sort(tmp_vector.begin(), tmp_vector.end(), std::greater<int>());
                max_candidate.push_back(tmp_vector[0]);

                tmp_vector.clear();
                tmp_vector.push_back(tmp_pair.first);
                current_min_idx = tmp_pair.second;

            } else if (i == profit_recorder.size() -1) {
                tmp_vector.push_back(tmp_pair.first);
                std::sort(tmp_vector.begin(), tmp_vector.end(), std::greater<int>());
                max_candidate.push_back(tmp_vector[0]);

            } else {
                tmp_vector.push_back(tmp_pair.first);
                if (current_min_idx == -1) {
                    current_min_idx = tmp_pair.second;
                }
            }
        }

        // sort to get 2 maximum profits from max_candidate
        std::sort(max_candidate.begin(), max_candidate.end(), std::greater<int>());
        for (int i = 0 ; i < max_candidate.size(); i++) {
            printf("max_candidate[i]:%d\n", max_candidate[i]);
        }
        
        // get two largest numbers
        if (max_candidate.size() >= 2) {
            return max_candidate[0] + max_candidate[1];
        } else if (max_candidate.size() == 1) {
            return max_candidate[0];
        } else {
            return 0;
        }
    }

};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();
    std::vector<int> prices{ 7,6,4,3,1 };
    printf("output:%d\n", s -> maxProfit(prices));
}