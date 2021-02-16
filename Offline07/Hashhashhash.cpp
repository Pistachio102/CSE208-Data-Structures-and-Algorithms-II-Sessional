#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int dhCollision=0;
int dhAvgHit=0;
int customCollision=0;
int chAvgHit=0;
int choice=0;

using namespace std;

class ListNode
{
public:
    string key;
    int value;
    ListNode * next;
};

class LinkedList
{

    ListNode * list;
    int length;

public:
    LinkedList()
    {
        list=0; //initially set to NULL
        length=0;
    }

    int getLength()
    {
        return length;
    }



    int deleteItem(string str)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->key == str) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0) return NULL_VALUE ; //item not found to delete
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }
        return SUCCESS_VALUE ;
    }


    int searchItem(string str)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->key == str) return SUCCESS_VALUE ;
            temp = temp->next ; //move to next node
        }
        return NULL_VALUE ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            //printf("%d->", temp->item);
            cout<<temp->key<<"->";
            temp = temp->next;
        }
        printf("\n");
        printf("Length: %d\n",length);
    }

    //------------write code for the functions below-----------

    int insertLast(string str,int val)
    {
        //write your codes here
        ListNode *temp1= new ListNode();//new node
        temp1->value=val;
        temp1->key=str;
        temp1->next= 0;
        ListNode *temp;
        temp= list;
        if(temp==0)
        {
            list=temp1;
            length++;
            return SUCCESS_VALUE;
        }
        while(temp->next!=0)
        {
            temp=temp->next;
        }
        temp->next=temp1;
        length++;
        return SUCCESS_VALUE;
    }





    ~LinkedList()
    {
        //write your codes here
        length=0;
        free(list);

    }

};


class sepHashTable
{
public:

    LinkedList *ll;
    int tsize;



    sepHashTable(int t)
    {
        tsize=t;
        ll= new LinkedList[tsize];


    }




    int Hash1(string str)
        {
            int sum1= Askii(str);

            return sum1%tsize;
        }

        int Hash2(string str)
        {
            int sum2=3-(Askii(str)%3);
            return sum2%tsize;
        }


        int Askii(string s)
        {

            int sum=0;

            for(int i=0;i<s.length();i++)
            {
                sum+=s[i];
            }

            return sum;

        }




        void sepInsert(string s, int val)
        {
            int hashvalue;
            if(choice==1)
            {
                hashvalue=Hash1(s);
            }
            else if(choice==2)
            {
                hashvalue=Hash2(s);
            }
            int x=ll[hashvalue].insertLast(s,val);

            if(x==SUCCESS_VALUE)
                cout<<"INSERTED"<<endl;
            else cout<<"COULDN'T INSERT"<<endl;
        }


        void sepDelete(string s)
        {
            int hashvalue;
            if(choice==3)
            {
                hashvalue=Hash1(s);

            }
            else if(choice==4)
            {
                hashvalue=Hash2(s);
            }

            int x=ll[hashvalue].deleteItem(s);

            if(x==SUCCESS_VALUE)
                cout<<"DELETED"<<endl;
            else cout<<"COULDN'T DELETE"<<endl;
        }

        void sepSearch(string s)
        {
            int hashvalue;
            if(choice==5)
            {
                hashvalue=Hash1(s);
            }
            if(choice==6)
            {
                hashvalue=Hash2(s);
            }
            int x=ll[hashvalue].searchItem(s);

            if(x==SUCCESS_VALUE)
                cout<<"FOUND AT INDEX "<<hashvalue<<endl;
            else cout<<"COULDN'T FIND"<<endl;
        }




};



class doubleHash
{
public:

    int dsize;
   // int numOfitems=0;
    bool *flagArr;
    ListNode **dtable;

    doubleHash(int t)
    {
        dsize=t;
        flagArr= new bool[dsize];
        dtable = new ListNode*[dsize];
        for(int i=0;i<dsize;i++)
        {
            dtable[i]=0;
            flagArr[i]=false;
        }
    }


    int Hash1(string str)
        {
            int sum1= Askii(str);

            return sum1%dsize;
        }

        int Hash2(string str)
        {
            int sum2= 2*Askii(str);

            return sum2%dsize;
        }

        int auxHash(string str)
        {
            int sum3=3*Askii(str);

            return sum3%dsize;

        }


        int Askii(string s)
        {

            int sum=0;

            for(int i=0;i<s.length();i++)
            {
                sum+=s[i];
            }

            return sum;

        }


        int doubleHashInsert(string str,int val)
        {
            int i=0;

            int flag=0;

            int h1;
            if(choice==7)
            {
                h1=Hash1(str);
            }
            if(choice==8)
            {
                h1=Hash2(str);
            }

            int h2=auxHash(str);

            int hashvalue= (h1+i*h2)%dsize;

            int hstart=hashvalue;

            if(dtable[hstart]==0)
            {
                ListNode *temp=new ListNode();
                temp->key=str;
                temp->value=val;
                temp->next=0;
                dtable[hashvalue]=temp;
                return hashvalue;

            }

            i=1;

            while(1)
            {

               // cout<<i<<endl;
                hashvalue= (h1+i*h2)%dsize;
               // cout<<"hash  "<<hashvalue<<endl;
               if(dtable[hashvalue]==0)
               {
                   ListNode *temp1=new ListNode();
                temp1->key=str;
                temp1->value=val;
                temp1->next=0;
                dtable[hashvalue]=temp1;
                return hashvalue;

               }
               i++;
               dhCollision++;

               if(hashvalue==hstart)
               {
                   return NULL_VALUE;
               }




            }


                /*ListNode *temp=new ListNode();
                temp->key=str;
                temp->value=val;
                temp->next=0;
                dtable[hashvalue]=temp;
                return hashvalue;*/




            /*int flag=0;
            int hashValue=Hash1(str);
            int hashValue1=hashValue;
            ListNode *node = dtable[hashValue];

            if(node == 0)
            {
                ListNode *temp=new ListNode();
                temp->key=str;
                temp->value=val;
                temp->next=0;
                dtable[hashValue]=temp;
                return SUCCESS_VALUE;
            }

            else
            {
                int i=1;
                int h=Hash1(str);
                while(dtable[hashValue]!=0)
                {
                    hashValue= (hashValue + i*Hash2(str))%dsize;

                    if(hashValue==hashValue1)
                    {
                        cout<<"No slots empty in the table."<<endl;
                        flag=1;
                        break;


                    }

                i++;
            }



            if(flag==0)
            {
                ListNode *temp=new ListNode();
                temp->key=str;
                temp->value=val;
                temp->next=0;
                dtable[hashValue]=temp;
                return SUCCESS_VALUE;
            }
            else if(flag==1)
            {
                return NULL_VALUE;
            }
        }


*/
        }
        int dhSearch(string str)
        {
            int i=0;
            int h1;
            if(choice==9)
            {
                h1=Hash1(str);
            }
            if(choice==10)
            {
                h1=Hash2(str);
            }
            int h2=auxHash(str);
            int hashvalue=(h1+i*h2)%dsize;
            int hstart=hashvalue;

            while(1)
            {
                hashvalue=(h1+i*h2)%dsize;
                if(dtable[hashvalue]==0)
                {


                    cout<<"NAI VAI NAI"<<endl;
                    return NULL_VALUE;

                }
                if(dtable[hashvalue]->key==str)
                {
                    cout<<"FOUND BHAI FOUND."<<endl;
                    return hashvalue;
                }
                i++;
                dhAvgHit++;
                if(i!=0 && hstart==hashvalue)
                {
                    cout<<"NAI VAI NAI."<<endl;
                    return NULL_VALUE;
                }
            }

        }

        int doubleDelete(string str)
        {
           // int flag=0;
            int i=0;


            int h1;
            if(choice==11)
            {
                h1=Hash1(str);
            }
            if(choice==12)
            {
                h1=Hash2(str);
            }
            int h2=auxHash(str);
            int hashvalue =(h1+h2*i) ;
            int hstart=hashvalue;

          //  ListNode *node= dtable[hashvalue];


           // int i=0;

            while(1)
            {
                hashvalue=(hashvalue + i*Hash2(str))%dsize;

                if(dtable[hashvalue]==0)
                {

                        //flag=1;
                        cout<<"No item found to delete."<<endl;
                        break;


                }
                if(dtable[hashvalue]->key==str)
                {
                    ListNode *temp= dtable[hashvalue];
                    dtable[hashvalue]=0;
                    cout<<"deleted"<<endl;
                    break;
                }

                i++;

                if(i!=0 && hstart==hashvalue)
                {
                    cout<<"Cannot delete."<<endl;
                    break;
                }









            }

            /*if(flag==0)
            {

             ListNode *temp=dtable[hashvalue];
             dtable[hashvalue]=0;
             flagArr[hashvalue]=true;
             numOfitems--;
             cout<<"Item deleted."<<endl;
             delete temp;
             return hashvalue;



            }


            if(flag==1)
            {
                return NULL_VALUE;
            }*/
        }






};











class customprobing
{
public:
    ListNode **hashtable;
    bool *flagArr;
    int bucket;
    int length;
    int C1=13;
    int C2=29;
    customprobing(int c)
    {
        bucket=c;
        //length=0;
        hashtable=new ListNode*[bucket];
        for(int i=0; i<bucket; i++)
        {
            hashtable[i]=0;
            flagArr[i]=false;
        }

    }
    bool full()
    {
        if(length==bucket)
        {
            return true;
        }
    }
    int hashfunction(string key)
    {
        string p = key;
        int  h = 0;
        int i;
        for (i = 0; i < 7; i++)
        {
            h ^= p[i];
        }


        return h%bucket;
    }
    int hashfunction3(string key)
    {
        long long res=0;
        for(int i=0; i<7; i++)
        {
            res=(res+(key[i]-'a'+1)*19);
        }
        return res%bucket;
    }
    int hashfunction2(string key)
    {
        long long res=0;
        for(int i=0; i<7; i++)
        {
            res=(res+(key[i]-'a'+3));
        }


    }
    int insertnode(string key,int value)
    {
        // cout<<"insert hoise 1"<<endl;
        int index1;
        if(choice==13)
        {
            index1=hashfunction(key);
        }
        if(choice==14)
        {
            index1=hashfunction2(key);
        }
        int index2=hashfunction3(key);

        int initialIndex = (index1 + C1*0*index2+ C2 *0) % bucket;
        if(hashtable[initialIndex]==0)
        {
            // cout<<"insert hoi actually"<<endl;
            ListNode *temp;
            temp->key=key;
            temp->value=value;
            hashtable[initialIndex]=temp;
            return initialIndex;
        }
        int i=1;
        while(1)
        {
            int index3=(index1+C1*i*index2+C2*i*i)%bucket;
            //cout<<index3<<endl;
            if(hashtable[index3]==0)
            {
                ListNode *temp1;
            temp1->key=key;
            temp1->value=value;
            hashtable[initialIndex]=temp1;
            return index3;
            }
            i++;
            customCollision++;

            if(index3 == initialIndex)
            {
                //counttc++;
                cout<<"JAYGA NAI"<<endl;
                return NULL_VALUE;
            }

        }

        // avhit21+=i;




    }
    int searchnode(string key)
    {
        int index1;
        if(choice==15)
           {
               index1=hashfunction(key);
           }
            if(choice==16)
            {
                index1=hashfunction2(key);
            }
        int index2 = hashfunction3(key);


         int initialIndex = (index1 + C1*0*index2+ C2 *0) % bucket;


        int i=0;
        while(1)
        {
           int index3=(index1+C1*i*index2+C2*i*i)%bucket;
            if(hashtable[index3]==0)
            {
                cout<<"Nai"<<endl;
                break;
            }
            if(hashtable[index3]->key==key)
            {
                return index3;
            }
            i++;
            chAvgHit++;
            if(i!= 0 && initialIndex == index3)
            {

                return NULL_VALUE;
            }
        }
    }

    void deletenode(string key)
    {
        int index1 ;
        if(choice==17)
        {
            index1=hashfunction(key);
        }
        if(choice==18)
        {
            index1=hashfunction2(key);
        }
        int index2 = hashfunction3(key);


         int initialIndex = (index1 + C1*0*index2+ C2 *0) % bucket;


        int i=0;
        while(1)
        {
            int index3=(index1+C1*i*index2+C2*i*i)%bucket;
            if(hashtable[index3]->key=="")
            {
                cout<<"cant delete"<<endl;
                break;
               // return false;
            }
            if(hashtable[index3]->key==key)
            {
                hashtable[index3]->key="";
                hashtable[index3]->value=0;
                cout<<"deleted"<<endl;
                break;
               // return true;
            }
            i++;
            if(i!= 0 && initialIndex == index3)
            {
                cout<<"cant delete"<<endl;
                break;
                //return false;
            }
        }




    }



};

string randword()
{
    //srand(time(0));
    string str="";
    while(str.size()<7)
    {

        char s=(abs(rand())%26)+'a';
        str+=s;
    }
    return str;




}





int main(void)
{


    return 0;
}
