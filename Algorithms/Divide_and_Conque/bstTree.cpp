#include <iostream>
#include "../BSTtree.h"

void preorderTraversalHelp(const BSTNode* root)
{
	std::cout << root->getElement() << " ";
    if (root -> left()!= NULL)
    	preorderTraversalHelp(root -> left());
    if (root -> right() != NULL)
        preorderTraversalHelp(root -> right());
    return;
}

void preorderTraversal(const BSTNode* root)
{
	if (root == NULL)
	{
		std::cout << "Tree is empty.\n";
		return;
	}
	else
	{
		std::cout << "preorder:\t";
		preorderTraversalHelp(root);
	}
	std::cout << std::endl;
}

void inorderTraversalHelp(const BSTNode* root)
    {
        if (root -> left()!= NULL)
            inorderTraversalHelp(root -> left());
        std::cout << root->getElement() << " ";
        if (root -> right() != NULL)
            inorderTraversalHelp(root -> right());
        return;
    }

void inorderTraversal(const BSTNode* root)
{
    if (NULL == root)
        std::cout << "Empty tree.\n";
    else
    {
        std::cout << "inorder:\t";
        inorderTraversalHelp(root);
        std::cout << std::endl;
    }
    return;
}

void posorderTraversalHelp(const BSTNode* root)
    {
        if (root -> left()!= NULL)
            posorderTraversalHelp(root -> left());
        if (root -> right() != NULL)
            posorderTraversalHelp(root -> right());
        std::cout << root->getElement() << " ";
        return;
    }

void posorderTraversal(const BSTNode* root)
    {
        if (NULL == root)
            std::cout << "Empty tree.\n";
        else 
        {
            std::cout << "postorder:\t" ;
            posorderTraversalHelp(root);
            std::cout << std::endl;
            return;
        }
    }

int height(const BSTNode* root)
{
    //递归计算二叉树的高度
    //输入：树的根节点
    //输出：树的高度
    if (NULL == root)
        return -1;
    else
        return std::max(height(root->left()), height(root->right())) + 1;
}
