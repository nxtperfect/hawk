#include <window.hpp>

int main() {
  auto [window, error] = initialize();
  if (error != InitError::NONE) {
    cleanup();
    return 1;
  }
  run(window);
  return 0;
}
