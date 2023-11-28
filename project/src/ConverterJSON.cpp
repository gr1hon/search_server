//
// Created by grigo on 23.11.2023.
//
#include "../include/ConverterJSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments(){
    std::ifstream file("../config/config.json");
    if (!file.is_open()) {
        return {};
    }
    json configJSON = json::parse(file);
    std::vector<std::string> files = configJSON["files"];
    file.close();
    std::vector<std::string> ans;
    for(auto& s : files){
        std::ifstream f(s);
        if (f.is_open()){
            std::string str;
            std::string input;
            while(!f.eof()){
                std::getline(f, str);
                input.append(str);
                input.append(" ");
            }
            f.close();
            ans.push_back(input);
        } else {
            std::cout << "File " << s << " cannot be open!" << std::endl;
        }
    }
    return ans;
}

int ConverterJSON::GetResponsesLimit(){
    std::ifstream file("../config/config.json");
    if (!file.is_open()) {
        return {};
    }
    json configJSON = json::parse(file);
    int limit = configJSON["config"]["max_responses"];
    file.close();
    return limit;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream file("../config/requests.json");
    if (!file.is_open()) {
        return {};
    }
    json requestsJSON = json::parse(file);
    std::vector<std::string> ans = requestsJSON["requests"];
    file.close();
    return ans;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers){
    std::ofstream file("../config/answers.json");
    json answersJSON;
    json requests_answers;
    for (int i = 0; i < answers.size(); ++i) {
        std::string str = "request" + std::to_string(i + 1);
        json request_answer;
        if (!answers[i].empty()){
            request_answer["result"] = "true";
            json relevance;
            for (auto & j : answers[i]) {
                json ans;
                ans["doc_id"] = j.first;
                ans["rank"] = round(j.second * 1000) / 1000;
                relevance.push_back(ans);
            }
            request_answer["relevance"] = relevance;
        } else {
            request_answer["result"] = "false";
        }
        requests_answers[str] = request_answer;
    }
    answersJSON["answers"] = requests_answers;
    file << answersJSON;
    file.close();
}