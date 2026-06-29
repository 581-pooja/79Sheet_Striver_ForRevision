/* 
Middle of a LinkedList [TortoiseHare Method]
Detect a loop in LL
Remove Nth node from the back of the LL
Find the intersection point of Y LL
Sort LL
Segregate odd and even nodes in LL
Check if LL is palindrome or not
Add two numbers in LL
*/

// Find the starting point in LL (Important : Intution)
/* Given the head of a singly linked list, the task is to find the starting point of a loop in the linked list 
if it exists. Return the starting node if a loop exists; otherwise, return null.
A loop exists in a linked list if some node in the list can be reached again by continuously 
following the next pointer. Internally, pos denotes the index (0-based) of the node from where the loop starts.
Note that pos is not passed as a parameter.

Input: head -> 1 -> 2 -> 3 -> 4 -> 5, pos = 1
Output(value of the returned node is displayed): 2
Explanation: The tail of the linked list connects to the node at 1st index.

Input: head -> 1 -> 3 -> 7 -> 4, pos = -1
Output(value of the returned node is displayed): null
Explanation: No loop is present in the linked list. */

// Brute Force: 
class Solution {
public:
    ListNode *findStartingPoint(ListNode *head) {
        if(head == NULL) return NULL;
        ListNode* temp = head;
        unordered_map<ListNode* , int> nodeMap;
        while(temp != NULL){
            if(nodeMap.find(temp) != nodeMap.end()){
                return temp;
            }
            nodeMap[temp] = 1;   // Marking node as visited
            temp = temp -> next;
        }
        return NULL;
    }
};
/* TC: O(N * 2 * log(N)) | so travere whole LL and logN to store 
Nodes & logN for searching so (2 * logN)
SC: O(N) (HashMap) */ 

// Optimal Code: -6.02 (Great Explanation in video must watch for intution)
class Solution {
public:
    ListNode *findStartingPoint(ListNode *head) {
        if(head == NULL) return NULL;
        ListNode* slow = head;
        ListNode* fast = head;
        // Phase 1: Detect the loop
        while(fast != NULL && fast -> next != NULL){
            slow = slow -> next;
            fast = fast -> next -> next;
            // If slow and fast meet, a loop is detected
            if(slow == fast){
                slow = head;
                // Phase 2: Find the first node of the loop
                while(slow != fast){
                    slow = slow -> next;
                    fast = fast -> next;
                }
                return slow;
            }
        }
        return NULL;
    }
};
// TC: O(N) | SC: O(1)

/* Find Middle of Linked List
Given the head of a singly Linked List, return the middle node of the Linked List.
If the Linked List has an even number of nodes, return the second middle one.

Input: head -> 3 -> 8 -> 7 -> 1 -> 3
Output(value at returned node): 7
Explanation: There are 5 nodes, so the middle node is the 3rd Node, with value 7.

Input: head -> 2 -> 9 -> 1 -> 4 -> 0 -> 4
Output(value at returned node): 4
Explanation: There are 6 nodes, thus both the 3rd and 4th nodes are middle. So the 2nd middle node (4th Node) is returned with value 4.
*/

class Solution {
public:
    ListNode* middleOfLinkedList(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast != nullptr && fast -> next != nullptr) {
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        return slow;
    }
};
// TC: O(N/2) | SC: O(1)


// Delete the middle node in LL (Important)
/*Given the head of a non-empty singly linked list containing integers, delete the middle node of the linked list. 
Return the head of the modified linked list.
The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based indexing, 
where ⌊x⌋ denotes the largest integer less than or equal to x.

Input: head -> 1 -> 2 -> 3 -> 4 -> 5
Output: head -> 1 -> 2 -> 4 -> 5
Explanation: n = 5.
⌊n / 2⌋ = 2, therefore middle node has index 2 and so the node with value 3 was deleted.

Input: head -> 7 -> 6 -> 5 -> 4
Output: head -> 7 -> 6 -> 4
Explanation: n = 4.
⌊n / 2⌋ = 2, therefore middle node has index 2 and so the node with value 5 was deleted*/

/* Intuition: First, count all the nodes by going through the list. Then, start again from the beginning and 
go to the node just before the middle one. Change the links to skip over the middle node, 
taking it out of the list.  */

// Brute Force:
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            delete head;
            return NULL;
        }
        int count = 0;
        ListNode* temp = head;
        // Traverse LL and find N
        while(temp != NULL){
            count++;
            temp = temp -> next;
        }
        // Find the node just before the middle node
        temp = head;
        int res = count/2;
        while(temp != NULL){
            res--;
            if(res == 0){
                ListNode* midNode = temp -> next;
                temp -> next = temp -> next -> next;
                delete midNode;
                break;
            }
            temp = temp -> next;
        }
        return head;
    }
};
// TC: O(N) + O(N/2) ~ O(N) | SC: O(1)

// Optimal Approach:
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            delete head;
            return NULL;
        }

        ListNode* slow = head;
        ListNode* fast = head;
        fast = fast -> next -> next;    // for getting 2st mid in even & odd LL
        while(fast != NULL && fast -> next != NULL){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        ListNode* midNode = slow -> next;
        slow -> next = slow -> next -> next;
        delete midNode;
        return head;
    }
};
// TC: O(N) | SC: O(1)


// Remove Nth node from the back of the LL
/* Given the head of a singly linked list and an integer n. Remove the nth node from the back 
of the linked List and return the head of the modified list. The value of n will always be less 
than or equal to the number of nodes in the linked list.

Input: head -> 1 -> 2 -> 3 -> 4 -> 5, n = 2
Output: head -> 1 -> 2 -> 3 -> 5
Explanation: The 2nd node from the back was the node with value 4.

Input: head -> 5 -> 4 -> 3 -> 2 -> 1, n = 5
Output: head -> 4 -> 3 -> 2 -> 1
Explanation: The 5th node from the back is the first node. */

// Brute Force: Calculate the len of LL then do Len - N = node before N Node delete its next
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == NULL) return NULL;

        int count = 0;
        ListNode* temp = head;
        // Count the number of nodes 
        while(temp != NULL){
            count++;
            temp = temp -> next;
        }
        // if n equals to total no. of nodes means delete head
        if(count == n){
            ListNode* newhead = head -> next;
            delete head;
            return newhead;
        }
        // calculate the position of node to delete (result node)
        int res = count - n;
        temp = head;
        while(temp != NULL){
            res--;
            if(res == 0){
                break;
            }
            temp = temp -> next;
        }
        // Delete the Nth node from the end
        ListNode* delNode = temp -> next;
        temp -> next = temp -> next -> next;
        delete delNode;
        return head;
    }
};
// TC: O(L) + O(L - N) | SC: O(1)

// Optimal Approach:
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == NULL) return NULL;

        ListNode* fast = head;
        ListNode* slow = head;
        /* Move the fast pointer n nodes ahead */
        for(int i=0; i<n; i++){
            fast = fast -> next;
        }
        // If fast is null means to delete head node
        if(fast == NULL){
            return head->next;
        }
        // Move both pointers untill fast reaches end i.e. cover Len - N distance
        while(fast->next != NULL){
            fast = fast -> next;
            slow = slow -> next;
        }
        // Delete the Nth node from the end
        ListNode* delNode = slow -> next;
        slow -> next = slow -> next -> next;
        delete delNode;
        return head;
    }
};
// TC: O(L) | SC: O(1)

// Find the intersection point of Y LL
/* Given the heads of two linked lists A and B, containing positive integers. Find the node at which the 
two linked lists intersect. If they do intersect, return the node at which the intersection begins, otherwise return null.
The Linked List will not contain any cycles. The linked lists must retain their original structure, 
given as per the input, after the function returns.
Note: for custom input, the following parameters are required(your program is not provided with these parameters):

Input: listA: intersectVal = 4, skipA = 3, skipB = 2, head -> 1 -> 2 -> 3 -> 4 -> 5, listB: head -> 7 -> 8 -> 4 -> 5
Output(value at returned node is displayed): 4
Explanation: The two lists have nodes with values 4 and 5 as their tails.

Input: listA: intersectVal = -1, skipA = -1, skipB = -1, head -> 1 -> 2 -> 3, listB: head -> 8 -> 9
Output(value at returned node is displayed): null
Explanation: The two lists do not intersect.

Input: listA: intersectVal = 4, skipA = 0, skipB = 0, head -> 4 -> 5 -> 6, listB: head -> 4 -> 5 -> 6
Output: 4 */

// Brute Force:
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == NULL || headB == NULL) return NULL;
        ListNode* temp = headA;
        // Inserting all Nodes of ListA or headA in HashMap
        unordered_map<ListNode* , int> nodeMap;
        while(temp != NULL){
            nodeMap[temp] = 1;  
            temp = temp -> next;
        }

        // Checking is any node of listA is present in listB then it is intersection
        temp = headB;
        while(temp != NULL){
            if(nodeMap.find(temp) != nodeMap.end()){
                return temp;
            }
            temp = temp -> next;
        }
        return NULL;
    }
};
// TC: O(N * log N + M * log N) | SC: O(N)
// TC:  (ListA Len * Insert in mpp logN + ListB len * find in mpp of len N so logN)  | SC: O(N) 

// Better Solution:
class Solution {
private:
    ListNode* collisionPoint(ListNode* t1, ListNode* t2, int d){
        // Traverse the extra d portion of greater list
        while(d){
            d--;
            t2 = t2 -> next;
        }
        // now both pointers are at same distance from collision Point so travere 
        while(t1 != t2){
            t1 = t1 -> next;
            t2 = t2 -> next;
        }
        return t1;
    }
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == NULL || headB == NULL) return NULL;
        ListNode* t1 = headA;
        ListNode* t2 = headB;
        int n1 = 0, n2 = 0;

        // Traverse List1 and get LengthA i.e. n1
        while(t1 != NULL){
            n1++;
            t1 = t1 -> next;
        }
        // Traverse List2 and get LengthB i.e. n2
        while(t2 != NULL){
            n2++;
            t2 = t2 -> next;
        }

        if(n1 < n2){
            // if ListB is greater than ListA
            return collisionPoint(headA, headB, n2 - n1);
        }
        else return collisionPoint(headB, headA, n1 - n2);
    }
};

// TC: O(N1 + N2 + (N2 - N1) + N1) ~ O(N1 + 2*N2)  | SC: O(1) 

// Amazing video Explanation short and easy
/* Optimal Approach: To find the intersection of two linked lists, we use the difference in their lengths to align their starting points 
and then traverse both lists simultaneously until we find the intersection node. 
t2 will take d distance to reach headA and t1 will take d distance to align itself to t1 at headA */

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == NULL || headB == NULL) return NULL;
        ListNode* t1 = headA;
        ListNode* t2 = headB;

        while(t1 != t2){
            t1 = t1 -> next;
            t2 = t2 -> next;

            // if same node return node else if both null return null
            if(t1 == t2) return t1; 

            if(t1 == NULL) t1 = headB;
            if(t2 == NULL) t2 = headA;
        }
        return t1;

    }
};

// TC: O(2*(n1 + n2))) (since two pointers) | SC: O(1) 

// Segregate odd and even nodes in LL
/*Given the head of a singly linked list. Group all the nodes with odd indices followed by all the 
nodes with even indices and return the reordered list.
Consider the 1st node to have index 1 and so on. The relative order of the elements inside the 
odd and even group must remain the same as the given input.
Input: head -> 1 -> 2 -> 3 -> 4 -> 5
Output: head -> 1 -> 3 -> 5 -> 2 -> 4
Explanation: The nodes with odd indices are 1, 3, 5 and the ones with even indices are 2, 4.

Input: head -> 4 -> 3 -> 2 -> 1
Output: head -> 4 -> 2 -> 3 -> 1
Explanation: The nodes with odd indices are 4, 2 and the ones with even indices are 3, 1*/

// Brute Force:
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head == NULL || head -> next == NULL){
            return head;
        } 
        vector<int> arr;
        ListNode* temp = head;

        // Traverse Odd indices and add in array
        while(temp != NULL && temp -> next != NULL){
            arr.push_back(temp -> val);
            temp = temp->next->next;
        }
        // If LL is odd length then add last index
        if(temp) arr.push_back(temp -> val);

        // Traverse Even indices and add in array
        temp = head -> next;
        while(temp != NULL && temp -> next != NULL){
            arr.push_back(temp -> val);
            temp = temp->next->next;
        }
        // If LL is even length then add last index
        if(temp) arr.push_back(temp -> val);

        // Replace Nodes in LL by arr elements
        int i = 0;
        temp = head;
        while(temp != NULL){
            temp -> val = arr[i];
            i++;
            temp = temp -> next;
        }
        return head;
    }
};
// TC: (O(N/2) + O(N/2)) ~ O(N) + O(N) | SC: O(N) (Extra space required for array)

// Optimal Approach:
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head == NULL || head -> next == NULL){
            return head;
        } 
        /* Initialize pointers for odd and even nodes and keep 
        track of the first even node */
        ListNode* odd = head;
        ListNode* even = head -> next;
        ListNode* evenHead = head -> next;

        // Rearranging nodes
        while(even != NULL && even->next != NULL){
            odd->next = odd->next->next;
            even->next = even->next->next;
            odd = odd->next;
            even = even->next;
        }
        /* Connect the last odd node to the first even node*/
        odd->next = evenHead;
        return head;
    }
};
// TC: (O(N/2) + O(N/2)) ~ O(N) (since two pointers traversing) | SC: O(1) 

// Add two numbers in LL
/*Given two non-empty linked lists l1 and l2 which represent two non-negative integers.
The digits are stored in reverse order with each node storing one digit.
Add two numbers and return the sum as a linked list.
    The sum Linked List will be in reverse order as well.
    The Two given Linked Lists represent numbers without any leading zeros, except when the number is zero itself.

Input: l1 = head -> 5 -> 4, l2 = head -> 4
Output: head -> 9 -> 4
Explanation: l1 = 45, l2 = 4.
l1 + l2 = 45 + 4 = 49.

Input: l1 = head -> 4 -> 5 -> 6, l2 = head -> 1 -> 2 -> 3
Output: head -> 5 -> 7 -> 9
Explanation: l1 = 654, l2 = 321.
l1 + l2 = 654 + 321 = 975.

Input: l1 = head -> 2 -> 4 -> 3, l2 = head -> 5 -> 6 -> 7 -> 9 (Great example to try)
Output: head -> 7 -> 0 -> 1 -> 0 -> 1
Explanation: l1 = 342, l2 = 9765.
l1 + l2 = 342  + 9765 = 10107
*/

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* list1, ListNode* list2) {
        
        ListNode* l1 = list1;
        ListNode* l2 = list2;
        ListNode* dummy = new ListNode();
        ListNode* temp = dummy;

        int carry = 0;
        while(l1 != NULL || l2 != NULL || carry){
            int sum = 0;
            if(l1 != NULL){
                sum += l1->val;
                l1 = l1 -> next;
            }
            if(l2 != NULL){
                sum += l2->val;
                l2 = l2 -> next;
            }

            sum += carry;
            ListNode* newNode = new ListNode(sum % 10);
            carry = sum / 10;
            temp -> next = newNode;
            temp = temp -> next;
        }
        return dummy->next;
    }
};
// TC: O(Max(l1, l2)) | SC: O(Max(l1, l2))

// Check if LL is palindrome or not (Important)
/*Given the head of a singly linked list representing a positive integer number. 
Each node of the linked list represents a digit of the number, with the 1st node containing the 
leftmost digit of the number and so on. Check whether the linked list values form a palindrome or not. 
Return true if it forms a palindrome, otherwise, return false.
A palindrome is a sequence that reads the same forward and backwards.

Input: head -> 3 -> 7 -> 5 -> 7 -> 3
Output: true
Explanation: 37573 is a palindrome.

Input: head -> 1 -> 1 -> 2 -> 1
Output: false
Explanation: 1121 is not a palindrome. */

// Brute Force:
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        stack<int> st;
        ListNode* temp = head;
        // Push all elems in Stack
        while(temp != NULL){
            st.push(temp ->val);
            temp = temp -> next;
        }

        temp = head;
        while(temp != NULL){
            if(temp -> val != st.top()){
                return false;
            }
            st.pop();
            temp = temp -> next;
        }
        return true;
    }
};
// TC: O(2*N) | SC: O(N) (Stack)

// Optimal Approach:
class Solution {
private: 
    ListNode* reverse(ListNode* head) {
        ListNode* temp = head;
        ListNode* prev = NULL;
        while(temp != NULL){
            ListNode* front = temp -> next;
            temp -> next = prev;
            prev = temp;
            temp = front;
        }
        return prev;
    }
public:
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        //      For odd Number       For even number - N/2
        while(fast -> next != NULL && fast->next->next != NULL){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        /*Reverse the second half of the linked list starting from the middle*/
        ListNode* newHead = reverse(slow -> next);   // N/2

        ListNode* first = head;
        ListNode* second = newHead;
        /*Compare data values of nodes from both halves.
        If values do not match, the list is not a palindrome*/
        while(second != NULL){                   // N/2
            if(first->val != second->val){
                reverse(newHead);
                return false;
            }
            first = first->next;
            second = second->next;
        } 
        /*Reverse the second half back to its original state*/
        reverse(newHead);    // N/2
        return true;
    }
};
// TC: O(2*N) | SC: O(1)

// Sorted Linked List
/* Given the head of a singly linked list. Sort the values of the linked list in non-decreasing order and 
return the head of the modified linked list.

Input: head -> 5 -> 6 -> 1 -> 2 -> 1
Output: head -> 1 -> 1 -> 2 -> 5 -> 6
Explanation: 1 <= 1 <= 2 <= 5 <= 6

Input: head -> 6 -> 5 -> -1 -> -2 -> -3
Output: head -> -3 -> -2 -> -1 -> 5 -> 6
Explanation: -3 <= -2 <= -1 <= 5 <= 6 */

// Brute Force:
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(head == NULL || head -> next == NULL) return head;
        // Traverse array and store the all elements in array
        vector<int> arr;
        ListNode* temp = head;
        while(temp != NULL){
            arr.push_back(temp->val);
            temp = temp -> next;
        }
        // sort the array
        sort(arr.begin(), arr.end());
        // replace array elements by LL elements
        temp = head;
        for(int i=0; i<arr.size(); i++){
            temp -> val = arr[i];
            temp = temp -> next;
        }
        return head;
    }
};
// TC: O(N) + O(N*logN) + O(N) | SC: O(N) (For array)

// Optimal Approach:
/* Intuition : Instead of using an external array to store node values, we can utilize an in-place sorting algorithm such as Merge Sort or Quick Sort, 
which can be adapted for linked lists. This approach avoids using additional space.
Merge Sort employs the divide and conquer strategy:-
Divides the linked list into smaller parts until they become trivial to sort (single node or empty list).
Merges and sorts the divided parts while combining them back together.
 */
class Solution {
private:
    ListNode* mergeTwoSortedLists(ListNode* list1, ListNode* list2) {
        // Temporary pointers to point to head of Lists
        ListNode* t1 = list1;
        ListNode* t2 = list2;
        // Create a dummy node to serve as the head of the merged list
        ListNode* dummyNode = new ListNode(-1);
        ListNode* temp = dummyNode;
        // Traverse both lists simultaneously
        while(t1 != NULL && t2 != NULL){
            // Merge smaller node to merged list
            if(t1 -> val < t2 -> val){
                temp -> next = t1;
                temp = t1;
                t1 = t1 -> next;
            }
            else{
                temp -> next = t2;
                temp = t2;
                t2 = t2 -> next;
            }
        }
        // If any list remaining then directly append list in merged list
        if(t1 != NULL) temp -> next = t1;
        else temp -> next = t2;
        return dummyNode -> next;
    }

    ListNode* findMiddle(ListNode* head){
        if(head == NULL || head -> next == NULL){
            return head;
        }

        ListNode* slow = head;
        ListNode* fast = head -> next;    // for getting 1st mid in even & odd LL
        while(fast != NULL && fast -> next != NULL){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        return slow;
    }

public:
    ListNode* sortList(ListNode* head) {
        /*Base case: if the list is empty or has only one node, 
        it is already sorted, so return the head*/
        if(head == NULL || head -> next == NULL){
            return head;
        }
        // Find middle of list using findMiddle function
        ListNode* middle = findMiddle(head);
        // Divide the list into two halves
        ListNode* right = middle -> next;
        middle -> next = NULL;
        ListNode* left = head;
        // Recursively sort left and right halves
        left = sortList(left);
        right = sortList(right);
        // Merge the sorted halves using the merge function
        return mergeTwoSortedLists(left, right);
    }
};
// TC : O(N * log2N ) (find Middle Stack tree)
/* Finding the middle node of the linked list requires traversing it linearly taking O(N) time complexity 
and to reach the individual nodes of the list, it has to be split log N times (continuously halve the list 
until we have individual elements).  */
// SC: O(1) + O(log N) (RSS)