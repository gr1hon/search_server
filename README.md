Реализация системы поиска по корпоративному порталу компании "AйТиБокс"

Поисковый движок представлет из себя консольное приложение, осуществляющее поиск и имеющее возможность настройки через файлы формата JSON.

Проект использует стандартные библиотеки языка C++, библиотеку nlohmann_json для работы с JSON файлами, библиотеку Google Test для проведения автоматических модульных тестов.


Пример работы проекта

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
  1. ex1.txt:
 ```
 milk milk milk milk water water water
```
  2. ex2.txt:
```
 milk water water
```
  3. ex3.txt:
```
 milk milk milk milk milk water water water water water
```
  4. ex4.txt:
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
      "relevance":[{
        "doc_id":2,"rank":1.0},
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
