# ppc-2025-threads

### Сборка проекта

```bash
git clone https://github.com/MaxikGuy/ppc-2025-threads
cd ppc-2025-threads
mkdir sln
cmake -D USE_SEQ=ON -D USE_OMP=ON -D USE_TBB=ON -D USE_STL=ON -D USE_FUNC_TESTS=ON -D USE_PERF_TESTS=ON -S ../ppc-2025-threads -B sln -D CMAKE_BUILD_TYPE=Release

```

#### Потоки
```bash
cmake -D USE_SEQ=ON -D USE_OMP=ON -D USE_TBB=ON -D USE_STL=ON -D USE_FUNC_TESTS=ON -D USE_PERF_TESTS=ON -S ../ppc-2025-threads -B sln -D CMAKE_BUILD_TYPE=Release
```

#### Весь
```bash
cmake -D USE_SEQ=ON -D USE_MPI=ON -D USE_OMP=ON -D USE_TBB=ON -D USE_STL=ON -D USE_FUNC_TESTS=ON -D USE_PERF_TESTS=ON -S ../ppc-2025-threads -B sln -D CMAKE_BUILD_TYPE=Release
```