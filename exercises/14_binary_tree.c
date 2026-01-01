#include <stdio.h>
#include <stdlib.h>

#define TITLE "=== Binary Tree ===\n\n"

typedef struct TreeNode {
  int id;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *insert(TreeNode *root, int id);
void print_inorder(TreeNode *root);
// void free_tree(TreeNode *root);

int main(void) {
  TreeNode *root = NULL;

  printf(TITLE);

  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 70);
  root = insert(root, 20);
  root = insert(root, 40);
  print_inorder(root);
  return 0;
}

TreeNode *insert(TreeNode *root, int id) {
  if (root == NULL) {
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
    new_node->id = id;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
  }

  if (root->id > id) {
    root->left = insert(root->left, id);
  } else {
    root->right = insert(root->right, id);
  }

  return root;
}

void print_inorder(TreeNode *root) {
  if (root != NULL) {
    print_inorder(root->left);
    printf("%d ", root->id);
    print_inorder(root->right);
  }
}

// void free_tree(TreeNode *root) { return; }
