
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

// Aggressive Cows
/* Given an array nums of size n, which denotes the positions of stalls, and an integer k, 
which denotes the number of aggressive cows, assign stalls to k cows such that the 
minimum distance between any two cows is the maximum possible. Find the maximum possible minimum distance.

Input: n = 6, k = 4, nums = [0, 3, 4, 7, 10, 9]
Output: 3
Explanation: The maximum possible minimum distance between any two cows will be 3 when 4 cows are 
placed at positions [0, 3, 7, 10]. Here the distances between cows are 3, 4, and 3 respectively. 
We cannot make the minimum distance greater than 3 in any ways.

Input : n = 5, k = 2, nums = [4, 2, 1, 3, 6]
Output: 5
Explanation: The maximum possible minimum distance between any two cows will be 5 when 2 cows are 
placed at positions [1, 6].  */
// Brute Force:
class Solution {
private:
    bool canWePlace(vector<int>& arr, int dist, int cows){
        int n = arr.size();
        int cntCows = 1;
        int lastCow = arr[0];
        for(int i=1; i<n; i++){
            if(arr[i] - lastCow >= dist){
                cntCows++;
                lastCow = arr[i];
            }
        }
        if(cntCows >= cows) return true;
        return false;
    }
public:
    int aggressiveCows(vector<int> &arr, int cows) {
        int n = arr.size();
        // sorting array for easier calculations
        sort(arr.begin(), arr.end());
        int limit = arr[n-1] - arr[0];
        for(int i=1; i <= limit ; i++){
            if (canWePlace(arr, i, cows) == false) {
                return (i - 1);
            }
        }
        return limit;
    }
};
// TC: O(N*logN) (Sorting) + O(Maxi - mini) * O(N) 

// Optimal Approach:
class Solution {
private:
    bool canWePlace(vector<int>& arr, int dist, int cows){
        int n = arr.size();
        int cntCows = 1;
        int lastCow = arr[0];
        for(int i=1; i<n; i++){
            if(arr[i] - lastCow >= dist){
                cntCows++;
                lastCow = arr[i];
            }
            if(cntCows >= cows) return true;
        }
        return false;
    }
public:
    int aggressiveCows(vector<int> &arr, int cows) {
        int n = arr.size();
        // sorting array for easier calculations
        sort(arr.begin(), arr.end());
        int limit = arr[n-1] - arr[0];
        // Binary Search
        int low = 1;
        int high = limit;
        while(low <= high){
            int mid = (low + high)/2;
            if(canWePlace(arr, mid, cows) == true){
                low = mid + 1;
            }
            else high = mid - 1;
        }
        return high;
    }
};
// TC: O(N*logN) (Sorting) + O(log(Maxi - mini)) * O(N) 

// Book Allocation Problem
/*Given an array nums of n integers, where nums[i] represents the number of pages in the i-th book, 
and an integer m representing the number of students, allocate all the books to the students so that 
each student gets at least one book, each book is allocated to only one student, and the allocation is contiguous.
Allocate the books to m students in such a way that the maximum number of pages assigned to a student 
is minimized. If the allocation of books is not possible, return -1.

Input: nums = [12, 34, 67, 90], m=2
Output: 113
Explanation: The allocation of books will be 12, 34, 67 | 90. One student will get the first 3 books and
 the other will get the last one.

Input: nums = [25, 46, 28, 49, 24], m=4
Output: 71
Explanation: The allocation of books will be 25, 46 | 28 | 49 | 24. */
// Brute Force:
class Solution {
private:
    int countStudents(vector<int> &arr, int pages){
        int n = arr.size();
        int students = 1;
        int pagesStudent = 0;
        for(int i = 0; i<n; i++){
            if(pagesStudent + arr[i] <= pages){
                pagesStudent += arr[i];           
            }
            else{
                students++;
                pagesStudent = arr[i];
            }
        }
        return students;
    }
public:
    int findPages(vector<int> &arr, int numStudents)  {
        int n = arr.size();
        // Book allocation impossible
        if(numStudents > n) return -1;
        // Calculate the range for binary Search
        int low = *max_element(arr.begin(), arr.end());
        int high = accumulate(arr.begin(), arr.end(), 0);
        // Linear Search for minimum maximum pages
        for(int pages = low; pages <= high; pages++){
            if(countStudents(arr, pages) == numStudents){
                return pages;
            }
        }
        return low;
    }
};
// TC: O((sum - maxi) * N) | SC: O(1)

// Optimal Approach:
class Solution {
private:
    int countStudents(vector<int> &arr, int pages){
        int n = arr.size();
        int students = 1;
        int pagesStudent = 0;
        for(int i = 0; i<n; i++){
            if(pagesStudent + arr[i] <= pages){
                pagesStudent += arr[i];           
            }
            else{
                students++;
                pagesStudent = arr[i];
            }
        }
        return students;
    }
public:
    int findPages(vector<int> &arr, int numStudents)  {
        int n = arr.size();
        // Book allocation impossible
        if(numStudents > n) return -1;
        // Calculate the range for binary Search
        int low = *max_element(arr.begin(), arr.end());
        int high = accumulate(arr.begin(), arr.end(), 0);
        // Binary Search for minimum maximum pages
        while(low <=high){
            int mid = (low + high)/2;
            if(countStudents(arr, mid) > numStudents){
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }
        return low;
    }
};
// TC: O(log(sum - maxi) * N) | SC: O(1)

// Median of 2 sorted arrays
/* Given two sorted arrays arr1 and arr2 of size m and n respectively, return the median of the two sorted arrays.
The median is defined as the middle value of a sorted list of numbers. In case the length of the list is even, 
the median is the average of the two middle elements.

Input: arr1 = [2, 4, 6], arr2 = [1, 3, 5]
Output: 3.5
Explanation: The array after merging arr1 and arr2 will be [ 1, 2, 3, 4, 5, 6 ]. As the length of the merged list is even, 
the median is the average of the two middle elements. Here two medians are 3 and 4. So the median will be the average of 3 and 4, which is 3.5.

Input: arr1 = [2, 4, 6], arr2 = [1, 3]
Output: 3.0
Explanation: The array after merging arr1 and arr2 will be [ 1, 2, 3, 4, 6 ]. The median is simply 3. */

// Brute Force:
class Solution {
public:
    double median(vector<int> &arr1, vector<int> &arr2) {
        int n1 = arr1.size();
        int n2 = arr2.size();
        vector<int> merged;
        // Apply the merge step
        int i = 0, j = 0;
        while (i < n1 && j < n2) {
            if (arr1[i] < arr2[j]) merged.push_back(arr1[i++]);
            else merged.push_back(arr2[j++]);
        }
        // Copy the remaining elements
        while (i < n1) merged.push_back(arr1[i++]);
        while (j < n2) merged.push_back(arr2[j++]);
        // Find the median
        int n = n1 + n2;
        // if odd length of merged array
        if(n % 2 == 1){
            return (double) merged[n/2];
        }
        // if even length of merged array
        double median = ((double) merged[n/2] + (double) merged[(n/2)-1])/2.0;
        return median;
    }
};
// TC: O(N1 + N2) (for loop) | SC: O(N1 + N2) (for merged array)

// Optimal Approach: 
class Solution {
public:
    //Function to find the median of two sorted arrays.
    double median(vector<int>& arr1, vector<int>& arr2) {
        int n1 = arr1.size(), n2 = arr2.size();
        /* Ensure arr1 is not larger than arr2 to simplify implementation*/
        if (n1 > n2) return median(arr2, arr1);
        int n = n1 + n2;
        // Length of left half
        int left = (n1 + n2 + 1) / 2; 

        // Apply binary search
        int low = 0, high = n1;
        while (low <= high) {
            // Calculate mid index for arr1
            int mid1 = (low + high) >> 1; 
            // Calculate mid index for arr2
            int mid2 = left - mid1; 

            // Calculate l1, l2, r1, and r2
            int l1 = (mid1 > 0) ? arr1[mid1 - 1] : INT_MIN;
            int r1 = (mid1 < n1) ? arr1[mid1] : INT_MAX;
            int l2 = (mid2 > 0) ? arr2[mid2 - 1] : INT_MIN;
            int r2 = (mid2 < n2) ? arr2[mid2] : INT_MAX;

            if (l1 <= r2 && l2 <= r1) {
                // If condition for finding median
                if (n % 2 == 1) return max(l1, l2);
                else return (max(l1, l2) + min(r1, r2)) / 2.0;
            } 
            else if (l1 > r2) {
                // Eliminate the right half of arr1
                high = mid1 - 1;
            } else {
                // Eliminate the left half of arr1
                low = mid1 + 1;
            }
        }
        // Dummy statement
        return 0; 
    }
};
// TC: O(log(min(N1 + N2))) (for loop) | SC: O(1)
