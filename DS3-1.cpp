#include<iostream>
#include<fstream>
using namespace std;

const int MAX=200000;
struct Node{
    int val;
    int min,max;
    Node *left, *right;
    Node(int l, int r): l(l), r(r), val(0), left(nullptr), right(nullptr) {}
};

int main(){
    int testcase;
    ifstream in("testcase1.txt");
    ofstream out("output1.txt");
    int n,m;
    in>>n>>m;
    int size=n+m;

    Node* root=new Node(1,size);
    Node* queue[MAX*4];
    int front=0,rear=0;//rear放入queue的位置 front提出queue的位置
    queue[rear++]=root;

    while(front<rear){
        Node* curr=queue[front++];
        if(curr->l==curr->r){
            continue;
        }
        int mid=(curr->l+curr->r)/2;
        curr->left=new Node(curr->l,mid);
        curr->right=new Node(mid+1,curr->r);
        queue[rear++]=curr->left;
        queue[rear++]=curr->right;
    }

    int pos[MAX];
    for(int i=1;i<=n;i++){
        pos[i]=m+i;
        Node* curr=root;
        while(curr->l!=curr->r){
            curr->val++;
            int mid=(curr->l+curr->r)/2;
            if(pos[i]<=mid){
                curr=curr->left;
            }else{
                curr=curr->right;
            }
        }
        curr->val++;
    }

    int Top=m;
    for(int i=1;i<=m;i++){
        int a;
        in>>a;

        //find
        int ans=0;
        int target=pos[a];
        Node* curr=root;
        while(curr->l!=curr->r){
            curr->val++;
            int mid=(curr->l+curr->r)/2;
            if(target<=mid){
                curr=curr->left;
            }else{
                ans+=curr->left->val;
                curr=curr->right;
            }
        }
        out<<ans<<" ";

        //remove 原本的
        curr=root;
        while(curr->l!=curr->r){
            curr->val--;
            int mid=(curr->l+curr->r)/2;
            if(pos[x]<=mid){
                curr=curr->left;
            }else{
                curr=curr->right;
            }
        }
        curr->val--;

        //insert new a
        pos[a]=Top--;
        curr=root;
        while(curr->l!=curr->r){
            curr->val++;
            int mid=(curr->l+curr->r)/2;
            if(pos[a]<=mid){
                curr=curr->lest;
            }else{
                curr=curr->right;
            }
        }
        cur->val++;
    }

    return 0;
}