#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<bits/stdc++.h>
#include<string>
using namespace std;
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    string item;
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

    int insertItem(string item) //insert at the beginning
    {
        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

    int deleteItem(string item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) break ;
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


     int searchItem(string item)
    {
        int i=-1;
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            ++i;
            if (temp->item == item) break ;
            temp = temp->next ; //move to next node
        }
        return i ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
             cout<<temp->item<<" -> "<<endl;
            temp = temp->next;
        }
        printf("\n");
    }

    //------------write code for the functions below-----------

    int insertLast(string item)
    {

        length++;
        ListNode *node =new ListNode;
        node->item=item;

        if(list==0)
        {
            return insertItem(item);

        }
        ListNode *temp=list;
        while(temp->next!=0)
        {
            temp=temp->next;

        }
       node->next=temp->next;
        temp->next=node;


        return SUCCESS_VALUE;
    }

    int insertAfter(string oldItem, string newItem)
    {
        length++;

       ListNode *temp=list;
       //ListNode *temp2=new ListNode;
       ListNode *node=new ListNode;
       node->item=newItem;
       while(1)
       {
           if(temp->item==oldItem||temp==NULL)
           {
              // temp2=temp->next;
               break;
           }
           temp=temp->next;

       }
       if(temp==NULL)
       {

           cout<<"Item not found"<<endl;
           length--;
           return NULL_VALUE;
       }
       node->next=temp->next;
       temp->next=node;

     return SUCCESS_VALUE;

    }

    ListNode * getItemAt(int pos)
    {
      if(pos>length)
      {
          ListNode *N=NULL;
          N->item=NULL_VALUE;

           return N;
      }

        ListNode *temp=list;
        int i=1;

        for(i=1;i<pos;i++)
        {
            temp=temp->next;

        }
        return temp;

    }

    int deleteFirst()
    {

        if(list==NULL)
        {
          cout<<"list is empty"<<endl;
          return NULL_VALUE;
        }
        length--;
        ListNode *tmp=list;
        delete list;
        list=tmp->next;

        return SUCCESS_VALUE;
    }


    ~LinkedList()
{


       ListNode *node =list;
       ListNode *temp=new ListNode;
      while (node != NULL)
     {
       temp = node;
      node = node->next ;
      free(temp);
     }
     list = NULL;

}

};

long long  hash1(string  s,long long m) {
     int p = 87;
    // long long m = 129;
    long long  hash_value = 0;
    for(int i=0;i<7;i++)
    {
        int x=s[i];
        hash_value=hash_value+(x*pow(p,i));

    }

    return (hash_value%m);
}
long long  hash2(string  s,long long m) {
     int p =129;
    long long  hash_value = 0;
    for(int i=0;i<7;i++)
    {
        int x=s[i];
        hash_value=hash_value+(x*pow(p,i));


    }

    return (hash_value%m);
}

class ChainingHash
{
    LinkedList *L,*T;
    long long cells;
    long long hits,hitsT;
public:
    ChainingHash(long long l)
    {
        cells=l;
        L=new LinkedList[cells];
        T=new LinkedList[cells];
        hits=0;
        hitsT=0;
    }
    void insertString(string s)
    {

        long long  i = hash1(s,cells);
         if(i<cells)
         L[i].insertItem(s);

    }
     void insertStringT(string s)
    {

        long long  i = hash2(s,cells);
         if(i<cells)
         T[i].insertItem(s);

    }

    long long searchString(string s)
    {
        long long i=hash1(s,cells);
        if(i<cells)
        {
            hits++;
            int n=L[i].searchItem(s);
            if(n!=-1)
            {
//                cout<<n<<endl;
                hits+=n;
                return i;

            }
            else
            {
                hits+=L[i].getLength();
  //              cout<<"b"<<endl;

                return -1;
            }
        }
        return -1;

    }
    long long searchStringT(string s)
    {
        long long i=hash2(s,cells);
        if(i<cells)
        {
            hitsT++;
            int n=T[i].searchItem(s);
            if(n!=-1)
            {
                hitsT+=n;
                return i;


            }
            else
            {
                hitsT+=T[i].getLength();
                return -1;

            }
        }
        return -1;

    }

   void deleteString(string s)
   {
       long long i= searchString(s);
       if(i!=-1)
       {
           L[i].deleteItem(s);
       }
       else printf("String is not in the table\n");
   }
    void deleteStringT(string s)
   {
       long long i= searchStringT(s);
       if(i!=-1)
       {
           T[i].deleteItem(s);
       }
       else printf("String is not in the table\n");
   }
   void display()
   {
       for(int i=0;i<cells;i++)
       {
           L[i].printList();
       }

   }
   long long collision()
   {
       long long num_of_collision=0;
       for(long long i=0;i<cells;i++)
       {
          if(L[i].getLength()>1)
            num_of_collision++;

       }
       return num_of_collision;
   }
   long long collisionT()
   {
       long long num_of_collision=0;
       for(long long i=0;i<cells;i++)
       {
          if(T[i].getLength()>1)
            num_of_collision++;

       }
       return num_of_collision;
   }
   double avg_hit()
   {
       //hits=0;
        for(long long i=0;i<cells;i++)
        {
            int x=L[i].getLength();
            for(int j=1;j<=x;j++)
            {
                hits+=j;
            }

        }
        return (hits*1.0)/(1000*1.0);

   }
    double avg_hitT()
   {
     //   hitsT=0;
        for(long long i=0;i<cells;i++)
        {
            int x=T[i].getLength();
            for(int j=1;j<=x;j++)
            {
                hitsT+=j;
            }

        }
        return (hitsT*1.0)/(1000*1.0);

   }

};

long long  auxhash(string  s,long long m) {
     int p = 23;
    // long long m = 129;
    long long  hash_value = 0;
    for(int i=0;i<7;i++)
    {
        int x=s[i];
        hash_value=hash_value+(x*pow(p,i));

    }

    return (hash_value%m);
}


class doubleHash
{
     LinkedList *L,*T;
    long long cells;
    long long collision,collisionT,hits,hitsT;
public:
    doubleHash(long long l)
    {
        cells=l;
        L=new LinkedList[cells];
        T=new LinkedList[cells];
        collision=0;
        collisionT=0;
        hits=0;
        hitsT=0;
    }

    void insertString(string s)
    {
        for(long long i=0;i<cells;i++)
        {
           long long x= (hash1(s,cells) + i*auxhash(s,cells)) % cells;
            if(x<cells)
            {
                if(L[x].getLength()==0)
                {
                    L[x].insertItem(s);
                    return;

                }
                else collision++;

            }

        }

    }
    void insertStringT(string s)
    {
        for(long long i=0;i<cells;i++)
        {
           long long x= (hash2(s,cells) + i*auxhash(s,cells)) % cells;
            if(x<cells)
            {
             //   cout<<"cell no:"<<x<<endl;
                if(T[x].getLength()==0)
                {
                    T[x].insertItem(s);
                    return;
                }
                else collisionT++;

            }

        }

    }

    long long SearchString(string s)
    {
        for(long long i=0;i<cells;i++)
        {
            hits++;
           long long x= (hash1(s,cells) + i*auxhash(s,cells)) % cells;
            if(x<cells)
            {
                ListNode *y=L[x].getItemAt(0);
                if(y->item==s)
                {
                   return x;
                }

            }

        }

        return -1;

    }




        long long SearchStringT(string s)
    {
        for(long long i=0;i<cells;i++)
        {
            hitsT++;
           long long x= (hash2(s,cells) + i*auxhash(s,cells)) % cells;
            if(x<cells)
            {
                ListNode *y=T[x].getItemAt(0);
                if(y->item==s)
                {
                   return x;
                }

            }

        }

        return -1;

    }

    void deleteString(string s)
    {
       long long x=SearchString(s);
       if(x!=-1)
       {
         L[x].deleteItem(s);

       }

    }
    void deleteStringT(string s)
    {
       long long x=SearchStringT(s);
       if(x!=-1)
       {
         T[x].deleteItem(s);

       }

    }
    long long col()
    {

        return collision;
    }
    long long colT()
    {

        return collisionT;
    }
    double avg_hits()
    {

        return hits*1.0/1000*1.0;
    }
    double avg_hitsT()
    {

        return hitsT*1.0/1000*1.0;
    }


};


class customHash
{
     LinkedList *L,*T;
    long long cells;
    long long collision,collisionT;
    long long hits,hitsT;
public:
    customHash(long long l)
    {
        cells=l;
        L=new LinkedList[cells];
        T=new LinkedList[cells];
        collision=0;
        collisionT=0;
        hits=0;
        hitsT=0;
    }

    void insertString(string s)
    {
        for(long long i=0;i<cells;i++)
        {
           long long x= (hash1(s,cells) + (3*i*auxhash(s,cells))+(7*i*i)) % cells;
            if(x<cells)
            {
                if(L[x].getLength()==0)
                {
                    L[x].insertItem(s);
                    return;

                }
                else collision++;

            }

        }

    }
    void insertStringT(string s)
    {
        for(long long i=0;i<cells;i++)
        {
           long long x= (hash2(s,cells) + (3*i*auxhash(s,cells))+(7*i*i)) % cells;
            if(x<cells)
            {
               // cout<<"1"<<endl;
                if(T[x].getLength()==0)
                {
                    T[x].insertItem(s);
                    return;
                }
                else collisionT++;

            }

        }

    }

    long long SearchString(string s)
    {
        for(long long i=0;i<cells;i++)
        {
            hits++;
           long long x= (hash1(s,cells) + (3*i*auxhash(s,cells))+(7*i*i)) % cells;
            if(x<cells)
            {
                ListNode *y=L[x].getItemAt(0);
                if(y->item==s)
                {
                   return x;
                }

            }

        }

        return -1;

    }




        long long SearchStringT(string s)
    {
        for(long long i=0;i<cells;i++)
        {
            hitsT++;
           long long x= (hash2(s,cells) + (3*i*auxhash(s,cells))+(7*i*i)) % cells;
            if(x<cells)
            {
                ListNode *y=T[x].getItemAt(0);
                if(y->item==s)
                {
                   return x;
                }

            }

        }

        return -1;

    }

    void deleteString(string s)
    {
       long long x=SearchString(s);
       if(x!=-1)
       {
         L[x].deleteItem(s);

       }

    }
    void deleteStringT(string s)
    {
       long long x=SearchStringT(s);
       if(x!=-1)
       {
         T[x].deleteItem(s);

       }

    }
    long long col()
    {

        return collision;
    }
    long long colT()
    {

        return collisionT;
    }
    double avg_hits()
    {

        return hits*1.0/1000*1.0;
    }
    double avg_hitsT()
    {

        return hitsT*1.0/1000*1.0;
    }


};


string genRandom(int len)
{
    string str = "abcdefghijklmnopqrstuvwxyzABCD"
               "EFGHIJKLMNOPQRSTUVWXYZ";
    int n = str.length();

    string s;

    for (int i=1; i<=len; i++)
        s.push_back(str[rand() % n]);

    return(s);
}






int main(void)
{

        int tableLength;
    printf("Enter the length of hash table:");
    scanf("%d",&tableLength);


    srand(time(NULL));
    ChainingHash h1(tableLength);
    doubleHash h2(tableLength);
    customHash h3(tableLength);

    for(int i=1;i<=10000;i++)
    {
            string s=genRandom(7);
            h1.insertString(s);
            h1.insertStringT(s);
            h1.searchString(s);
            h1.searchStringT(s);
            h2.insertString(s);
            h2.insertStringT(s);
            h2.SearchString(s);
            h2.SearchStringT(s);
            h3.insertString(s);
            h3.insertStringT(s);
            h3.SearchString(s);
            h3.SearchStringT(s);
    }
    cout<<"For Separete Chaining:"<<endl<<endl;
    cout<<"Hash1"<<endl;
    cout<<"Collisions "<<h1.collision()<<endl;
    cout<<"Hits "<<h1.avg_hit()<<endl<<endl;
    cout<<"Hash2"<<endl;
    cout<<"Collisions "<<h1.collisionT()<<endl<<endl;
    cout<<"Hits "<<h1.avg_hitT()<<endl<<endl;


    cout<<"For Double Hashing"<<endl<<endl;
    cout<<"Hash1"<<endl;
    cout<<"Collisions "<<h2.col()<<endl;
    cout<<"Hits "<<h2.avg_hits()<<endl<<endl;
    cout<<"Hash2"<<endl;
    cout<<"Collisions "<<h2.colT()<<endl;
    cout<<"Hits "<<h2.avg_hitsT()<<endl<<endl;

    cout<<"For Custom Hashing"<<endl<<endl;
    cout<<"Hash1"<<endl;
    cout<<"Collisions "<<h3.col()<<endl;
    cout<<"Hits "<<h3.avg_hits()<<endl<<endl;
    cout<<"Hash2"<<endl;
    cout<<"Collisions "<<h3.colT()<<endl;
    cout<<"Hits "<<h3.avg_hitsT()<<endl<<endl;





}
