// Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

// Example:

// Input: S = "ADOBECODEBANC", T = "ABC"
// Output: "BANC"
// Note:

// If there is no such window in S that covers all characters in T, return the empty string "".
// If there is such window, you are guaranteed that there will always be only one unique minimum window in S.


class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.size() < t.size())
        {
            return "";
        }
        
        // 先用t创建字典
        unordered_map<char, int> dict;  
        for (char ch: t)
        {
            dict[ch]++;
        }
        
        int left = 0;
        int right = 0;
        int resLen = INT_MAX; // 记录最终结果的长度，初始化为最大值
        int resLeft = 0;
        int resRight = 0;
        int required = dict.size(); // t中所有不同字符个数
        int formed = 0; // 遍历s过程中个数已经匹配的字符数目
        unordered_map<char, int> window; // 滑动窗口
        while (right < s.size())
        {
            char ch = s[right];            
            window[ch]++; // 增加窗口内容
            
            // 如果某个字符数目已经匹配，要记录下来
            if (dict.find(ch) != dict.end() && dict[ch] == window[ch])
            {
                formed++;
            }
            
            // 尝试增加left以缩小窗口，获得最优解
            while (left <= right && formed == required)
            {
                if (resLen > right - left + 1)
                {
                    resLen = right - left + 1;
                    resLeft = left;
                    resRight = right;
                }
                
                char ch = s[left];
                window[ch]--; // 缩小窗口
                if (dict.find(ch) != dict.end() && window[ch] < dict[ch])
                {
                    formed--; // 万一移除导致窗口失效，要处理formed
                }
                
                left++;
            }
            
            right++;
        }        
        
        // 注意窗口为空的情况
        return resLen == INT_MAX ? "" : s.substr(resLeft, resLen);
    }
};

// 此处有个优化方案：如果s中有许多t中不包含的字符，会导致窗口过大
// 可将s进行“瘦身”，只包含t中存在的字符
// 后续处理类似
class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.size() < t.size())
        {
            return "";
        }        
        
        unordered_map<char, int> dict;  
        for (char ch: t)
        {
            dict[ch]++;
        }
        
        // 此处多了一个瘦身数组v，仅记录t中出现的字符在s中的位置
        vector<int> v;
        for (int i = 0; i < s.size(); i++)
        {
            if (dict.find(s[i]) != dict.end())
            {
                v.push_back(i);
            }
        }
        
        // 这时left和right就代表v中的位置了
        int left = 0; 
        int right = 0;
        int resLen = INT_MAX;
        int resLeft = 0;
        int resRight = 0;
        int required = dict.size();
        int formed = 0;
        unordered_map<char, int> window;
        while (right < v.size())
        {
            char ch = s[v[right]]; // 一定要转成s中的位置          
            window[ch]++;
            
            if (dict.find(ch) != dict.end() && dict[ch] == window[ch])
            {
                formed++;
            }
            
            while (left <= right && formed == required)
            {
                // 一定要转成s中的位置         
                if (resLen > v[right] - v[left] + 1)
                {
                    resLen = v[right] - v[left] + 1;
                    resLeft = v[left];
                    resRight = v[right];
                }
                
                char ch = s[v[left]];
                window[ch]--;
                if (dict.find(ch) != dict.end() && window[ch] < dict[ch])
                {
                    formed--;
                }
                
                left++;
            }
            
            right++;
        }        
        
        return resLen == INT_MAX ? "" : s.substr(resLeft, resLen);
    }
};
