//
// Created by grigo on 23.11.2023.
//
#include "../include/InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs){
    docs = std::move(input_docs);
    freq_dictionary.clear();
    int doc_id = 0;
//    std::vector<std::thread> threads;
    for (auto& file_name : docs) {
        InvertedIndex::updateDocument(doc_id);
        doc_id++;
        //для каждого нового файла создаем отдельный поток
//        std::thread th(&InvertedIndex::updateDocument, std::ref(doc_id));
//        threads.emplace_back(th);
//        doc_id++;
//    }
//    for (auto& thread : threads) {
//        thread.join();
//    }
    }
//    for (const auto& word : freq_dictionary) {
//        cout << word.first << endl;
//        for (auto entry : word.second) {
//            cout << entry.doc_id << " " << entry.count << endl;
//        }
//    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word){
    //ищем word в freq_dictionary
    auto item = freq_dictionary.find(word);
    if (item == freq_dictionary.end()) {
        return {};
    }
//    cout << item->first << endl;
//    for (auto entry : item->second) {
//        cout << entry.doc_id << " " << entry.count << endl;
//    }
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
//    dictionary_access.lock();
    for (const auto& pair : file_freq_dictionary) {
        auto item = freq_dictionary.find(pair.first);
        if (item != freq_dictionary.end()){
            item->second.emplace_back(pair.second);
        } else{
            freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(pair.first, {pair.second}));
        }
    }
//    for (const auto& pair : file_freq_dictionary) {
//        cout << pair.first << " " << pair.second.doc_id << " " << pair.second.count << endl;
//    }
//    dictionary_access.unlock();
}