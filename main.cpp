//A  Restaurant Project Struct style Dr_T Dr. Tyson McMillan 10-2-2019

#include <iostream>
#include <unistd.h>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream> 
using namespace std; 

class MenuItem
{
  private: 
    string name;
    double itemCost; 
    string desc; 
    char removeLetter;
    char addLetter; 
    int count;
  public: 
    /*MenuItem()
    {
      name = "";
      itemCost = 0.0;
      desc = "";
      get = '\0';
      removeLetter = '\0';
      count = 0;
    }*/
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
};

void populateMenu(vector<MenuItem> &m);
void showMenu(vector<MenuItem> &);
void printReceipt(vector<MenuItem> &, double, double, double, double, double, int);
void acceptOrder(vector<MenuItem> &);

int main()
{
  vector<MenuItem> wholeMenu; 
  populateMenu(wholeMenu); //put some default values in the menu
  showMenu(wholeMenu); //print the current data of the menu on screen 
  acceptOrder(wholeMenu); 

  return 0; 
}


//function definitions
void populateMenu(vector<MenuItem> &m)
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

  m.push_back(Item1); //add to the end of list the Item1
  m.push_back(Item2); //add to the end of list the Item2
  m.push_back(Item3); //add to the end of list the Item3
  m.push_back(Item4); //add to the end of list the Item4
  m.push_back(Item5); //add to the end of list the Item5
  m.push_back(Item6); //add to the end of list the Item6
  m.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Edamame", "Gyoza", "Takoyaki", "Kushiage", "Futomaki", "Udon", "Uji Tea"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 
  vector<string> defaultDescriptions = {"Beans", "Dumplings", "Octopus Balls", "Chicken Stick", "Sushi Rolls", "Soup", "Tea"}; 

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently 
    m[i].setName(defaultMenuNames[i]); 
    m[i].setaddLetter(defaultAddLetters[i]); 
    m[i].setremoveLetter(defaultRemoveLetters[i]); 
    m[i].setitemCost(3.00 + i); //set a random starter cost for each item
    m[i].setCount(0); //initialze all counts to 0
    m[i].setDesc(defaultDescriptions[i]); //set all default desc to "delicous"
  }


}

void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << "OSAKA SOUL" << endl; 
  cout << "ADD    NAME \t  COST \tREMOVE\tCOUNT\tDESC"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << m[i].getaddLetter() << ")" << setw(12) << m[i].getName() 
    << setw(5) << "$" << m[i].getitemCost()<< setw(5) << "(" << m[i].getremoveLetter()
    << ")" << setw(7) << m[i].getCount() << setw(13) << m[i].getDesc() 
    <<endl; 
  }

}


void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0';// the user-selected menu item
  double subtotal; 

  do
  {
    cout << "\nPlease choose an item (X to end and Checkout): ";
    cin >> option; 

    for(int i=0; i < m.size(); i++)
    {
      if(option == m[i].getaddLetter())
      {
        cout << "\nMenu Item " << m[i].getaddLetter() << " selected."; 
        m[i].setCount(m[i].getCount()+1); //increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << "\n1 UP on " << m[i].getName() << endl;
        subtotal += m[i].getitemCost(); //increment the subtotal by the cost of the item 
        showMenu(m); //show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;  
      }
      else if(option == m[i].getremoveLetter())
      {
        cout << "\nRemove Item " << m[i].getremoveLetter() << " selected."; 
        if(m[i].getCount() > 0) //subtract if and only if the count is > 0
        {
          m[i].setCount(m[i].getCount()-1); //decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].getName() << endl;
          subtotal -= m[i].getitemCost(); //decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;  
        }
        else //the the user why you blocked item removal 
        {
            
            cout << "\nItem count must be > 0 to remove: " << m[i].getName() << endl;
        }
      }
      else if(
                option != m[i].getaddLetter() && 
                option != m[i].getremoveLetter() &&
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
 
  double sugGrat;
  double userGrat; 
  double taxRate;
  double taxTotal; 
  int payChoice; 
  sugGrat = subtotal * .2; 
  taxRate = 1.0625; 
  taxTotal = subtotal * taxRate; 

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
  printReceipt(m,subtotal, sugGrat,userGrat, taxRate, taxTotal, payChoice); 
  }

void printReceipt(vector<MenuItem> &m, double subtotal, double sugGrat, double userGrat, double taxRate, double taxTotal, int payChoice) // PRINTS RECEIPT 
{
  ofstream outfile("RECEIPT.txt"); 
  
  outfile << fixed << setprecision(2);//set doubles to 2 decimal places
  outfile<< "RECEIPT:" << endl;
  for (int i = 0; i < m.size(); ++i)
    {
      cout <<m[i].getName() << " " << m[i].getitemCost() << " x " << m[i].getCount() << "=" << m[i].getCount() * m[i].getitemCost() << endl; 
    }
  outfile << "Subtotal: " << subtotal;
  
  outfile.close();
  }


