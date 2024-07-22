/* Merge 2 arrays and sort the result */
#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
};

Node *FindMin(Node *root);
Node *Delete(Node *root, int data);
void Inorder(Node *root);
Node *Insert(Node *root, char data);

int main() {
  Node *root = NULL;
  root = Insert(root, 5);
  root = Insert(root, 10);
  root = Insert(root, 3);
  root = Insert(root, 4);
  root = Insert(root, 1);
  root = Insert(root, 11);

  root = Delete(root, 5);

  cout << "Inorder: ";
  Inorder(root);
  cout << "\n";
}

Node *FindMin(Node *root) {
  while (root->left != NULL) {
    root = root->left;
  }
  return root;
}

Node *Delete(Node *root, int data) {
  if (root == NULL) {
    return root;
  } else if (data < root->data) {
    root->left = Delete(root->left, data);
  } else if (data > root->data) {
    root->right = Delete(root->right, data);
  } else {
    if ((root->left == NULL) && (root->right == NULL)) { /*Case 1: no child*/
      delete root;
      root = NULL;
    } else if (root->left == NULL) { /*Case 2: one child*/
      Node *temp = root;
      root = root->right;
      delete temp;
    } else if (root->right == NULL) {
      Node *temp = root;
      root = root->left;
      delete temp;
    } else { /*Case 3: two children*/
      Node *temp = FindMin(root->right);
      root->data = temp->data;
      root->right = Delete(root->right, temp->data);
    }
  }
  return root;
}

void Inorder(Node *root) {
  if (root == NULL) {
    return;
  }

  Inorder(root->left);
  cout << root->data << " ";
  Inorder(root->right);
}

Node *Insert(Node *root, char data) {
  if (root == NULL) {
    root = new Node();
    root->data = data;
    root->left = root->right = NULL;
  } else if (data <= root->data) {
    root->left = Insert(root->left, data);
  } else {
    root->right = Insert(root->right, data);
  }
  return root;
}