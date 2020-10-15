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

/*
    7,          1,          5,          3,          6,          4
    ^_______________________^___________________________________^
    |          ->                                   <-          |
    |         left                                 right        |
    find the first possible maximum profit                      |
                                            find the second possible maximum profit


    7,          1,          5,          3,          6,          4
    ^_______________________^___________________________________^
    left[0] = 0 profit                                     right[5] = 0 profit
    left[1] = 0 profit (1-7 = -6)                          right[4] = 0 profit (maximum(4-6, 0))
    left[2] = 4 profit (5-1 = 4, max profit = 4)           right[3] = 3 profit (maximum(6-3, 0), max profit = 3)
    left[3] = 4 profit ( maximum(3-1, 4) )                 right[2] = 3 profit (maximum(6-5, 3))
    left[4] = 5 profit ( maximum(6-1, 4), max profit = 5)  right[1] = 5 profit (maximum(6-1, 3), max profit = 5)
    left[5] = 5 profit ( maximum(4-1, 5) )                 right[0] = 5 profit (maximum(6-7, 5))
*/

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) {
        	return 0;
        }
        int *left = new int[prices.size()];
        int *right = new int[prices.size()];
        left[0] = 0;
        right[prices.size()] = 0;

        int min = prices[0];
        for (int i = 1 ; i < prices.size() ; i++) {
            // find the minimum value
            min = std::min(min, prices[i]);

            // calculate ith day's maximum profit
            int cur_profit = prices[i] - min;
            left[i] = std::max(left[i-1], cur_profit);
        }

        int max = prices[prices.size()-1];
        for (int i = prices.size() - 2 ; i >= 0 ; i--) {
            // find the minimum value
            max = std::max(max, prices[i]);

            // calculate ith day's maximum profit
            int cur_profit = max - prices[i];
            right[i] = std::max(right[i+1], cur_profit);
        }

        int maximum_res = 0;
        for (int i = 0 ; i < prices.size() ; i++) {
            printf("right[%d]: %d, left[%d]: %d\n", i, right[i], i, left[i]);
            maximum_res = std::max(maximum_res, right[i]+left[i]);
        }

        return maximum_res;
    }

};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();
    std::vector<int> prices{ 7,1,5,3,6,4 };
    printf("output:%d\n", s -> maxProfit(prices));
}