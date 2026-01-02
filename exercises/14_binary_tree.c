/*
 ===============================================================================
 Exercise: 14_binary_tree.c
 Description: Implements a binary search tree with insertion and traversal
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Builds a binary search tree from user input
 - Inserts nodes maintaining BST property (left < parent < right)
 - Displays tree contents using inorder, preorder, and postorder traversals
 - Proper memory cleanup with recursive tree deletion
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TITLE "=== Binary Tree ===\n\n"
#define TITLE_GRAPH_TREE "\nGraph tree:\n"
#define TITLE_INITIAL_TREE "\nInitial tree contents:\n"

#define TEXT_EMPTY_TREE "  (Tree is empty)\n"
#define TEXT_INORDER "  Inorder: "
#define TEXT_PREORDER "\n  Preorder: "
#define TEXT_POSTORDER "\n  Postorder: "
#define TEXT_FREEING_MEMORY "\n\nFreeing remaining memory...\n"
#define TEXT_MEMORY_FREED "Memory freed successfully.\n"
#define TEXT_SPACE " "

#define INPUT_ITEMS "How many items do you want to add to the tree?: "
#define INPUT_VALUE "  Enter value %u: "

#define FORMAT_STRING "%s"
#define FORMAT_UNSIGNED "%u"
#define FORMAT_INTEGER "%d"
#define FORMAT_NODE "%d "
#define FORMAT_TREE_NODE "[%d]\n"

#define ERR_MSG_INVALID_INPUT "Error: Invalid input.\n"
#define ERR_MSG_INVALID_VALUE "Error: Invalid value input.\n"
#define ERR_MSG_GREATER_THAN_ZERO "Error: Value must be greater than zero.\n"
#define ERR_MSG_COULD_ALLOCATE_NODE "Error: Could not allocate memory for new node.\n"

#define MIN_VALUE 1
#define SCANF_SUCCESS 1
#define NEWLINE_CHAR '\n'
#define NEWLINE "\n"

#define TREE_SPACE_START 0
#define TREE_SPACE_INCREMENT 8
#define TREE_SPACE_INITIAL 10

typedef enum {
  SUCCESS = 0,
  ERROR_INVALID_INPUT = 1,
  ERROR_ALLOCATION_FAILED = 1,
  ERROR_ZERO_VALUE = 1
} StatusCode;

typedef struct TreeNode {
  int id;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

void clear_input_buffer(void);
StatusCode read_positive_integer(const char *prompt, unsigned int *value);
TreeNode *insert(TreeNode *root, int id);
TreeNode *build_tree(TreeNode *root, unsigned int items);
int is_tree_empty(const TreeNode *root);
void print_tree(TreeNode *root, int space);
void print_inorder(const TreeNode *root);
void print_preorder(const TreeNode *root);
void print_postorder(const TreeNode *root);
void free_tree(TreeNode *root);

int main(void) {
  TreeNode *root = NULL;
  unsigned int items;

  printf(TITLE);

  if (read_positive_integer(INPUT_ITEMS, &items) != SUCCESS) {
    return ERROR_INVALID_INPUT;
  }

  root = build_tree(root, items);
  if (root == NULL && items > 0) {
    return ERROR_ALLOCATION_FAILED;
  }

  printf(TITLE_GRAPH_TREE);
  print_tree(root, TREE_SPACE_START);

  printf(TITLE_INITIAL_TREE);
  if (is_tree_empty(root)) {
    printf(TEXT_EMPTY_TREE);
  } else {
    printf(TEXT_INORDER);
    print_inorder(root);
    printf(TEXT_PREORDER);
    print_preorder(root);
    printf(TEXT_POSTORDER);
    print_postorder(root);
  }

  printf(TEXT_FREEING_MEMORY);
  free_tree(root);
  printf(TEXT_MEMORY_FREED);

  return SUCCESS;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != NEWLINE_CHAR && c != EOF)
    ;
}

StatusCode read_positive_integer(const char *prompt, unsigned int *value) {
  printf(FORMAT_STRING, prompt);

  if (scanf(FORMAT_UNSIGNED, value) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_INPUT);
    clear_input_buffer();
    return ERROR_INVALID_INPUT;
  }
  clear_input_buffer();

  if (*value < MIN_VALUE) {
    fprintf(stderr, ERR_MSG_GREATER_THAN_ZERO);
    return ERROR_ZERO_VALUE;
  }

  return SUCCESS;
}

TreeNode *insert(TreeNode *root, int id) {
  if (root == NULL) {
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
    if (new_node == NULL) {
      fprintf(stderr, ERR_MSG_COULD_ALLOCATE_NODE);
      return NULL;
    }
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

TreeNode *build_tree(TreeNode *root, unsigned int items) {
  int value;

  for (unsigned int i = 0; i < items; i++) {
    printf(INPUT_VALUE, i + 1);

    if (scanf(FORMAT_INTEGER, &value) != SCANF_SUCCESS) {
      fprintf(stderr, ERR_MSG_INVALID_VALUE);
      clear_input_buffer();
      free_tree(root);
      return NULL;
    }
    clear_input_buffer();

    root = insert(root, value);
    if (root == NULL) {
      return NULL;
    }
  }

  return root;
}

int is_tree_empty(const TreeNode *root) { return root == NULL; }

void print_tree(TreeNode *root, int space) {
  if (root == NULL)
    return;

  space += TREE_SPACE_INCREMENT;

  print_tree(root->right, space);

  printf(NEWLINE);
  for (int i = TREE_SPACE_INITIAL; i < space; i++)
    printf(TEXT_SPACE);
  printf(FORMAT_TREE_NODE, root->id);

  print_tree(root->left, space);
}

void print_inorder(const TreeNode *root) {
  if (root != NULL) {
    print_inorder(root->left);
    printf(FORMAT_NODE, root->id);
    print_inorder(root->right);
  }
}

void print_preorder(const TreeNode *root) {
  if (root != NULL) {
    printf(FORMAT_NODE, root->id);
    print_preorder(root->left);
    print_preorder(root->right);
  }
}

void print_postorder(const TreeNode *root) {
  if (root != NULL) {
    print_postorder(root->left);
    print_postorder(root->right);
    printf(FORMAT_NODE, root->id);
  }
}

void free_tree(TreeNode *root) {
  if (root == NULL)
    return;
  free_tree(root->left);
  free_tree(root->right);
  free(root);
}
