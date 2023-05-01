#include <string>
#include <sstream>
#include <any>
#include <vector>


std::string toJsonStrings(const std::vector<std::any>& values) {
  std::stringstream ss;
  ss << "{";
  for (int i = 0; i < values.size(); i++) {
    ss << "\"value_" << i << "\": ";
    if (values[i].type() == typeid(std::string)) {
      ss << "\"" << std::any_cast<std::string>(values[i]) << "\"";
    } else if (values[i].type() == typeid(int)) {
      ss << std::any_cast<int>(values[i]);
    } else if (values[i].type() == typeid(double)) {
      ss << std::any_cast<double>(values[i]);
    }
    if (i < values.size() - 1) {
      ss << ",";
    }
  }
  ss << "}";
  return ss.str();
}