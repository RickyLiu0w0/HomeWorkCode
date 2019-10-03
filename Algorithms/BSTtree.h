#ifndef BSTTREE_H
#define BSTTREE_H

#include <iostream>
class BSTNode
{
public:
    BSTNode() { lc = rc = NULL;}
    BSTNode(int K, int e, BSTNode* l = NULL, BSTNode* r = NULL)
    { k = K; it = e ; lc = l ; rc = r;}
    ~BSTNode() {}
    
    int& element() { return it;}

    inline int getElement() const {return it;}
    
    void set_element( const int& e) { it = e;}
    int& key() {return k;}
    void set_key( const int& K) { k = K; }
    
    inline BSTNode* right() const {return rc;}
    inline BSTNode* left() const {return lc;}
    
    void setRight(BSTNode* b) { rc = b;}
    void setLeft(BSTNode* b) { lc = b;}
    
    bool isLeaf() { return (lc == NULL) && (NULL == rc);}

private:
    int it;
    int k;
    BSTNode* lc;
    BSTNode* rc;
};

class BST
{
    
public:
    BST() { root = NULL ; nodecout = 0;}
    ~BST() {clearhelp(root);}
    
    void insert(const int& k, const int& e)
    {
        root = inserthelp(root,k ,e);
        nodecout++;
    }
    
    bool remove(const int& k, int& e)
    {
        if ( findhelp(root, k, e))
        {
            root = removehelp(root, k);
            nodecout--;
            return true;
        }
        else return false;
    }
    
    bool remove_any(int& it)
    {
        if (root != NULL)
        {
            it = root -> element();
            root = removehelp(root, root -> element()); // 删除根节点
            nodecout--;
            return true;
        }
        else return false;
    }
    
    void find(const int& key, int& e) const
    {
        if (findhelp(root, key, e))
		{
            std::cout << "Find " << e  << " !\n";
			return ;
		}
        else 
		{
			std::cout << "Can't find " << key << std::endl;
			return ;
		}
    }
    
    int size() {return nodecout;}
    
    void print() const
    {
        if (root == NULL)
            std::cout << "The BST is empty.\n";
        else printhelp(root, 0);
    }
    
    void build()
    {
        int it;
        char ch;
        std::cout << "Enter the array(q to quit): ";
        while (std::cin >> it)  { insert(it, it); }
        std::cin.clear();
        std::cin >> ch;
        while (ch != '\n')  {ch = std::cin.get();};
    }

    inline BSTNode* getRoot() const {return root;}
    
    /**
    //放入算法分治法中
    void preOrderTraversal()
    {
        if (NULL == root)
            std::cout << "Empty tree.\n";
        preorderTraversalHelp(root);
        std::cout << std::endl;
        return;
    }
    
    void inOrderTraversal()
    {
        if (NULL == root)
            std::cout << "Empty tree.\n";
        inorderTraversalHelp(root);
        std::cout << std::endl;
        return;
    }
    
    void posOrderTraversal()
    {
        if (NULL == root)
            std::cout << "Empty tree.\n";
        posorderTraversalHelp(root);
        std::cout << std::endl;
        return;
    }
	**/
private:
    BSTNode* root;
    int nodecout;
    
    void clearhelp(BSTNode* rt)
    {
        if (rt == NULL) return;
        clearhelp(rt->left());
        clearhelp(rt->right());
        delete rt;
    }
    
    BSTNode* inserthelp(BSTNode* rt, const int& k, const int& it)
    {
        if (rt == NULL)
            return new BSTNode(k ,it, NULL, NULL);
        if (k < rt->key())
            rt -> setLeft(inserthelp(rt->left(), k, it));
        else
            rt -> setRight(inserthelp(rt->right(), k, it));
        return rt;
    }
    
    BSTNode* delete_min( BSTNode* rt)
    {
        if (rt->left() == NULL)
            return rt->right();
        else
        {
            rt -> setLeft(delete_min(rt->left()));
            return rt;
        }
    }
    
    BSTNode* getmin(BSTNode* rt)
    {
        if (root -> left() == NULL )
            return rt;
        else return getmin( rt-> left());
    }
    
    BSTNode* removehelp( BSTNode* rt, const int& k)
    {
        if (NULL == rt) return NULL;
        else if (k < rt->key())
            rt -> setLeft(removehelp(rt->left(), k));
        else if (k > rt->key())
            rt -> setRight(removehelp(rt->right(), k));
        else
        {
            BSTNode* temp = rt ;
            if (rt -> right() == NULL)
            {
                rt = rt -> left();
                delete temp;
            }
            else if (rt -> left() == NULL)
            {
                rt = rt -> right();
                delete temp;
            }
            else
            {
                temp = getmin(rt->right());
                rt->set_element(temp->element());
                rt->set_key(temp->key());
                rt->setRight(delete_min(rt->right()));
                delete temp;
            }
        }
        return rt;
    }
    
    bool findhelp( BSTNode* root, const int& k,int& e) const
    {
        if (root == NULL) return false;
        if (k < root -> key())
            return findhelp(root -> left(), k, e);
        else if (k > root -> key())
            return findhelp(root -> right(), k, e);
        else { e = root -> element(); return true;}
    }
    
    void printhelp( BSTNode* root,int level) const
    {
        if (NULL == root) return;
        printhelp(root->right(), level+1);
        for (int i = 0; i < level; i++)
            std::cout << "   ";
        std::cout << root->key() << "\n";
        printhelp(root->left(), level+1);
        
    }
    
    /**
    //放入算法分治法中
    void preorderTraversalHelp(BSTNode* root)
    {
        std::cout << root->element() << " ";
        if (root -> left()!= NULL)
            preorderTraversalHelp(root -> left());
        if (root -> right() != NULL)
            preorderTraversalHelp(root -> right());
        return;
    }
    
    void inorderTraversalHelp(BSTNode* root)
    {
        if (root -> left()!= NULL)
            preorderTraversalHelp(root -> left());
        std::cout << root->element() << " ";
        if (root -> right() != NULL)
            preorderTraversalHelp(root -> right());
        return;
    }
    
    void posorderTraversalHelp(BSTNode* root)
    {
        if (root -> left()!= NULL)
            preorderTraversalHelp(root -> left());
        if (root -> right() != NULL)
            preorderTraversalHelp(root -> right());
        std::cout << root->element() << " ";
        return;
    }
    **/
};

#endif