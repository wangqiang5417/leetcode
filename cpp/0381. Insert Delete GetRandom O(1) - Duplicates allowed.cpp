// Design a data structure that supports all following operations in average O(1) time.

// Note: Duplicate elements are allowed.
 

// insert(val): Inserts an item val to the collection.
// remove(val): Removes an item val from the collection if present.
// getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
 

// Example:

// // Init an empty collection.
// RandomizedCollection collection = new RandomizedCollection();

// // Inserts 1 to the collection. Returns true as the collection did not contain 1.
// collection.insert(1);

// // Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
// collection.insert(1);

// // Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
// collection.insert(2);

// // getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
// collection.getRandom();

// // Removes 1 from the collection, returns true. Collection now contains [1,2].
// collection.remove(1);

// // getRandom should return 1 and 2 both equally likely.
// collection.getRandom();


class RandomizedCollection {

public:
    /** Initialize your data structure here. */
    RandomizedCollection() {}
   
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        m[val].push(nums.size());
        nums.push_back(val);
        return m[val].size() == 1;
    }
   
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (m[val].empty()) return false;
        int idx = m[val].top();
        m[val].pop();
        if (nums.size() - 1 != idx) {
            int t = nums.back();
            nums[idx] = t;
            m[t].pop();
            m[t].push(idx);
        }
        nums.pop_back();
        return true;
    }
   
    /** Get a random element from the collection. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
private:
    vector<int> nums;
    unordered_map<int, priority_queue<int>> m;
};
