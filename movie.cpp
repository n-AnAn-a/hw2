#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string& category, const std::string& name, double price, int qty, const std::string& genre, const std::string& rating) : Product(category, name, price, qty), genre_(genre), rating_(rating) {
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> genreWords = parseStringToWords(genre_);
  keys_ = setUnion(nameWords, genreWords);
}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
  return keys_;
}

std::string Movie::displayString() const {
  std::string info = name_ + "\n" + "Genre: " + genre_ + " " + "Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return info;
}

void Movie::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
} 

std::string Movie::getGenre() const {return genre_;}
std::string Movie::getRating() const {return rating_;}
