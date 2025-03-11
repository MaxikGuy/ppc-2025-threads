# ppc-2025-threads

### Скачивание внешних библиотек
```bash
git submodule update --init --recursive --depth=1
```

### Сборка проекта

```bash
git clone https://github.com/MaxikGuy/ppc-2025-threads
cd ppc-2025-threads
cmake -D USE_SEQ=ON -D USE_OMP -D USE_TBB=ON -D USE_STL=ON -D USE_FUNC_TESTS=ON -D USE_PERF_TESTS=ON -D USE_CPPCHECK=ON -S ../ppc-2024-autumn -B sln -D CMAKE_BUILD_TYPE=Release
```

#### Потоки
```bash
cmake -D USE_SEQ=ON -D USE_OMP -D USE_TBB=ON -D USE_STL=ON -D USE_FUNC_TESTS=ON -D USE_PERF_TESTS=ON -D USE_CPPCHECK=ON -S ppc-2024-autumn -B ppc_build -D CMAKE_BUILD_TYPE=Release
```

#### Весь
```bash
cmake -D USE_SEQ=ON -D USE_MPI=ON -D USE_OMP -D USE_TBB=ON -D USE_STL=ON -D USE_FUNC_TESTS=ON -D USE_PERF_TESTS=ON -D USE_CPPCHECK=ON -S ppc-2024-autumn -B ppc_build -D CMAKE_BUILD_TYPE=Release
```