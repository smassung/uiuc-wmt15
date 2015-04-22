/**
 * @file sentence-writer.cpp
 * @author Sean Massung
 */

#include <iostream>
#include <fstream>
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
    std::cerr << "Usage: " << prog << " [filename]"
              << std::endl;
    std::cerr << "which creates [filename].sentences where each line is a single sentence" << std::endl;
    std::cerr << std::endl;
    return 1;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        return print_usage(argv[0]);


    std::ifstream infile{argv[1]};
    std::ofstream outfile{std::string{argv[1]} + ".sentences"};
    std::string line;

    using namespace meta::analyzers;
    std::unique_ptr<token_stream> stream = make_unique<tokenizers::icu_tokenizer>();
    stream = make_unique<filters::empty_sentence_filter>(std::move(stream));

    while (std::getline(infile, line))
    {
        if (line.empty())
            continue;

        stream->set_content(line);
        while (*stream)
        {
            auto next = stream->next();
            if (next != "<s>" && next != "</s>")
                outfile << next;
            if (next == "</s>")
                outfile << std::endl;
        }
    }
}
