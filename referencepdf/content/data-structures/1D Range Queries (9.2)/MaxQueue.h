/**
* Description: queue, but get() returns max element
* Time: O(1)
* Source: none
* Verification: none
*/

struct maxQueue {
    queue<int> q;
    deque<int> dq;
    void push(int v) {
        q.push(v);
        if(q.empty()) {dq.push_back(v); return;}
        while(!dq.empty() && dq.back() < v) dq.pop_back();
        dq.push_back(v);
    }
    void pop() {
        if(q.front() == dq.front()) dq.pop_front();
        q.pop();
    }
    int get() {return dq.front();}
    int size() {return (int)q.size();}
};
