// Given a nested list of integers, return the sum of all integers in the list weighted by their depth.

// Each element is either an integer, or a list -- whose elements may also be integers or other lists.

// Example 1:
// Given the list [[1,1],2,[1,1]], return 10. (four 1's at depth 2, one 2 at depth 1)

// Example 2:
// Given the list [1,[4,[6]]], return 27. (one 1 at depth 1, one 4 at depth 2, and one 6 at depth 3; 1 + 4*2 + 6*3 = 27)

// 本质上就是树的另一种表达形式
// solution I: dfs
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        return helper(nestedList, 1);
    }
    
    // 类似341. Flatten Nested List Iterator
    int helper(vector<NestedInteger>& nl, int depth) 
    {
        int res = 0;
        
        for (auto a : nl) 
        {
            if (a.isInteger())
                res += a.getInteger() * depth;
            else
                res += helper(a.getList(), depth + 1);
        }
        
        return res;
    }
};

// solution II: bfs
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        int res = 0;
        int depth = 1;
        queue<NestedInteger> q;

        for (const NestedInteger& ni: nestedList)
        {
            q.push(ni);
        }

        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                NestedInteger ni = q.top();
                q.pop();

                if (ni.isInteger())
                {
                    res += q.getInteger() * depth;
                }
                else
                {
                    for (const NestedInteger& t: ni.getList())
                    {
                        q.push(t);
                    }
                }
            }

            depth++; // 记得递增深度
        }
        
        return res;
    }
};