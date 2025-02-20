# MatrixChain
Реализация класса, хранящего цепочку матриц, для последующего перемножения, используя оптимальный алгоритм с помощью динамического программирования.
# Клонирование репозитория
```
git clone https://github.com/kakov1/MatrixChain.git
cd MatrixChain/
```
# Настройка виртуального окружения
```
python3 -m venv .venv
source .venv/bin/activate
pip3 install conan
conan profile detect --force
```
# Сборка проекта
```
conan install . --output-folder=build --build=missing
cd build/
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
# Запуск основной программы
```
cd src/
./main
```
# Запуск тестов
```
cd tests/
./test
```