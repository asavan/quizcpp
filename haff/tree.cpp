#include "tree.h"
#include <assert.h>

TreeNode* CreateNote1(int k, int c)
{
	TreeNode* a = new TreeNode;
	a->value.kolvo = k;
	a->value.nomer = c;
	a->prev = a->left = a->right = NULL;
	return a;
}

TreeNode* GoLeft(TreeNode* a)
{
	assert(a);
	return a->left;
}
TreeNode* GoRight(TreeNode* a)
{
	assert(a);
	return a->right;
}

TreeNode* AddLeft(TreeNode* x, TreeNode* root)
{
	if (!root) {
		// DANGER
		return x;
	}
	root->left = x;
	x->prev = root;
	return root;
}
TreeNode* AddRight(TreeNode* x, TreeNode* root)
{
	assert(root);
	root->right = x;
	x->prev = root;
	return root;
}

//obhody
void Left_Right1(TreeNode* pos, void(*f)(TreeNode*))
{
	if (pos == NULL) return;
	Left_Right1(GoLeft(pos), f);
	f(pos);
	Left_Right1(GoRight(pos), f);
}

void Down_Up(TreeNode* pos, void(*f)(TreeNode*))
{
	if (pos == NULL) return;
	Down_Up(GoLeft(pos), f);
	Down_Up(GoRight(pos), f);
	f(pos);
}


static void FreeSpase(TreeNode* a)
{
	delete a;
}

void DelTree(TreeNode* root)
{
	TreeNode* a;
	a = root;
	Down_Up(a, FreeSpase);
}