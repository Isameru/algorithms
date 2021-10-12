//
// https://leetcode.com/problems/add-two-numbers/
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*struct NodePool
{
    struct Chunk
    {
        int count;
        int capacity;
        unique_ptr<ListNode[]> data;
    };

    int next_chunk_size = 64;
    vector<Chunk> chunks;
    
    void clear()
    {
        chunks.clear();
        chunks.reserve(32);
        next_chunk_size = 64;
    }
    
    ListNode* newNode(int x)
    {
        if (chunks.empty() || chunks.back().count == chunks.back().capacity) {
            chunks.push_back(Chunk{0, next_chunk_size, make_unique<ListNode[]>(next_chunk_size)});
            next_chunk_size *= 2;
        }
                             
        auto& last_chunk = chunks.back();
        auto* node = &last_chunk.data[last_chunk.count++];
        node->val = x;
        return node;
    }
};*/

class Solution {
    //NodePool pool;

public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //pool.clear();
        
        ListNode* out_head = nullptr;
        ListNode* out = nullptr;
        int val = 0;
        
        while (l1 || l2 || val) {
            if (l1 != nullptr) {
                val += l1->val;
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                val += l2->val;
                l2 = l2->next;
            }

            auto* out_next = new ListNode(val % 10);
            //auto* out_next = pool.newNode(val % 10);
            if (out != nullptr) {
                out->next = out_next;
            }
            else {
                assert(out_head == nullptr);
                out_head = out_next;
            }
            
            out = out_next;

            val = val / 10;
        }

        if (out_head != nullptr) {
            return out_head;
        }
        else {
            return new ListNode(0);
        }
    }
};
