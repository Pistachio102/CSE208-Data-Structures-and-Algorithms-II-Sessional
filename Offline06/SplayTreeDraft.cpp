#include <bits/stdc++.h>


using namespace std;



class Node
{


public:
    int key;
    Node *left;
    Node *right;




    Node(int item)
    {
        key=item;
        left=right=0;
    }

};

class SplayBST

{


public:

    Node *root;
    int flag;



    SplayBST()
    {
        root=0;
    }







    Node *rightRotate(Node *p)
    {
        Node *q = p->left;
        p->left = q->right;
        q->right = p;
        return q;
    }


    Node *leftRotate(Node *p)
    {
        Node *q = p->right;
        p->right = q->left;
        q->left = p;
        return q;
    }





    Node *splay(Node *node, int key)
    {

        if (node == 0 || node->key == key)
            return node;


        if (node->key > key)
        {
            if (node->left == 0) return node;

            if (node->left->key > key)
            {

                node->left->left = splay(node->left->left, key);
                node = rightRotate(node);

            }

            else if (node->left->key < key)
            {

                node->left->right = splay(node->left->right, key);


                if (node->left->right != 0)
                    node->left = leftRotate(node->left);

            }


            return (node->left == 0)? node: rightRotate(node);
        }
        else
        {

            if (node->right == 0) return node;


            if (node->right->key > key)
            {

                node->right->left = splay(node->right->left, key);

                if (node->right->left != 0)
                    node->right = rightRotate(node->right);

            }

            else if (node->right->key < key)
            {

                node->right->right = splay(node->right->right, key);
                node = leftRotate(node);

            }


            return (node->right == 0)? node: leftRotate(node);
        }
    }

    Node * Insert(Node *node,int k)
    {


        if (node == NULL)
        {
            Node *newNode=new Node(k);
            return newNode;

        }



        node = splay(node, k);
        if (node->key == k) return node;


        Node *newnode  = new Node(k);


        if (node->key > k)
        {
            newnode->right = node;
            newnode->left = node->left;
            node->left = 0;
        }


        else
        {
            newnode->left = node;
            newnode->right = node->right;
            node->right = 0;
        }

        return newnode;
    }




    Node* Delete(Node *node, int key)
    {
        Node *temp;
        if (!node)
            return 0;


        node = splay(node, key);


        if (key != node->key)
            return node;


        if (!node->left)
        {
            temp = node;
            node = node->right;
        }


        else
        {
            temp = node;

            node = splay(node->left, key);
            node->right = temp->right;
        }


        free(temp);


        return node;

    }








    void SplayInsert(int value)
    {
        root=Insert(root,value);

    }


    void SplayDelete(int value)
    {
        if(root==0)
        {
            cout<<"No item in the splay tree to delete."<<endl;
            cout<<endl;
            return;
        }

        root=Delete(root,value);
       // cout<<value<<" is deleted from the splay tree."<<endl;
        cout<<endl;
    }


    void SplaySearch(int value)
    {
        root=splay(root,value);
        if(root->key==value)
            cout<<"The key is found in the splay tree"<<endl;
        else cout<<"Item not found!"<<endl;

        cout<<endl;
    }


    void PrintpreOrder(Node *node)
{
    if (node != 0)
    {
        printf("%d -> ", node->key);
        PrintpreOrder(node->left);
        PrintpreOrder(node->right);
    }
}





    ~SplayBST()
    {
        if(root!=0)
            free(root);
    }

};





int main()
{
    SplayBST S;

    while(1)
    {

        int choice;



        cout<<"1.Insert  2.Delete  3.Search"<<endl;
        cout<<"4.Print  5.Print the root  6.Exit"<<endl;

        cin>>choice;

        cout<<endl;

        switch(choice)

        {
        case 1:
            {
                int val;

                cout<<"Enter the value to insert: "<<endl;

                cin>>val;

                S.SplayInsert(val);

                cout<<val<<" is inserted to the splay tree."<<endl;

                cout<<endl;

                break;
            }
        case 2:
            {
                int val;

                cout<<"Enter the value to delete: "<<endl;

                cin>>val;

                S.SplayDelete(val);

                break;



            }
        case 3:
            {
                int val;

                cout<<"Enter the value to search: "<<endl;

                cin>>val;

                S.SplaySearch(val);

                break;
            }
        case 4:
            {
                cout<<"Splay tree in preorder sequence: "<<endl;

                S.PrintpreOrder(S.root);

                cout<<endl;

                break;
            }
        case 5:
            {
                cout<<"The root of the splay tree: ";
                cout<<S.root->key<<endl;
                cout<<endl;
            }
        }


        if(choice==6)
        {
            break;
        }

    }






    return 0;
}
