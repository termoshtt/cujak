
#include "../plan.hpp"

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    return 1;
  }
  const std::string filename(argv[1]);

  return 0;
}
