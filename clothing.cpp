#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty, const std::string& size, const std::string& brand) : Product(category, name, price, qty), size_(size), brand_(brand) {
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> brandWords = parseStringToWords(brand_);
  keys_ = setUnion(nameWords, brandWords);
}

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
  return keys_;
}

std::string Clothing::displayString() const {
  std::string info = name_ + "\n" + "Size: " + size_ + " " + "Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return info;
}

void Clothing::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
} 

std::string Clothing::getSize() const {return size_;}
std::string Clothing::getBrand() const {return brand_;}
