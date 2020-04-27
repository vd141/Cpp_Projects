#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

using namespace std;

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

int getNumberofPeople(){
  // welcome the user and ask how many people are going to be charged today
  int people;
  cout << "Hello! To help you calculate your charges, I will need "
          "some information.\nPress ENTER to continue." << endl;
  cin.ignore();
  cout << "How many people did you buy things for?" << endl;
  cin >> people;
  return people;
}

void fillPeople(ChargeMe *list, int people){
  cout << "Please enter a unique initial for each person. (r for Ryan,"
          " b for Britnie)\n";
  for (int i = 0; i < people; i++){
    list[i].setInitial(cin);
  };
}

void waitMil(int ms){
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void howMany(int people){
  if (people == 1){
    cout << "Thank you. " << people << " person has been added..." << endl << endl;
  }
  else{
    cout << "Thank you. " << people << " people have been added..." << endl << endl;
  }
}

void askforItem(){
  cout << "Please enter the price of each item followed by a space and then the "
          "initial of each person sharing the cost of that item. Ex: '9.99 vdh'"
          << endl;
}

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

void owerBreakdown(int people,ChargeMe *list){
  for (int i = 0; i < people; i ++){
    cout << list[i].getInitial() << " owes $" << list[i].getTotal() << endl;
  }
}


int main(){
  int people = getNumberofPeople(); // save number of people to be charged today
  vector<double> receipt;

  // list of people and what they owe
  ChargeMe payers[people];

  // set each payer class with a person's initial
  fillPeople(payers,people);

  // return number of poeple entered
  howMany(people);

  // wait some time so as not to overwhelm the user
  cout <<  "How many items do you have?" << endl;
  int itemCount;
  cin >> itemCount;

  // ask user to input item prices and initials
  askforItem();

  // divide all costs by each person and add totals
  for (int i = 0; i < itemCount; i++){
    splitCost(payers,receipt,people);
  }

  // return what each person owes
  owerBreakdown(people,payers);

}
