#ifndef _TARGET_H_
#define _TARGET_H_
#include <iostream>
#include <string>

const int maxDepends = 10;

struct Target {  // You may add fields and methods as you see fit
  std::ostream &out;  // Stream where Target will print its output
  std::string name;

  int curDepends;
  int lastUp;
  Target** depends;
  // need to destroy array but not contents of it, free dtor should be ok

  Target *parent;

  Target(const std::string &name, std::ostream &out = std::cout);
  ~Target();
  bool isLeaf() const;
  void addDepend(Target *d);
  void update(const int time);
  int lastUpdated() const;
  void build(int time);
};

#endif
