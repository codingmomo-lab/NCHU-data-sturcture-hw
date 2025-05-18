#include <iostream>
#include <cstring>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    bool has_val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() {
        val = 0;
        has_val = false;
        left = right = NULL;
    }
};

int main(){
    ifstream in("testcase3.txt");
    ofstream out("output3.txt");
    string s;

    while (true) {
        TreeNode* root = new TreeNode();
        bool failed = false;
        bool has_input = false;

        while (in >> s) {
            if (s == "()") {
                break;
            }
            has_input = true;

            int val = 0;
            string path;
            int i = 1;
            while (isdigit(s[i])) {
                val = val * 10 + (s[i] - '0');
                ++i;
            }
            while (i < s.length() && (s[i] == ' ' || s[i] == ',')) {
                i++;
                
            }
            while (s[i] != ')') {
                path += s[i];
                ++i;
            }

            TreeNode* cur = root;
            for (char c : path) {
                if (c == 'L') {
                    if (cur->left == NULL) {
                        cur->left = new TreeNode();
                    }
                    cur = cur->left;
                } else if (c == 'R') {
                    if (cur->right == NULL) {
                        cur->right = new TreeNode();
                    }
                    cur = cur->right;
                }
            }
            if (cur->has_val) {
                failed = true;
            }
            cur->val = val;
            cur->has_val = true;
        }

        if (!has_input) {
            break;
        }

        if (failed) {
            out << "not complete" << endl;
        } else {
            queue<TreeNode*> q;
            TreeNode* output[300];
            int idx = 0;
            bool valid = true;

            q.push(root);
            while (!q.empty()) {
                TreeNode* cur = q.front(); q.pop();
                if (!cur->has_val) {
                    valid = false;
                    break;
                }
                output[idx++] = cur;
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }

            if (!valid) {
                out << "not complete" << endl;
            } else {
                for (int i = 0; i < idx; ++i) {
                    if (i > 0) out << " ";
                    out << output[i]->val;
                }
                out << endl;
            }
        }

        // Clean up memory
        queue<TreeNode*> cleanup;
        cleanup.push(root);
        while (!cleanup.empty()) {
            TreeNode* cur = cleanup.front(); cleanup.pop();
            if (cur->left) cleanup.push(cur->left);
            if (cur->right) cleanup.push(cur->right);
            delete cur;
        }
    }

    return 0;
}
