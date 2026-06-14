
// Search in rotated sorted array-II
/* Given an integer array nums, sorted in ascending order (may contain duplicate values) and a target value k. 
Now the array is rotated at some pivot point unknown to you. Return True if k is present and otherwise, return False.

Input : nums = [7, 8, 1, 2, 3, 3, 3, 4, 5, 6], k = 3
Output: True
Explanation: The element 3 is present in the array. So, the answer is True.

Input : nums = [7, 8, 1, 2, 3, 3, 3, 4, 5, 6], k = 10
Output: False
Explanation:The element 10 is not present in the array. So, the answer is False. */

// Brute Force: Usig Linear Search
class Solution {
public:
    bool searchInARotatedSortedArrayII(vector<int> &arr, int target)  {
        int n = arr.size();
        for(int i=0; i<n; i++){
            if(arr[i] == target){
                return true;
            }
        }
        return false;
    }
};
// TC: O(N) | SC: O(1)

// Optimal Approach: Cover Only Edge Case for duplicates : Srinking the search Space 
class Solution {
public:
    bool searchInARotatedSortedArrayII(vector<int> &arr, int target)  {
        int n = arr.size();
        int low = 0;
        int high = n-1;
        int ans = -1;
        while(low <= high){
            int mid = (low + high)/2;
            if(arr[mid] == target){
                return true;
            }
            // edge case for duplicates
            if(arr[low] == arr[mid] && arr[mid] == arr[high]){
                low++; high--;
                continue;
            }
            // check sorted half
            // left half sorted
            else if(arr[low] <= arr[mid]){
                if(arr[low] <= target && target <= arr[mid]){
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            // Right half sorted : // arr[mid] <= arr[high]
            else { 
                if(arr[mid] <= target && target <= arr[high]){
                    low = mid + 1;
                }
                else{
                    high = mid - 1;
                }
            }
        }
        return false;
    }
};
// Best & Average Case: TC: O(Log2(N)) | SC: O(1)
// Worst Case: TC: O(N/2) | SC: O(1) (case when only duplicates present)

// Find minimum in Rotated Sorted Array
/* Given an integer array nums of size N, sorted in ascending order with distinct values, and then rotated an unknown number of times 
(between 1 and N), find the minimum element in the array.
Input : nums = [4, 5, 6, 7, 0, 1, 2, 3]
Output: 0
Explanation: Here, the element 0 is the minimum element in the array.

Input : nums = [3, 4, 5, 1, 2]
Output: 1
Explanation:Here, the element 1 is the minimum element in the array. */

// Brute Force:
class Solution {
public:
    int findMin(vector<int> &arr)  {
        int mini = INT_MAX;
        int n = arr.size();
        for(int i=0; i<n; i++){
            if(arr[i] < mini){
                mini = arr[i];
            }
        }
        return mini;
    }
};
// TC: O(N) | SC: O(1)

// Optimal Approach: Sorted half may or may not contain the ans so we will take minimum from sorted part and check with other part
class Solution {
public:
    int findMin(vector<int> &arr)  {
        int ans = INT_MAX;
        int n = arr.size();
        int low = 0;
        int high = n-1;
        while(low <= high){
            int mid = (low + high)/2;
            // check the sorted half & take min element from it 
            if(arr[low] <= arr[mid]){
                ans = min(arr[low], ans);
                low = mid + 1;
            } 
            else{   // arr[mid] <= arr[high]
                ans = min(arr[mid], ans);
                high = mid - 1;
            }
        }
        return ans;
    }
};
// TC: O(log(N)) | SC: O(1)

// slightly optimized : Ur choice
class Solution {
public:
    int findMin(vector<int> &arr)  {
        int ans = INT_MAX;
        int n = arr.size();
        int low = 0;
        int high = n-1;
        while(low <= high){
            int mid = (low + high)/2;
            // if search space is already sorted then arr[low] will be smaller
            if(arr[low] <= arr[mid] && arr[mid] <= arr[high]){
                ans = min(ans, arr[low]);
                break;
            }
            // check the sorted half & take min element from it 
            if(arr[low] <= arr[mid]){
                ans = min(arr[low], ans);
                low = mid + 1;
            } 
            else{   // arr[mid] <= arr[high]
                ans = min(arr[mid], ans);
                high = mid - 1;
            }
        }
        return ans;
    }
};
// TC: O(log(N)) | SC: O(1)


// Find peak element
/*Given an array arr of integers. A peak element is defined as an element greater than both of its neighbors. 
Formally, if arr[i] is the peak element, arr[i - 1] < arr[i] and arr[i + 1] < arr[i]. 
Find the index(0-based) of a peak element in the array. If there are multiple peak numbers, 
return the index of any peak number.

Input : arr = [1, 2, 3, 4, 5, 6, 7, 8, 5, 1]
Output: 7
Explanation: In this example, there is only 1 peak that is at index 7.

Input : arr = [1, 2, 1, 3, 5, 6, 4]
Output: 1
Explanation: In this example, there are 2 peak numbers at indices 1 and 5. We can consider any of them. */
// Brute Force:
class Solution {
public:
    int findPeakElement(vector<int> &arr) {
        int n = arr.size();
        int ans = 0;
        for(int i=0; i<n; i++){
            if(( i==0 || arr[i-1] < arr[i]) && (i == n-1 || arr[i+1] < arr[i] )){
                return i;
            }
        }
        return -1;
    }
};
// TC: O(N) | SC: O(1) 

class Solution {
public:
    int findPeakElement(vector<int> &arr) {
        int n = arr.size();
        // Edge Cases:
        if(n == 1) return 0;
        if(arr[0] > arr[1]) return 0;
        if(arr[n-1] > arr[n-2]) return n-1;
        // Binary Search
        int low = 1;
        int high = n-2;
        while(low <= high){
            int mid = (low + high)/2;
            // if arr[mid] is Peak
            if(arr[mid - 1] < arr[mid] && arr[mid + 1] < arr[mid] ){
                return mid;
            }
            // Lying on increasing curve i.e. on left half
            else if(arr[mid - 1] < arr[mid]){
                low = mid + 1;
            }
            // Lying on decreasing curve i.e. on right half
            else {
                high = mid - 1;
            }
        }
        return -1;
    }
};
// TC: O(log2(N)) | SC: O(1) 


// Koko eating bananas
/*A monkey is given n piles of bananas, where the 'ith' pile has nums[i] bananas. 
An integer h represents the total time in hours to eat all the bananas.
Each hour, the monkey chooses a non-empty pile of bananas and eats k bananas. If the pile contains fewer than k bananas, 
the monkey eats all the bananas in that pile and does not consume any more bananas in that hour.
Determine the minimum number of bananas the monkey must eat per hour to finish all the bananas within h hours.

Input: n = 4, nums = [7, 15, 6, 3], h = 8
Output: 5
Explanation: If Koko eats 5 bananas/hr, he will take 2, 3, 2, and 1 hour to eat the piles accordingly. So, he will take 8 hours to complete all the piles.  

Input: n = 5, nums = [25, 12, 8, 14, 19], h = 5
Output: 25
Explanation: If Koko eats 25 bananas/hr, he will take 1, 1, 1, 1, and 1 hour to eat the piles accordingly. So, he will take 5 hours to complete all the piles */
// Brute Force:
class Solution {
private:
    // Helper function to find Maximum Element in the array : O(N)
    int findMax(vector<int> &arr){
        int n = arr.size();
        int maxi = INT_MIN;
        for(int i=0; i<n; i++){
            maxi = max(maxi, arr[i]);
        }
        return maxi;
    }

    // Helper function to calculate total hours required at given hourly rate
    // hourly is koko eating bananas per hour
    int calculateTotalHours(vector<int> &arr, int hourly){
        int totalHours = 0;
        int n = arr.size();
        for(int i=0; i<n; i++){
            totalHours += ceil((double)(arr[i]) / (double) (hourly));
        }
        return totalHours;
    }

public:
int minimumRateToEatBananas(vector<int> arr, int limit) {
    int maxi = findMax(arr);
    for(int i=1; i<=maxi; i++){
        int reqTime = calculateTotalHours(arr, i);
        if(reqTime <= limit){
            return i;
        }
    }
    return maxi; // dummy return value
    }
};
// TC: O((maxEle) * N) (Bound * Helper function) | SC: O(1)

// Optimal Approach:
class Solution {
private:
    // Helper function to find Maximum Element in the array : O(N)
    int findMax(vector<int> &arr){
        int n = arr.size();
        int maxi = INT_MIN;
        for(int i=0; i<n; i++){
            maxi = max(maxi, arr[i]);
        }
        return maxi;
    }

    // Helper function to calculate total hours required at given hourly rate
    int calculateTotalHours(vector<int> &arr, int hourly){
        int totalHours = 0;
        int n = arr.size();
        for(int i=0; i<n; i++){
            totalHours += ceil((double)(arr[i]) / (double) (hourly));
        }
        return totalHours;
    }
public:
int minimumRateToEatBananas(vector<int> arr, int limit) {
    int low = 1, high = findMax(arr);
    while(low <= high){
        int mid = (low + high)/2;
        int totalHours = calculateTotalHours(arr, mid);
        if(totalHours <= limit){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    return low;
    }
};
// TC: O(log2(maxEle) * N) (Bound * Helper function) | SC: O(1)
