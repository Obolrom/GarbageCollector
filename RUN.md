### Before any move, generate build system
```bash
cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug
```

### How to run tests
```bash
cmake --build cmake-build-debug --target vm_tests &&
./cmake-build-debug/vm_tests
```

### Or run with CTest
```bash
cmake --build cmake-build-debug --target vm_tests &&
ctest --test-dir cmake-build-debug --output-on-failure
```

### Run main.c
```bash
cmake --build cmake-build-debug --target GarbageCollector &&
./cmake-build-debug/GarbageCollector
```
