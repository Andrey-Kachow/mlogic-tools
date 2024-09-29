#pragma once
#include <string>

class AtomIdentifier {
  private:
    std::string _name;

  public:
    AtomIdentifier(std::string name) : _name(name){}

    bool operator<(const AtomIdentifier& other) const {
        return this->_name < other._name;
    }

    bool operator==(const AtomIdentifier& other) const {
        return this->_name == other._name;
    }
};
