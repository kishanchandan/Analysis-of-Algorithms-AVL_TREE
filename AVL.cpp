#include <iostream>
#include <stdlib.h>
//#include <iomanip>

using namespace std;

#include "AVL.h"

//--- Definition of constructor
AVL::AVL()
: myRoot(0)
{}

bool AVL::empty() const
{ return myRoot == 0; }

int consistencyflag = 0;
int consistencycount=0;
int heavycase2;
bool AVL::search(const int & item) const
{
   BinNode * locptr = myRoot;
   bool found = false;
   while (!found && locptr != 0)
   {
      if (item < locptr->data)       // descend left
        locptr = locptr->left;
      else if (locptr->data < item)  // descend right
        locptr = locptr->right;
      else                           // item found
        found = true;
   }
   return found;
}


void AVL::insert(const int & item)
{
    int balancefactor= 0;
   BinNode * locptr = myRoot;   // search pointer
   BinNode * parent = 0;        // pointer to parent of current node
   bool found = false;     // indicates if item already in AVL
   while (!found && locptr != 0)
   {
      parent = locptr;
      if (item < locptr->data)       // descend left
         locptr = locptr->left;
      else if (locptr->data < item)  // descend right
         locptr = locptr->right;
      else                           // item found
         found = true;
   }
   if (!found)
   {                                 // construct node containing item
      locptr = new BinNode(item);  
      if (parent == 0)               // empty tree
         myRoot = locptr;
      else if (item < parent->data )  // insert to left of parent
         {
            parent->left = locptr;
            locptr->parentofnode = parent;
            locptr->height=0;
            while(parent!=0)
                {
                    if(parent->left!=0&&parent->right!=0){
                    parent->height=max(parent->left->height,parent->right->height)+1;
                    parent = parent->parentofnode;
                    }
                    else if(parent->left==0&&parent->right==0){
                        
                        
                    }
                    else if(parent->left!=0){
                    parent->height = parent->left->height+1;    
                    parent= parent->parentofnode;
                    
                    }
                    else if(parent->right!=0){
                    parent->height = parent->right->height+1;
                    parent = parent->parentofnode;
                    
                    }
                    
                }
                checkInconsistency(myRoot,-1);
                //balancefactor = heavyside(locptr);
                
                
         }

      else
        {// insert to right of parent
         parent->right = locptr;
         locptr->parentofnode = parent;
         locptr->height=0;
         
                while(parent!=0)
                    {
                        if(parent->left!=0&&parent->right!=0){
                        parent->height=max(parent->left->height,parent->right->height)+1;
                        parent = parent->parentofnode;
                        }
                        else if(parent->left!=0&&parent->right!=0){
                            
                            
                        }
                        else if(parent->left!=0){
                        parent->height = (parent->left->height)+1;    
                        parent= parent->parentofnode;
                        
                        }
                        else if(parent->right!=0){
                        parent->height = (parent->right->height)+1;
                        parent = parent->parentofnode;
                    
                        }
                    }
                    checkInconsistency(myRoot,1);
         }

   }
   else
      cout << "Item already in the tree\n";
}


void AVL::preOrderRecursion(BinNode* currentnode)const{
    BinNode * locptr = myRoot;   // search pointer
    BinNode * parent = 0; 
    
    if(currentnode!=0){
            cout<<currentnode->data<<"\n";
            preOrderRecursion(currentnode->left);
            preOrderRecursion(currentnode->right);
    }
    
}
void AVL::preOrder()const{
    BinNode * locptr = myRoot;   // search pointer
    BinNode * parent = 0; 
    preOrderRecursion(myRoot);
}

void AVL::checkInconsistency(BinNode* currentnode, int heavycase1)const{
    BinNode * locptr = myRoot;   // search pointer
    BinNode * parent = 0;
    BinNode * nodetoattach = 0;
   
    //int consistencycount = 0;
    
    int leftnodeheight;
    int rightnodeheight;
    int difference;
    if(currentnode!=0){
            checkInconsistency(currentnode->left,heavycase1);
            
            checkInconsistency(currentnode->right,heavycase1);
            
            if(currentnode->left!=0&&currentnode->right!=0){
                
            leftnodeheight = currentnode->left->height;
            rightnodeheight = currentnode->right->height;
            difference = abs(leftnodeheight-rightnodeheight);    
                    
                    if(difference>1){
                        
                        consistencycount+=1;
                        consistencyflag=1;
                        
                        if(consistencycount==1){
                                cout<<"\nInconsistency here "<<consistencycount<<"\n";
                                if(leftnodeheight>rightnodeheight)
                                {
                                    heavycase2=-1;
                                    cout<<heavycase1<<" "<<heavycase2<<"\n";
                                }
                                else{
                                    heavycase2=1;
                                    cout<<heavycase1<<" "<<heavycase2<<"\n";
                                }
                                if(heavycase1==-1&&heavycase2==-1){
                                        rightRotate(currentnode,myRoot);
                                }
                                else if(heavycase1==1&&heavycase2==-1){
                                    leftRotatethenRightRotate(currentnode);
                                }
                                else if(heavycase1==-1&&heavycase2==1){
                                    rightRotatethenLeftRotate(currentnode);
                                }
                                else if(heavycase1==1&&heavycase2==1){
                                    leftRotate(currentnode,myRoot);
                                }
                                    
                        }
                        
                    
            }
            }
            else if (currentnode->left!=0&&currentnode->right==0){
                    leftnodeheight = currentnode->left->height;
                    rightnodeheight = -1;
                    difference = abs(leftnodeheight-rightnodeheight);
                    if(difference>1){
                        
                        consistencycount+=1;
                        consistencyflag=1;
                        if(consistencycount==1){
                            cout<<"\nInconsistency here "<<consistencycount<<"\n";
                            if(leftnodeheight>rightnodeheight)
                                {
                                    heavycase2=-1;
                                    cout<<heavycase1<<" "<<heavycase2<<"\n";
                                }
                                else{
                                    heavycase2=1;
                                    cout<<heavycase1<<" "<<heavycase2<<"\n";
                                }
                                if(heavycase1==-1&&heavycase2==-1){
                                        rightRotate(currentnode,myRoot);
                                }
                                else if(heavycase1==1&&heavycase2==-1){
                                    leftRotatethenRightRotate(currentnode);
                                }
                                else if(heavycase1==-1&&heavycase2==1){
                                    rightRotatethenLeftRotate(currentnode);
                                }
                                else if(heavycase1==1&&heavycase2==1){
                                    leftRotate(currentnode,myRoot);
                                }
                        }
                    }
            }
            else if (currentnode->left==0&&currentnode->right!=0){
                    leftnodeheight = -1;
                    rightnodeheight = currentnode->right->height;
                    difference = abs(leftnodeheight-rightnodeheight);
                    if(difference>1){
                        consistencycount+=1;
                        consistencyflag=1;
                        if(consistencycount==1){
                            cout<<"\nInconsistency here "<<consistencycount<<"\n";
                            if(leftnodeheight>rightnodeheight)
                                {
                                    heavycase2=-1;
                                    cout<<heavycase1<<" "<<heavycase2<<"\n";
                                }
                                else{
                                    heavycase2=1;
                                    cout<<heavycase1<<" "<<heavycase2<<"\n";
                                }
                                if(heavycase1==-1&&heavycase2==-1){
                                        rightRotate(currentnode,myRoot);
                                }
                                else if(heavycase1==1&&heavycase2==-1){
                                    leftRotatethenRightRotate(currentnode);
                                }
                                else if(heavycase1==-1&&heavycase2==1){
                                    rightRotatethenLeftRotate(currentnode);
                                }
                                else if(heavycase1==1&&heavycase2==1){
                                    leftRotate(currentnode,myRoot);
                                }
                        }
                        
                    }
            }
            else if (currentnode->left==0&&currentnode->right==0){
                    leftnodeheight = -1;
                    rightnodeheight = -1;
                    difference = abs(leftnodeheight-rightnodeheight);
                    if(difference>1){
                        consistencycount+=1;
                        consistencyflag=1;
                        if(consistencycount==1){
                            cout<<"\nInconsistency here "<<consistencycount<<"\n";
                            if(leftnodeheight>rightnodeheight)
                                {
                                    heavycase2=-1;
                                    cout<<heavycase1<<" "<<heavycase2<<"\n";
                                }
                                else{
                                    heavycase2=1;
                                    cout<<heavycase1<<" "<<heavycase2<<"\n";
                                }
                                if(heavycase1==-1&&heavycase2==-1){
                                        rightRotate(currentnode,myRoot);
                                }
                                else if(heavycase1==1&&heavycase2==-1){
                                    leftRotatethenRightRotate(currentnode);
                                }
                                else if(heavycase1==-1&&heavycase2==1){
                                    rightRotatethenLeftRotate(currentnode);
                                }
                                else if(heavycase1==1&&heavycase2==1){
                                    leftRotate(currentnode,myRoot);
                                }
                        }
                        
                    }
            }
    }
    
    
}
void AVL::inOrderRecursion(BinNode* currentnode)const{
    BinNode * locptr = myRoot;   // search pointer
    BinNode * parent = 0; 
    int leftnodeheight;
    int rightnodeheight;
    int difference;
    if(currentnode!=0){
            inOrderRecursion(currentnode->left);
            
            cout<<currentnode->data<<"\n";
            inOrderRecursion(currentnode->right);
            
        
            //cout<<currentnode->data;
    }
    
}
void AVL::inOrder()const{
    BinNode * locptr = myRoot;   // search pointer
    BinNode * parent = 0; 
    inOrderRecursion(myRoot);
}

int AVL::nodecountRecursion(BinNode* currentnode, int totalnodes)const{
    
    if(currentnode==0){
        return 0;
    }
    else{
    totalnodes = 1+nodecountRecursion(currentnode->left,totalnodes)+nodecountRecursion(currentnode->right,totalnodes);    
    return totalnodes;
    }
    
}


void AVL::nodecount()const{
    BinNode * locptr = myRoot;   // search pointer
    BinNode * parent = 0; 
    int totalnodes = 0;
    totalnodes =  nodecountRecursion(myRoot,0);
    cout<<"\nTotal number of nodes is : "<<totalnodes;
}
//
//void AVL::heightnode()const{
//    BinNode * locptr = myRoot;   // search pointer
//    BinNode * parent = 0; 
//    int height = 0;
//    height =  heightnodeRecursion(myRoot,0);
//    //cout<<"\nTotal number of nodes is : "<<totalnodes;
//}

void AVL::deletenode(const int & item)
{
   BinNode * locptr = myRoot;   // search pointer
   BinNode * parent = 0;        // pointer to parent of current node
   bool found = false;     // indicates if item already in AVL
   while (!found && locptr != 0)
   {
      
      if (item < locptr->data) {
        parent = locptr;
        locptr = locptr->left;
    }
         
      else if (locptr->data < item){
        parent =locptr;
        locptr = locptr->right;
      
    }
      else{
        cout<<parent->data<<"\n"<<locptr->data;
        found = true;
    }                           // item found
     
   }
   if (!found)
    {                                 // construct node containing item
      cout << "Item Not found in the tree, so deletion is not possible.\n";
    }
    
    if(found){
        
        if(parent==0){
                cout<<"This is root";
            }
        else{
            if(parent->left->data==locptr->data){
                cout<<"Left Child\n";
            
                if(locptr->left==0&&locptr->right==0){
                    cout<<"Node has no children\n";
                    parent->left=0;
                    
                }
                else if(locptr->left==0||locptr->right==0){
                    cout<<"Has one child";
                    if(locptr->left!=0)
                        parent->left=locptr->left;
                    else
                        parent->left=locptr->right;
                }
                else {
                    cout<<"Has two Childs";
                    locptr=locptr->right;
                    BinNode *parenttemp;
                    while(locptr!=0&&locptr->left!=0){
                         parenttemp= locptr;
                        locptr=locptr->left;
                    }
                    
                    cout<<locptr->data;
                    if(locptr->right==0){
                        parent->left->data = locptr->data;
                        parenttemp->left = 0;
                    }
                    else{
                        parent->left->data = locptr->data;
                        parenttemp->left = locptr->right;
                        
                    }
                }
                preOrderRecursion(myRoot);
                if(parent->left!=0&&parent->right!=0){
                        if(parent->left->height>parent->right->height){
                                    checkInconsistency(myRoot,-1);
                        }
                        else
                            checkInconsistency(myRoot,1);
                }
                if(parent->left==0&&parent->right==0){
                        
                }
                if(parent->left!=0&&parent->right==0){
                        checkInconsistency(myRoot,-1);
                }
                if(parent->left==0&&parent->right!=0){
                            checkInconsistency(myRoot,1);
                }
                
                
            }
            
            
            else{                                           //Right Child Case
                cout<<"Right Child";
                if(locptr->left==0&&locptr->right==0){
                    cout<<"Node has no children";
                    parent->right=0;
                }
                else if(locptr->left==0||locptr->right==0){
                    cout<<"Has one child";
                    if(locptr->left!=0)
                        parent->right=locptr->left;
                    else
                        parent->right=locptr->right;
                }
                else {
                    cout<<"Has two Childs";
                    cout<<"Data on temp"<<parent->data;
                    cout<<locptr->data;
                    locptr=locptr->right;
                    BinNode *parenttemp;
                    while(locptr!=0&&locptr->left!=0){
                         parenttemp= locptr;
                        locptr=locptr->left;
                    }
                    
                    cout<<locptr->data;
                    if(locptr->right==0){
                        parent->right->data = locptr->data;
                        parenttemp->left = 0;
                    }
                    else{
                        parent->right->data = locptr->data;
                        parenttemp->left = locptr->right;
                        
                    }
                    //locptr->
                    //cout<<parent->right->right->data;
                    
                }
                if(parent->left!=0&&parent->right!=0){
                        if(parent->left->height>parent->right->height){
                                    checkInconsistency(myRoot,-1);
                        }
                        else
                            checkInconsistency(myRoot,1);
                }
                if(parent->left==0&&parent->right==0){
                        
                }
                if(parent->left!=0&&parent->right==0){
                        checkInconsistency(myRoot,-1);
                }
                if(parent->left==0&&parent->right!=0){
                            checkInconsistency(myRoot,1);
                }
                
            }
        
        }
    }    
        
        
        
}
  
void AVL::rightRotate(BinNode* currentnode, BinNode * myRoot)const{
    cout<<"Right Rotate to be performed on "<<currentnode->data<<"\n";
    BinNode * locptr = myRoot;
    cout<<"\nPreorder before rotating\n";
    preOrderRecursion(myRoot);
    cout<<"\n After Right Rotate Output is "<<"\n";
    BinNode * temporaryrightnodeholder;
    BinNode * tempnode;
    BinNode * tempnode2;
    
    tempnode2=currentnode->left;
    
    tempnode2->parentofnode = currentnode->parentofnode;// Attaching left node to parent node
    
    if(tempnode2->parentofnode!=0){ // Not a root
                    if(tempnode2->parentofnode->right==currentnode){ // Is a right  child 
                            tempnode2->parentofnode->right=tempnode2;
                    }
                    else{
                            tempnode2->parentofnode->left=tempnode2;
                    }
            }
            
    else
        myRoot = currentnode->left;
    
    if(tempnode2->right!=0){ // If right has some nodes 
        temporaryrightnodeholder = tempnode2->right;
        tempnode2->right=new BinNode(currentnode->data);
        tempnode2->right->left = temporaryrightnodeholder;  //Adding right child
        currentnode->parentofnode=tempnode2;
    }
    else
        tempnode2->right=new BinNode(currentnode->data); 
    
    
    if(currentnode->right!=0)
        tempnode2->right->right = currentnode->right;
    
    cout<<"\nPreorder after rotating\n";
    preOrderRecursion(myRoot);
    cout<<"\nIn order after rotating\n";
    inOrderRecursion(myRoot);
    recalculateheight(tempnode2);
    consistencycount=0;
    
    
}

void AVL::leftRotate(BinNode* currentnode, BinNode * myRoot)const{
    cout<<"Left Rotate to be performed on "<<currentnode->data<<"\n";
    BinNode * locptr = myRoot;
    //BinNode * temporaryrightofleftnodeholder;
    //BinNode * temporaryleftnodeholder;
    cout<<"\nPreorder before rotating\n";
    preOrderRecursion(myRoot);
    cout<<"\n After Left Rotate Output is"<<"\n";
    BinNode * temporaryleftnodeholder;
    BinNode * tempnode;
    BinNode * tempnode2;
    
    tempnode2=currentnode->right; //right nodes
    tempnode2->parentofnode = currentnode->parentofnode;// Attaching right node to parent node
    
    if(tempnode2->parentofnode!=0){ // Not a root
                    if(tempnode2->parentofnode->right==currentnode){ // Is a right  child 
                            tempnode2->parentofnode->right=tempnode2;
                    }
                    else{
                            tempnode2->parentofnode->left=tempnode2;
                    }
    }
    else{
        myRoot = locptr->right;
    }
    
    if(tempnode2->left!=0){ // If left has some nodes 
        cout<<"Entering here";
        temporaryleftnodeholder = tempnode2->left;
        tempnode2->left=new BinNode(currentnode->data);
        tempnode2->left->right = temporaryleftnodeholder;  //Adding right child
        currentnode->parentofnode=tempnode2;
        //tempnode2->parentofnode=0; doubt
    }
    else
        tempnode2->left=new BinNode(currentnode->data); 
    
    
    if(currentnode->left!=0)
        tempnode2->left->left = currentnode->left;
    cout<<"\nPreorder after rotating\n";
    preOrderRecursion(myRoot);
    cout<<"\nIn order after rotating\n";
    inOrderRecursion(myRoot);
    recalculateheight(tempnode2);
    consistencycount=0;
    
   
}
 
void AVL::leftRotatethenRightRotate(BinNode* currentnode)const{
    cout<<"Left First then Right Rotate to be performed on "<<currentnode->data<<"\n";
    BinNode * locptr = myRoot;
    //BinNode * temporaryrightofleftnodeholder;
    //BinNode * temporaryleftnodeholder;
    preOrderRecursion(myRoot);
    cout<<"\n After Left Rotate then right rotate "<<"\n";
    BinNode * temporaryrightnodeholder;
    BinNode * tempnode;
    BinNode * tempnode2;
    
    leftRotate(currentnode->left,myRoot);
    rightRotate(currentnode,myRoot);
    
}

void AVL::rightRotatethenLeftRotate(BinNode* currentnode)const{
    cout<<"Right first then left Rotate to be performed on "<<currentnode->data<<"\n";
    BinNode * locptr = myRoot;
    //BinNode * temporaryrightofleftnodeholder;
    //BinNode * temporaryleftnodeholder;
    preOrderRecursion(myRoot);
    cout<<"\n After Right Rotate then left rotate "<<"\n";
    BinNode * temporaryrightnodeholder;
    BinNode * tempnode;
    BinNode * tempnode2;
    
   rightRotate(currentnode->right,myRoot);
   leftRotate(currentnode,myRoot);
   
}  

void AVL::recalculateheight(BinNode* currentnode)const{
    BinNode * parent=currentnode;
    while(parent!=0)
                    {
                        
                        if(parent->left!=0&&parent->right!=0){
                        parent->height=max(parent->left->height,parent->right->height)+1;
                        parent = parent->parentofnode;
                        }
                        else if(parent->left!=0&&parent->right!=0){
                            
                            
                        }
                        else if(parent->left!=0){
                        parent->height = (parent->left->height)+1;    
                        parent= parent->parentofnode;
                        
                        }
                        else if(parent->right!=0){
                        parent->height = (parent->right->height)+1;
                        parent = parent->parentofnode;
                    
                        }
                    }
    
}
