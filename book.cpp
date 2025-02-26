#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "book.h"
#include "util.h"

Book::Book(const std::string& category, const std::string& name, double price, int qty, const std::string& author, const std::string& isbn) : Product(category, name, price, qty), author_(author), isbn_(isbn) {
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> authorWords = parseStringToWords(author_);
  keys_ = setUnion(nameWords, authorWords);
  keys_.insert(isbn_);
}

Book::~Book() {}

std::set<std::string> Book::keywords() const {
  return keys_;
}

std::string Book::displayString() const {
  std::string info = name_ + "\n" + "Author: " + author_ + " " + "ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return info;
}

void Book::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
} 

std::string Book::getAuthor() const {return author_;}
std::string Book::getISBN() const {return isbn_;}
