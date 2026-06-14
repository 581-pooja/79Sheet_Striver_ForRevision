
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
