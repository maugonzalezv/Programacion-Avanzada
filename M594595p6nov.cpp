#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int main() {
    int n;
    
    while(cin >> n && n != 0) {
        int ops[1000][2];
        
        for(int i = 0; i < n; i++) {
            char op;
            cin >> op >> ops[i][1];
            ops[i][0] = (op == 'i') ? 0 : 1;
        }
        
        bool esStack = true;
        bool esQueue = true;
        bool esPQ = true;
        
        stack<int> st;
        queue<int> q;
        priority_queue<int> pq;
        
        for(int i = 0; i < n; i++) {
            if(ops[i][0] == 0) {
                st.push(ops[i][1]);
                q.push(ops[i][1]);
                pq.push(ops[i][1]);
            } else {
                if(st.empty() || st.top() != ops[i][1]) {
                    esStack = false;
                } else {
                    st.pop();
                }
                
                if(q.empty() || q.front() != ops[i][1]) {
                    esQueue = false;
                } else {
                    q.pop();
                }
                
                if(pq.empty() || pq.top() != ops[i][1]) {
                    esPQ = false;
                } else {
                    pq.pop();
                }
            }
        }
        
        int count = 0;
        if(esStack) count++;
        if(esQueue) count++;
        if(esPQ) count++;
        
        if(count == 0) {
            cout << "impossible" << endl;
        } else if(count > 1) {
            cout << "uncertain" << endl;
        } else {
            if(esStack) cout << "stack" << endl;
            else if(esQueue) cout << "queue" << endl;
            else cout << "priority queue" << endl;
        }
    }
    
    return 0;
}