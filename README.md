Пример работы проекта

содержимое config.json

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

содержимое текстовых файлов:

ex1.txt: milk milk milk milk water water water
ex2.txt: milk water water
ex3.txt: milk milk milk milk milk water water water water water
ex4.txt: americano cappuccino

содержимое requests.json

{
  "requests": [
    "milk water",
    "sugar"
  ]
}

Тогда, запуская проект, ответ помещается в файл answers.json. В данном примере ответ получится таким:

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
