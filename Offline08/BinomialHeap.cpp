#include<bits/stdc++.h>

using namespace std;

int factorial(int  n)
{
    int result=1;
    for(int i=1;i<=n;i++)
    {
        result=result*i;
    }
    return result;
}
int nCr(int n,int r)
{
    return factorial(n)/(factorial(r)*factorial(n-r));
}


class node

{
    public:

    int key;

    int degree;

    node* parent;

    node* child;

    node* sibling;

    node()
    {
        key=0;

        degree=0;

        parent=0;

        child=0;

        sibling=0;
    }

};

/*

 * Class Declaration

 */

class BinomialHeap

{

    private:

        node *H;

        node *Hr;

        int count;

    public:

        node* Initializeheap();

        int Binomial_link(node*, node*);

        node* Create_node(int);

        node* Union(node*, node*);

        node* Insert(node*, node*);

        node* Merge(node*, node*);

        node* Extract_Min(node*);

        node* Find_Min(node*);

        int Revert_list(node*);

        int Display(node*);

        BinomialHeap()

        {

            H = Initializeheap();

            Hr = Initializeheap();

            int count = 1;

        }

};





node* BinomialHeap::Initializeheap()

{

    node* n;

    n = NULL;

    return n;

}



int BinomialHeap::Binomial_link(node* y, node* z)

{

    y->parent = z;

    y->sibling = z->child;

    z->child = y;

    z->degree = z->degree + 1;

}



node* BinomialHeap::Create_node(int k)

{

    node* p = new node();

    p->key = k;

    return p;

}



node* BinomialHeap::Insert(node* H, node* x)

{

    node* H1 = Initializeheap();

    x->parent = NULL;

    x->child = NULL;

    x->sibling = NULL;

    x->degree = 0;

    H1 = x;

    H = Union(H, H1);

    return H;

}



node* BinomialHeap::Union(node* H1, node* H2)

{

    node *H = Initializeheap();

    H = Merge(H1, H2);

    if (H == NULL)

        return H;

    node* prev_x;

    node* next_x;

    node* x;

    prev_x = NULL;

    x = H;

    next_x = x->sibling;

    while (next_x != NULL)

    {

        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)

            && (next_x->sibling)->degree == x->degree))

        {

            prev_x = x;

            x = next_x;

        }

        else

	    {

            if (x->key <= next_x->key)

            {

                x->sibling = next_x->sibling;

                Binomial_link(next_x, x);

            }

            else

            {

                if (prev_x == NULL)

                    H = next_x;

                else

                    prev_x->sibling = next_x;

                Binomial_link(x, next_x);

                x = next_x;

            }

	    }

        next_x = x->sibling;

    }

    return H;

}



node* BinomialHeap::Merge(node* H1, node* H2)

{

    node* H = Initializeheap();

    node* y;

    node* z;

    node* a;

    node* b;

    y = H1;

    z = H2;

    if (y != NULL)

    {

        if (z != NULL)

        {

            if (y->degree <= z->degree)

                H = y;

            else if (y->degree > z->degree)

                H = z;

        }

        else

            H = y;

    }

    else

        H = z;

    while (y != NULL && z != NULL)

    {

        if (y->degree < z->degree)

        {

            y = y->sibling;

        }

        else if (y->degree == z->degree)

        {

            a = y->sibling;

            y->sibling = z;

            y = a;

        }

        else

        {

            b = z->sibling;

            z->sibling = y;

            z = b;

        }

    }

    return H;

}



int BinomialHeap::Display(node* H)

{
     int c,flag,level;
		node *now = H;
		int counter=0;
		//cout<<now->key<<endl;



		while (now != NULL) {
			cout<<"B"<<now->degree<<endl;
			queue<node*> q;
			q.push(now);
			while (!q.empty()) {

				node *p   = q.front();
				if(p->parent!=NULL && flag==0)
                {
                  c=nCr(now->degree,level);
                 flag=1;
                }
                else if(flag==0 && p->parent==NULL)
                {
                     level=0;
                    c=nCr(now->degree,level);
                     flag=1;
                }


				q.pop();
				c--;
				cout<<p->key<<" ";



				if (p->child!= NULL) {


					node *temp = p->child;
					while (temp !=NULL) {
						q.push(temp);
						temp = temp->sibling;
					}
				}
				if(c==0)
                {
                level++;
                cout<<endl<<endl;
                flag=0;

                }
			}





			now = now->sibling;
			level=0;

		}


/*
    if (H == NULL)

    {

        cout<<"The Heap is empty"<<endl;

        return 0;

    }

    cout<<"The root nodes are: "<<endl;

    node* p;

    p = H;

    while (p != NULL)

    {

        cout<<p->key;

        if (p->sibling != NULL)

            cout<<"-->";

        p = p->sibling;

    }

    cout<<endl;
    */

}



node* BinomialHeap::Extract_Min(node* H1)

{

    Hr = NULL;

    node* t = NULL;

    node* x = H1;

    if (x == NULL)

    {

        cout<<"Nothing to Extract"<<endl;

        return x;

    }

    int min = x->key;

    node* p = x;

    while (p->sibling != NULL)

    {

        if ((p->sibling)->key < min)

        {

            min = (p->sibling)->key;

            t = p;

            x = p->sibling;

        }

        p = p->sibling;

    }

    if (t == NULL && x->sibling == NULL)

        H1 = NULL;

    else if (t == NULL)

        H1 = x->sibling;

    else if (t->sibling == NULL)

        t = NULL;

    else

        t->sibling = x->sibling;

    if (x->child != NULL)

    {

        Revert_list(x->child);

        (x->child)->sibling = NULL;

    }

    H = Union(H1, Hr);

    return x;


}

node* BinomialHeap::Find_Min(node* H1)
{
    node* y;

    y=0;

    node* x;

    x=H1;

    int min=INT_MAX;

    while(x!=0)
    {
        if(x->key<min)
            y=x;
        x=x->sibling;
    }
    return y;

}



int BinomialHeap::Revert_list(node* y)

{

    if (y->sibling != NULL)

    {

        Revert_list(y->sibling);

        (y->sibling)->sibling = y;

    }

    else

    {

        Hr = y;

    }

}






int main()

{

    int n, m, choice, i;

    BinomialHeap bh;

    node* p;

    node *H;

    H = bh.Initializeheap();

    char ch;

    while (1)

    {

         cout<<"----------------------------"<<endl;

        cout<<"1)Insert Element in the heap"<<endl;

        cout<<"2)Extract Minimum key node"<<endl;

        cout<<"3)Find minimum node"<<endl;

        cout<<"4)Print"<<endl;

        cout<<"5)Exit"<<endl;

        cout<<"Enter Your Choice: ";

        cin>>choice;

        switch(choice)

        {

        case 1:

            cout<<"Enter the element to be inserted: ";

            cin>>m;

            p = bh.Create_node(m);

            H = bh.Insert(H, p);

            break;

        case 2:

            p = bh.Extract_Min(H);

            if (p != NULL)

                cout<<"The node with minimum key: "<<p->key<<endl;

            else

                cout<<"Heap is empty"<<endl;

            break;

        case 3:

            p = bh.Find_Min(H);

            if (p != NULL)

                cout<<"The node with minimum key: "<<p->key<<endl;

            else

                cout<<"Heap is empty"<<endl;



            break;

        case 4:

            cout<<"The Heap is: "<<endl;

            bh.Display(H);



            break;



	  }
	  if(choice==5)
      {
          cout<<"Exited successfully."<<endl;

          break;
      }

    }

    return 0;

}
