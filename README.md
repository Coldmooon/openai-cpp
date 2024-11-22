# openai-cpp

A Python-like OpenAI API implementation in C++. This library provides a clean and intuitive interface for interacting with OpenAI's API and other compatible LLM services.

** To use this library, you just need to include the header file `openai.hpp` **

## Features

- Python-like API design for familiar usage patterns
```
// Initialize client
OpenAI client("api_key", "base_url");

// Create a chat completion
auto response = client.chat.completions.create();

// Print the response
std::cout << response.choices[0].message.content << std::endl;
```
- Support for OpenAI chat completions endpoint
- Compatible with OpenAI API and other LLM services
- Built with modern C++ (C++17)


## Prerequisites

- C++17 compatible compiler
- CMake (3.10 or higher)
- libcurl
- nlohmann/json


## Installation

1. Clone the repository:

```bash
git clone https://github.com/coldmooon/openai-cpp.git
```
Then include the header file `openai.hpp` in your project.

2. Build the example to test:

```bash
mkdir build
cd build
cmake ..
make
```

Set the `base_url` and `api_key` in the example code.


## An Example Usage
```cpp
#include "openai.hpp"
#include <iostream>

int main() {
    // Initialize client with your API key and base URL
    OpenAI client("your_api_key", "https://api.openai.com/v1");

    // Create a conversation
    std::vector<ChatCompletion::Message> messages = {
    ChatCompletion::Message::system("You are a helpful assistant")
    };

    // Add a user message
    messages.push_back(ChatCompletion::Message::user("Hello!"));

    // Get completion
    auto response = client.chat.create(
    ChatCompletion::CreateParams()
        .model("gpt-3.5-turbo")
        .messages(messages)
        .max_tokens(1024)
        .temperature(0.7)
    );

    // Print the response
    std::cout << "Assistant: " << response.choices[0].message.content << std::endl;
    return 0;
}

```

## Acknowledgments

- [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing
- OpenAI for the API design inspiration