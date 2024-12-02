g++ "src/C++/main.cpp" -o "bin/C++/vop" -Wall -Wextra -Werror -Wpedantic -lSDL2 -O3
gcc "src/C/main.c" -o "bin/C/vop" -Wall -Wextra -Werror -Wpedantic -lSDL2 -O3 -std=c99
rustc "src/Rust/main.rs" -o "bin/Rust/vop"
