# Sliding Window

| Name                                                                                                                            | Level  | Solution           | LC Premium |
| ------------------------------------------------------------------------------------------------------------------------------- | ------ | ------------------ | ---------- |
| [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)                               | Easy   | [Python](./121.py) |            |
| [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | Medium | [Python](./3.py)   |            |
| [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)               | Medium | [Python](./424.py) |            |
| [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)                                             | Hard   | [Python]           |            |
| [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)                                                 | Hard   | [Python]           |            |
| [Permutation in String](https://leetcode.com/problems/permutation-in-string/)                                                   | Medium | [Python](./567.py) |            |


## Template

```cpp
int findSubstring(string s){
        vector<int> map(128,0);
        int counter; // check whether the substring is valid
        int begin=0, end=0; //two pointers, one point to tail and one  head
        int d; //the length of substring

        for() { /* initialize the hash map here */ }

        while(end<s.size()){

            if(map[s[end++]]-- ?){  /* modify counter here */ }

            while(/* counter condition */){ 
                 
                 /* update d here if finding minimum*/

                //increase begin to make it invalid/valid again
                
                if(map[s[begin++]]++ ?){ /*modify counter here*/ }
            }  

            /* update d here if finding maximum*/
        }
        return d;
  }
```