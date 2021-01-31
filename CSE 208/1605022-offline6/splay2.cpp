#include<iostream>
#include<stdio.h>
using namespace std;
class node
{
    public:
    int item;
    node *left,*right;
    node(int x)
    {
        this->item=x;
        this->left= NULL;
        this->right=NULL;

    }


};

class Tree
{
 public:
    node *rightRotate( node *a)
{
     node *b = a->left;
    a->left = b->right;
    b->right = a;
    return b;
}

 node *leftRotate(node *a)
{
     node *b = a->right;
    a->right = b->left;
    b->left = a;
    return b;
}

node * splay(node *root, int x)
{
   if(root == NULL || root->item ==x)
        return root;
    if(root->item >x)
    {
        if(root->left == NULL)
            return root;
        //zig-zig
        if(root->left->item >x)
        {
            root->left->left = splay(root->left->left, x);
            root = rightRotate(root);
        }
        //zig-zag
        else if(root->left->item<x)
        {
            root->left->right = splay(root->left->right, x);
            if(root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        if(root->left != NULL)
            root = rightRotate(root);
        return root;
    }
    else
    {
        if(root->right == NULL)
            return root;
            //zig-zig
        if(root->right->item > x)
        {
            root->right->left = splay(root->right->left, x);
            if(root->right->left != NULL)
            {
                root->right = rightRotate(root->right);
            }
        }
        //zig-zag
        else if(root->right->item < x)
        {
            root->right->right = splay(root->right->right, x);
            root = leftRotate(root);
        }
        if(root->right != NULL)
            root = leftRotate(root);
        return root;
    }
}

node* search(node* root, int x)
{
    return splay(root, x);
}

 node *insert( node *root, int x)
{
    if (root == NULL) return new node(x);

    root = splay(root, x);

    if (root->item == x) return root;

     node *Node  = new node(x);

    if (root->item > x)
    {
        Node->right = root;
        Node->left = root->left;
        root->left = NULL;
    }

      else
    {
        Node->left = root;
        Node->right = root->right;
        root->right = NULL;
    }

    return Node;
}

node* delete_node(node *root, int x)
{

    if (root==NULL)
        return root;

    root = splay(root, x);


    if (root->item!=x)
    {
        printf("Key is not present in the tree\n");
        return root;

    }



    node *Node;
    if (root->left==NULL)
    {
        Node = root;
        root = Node->right;
    }

    else
    {
        Node = root;
        root = splay(root->left, x);

        root->right = Node->right;
    }


    return root;

}

void preorder_traversal(node* root)
{
    if(root != NULL)
    {
        printf("%d ",root->item);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }

}



};



int main()
{
    node *r=NULL;
    Tree T;
    printf("Enter your choice:\n");
    int n;

    while(1)
    {
        printf("1.Insert 2.Delete 3.Search 4.Print 5.Break\n");
        scanf("%d",&n);

        if(n==1)
        {
            int item;
            printf("Enter item:");
            scanf("%d",&item);
            r=T.insert(r,item);

        }
        if(n==2)
        {
            int item;
            printf("Enter item:");
            scanf("%d",&item);
            r=T.delete_node(r,item);

        }
        if(n==3)
        {
            int item;
            printf("Enter item:");
            scanf("%d",&item);
            r=T.search(r,item);
        }
        if(n==4)
        {
           printf("The preorder traversal is\n");
           T.preorder_traversal(r);
           printf("\n");

        }
        if(n==5) break;


    }

}


