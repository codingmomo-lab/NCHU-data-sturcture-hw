#include <iostream>
#include <fstream>
#include <algorithm> 


using namespace std;

// �w�q�u���V�s����C�v�`�I
struct Node {
    int id;           
    long long val;   
    Node* prev;      
    Node* next;      
};

int main() {
    ifstream fin("testcase4.txt");  
    ofstream fout("output4.txt");   

    int t; // ���ղռ�
    fin >> t;

    while(t--) {
        int n, m;
        fin >> n >> m;  // Ū�J n(��m��), m(�n�諸�O��)

        // �ʺA�t�m�}�C�H�x�s�G�׭�
        long long* A = new long long[n];

        // Ū���C�Ӧ�m���G��
        for(int i = 0; i < n; i++) {
            fin >> A[i];
        }

        // �إ� n �� Node (�ʺA�t�m)
        Node* nodes = new Node[n];
        for(int i = 0; i < n; i++) {
            nodes[i].id  = i;//id���ĴX��A[i]���G�� 
            nodes[i].val = A[i];
        }
        // �զ��u��Ρv���V��C
        // i �� next ���V (i+1) % n
        // i �� prev ���V (i-1+n) % n
        for(int i = 0; i < n; i++) {
            nodes[i].next = &nodes[(i+1) % n];
            nodes[i].prev = &nodes[(i-1 + n) % n];//��0�i�H���^���� 
        }

        // �Y m > n�A���i���� m �Ӥ����۾F��m
        if(m > n) {
            fout << "Error!" << "\n";
            continue;
        }

        long long maxSum = -1; // �ΨӰO���̤j�M�A-1 �N��|������

        long long total = (1<< n);

        for(long long mask = 0; mask < total; mask++) {
        	if(__builtin_popcountll(mask) != m) {//�Y����m�N�����ˬd�U�@�ӾB�n 
                continue;
            }
            // �ˬd�O�_���۾F��m�P�ɳQ��
            bool valid = true;
            for(int i = 0; i < n; i++) {
                if(mask & (1LL << i)) {
                    Node* current = &nodes[i];
                    int leftID  = current->prev->id; // i ���e�@��
                    int rightID = current->next->id; // i ���U�@��

                    // �P�_�e��O�_���� 
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

            // �q�L�۾F�ˬd��A�p��G���`�M
            long long sumVal = 0;
            for(int i = 0; i < n; i++) {
                if(mask & (1LL << i)) {
                    sumVal += nodes[i].val;
                }
            }
            // ��s�̤j��
            if(sumVal > maxSum) {
                maxSum = sumVal;
            }
        }

        // �p�G maxSum �٬O -1�A�N��䤣��i���
        if(maxSum == -1) {
            fout << "Error!" << "\n";
        } else {
            fout << maxSum << "\n";
        }
        delete[] A;
        delete[] nodes;//����O����H�]�U�@������ 
        
    }

    fin.close();
    fout.close();
    return 0;
}
