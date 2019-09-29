#include <iostream>

void preorderTraversal(const BSTNode* root)
{
	if (root == NULL)
	{
		std::cout << "Tree is empty.\n";
		return;
	}
	else
	{
		std::cout << root->element() << " ";
        if (root -> left()!= NULL)
            preorderTraversalHelp(root -> left());
        if (root -> right() != NULL)
            preorderTraversalHelp(root -> right());
        return;
	}
}