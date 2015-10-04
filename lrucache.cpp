#include <iostream>
#include <unordered_map>
#include <climits>
using namespace std;

struct CacheNode
{
    int key;
    int value;
    CacheNode *prev;
    CacheNode *next;
    
    CacheNode(int k, int v)
    {
        key = k;
        value = v;
        prev = NULL;
        next = NULL;
    }
};

class LRUCache{
private: 
    int capacity;
    CacheNode *head;
    CacheNode *tail;
    unordered_map<int, CacheNode *> cacheMap;
public:
    // @param capacity, an integer
    LRUCache(int _capacity) {
        this->capacity = _capacity;
        this->head = NULL;
        this->tail = NULL;
    }
    
    // @return an integer
    int get(int key) {
        if(cacheMap.find(key) == cacheMap.end())
        {
            return INT_MIN;
        }
        
        CacheNode *node = cacheMap[key];
        removeNode(node);
        updateHead(node);
        return node->value;
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    void set(int key, int value) {
        CacheNode *node;
        if(cacheMap.find(key) == cacheMap.end())
        {
            node = new CacheNode(key, value);
            if(cacheMap.size() == capacity)
            {
                cacheMap.erase(tail->key);
                tail = tail->prev;
                if(tail != NULL)
                {
                    tail->next = NULL;
                }
            }
            cacheMap[key] = node;
        }
        else
        {
            node = cacheMap[key];
            removeNode(node);
            node->value = value;
        }
        
        updateHead(node);
    }
    
    // @param node, a cache node to be removed 
    // @return nothing
    void removeNode(CacheNode *node)
    {
        CacheNode *prev = node->prev;
        CacheNode *next = node->next;
        if(prev != NULL)
        {
            prev->next = next;
        }
        else
        {
            head = next;
        }
        
        if(next != NULL)
        {
            next->prev = prev;
        }
        else
        {
            tail = prev;
        }
    }
    
    // @param node, a cache node to be updated to head position
    // @return nothing
    void updateHead(CacheNode *node)
    {
        node->next = head;
        node->prev = NULL;
        if(head != NULL)
        {
            head->prev = node;
        }
        head = node;
        
        if(tail == NULL)
        {
            tail = head;
        }
    }
};



int main()
{
    LRUCache lru(4);

    cout << "set 7 28" << endl;
    lru.set(7, 28);
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "set(7, 1): " << endl;
    lru.set(7, 1);
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "get(7) ->  " ;
    cout << lru.get(7) << endl;
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "set(8, 15): " << endl;
    lru.set(8, 15);
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "get(6) ->  " ;
    cout << lru.get(6) << endl;
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "set(10, 27): " << endl;
    lru.set(10, 27);
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "set(8, 10): " << endl;
    lru.set(8, 10);
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "get(8) ->  " ;
    cout << lru.get(8) << endl;
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "get(6) ->  " ;
    cout << lru.get(6) << endl;
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "set(6, 29): " << endl;
    lru.set(6, 29);
    cout << "Press any key to continue " << endl;
    getchar();

    cout << "get(6) ->  " ;
    cout << lru.get(6) << endl;
    cout << "Press any key to continue " << endl;
    getchar();
    return 0;
}
