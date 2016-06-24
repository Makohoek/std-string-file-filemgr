/*
 * Copyright (c) 2016, Mattijs Korpershoek
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "File.hpp"

#include <fstream>
#include <string>
#include <cstring>
#include <future>
#include <thread>

File::File(const std::string name) : mName(name)
{}

File::File(File &&other): mName(std::move(other.mName))
{}

std::future<std::vector<String> *> File::readAsync(std::vector<String> *result) const
{
    return std::async(std::launch::async, &File::internalRead, this, result);
}

std::future<void> File::writeAsync(const std::vector<String> &input) const
{
    return std::async(std::launch::async, &File::internalWrite, this, input);
}

std::vector<String> *File::internalRead(std::vector<String> *result) const
{
    std::fstream myStream;
    std::string line;
    myStream.open(mName, std::ios::in);
    while (myStream.good()) {
        getline(myStream, line);
        if (!line.empty()) {
            result->push_back(String(line.c_str()));
        }
    }
    myStream.close();
    return result;
}

void File::internalWrite(const std::vector<String> &input) const
{
    std::fstream myStream;
    myStream.open(mName, std::ios::out);
    for (auto line : input) {
        for (auto c : line) {
            myStream << c;
        }
        myStream << std::endl;
    }
    myStream.close();
}

const std::string& File::getName() const
{
    return mName;
}

size_t File::size() const
{
    size_t totalSize = 0;
    std::vector<String> content;
    internalRead(&content);
    for (auto line : content) {
        totalSize += line.size();
    }
    return totalSize;
}

bool operator<(const File &left, const File &right)
{
    return strcmp(left.mName.c_str(), right.mName.c_str()) < 0;
}

bool operator==(const File &left, const File &right)
{
    return left.mName == right.mName;
}
