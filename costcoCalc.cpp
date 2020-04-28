// costcoCalc.cpp
// Victor Dinh, 4/24/2020
//
// Description: This is a terminal-based app that takes in a list of purchases
// (receipt), the initials of each person paying for each item, and returns the
// total amount owed by each person.
//

#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

using namespace std;

// class ChargeMe
// each ChargeMe object holds the initial and the running total amount owed for
// each person
// data: m_totalOwed, m_Initial
// methods: ChargeMe, setInitial, getInitial, addPayment, getTotal
class ChargeMe {
  private:
    double m_totalOwed;
    char m_Initial;
  public:
    ChargeMe(){
      m_totalOwed = 0;
    }
    void setInitial(istream& in){
        in >> m_Initial;
    };
    char getInitial(){
      return m_Initial;
    };
    void addPayment(double money){
      m_totalOwed += money;
    };
    double getTotal(){
      return m_totalOwed;
    };
};

// int getNumberofPeople()
// Description: asks the user for the total number of people to be charged today
//              (the number of ChargeMe objects)
// Parameters: none
// Returns: the number of people
int getNumberofPeople(){
  int people;
  cout << "Hello! To help you calculate your charges, I will need "
          "some information.\nPress ENTER to continue." << endl;
  cin.ignore();
  cout << "How many people did you buy things for?" << endl;
  cin >> people;
  return people;
}

// void fillPeople(ChargeMe *list, int people)
// Description: Sets the initial of each ChargeMe object
// Paramters: array of ChargeMe objects, total number of ChargeMe objects
// Returns: nothing
void fillPeople(ChargeMe *list, int people){
  cout << "Please enter a unique initial for each person. (r for Ryan,"
          " b for Britnie)\n";
  for (int i = 0; i < people; i++){
    list[i].setInitial(cin);
  };
}

// void waitMil(int ms)
// Description: tells the program to wait for some milliseconds. Originally
//              intended to be used between prompts for user information
// Parameters: number of milliseconds
// Returns: nothing
void waitMil(int ms){
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// void howMany(int people)
// Description: tells the user the number of people added to the list of payers
// Parameters: number of people
// Returns: nothing
void howMany(int people){
  if (people == 1){
    cout << "Thank you. " << people << " person has been added..." << endl << endl;
  }
  else{
    cout << "Thank you. " << people << " people have been added..." << endl << endl;
  }
}

// int itemCount()
// Description: asks the user for the number of items on the receipt
// Parameters: none
// Returns: number of items on receipt
int itemCount(){
  cout <<  "How many items do you have?" << endl;
  int itemCount;
  cin >> itemCount;
  return itemCount;
}

// void askforItem()
// Description: gives the user instructions on how to enter item price and payer
//              information
// Parameters: none
// Returns: nothing
void askforItem(){
  cout << "Please enter the price of each item followed by a space and then the "
          "initial of each person sharing the cost of that item. Ex: '9.99 vdh'"
          << endl;
}

// void splitCost(ChargeMe *list, vector<double> &receipt, int people)
// Description: Gets the item price and initials of people who paid for that item
//              then divides the cost of that item evenly between the people who
//              paid for that item
// Paramters: list of payers, list of item prices, total number of itemPayers
// Returns: nothing
void splitCost(ChargeMe *list, vector<double> &receipt, int people){
    // get price of one item
      double price;
      cin >> price;
      receipt.push_back(price);

      // get initials of people paying for said item
      string itemPayers;
      cin >> itemPayers;
      int divisor = itemPayers.length(); // get number of people paying for item

      // add divided cost to each person who signed for it
      for (int j = 0; j < divisor; j++){
        for (int i = 0; i < people; i++){
          if (list[i].getInitial() == itemPayers[j]){
            list[i].addPayment(price/(double)divisor);
          }
        }
      }
      cin.clear();
      cin.ignore(1);
}

// void owerBreakdown(int people, ChargeMe *list)
// Description: outputs the total amount owed by each person to the user
// Paramters: total number of payers and list of each payer's information
// Returns: nothing
void owerBreakdown(int people, ChargeMe *list){
  for (int i = 0; i < people; i ++){
    cout << list[i].getInitial() << " owes $" << list[i].getTotal() << endl;
  }
}

// void itemBreakdown(int itemCount, int people, ChargeMe *list, vector<double> &receipt)
// Description: runs the split cost function x times for the x number of items
//              on the receipt. Then outputs the total amount owed by each
//              person to the user
// Parameters: total number of items, total number of payers, list of payer info,
//             list of item costs
// Returns: nothing
void itemBreakdown(int itemCount, int people, ChargeMe *list, vector<double> &receipt){
  for (int i = 0; i < itemCount; i++){
    splitCost(list,receipt,people);
  }
  owerBreakdown(people,list);
}

int main(){

  int peopleCount = getNumberofPeople();
  vector<double> receipt;
  ChargeMe payers[peopleCount];
  int numberofItems;

  fillPeople(payers,peopleCount);
  howMany(peopleCount);
  numberofItems = itemCount();
  askforItem();
  itemBreakdown(numberofItems,peopleCount,payers,receipt);

}
