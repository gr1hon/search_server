//
// Created by grigo on 14.11.2023.
//

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H
#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <thread>
#include <mutex>
#include "ConverterJSON.h"

struct Entry {
size_t doc_id, count;
// Данный оператор необходим для проведения тестовых сценариев
bool operator ==(const Entry& other) const {
    return (doc_id == other.doc_id &&
            count == other.count);
}
};

using namespace std;
//mutex dictionary_access;

class InvertedIndex {
public:
    InvertedIndex() = default;
/**
* Обновить или заполнить базу документов, по которой будем совершать
поиск*
@param texts_input содержимое документов
*/
    void UpdateDocumentBase(std::vector<std::string> input_docs);
/**
* Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
    std::vector<Entry> GetWordCount(const std::string& word);
    //обновляем данные внутри одного документа
    void updateDocument(int doc_id);


private:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь
};

#endif //SEARCH_ENGINE_INVERTEDINDEX_H