#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <vector>
#include <set>
#include <queue>
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"

class MyDataStore : public DataStore {
  public:
    MyDataStore();
    ~MyDataStore();
    
    void addProduct(Product* product);
    void addUser(User* user);
    std::vector<Product*> search(std::vector<std::string>& searchTerms, int searchType);
    void dump(std::ostream& os);
    void addToCart(const std::string& username, Product* product);
    void displayCart(const std::string& username);
    void buyCart(const std::string& username);
  
  private: 
    std::map<std::string, std::set<Product*>> keyMapping_;
    std::map<std::string, Product*> pCatalog_;
    std::map<std::string, User*> uDirectory_;
    std::map<std::string, std::vector<Product*>> uCarts_;
    std::vector<Product*> recentSearch_;
};
#endif
