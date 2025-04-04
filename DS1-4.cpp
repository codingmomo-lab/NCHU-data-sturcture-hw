#include <iostream>
#include <fstream>
#include <algorithm> 


using namespace std;

// 定義「雙向連結串列」節點
struct Node {
    int id;           
    long long val;   
    Node* prev;      
    Node* next;      
};

int main() {
    ifstream fin("testcase4.txt");  
    ofstream fout("output4.txt");   

    int t; // 測試組數
    fin >> t;

    while(t--) {
        int n, m;
        fin >> n >> m;  // 讀入 n(位置數), m(要選的燈數)

        // 動態配置陣列以儲存亮度值
        long long* A = new long long[n];

        // 讀取每個位置的亮度
        for(int i = 0; i < n; i++) {
            fin >> A[i];
        }

        // 建立 n 個 Node (動態配置)
        Node* nodes = new Node[n];
        for(int i = 0; i < n; i++) {
            nodes[i].id  = i;//id為第幾個A[i]為亮度 
            nodes[i].val = A[i];
        }
        // 組成「圓形」雙向串列
        // i 的 next 指向 (i+1) % n
        // i 的 prev 指向 (i-1+n) % n
        for(int i = 0; i < n; i++) {
            nodes[i].next = &nodes[(i+1) % n];
            nodes[i].prev = &nodes[(i-1 + n) % n];//讓0可以接回尾巴 
        }

        // 若 m > n，不可能選到 m 個互不相鄰位置
        if(m > n) {
            fout << "Error!" << "\n";
            continue;
        }

        long long maxSum = -1; // 用來記錄最大和，-1 代表尚未找到解

        long long total = (1<< n);

        for(long long mask = 0; mask < total; mask++) {
        	if(__builtin_popcountll(mask) != m) {//若不為m就直接檢查下一個遮罩 
                continue;
            }
            // 檢查是否有相鄰位置同時被選
            bool valid = true;
            for(int i = 0; i < n; i++) {
                if(mask & (1LL << i)) {
                    Node* current = &nodes[i];
                    int leftID  = current->prev->id; // i 的前一個
                    int rightID = current->next->id; // i 的下一個

                    // 判斷前後是否有樹 
                    if(mask & (1LL << leftID)) {
                        valid = false;
                        break;
                    }
                    if(mask & (1LL << rightID)) {
                        valid = false;
                        break;
                    }
                }
                if(!valid) break;
            }

            if(!valid) {
                continue;
            }

            // 通過相鄰檢查後，計算亮度總和
            long long sumVal = 0;
            for(int i = 0; i < n; i++) {
                if(mask & (1LL << i)) {
                    sumVal += nodes[i].val;
                }
            }
            // 更新最大值
            if(sumVal > maxSum) {
                maxSum = sumVal;
            }
        }

        // 如果 maxSum 還是 -1，代表找不到可行解
        if(maxSum == -1) {
            fout << "Error!" << "\n";
        } else {
            fout << maxSum << "\n";
        }
        delete[] A;
        delete[] nodes;//釋放記憶體以跑下一次測資 
        
    }

    fin.close();
    fout.close();
    return 0;
}
