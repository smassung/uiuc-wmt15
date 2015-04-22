/**
 * @file cin-tokenizer.cpp
 * @author Sean Massung
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "utf/utf.h"
#include "util/shim.h"
#include "analyzers/analyzer.h"
#include "analyzers/tokenizers/icu_tokenizer.h"
#include "analyzers/filters/all.h"

using namespace meta;

int print_usage(const std::string& prog)
{
    std::cerr << std::endl;
    std::cerr << "Usage: " << prog << " [OPTION]"
              << std::endl;
    std::cerr << "where [OPTION] is one of:" << std::endl;
    std::cerr << "\t--simple\tpunctuation-based tokenization using ICU" << std::endl;
    std::cerr << "\t--hard-stem\ttruncate each word at 5 characters" << std::endl;
    std::cerr << "\t--char-tok\ttokenize based on single characters" << std::endl;
    std::cerr << "\t--hybrid\tsplit word after first 5 chars, then split characters" << std::endl;
    std::cerr << std::endl;
    return 1;
}

std::string simple_tokenize(const std::string& line)
{
    using namespace meta::analyzers;
    std::unique_ptr<token_stream> stream
        = make_unique<tokenizers::icu_tokenizer>();
    stream = make_unique<filters::lowercase_filter>(std::move(stream));
    stream = make_unique<filters::empty_sentence_filter>(std::move(stream));

    std::string output;
    stream->set_content(line);
    while (*stream)
    {
        auto next = stream->next();
        if (next != "<s>" && next != " " && next != "</s>")
            output += next + " ";
    }
    return output;
}

std::string hard_stem(const std::string& line)
{
    using namespace meta::analyzers;
    std::unique_ptr<token_stream> stream
        = make_unique<tokenizers::icu_tokenizer>();
    stream = make_unique<filters::lowercase_filter>(std::move(stream));
    stream = make_unique<filters::empty_sentence_filter>(std::move(stream));

    std::string output;
    stream->set_content(line);
    while (*stream)
    {
        auto next = stream->next();
        if (next != "<s>" && next != " " && next != "</s>")
            output += next.substr(0, 5) + " ";
    }
    return output;
}

std::string char_tokenize(std::string line)
{
    line.erase(std::remove_if(line.begin(), 
                              line.end(),
                              [](char ch){ return std::isspace(ch); }), line.end());
    std::string output{""};
    for (auto& ch: line)
        output = output + " " + ch;
    return output;
}

std::string hybrid(const std::string& line)
{
    using namespace meta::analyzers;
    std::unique_ptr<token_stream> stream
        = make_unique<tokenizers::icu_tokenizer>();
    stream = make_unique<filters::lowercase_filter>(std::move(stream));
    stream = make_unique<filters::empty_sentence_filter>(std::move(stream));

    std::string output;
    stream->set_content(line);
    while (*stream)
    {
        auto next = stream->next();
        if (next != "<s>" && next != " " && next != "</s>")
        {
            auto end = next.size() > 5 ? char_tokenize(next.substr(5)) + " " : "";
            output = output + next.substr(0, 5) + " " + end;
        }
    }
    return output;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        return print_usage(argv[0]);

    std::string opt{argv[1]};
    std::string line;
    while(std::getline(std::cin, line))
    {
        line = utf::transform(line, "fi-ascii");
        if (opt == "--hard-stem")
            std::cout << hard_stem(line) << std::endl;
        else if (opt == "--char-tok")
            std::cout << char_tokenize(line) << std::endl;
        else if (opt == "--hybrid")
            std::cout << hybrid(line) << std::endl;
        else if (opt == "--simple")
            std::cout << simple_tokenize(line) << std::endl;
    }
}
