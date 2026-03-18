#include <iostream>

#include "Polinoms.h"

int main() {
  Polinom p1, p2, res;
  int choice;

  std::cout << "---The output of the first polynomial(p1)---\n";
  std::cout << "How many monomials are there in a polynomail(p1)?\n";
  int n1;
  std::cin >> n1;

  std::cout << "\nEnter the coefficient and degree of the monomial separated "
               "by a space\n";
  std::cout << "(The coefficient is a double-type and the degree is a "
               "integer-type)\n";

  for (int i = 0; i < n1; i++) {
    double c;
    int d;

    std::cout << "\nMonome " << i + 1 << " data ";
    std::cin >> c >> d;
    p1.addMonom(c, d);
  }

  std::cout << "\n---The output of the second polynomial(p2)---\n";
  std::cout << "How many monomials are there in a polynomail(p2)?\n";
  int n2;
  std::cin >> n2;

  for (int i = 0; i < n2; i++) {
    double c;
    int d;

    std::cout << "\nMonome " << i + 1 << " data ";
    std::cin >> c >> d;
    std::cout << "\n";
    p2.addMonom(c, d);
  }
  do {
    std::cout << "\nCurrent polynomials:\n";
    std::cout << "p1: ";
    p1.print();
    std::cout << "\n";
    std::cout << "p2: ";
    p2.print();
    std::cout << "\n";
    std::cout << "\nWhat do you want to do with these polynomials?\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Subtraction\n";
    std::cout << "3. Multiplication by a scalar\n";
    std::cout << "4. Multiplication of polynomials\n";
    std::cout << "5. Equate p1 to p2\n";
    std::cout << "6. Comparison\n";
    std::cout << "0. Exit\n";
    std::cout << "\nYour choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
      res = p1 + p2;
      std::cout << "\nThe result of the addition: ";
      res.print();
      std::cout << "\n";
      break;
    case 2:
      res = p1 - p2;
      std::cout << "\nThe result of the subtraction: ";
      res.print();
      std::cout << "\n";
      break;
    case 3:
      double value;
      std::cout << "\nEnter the number to multiply: ";
      std::cin >> value;
      res = p1 * value;
      std::cout << "\nThe result of multiplication by a number: ";
      res.print();
      std::cout << "\n";
      break;
    case 4:
      res = p1 * p2;
      std::cout << "\nThe result of multiplying polynomials: ";
      res.print();
      std::cout << "\n";
      break;
    case 5:
      p1 = p2;
      std::cout << "\nNow p1 is equal to p2.\n";
      break;
    case 6:
      if (p1 == p2) {
        std::cout << "\nThe polynomials are equal\n";
      } else {
        std::cout << "\nThe polynomials are different\n";
      }
      break;
    case 0:
      std::cout << "\nThe program is completed.\n";
      break;
    default:
      std::cout << "\nIncorrect menu item!\n";
    }
  } while (choice != 0);

  return 0;
}