#include "../include/InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs){
    docs = std::move(input_docs);
    freq_dictionary.clear();
    int doc_id = 0;
    mutex dictionary_access;
    std::vector<std::thread> threads;
    for (auto& file_name : docs) {
        threads.emplace_back([&dictionary_access, doc_id, this]{
            dictionary_access.lock();
            InvertedIndex::updateDocument(doc_id);
            dictionary_access.unlock();
        });
        doc_id++;
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word){
    //ищем word в freq_dictionary
    auto item = freq_dictionary.find(word);
    if (item == freq_dictionary.end()) {
        return {};
    }
    return item->second;
}

void InvertedIndex::updateDocument(int doc_id){
    std::stringstream ss(docs[doc_id]);
    std::map<std::string, Entry> file_freq_dictionary;
    std::string w;
    while (ss >> w) {
        std::transform(w.begin(), w.end(), w.begin(),[](unsigned char c){ return std::tolower(c); });
        if (!std::isalpha(w.at(w.size() - 1))){
            w.resize(w.size() - 1);
        }
        auto item = file_freq_dictionary.find(w);
        if (item != file_freq_dictionary.end()){
            item->second.count++;
        } else{
            Entry entry{(size_t) doc_id, 1};
            file_freq_dictionary.insert(std::pair<std::string, Entry>(w, entry));
        }
    }
    for (const auto& pair : file_freq_dictionary) {
        auto item = freq_dictionary.find(pair.first);
        if (item != freq_dictionary.end()){
            item->second.emplace_back(pair.second);
        } else{
            freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(pair.first, {pair.second}));
        }
    }
}
