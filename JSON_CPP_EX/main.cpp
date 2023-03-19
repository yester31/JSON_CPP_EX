#define _CRT_SECURE_NO_WARNINGS    // scanf 보안 경고로 인한 컴파일 에러 방지
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

std::string get_time_stamp();

int main() {

    // 1. load file and parse a JSON string into DOM.
    std::ifstream ifs("../json_example.json");
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document d;
    d.ParseStream(isw);

    // 2. variable parsing
    int test = d["test"].GetInt();
    bool test1 = d["test1"].GetBool();
    std::string test2 = d["test2"].GetString();
    std::cout << "test = " << test << std::endl;
    std::cout << "test1 = " << test1 << std::endl;
    std::cout << "test2 = " << test2 << std::endl;

    // 3. Stringify the DOM
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    // 4. print
    // Output 2023-03-20 01:16:29.229 {"test":15,"test1":true,"test2":"test2"}
    std::cout << get_time_stamp() << " " << buffer.GetString() << std::endl;

    return 0;
}

std::string get_time_stamp()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration tp = now.time_since_epoch();
    tp -= std::chrono::duration_cast<std::chrono::seconds>(tp);
    time_t tt = std::chrono::system_clock::to_time_t(now);
    char time_str[1000];
    tm t = *localtime(&tt);
    sprintf(time_str, "%04u-%02u-%02u %02u:%02u:%02u.%03u", t.tm_year + 1900,
        t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
        static_cast<unsigned>(tp / std::chrono::milliseconds(1)));
    return time_str;
}