#include <iostream>
#include <sstream>
#include "mydatastore.h"
#include "util.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
  for (std::map<std::string, Product*>::iterator i = pCatalog_.begin(); i != pCatalog_.end(); i++) {
    delete i->second;
  }
  for (std::map<std::string, User*>::iterator i = uDirectory_.begin(); i != uDirectory_.end(); i++) {
    delete i->second;
  }
}

void MyDataStore::addProduct(Product* product){
  if (!product) {
    return;
  }
  pCatalog_[product->getName()] = product;

  std::set<std::string> keywordSet = product->keywords(); //Copying the keywords beforehand to avoid modification issues
  std::vector<std::string> keywords(keywordSet.begin(), keywordSet.end()); //Before: Modifies a std::vector while iterating over it.

  for (size_t i = 0; i < keywords.size(); i++) {
    keyMapping_[keywords[i]].insert(product);
  }
}

void MyDataStore::addUser(User* user) {
  uDirectory_[convToLower(user->getName())] = user;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& searchTerms, int searchType) {
    std::vector<Product*> results;
    if (searchTerms.empty()) {
        return results;
    }
    
    std::set<Product*> matchedProducts;
    bool firstTermProcessed = false;

    for (const std::string& term : searchTerms) {
        std::string lowerTerm = convToLower(term);


        if (!keyMapping_.count(lowerTerm)) {
            if (searchType == 0) {
                return results;
            }
            continue;
        }
        const std::set<Product*>& productSet = keyMapping_[lowerTerm];

        if (!firstTermProcessed) {
            matchedProducts = productSet;
            firstTermProcessed = true;
            continue;
        }
        if (searchType == 0) {
            matchedProducts = setIntersection(matchedProducts, productSet);
            if (matchedProducts.empty()) { // If no common products left, exit early
                return results;
            }
        }
        else {
            matchedProducts = setUnion(matchedProducts, productSet);
        }
    }
    results.assign(matchedProducts.begin(), matchedProducts.end());
    recentSearch_ = results;
    return results;
}

void MyDataStore::dump(std::ostream& os) {
    os << "<products>" << std::endl;
    std::map<std::string, Product*>::iterator x = pCatalog_.begin();
    while (x != pCatalog_.end()) {
        x->second->dump(os);
        x++;
    }
    os << "</products>" << std::endl;

    os << "<users>" << std::endl;
    std::map<std::string, User*>::iterator y = uDirectory_.begin();
    while (y != uDirectory_.end()) {
        y->second->dump(os);
        y++;
    }
    os << "</users>" << std::endl;
}

void MyDataStore::addToCart(const std::string& username, Product* product) {
  std::string lowerName = convToLower(username);
  if (!uDirectory_.count(lowerName)) {
    std::cout << "Invalid request" << std::endl;
    return;
  }
  uCarts_[lowerName].push_back(product);
}

void MyDataStore::displayCart(const std::string& username) {
    std::string lowerName = convToLower(username);
    std::map<std::string, User*>::iterator x = uDirectory_.find(lowerName);
    if (x == uDirectory_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    const std::vector<Product*>& cart = uCarts_.at(lowerName);
    for (size_t i = 0; i < cart.size(); i++) {
        std::cout << "Item " << (i + 1) << std::endl;
        std::cout << cart[i]->displayString() << std::endl;
    }
}

void MyDataStore::buyCart(const std::string& username) {
    std::string lowerName = convToLower(username);
    std::map<std::string, User*>::iterator x = uDirectory_.find(lowerName);
    if (x == uDirectory_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    User* user = x->second;
    std::vector<Product*>& cartItems = uCarts_[lowerName];
    std::vector<Product*> remainingItems;

    for (std::vector<Product*>::iterator it = cartItems.begin(); it != cartItems.end(); ++it) {
        Product* product = *it;
        if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
            product->subtractQty(1);
            user->deductAmount(product->getPrice());
        } else {
            remainingItems.push_back(product);
        }
    }
    cartItems = std::move(remainingItems);
}
