#include <sys/statvfs.h>
#include <cstdlib>
#include <iostream>

// This will print a warning suitable for inclusion in `PS1` if your $HOME
// partition is nearly full.
int main() {
  // We'll use the environment variable and just exit if it isn't set.
  const char* home = std::getenv("HOME");
  if (home == nullptr) {
    return 0;
  }

  struct statvfs buf;
  int rc = statvfs(home, &buf);

  std::uint64_t block_size = buf.f_bsize;
  std::uint64_t blocks_free = buf.f_bfree;
  std::uint64_t space_free = block_size * blocks_free;

  // 1 GB warning.
  if (space_free < 1073741824ULL) {
    std::cout << "\e[0;1;48;5;160mDISK\e[0m ";
  }
  return 0;
}
