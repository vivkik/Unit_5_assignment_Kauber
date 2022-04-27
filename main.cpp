//A  Restaurant Project Struct style Dr_T Dr. Tyson McMillan 10-2-2019

#include <iostream>
#include <unistd.h>
#include<string>
#include<vector>
#include<iomanip>
using namespace std; 

class MenuItem
{
  private: 
    string name;
    double itemCost; 
    string desc; 
    char addLetter; 
    char removeLetter;
    int count;
  public: 
    MenuItem()
    {
      name = "";
      itemCost = 0.0;
      desc = "";
      addLetter = '\0';
      removeLetter = '\0';
      count = 0;
    }
    void setName(string n) 
      {name =n;}
    void setitemCost(double iC) 
      {itemCost = iC;}
    void setDesc(string d) 
      {desc = d;}
    void setaddLetter(char a) 
      {addLetter = a;}
    void setremoveLetter(char r) 
      {removeLetter = r;}
    void setCount(int c)
      {count = c;}
    string getName() const 
      {return name;}
    double getitemCost() const 
      {return itemCost;}
    string getDesc() const 
      {return desc;}
    char getaddLetter() const 
      {return addLetter;}
    char getremoveLetter() const 
      {return removeLetter;}
    int getCount()const 
      {return count;}

//function definitions
void populateMenu(vector<MenuItem> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItem Item1; 
  MenuItem Item2;
  MenuItem Item3; 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Edamame", "Gyoza", "Takoyaki", "Kushiage", "Futomaki", "Udon", "Uji Tea"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently 
    entireMenu[i].name = defaultMenuNames[i]; 
    entireMenu[i].addLetter = defaultAddLetters[i]; 
    entireMenu[i].removeLetter = defaultRemoveLetters[i]; 
    entireMenu[i].itemCost = (3.00 + i); //set a random starter cost for each item
    entireMenu[i].count = 0; //initialze all counts to 0
    entireMenu[i].desc = "delicious"; //set all default desc to "delicous"
  }


}

void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << "OSAKA SOUL" << endl; 
  cout << "ADD    NAME \t  COST \tREMOVE\tCOUNT\tDESC"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << m[i].addLetter << ")" << setw(12) << m[i].name 
    << setw(5) << "$" << m[i].itemCost << setw(5) << "(" << m[i].removeLetter
    << ")" << setw(7) << m[i].count << setw(13) << m[i].desc 
    <<endl; 
  }

}


void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0';// the user-selected menu item
  double subtotal = 0.0; 

  do
  {
    cout << "\nPlease choose an item (X to end and Checkout): ";
    cin >> option; 

    for(int i=0; i < m.size(); i++)
    {
      if(option == m[i].addLetter)
      {
        cout << "\nMenu Item " << m[i].addLetter << " selected."; 
        m[i].count++; //increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << "\n1 UP on " << m[i].name << endl;
        subtotal += m[i].itemCost; //increment the subtotal by the cost of the item 
        showMenu(m); //show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;  
      }
      else if(option == m[i].removeLetter)
      {
        cout << "\nRemove Item " << m[i].removeLetter << " selected."; 
        if(m[i].count > 0) //subtract if and only if the count is > 0
        {
          m[i].count--; //decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].name << endl;
          subtotal -= m[i].itemCost; //decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;  
        }
        else //the the user why you blocked item removal 
        {
            
            cout << "\nItem count must be > 0 to remove: " << m[i].name << endl;
        }
      }
      else if(
                option != m[i].addLetter && 
                option != m[i].removeLetter &&
                option != 'x' &&
                option != 'X' 
            ) //test for all of my valid inputs
            {
              if(i == 0)
              {
                cout << "\nInvalid input (" << option << "). Please try again." << endl; 
              }  
            }
    }
  }while(option != 'x' && option != 'X');
  double sugGrat = subtotal * .2;
  double userGrat; 
  double taxRate = 1.0625;
  double taxTotal = subtotal *taxRate; 
  int payChoice; 

  cout << "\nTotal after tax: $" << taxTotal <<endl;
  cout << "Would you like to place a gratuity?" << endl;
  cout << "Suggested tip (20%): $" << sugGrat << endl; 
  cout << "\nPlease enter tip amount: " << endl; 
  cin >> userGrat;
  cout << "\nTOTAL: $" << userGrat + taxTotal <<endl; 
  cout << "\nHow would you like to pay? Enter (1) for Cash (2) for Card" << endl; 
  cin >> payChoice; 
    if(payChoice == 1)
      {
        double tender; 
        double change; 
        cout << "Enter the cash amount paid: ";
        cin >> tender; 
          if(tender >= (userGrat + taxTotal))
            change = tender - (userGrat+taxTotal); 
            cout << "Your change is: $" << change << endl; 
      }
    else if(payChoice == 2)
      {
        cout << "Please swipe your Card: " <<endl; 
        sleep(3);
        cout << "Payment Processed";
      }
  }
};


int main()
{
  MenuItem m;
  
  vector<MenuItem> wholeMenu; 
  m.populateMenu(wholeMenu); //put some default values in the menu
  m.showMenu(wholeMenu); //print the current data of the menu on screen 
  m.acceptOrder(wholeMenu); 
  
  return 0; 
}
