// Implement an iterator to flatten a 2d vector.

// For example,
// Given 2d vector =

// [
//   [1,2],
//   [3],
//   [4,5,6]
// ]

// By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

// Hint:

// How many variables do you need to keep track?
// Two variables is all you need. Try with x and y.
// Beware of empty rows. It could be the first few rows.
// To write correct code, think about the invariant to maintain. What is it?
// The invariant is x and y must always point to a valid point in the 2d vector. Should you maintain your invariant ahead of time or right when you need it?
// Not sure? Think about how you would implement hasNext(). Which is more complex?
// Common logic in two different places should be refactored into a common method.
// Follow up:
// As an added challenge, try to code it using only iterators in C++ or iterators in Java.


// solution I: 简单拷贝
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        for (auto a : vec2d) {
            v.insert(v.end(), a.begin(), a.end());
        }    
    }
    int next() {
        return v[i++]; // 更新next下标
    }
    bool hasNext() {
        return i < v.size();
    }
private:
    vector<int> v;
    int i = 0;
};

// solution II: 双索引
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        v = vec2d;
        x = y = 0;
    }
    int next() {
        return v[x][y++];
    }
    bool hasNext() {
        while (x < v.size() && y == v[x].size()) {
            ++x; 
            y = 0;
        }
        return x < v.size();
    }    
private:
    vector<vector<int>> v;
    int x, y;
};

