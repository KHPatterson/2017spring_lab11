#include "wx/wx.h"
#include "wx/sizer.h"

#include "DrawPanel.h"
#include "ImageLoader.h"

#include "Circle.h"
#include "Line.h"
//#include "ListArray.h"
#include "CD.h"
#include "BinarySearchTree.h"
#include "Text.h"
#include <iostream>

using namespace CSC2110;
using namespace std;

class MyApp: public wxApp
{
    bool OnInit();
 
    wxFrame* frame;
    DrawPanel* drawPane;
public:
 
};
 
IMPLEMENT_APP(MyApp)
 
bool MyApp::OnInit()
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_items = cds->size();
   cout << num_items << endl;

   ListArrayIterator<CD>* iter = cds->iterator();

   BinarySearchTree<CD>* bst = new BinarySearchTree<CD>(&CD::compare_items, &CD::compare_keys);

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      bst->insert(cd);
   }
   delete iter;

   
   //DO THIS
   //test your tree sort method

   CD** unsorted_cds = cds->toArray();

   CD** sorted_cds = bst->treeSort(unsorted_cds, num_items, &CD::compare_items, &CD::compare_keys);

  for(int i = 0; i < num_items; i++)
  {
    String* title = sorted_cds[i]->getKey();
    title->displayString();
  }

  ListArrayIterator<CD>* iterer = cds->iterator();

  int count = 0;

  while(iterer->hasNext() && count < num_items)
  {
    String* name = iterer->next()->getKey();
    bst->remove(name);

    cout << "removed inorder item " << count+1 << endl;

    name->displayString();

    cout << endl << endl;

    count++;
  }

  cout << "repopulating BST for graphic" << endl << endl;

   ListArrayIterator<CD>* iter3 = cds->iterator();

   while(iter3->hasNext())
   {
      CD* cd = iter3->next();
      bst->insert(cd);
   }


   delete iter3;
   delete iterer;
   delete cds;
   wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
   frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Binary Search Tree"), wxPoint(500,500), wxSize(1100,600));
 
   drawPane = new DrawPanel((wxFrame*) frame, bst);
   sizer->Add(drawPane, 1, wxEXPAND);
 
   frame->SetSizer(sizer);
   frame->SetAutoLayout(true);
 
   frame->Show();
   return true;
} 
