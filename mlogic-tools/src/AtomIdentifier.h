#pragma once
#include <string>

class AtomIdentifier {
  private:
    std::string _name;

  public:
    AtomIdentifier(std::string name) : _name(name){}
};
