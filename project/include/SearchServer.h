//
// Created by grigo on 14.11.2023.
//

#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H
#pragma once
#include <set>
#include "InvertedIndex.h"
#include "ConverterJSON.h"
using namespace std;
struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B, template<class,class,class...> class M, class... Args>
std::multimap<B,A> flip_map(const M<A,B,Args...> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(),
                   std::inserter(dst, dst.begin()),
                   flip_pair<A,B>);
    return dst;
}

class SearchServer {
public:
/**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    SearchServer(InvertedIndex& idx) : _index(idx){ };
/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
private:
    InvertedIndex _index;
};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
