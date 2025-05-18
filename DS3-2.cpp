#include<iostream>
#include<fstream>
using namespace std;

struct Node{
    int val;
    Node* right;
    Node* left;
    Node(int x){
        val=x;
        left=NULL;
        right=NULL;
    }
};

int findindex(int inorder[],int start, int end, int val){
    for(int i=start;i<=end;++i){
        if(inorder[i]==val){
            return i;
        }
    }
    return -1;
}

Node* buildTree(int inorder[],int postorder[],int start,int end,int& postindex){
    if(start>end){
        return NULL;
    }
    int rootval=postorder[postindex--];
    Node* root=new Node(rootval);
    if(start==end){
        return root;
    }
    int rootindex =findindex(inorder,start,end,rootval);

    root->right=buildTree(inorder,postorder,rootindex+1,end,postindex);
    root->left=buildTree(inorder,postorder,start, rootindex-1,postindex);
    return root;
}
void preorderPrint(Node* root,ofstream& out) {
    if (root == NULL) return;
    out << root->val << " ";
    preorderPrint(root->left,out);
    preorderPrint(root->right,out);
}

int main(){
    ifstream in("testcase2.txt");
    ofstream out("output2.txt");
    int testcase;
    in>>testcase;
    while(testcase--){
        int order;
        in>>order;
        int* inorder = new int[order];
        int* postorder = new int[order];
        for(int i=0;i<order;i++){
            in>>inorder[i];
        }
        for(int i=0;i<order;i++){
            in>>postorder[i];
        }
        int postindex=order-1;

        Node* root=buildTree(inorder,postorder,0,order-1,postindex);
        preorderPrint(root,out);
        out<<endl;
        delete[] inorder;
        delete[] postorder;
    }
    return 0;
    

}
