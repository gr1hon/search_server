# Search_engine

Поисковый движок представлет из себя консольное приложение, осуществляющее поиск и имеющее возможность настройки через файлы формата JSON.
## Используемые технологии
Проект использует:
- стандартные библиотеки языка C++ 17
- [CMake](https://cmake.org/download/) 3.24 для сборки проекта
- библиотеку [nlohmann_json](https://github.com/nlohmann/json) для работы с JSON файлами
- библиотеку Google Test для проведения автоматических модульных тестов

## Инструкция по запуску

Клонируйте этот репозиторий командой  
```git clone --recurse-submodules https://github.com/gr1hon/search_server.git```

В файле config/config.json в поле files нужно указать названия файлов, в которым будет производиться поиск, а также максимальное количество ответов на один запрос в поле max_responses.

В файле config/requests.json нужно указать список запросов.

Далее в папку resources нужно скопировать файлы txt, в которых будет производиться поиск.
```
cd 'путь-к-проекту'
mkdir build
cd build
cmake -G "MinGW Makefiles" ../
//после -G нужно указать нужный компилятор, список можно найти с помощью cmake --help
make
./search_project
```
После этого в файле answers.json появится результат
## Пример работы проекта

- Содержимое config.json
```
{
  "config": {
		"name": "MySearchEngine",
    "version": "1.1",
    "max_responses": 5
  },
  "files": [
    "../resources/ex1.txt",
    "../resources/ex2.txt",
    "../resources/ex3.txt",
    "../resources/ex4.txt"
  ]
}
```
- Содержимое текстовых файлов:

 ex1.txt:
 ```
 milk milk milk milk water water water
```
 ex2.txt:
```
 milk water water
```
 ex3.txt:
```
 milk milk milk milk milk water water water water water
```
 ex4.txt:
```
 americano cappuccino
```

- Содержимое requests.json
```
{
  "requests": [
    "milk water",
    "sugar"
  ]
}
```
Тогда, запуская проект, ответ помещается в файл answers.json. В данном примере ответ получится таким:
```
{
  "answers":{
    "request1":{
      "relevance":[
        {"doc_id":2,"rank":1.0},
        {"doc_id":0,"rank":0.7},
        {"doc_id":1,"rank":0.3}
      ],
      "result":"true"
    },
    "request2":{
      "result":"false"
    }
  }
}
```
