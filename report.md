# Kỹ thuật mới của C++ từ C++17 đến C++23
## Tài liệu chi tiết về các tính năng hiện đại

---

## Mục lục

1. [C++17 - Những cải tiến đột phá](#cpp17)
2. [C++20 - Cuộc cách mạng lớn](#cpp20)
3. [C++23 - Hoàn thiện và tối ưu](#cpp23)
4. [So sánh và Migration Guide](#migration)
5. [Best Practices và Performance](#best-practices)
6. [Ứng dụng thực tế](#applications)

---

## C++17 - Những cải tiến đột phá {#cpp17}

### 1. Structured Bindings (Khai báo cấu trúc)

**Khái niệm:** Cho phép tách các thành phần của tuple, pair, array hoặc struct thành các biến riêng biệt.

**Cú pháp:**
```cpp
auto [a, b, c] = expression;
```

**Ví dụ chi tiết:**
```cpp
#include <iostream>
#include <map>
#include <tuple>

// Với std::pair
std::pair<int, std::string> getPerson() {
    return {25, "John"};
}

// Với struct
struct Point {
    int x, y;
};

int main() {
    // Structured binding với pair
    auto [age, name] = getPerson();
    std::cout << "Age: " << age << ", Name: " << name << std::endl;
    
    // Với map iteration
    std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << std::endl;
    }
    
    // Với struct
    Point p{10, 20};
    auto [x, y] = p;
    std::cout << "Point: (" << x << ", " << y << ")" << std::endl;
    
    return 0;
}
```

**Ứng dụng thực tế:**
- Xử lý kết quả trả về từ database (id, name, email)
- Parse JSON objects
- Xử lý coordinates trong game development
- Iteration qua containers với key-value pairs

### 2. If Constexpr (Điều kiện compile-time)

**Khái niệm:** Cho phép thực hiện điều kiện tại compile-time, loại bỏ các nhánh code không cần thiết.

**Ví dụ chi tiết:**
```cpp
#include <iostream>
#include <type_traits>
#include <vector>
#include <string>

template<typename T>
void processData(const T& data) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Processing integer: " << data * 2 << std::endl;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Processing float: " << data * 1.5 << std::endl;
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "Processing string: " << data + " (processed)" << std::endl;
    } else {
        std::cout << "Unknown type processing" << std::endl;
    }
}

// Template metaprogramming example
template<int N>
constexpr int factorial() {
    if constexpr (N <= 1) {
        return 1;
    } else {
        return N * factorial<N-1>();
    }
}

int main() {
    processData(42);           // Integer processing
    processData(3.14);         // Float processing
    processData(std::string("Hello")); // String processing
    
    constexpr int fact5 = factorial<5>();
    std::cout << "5! = " << fact5 << std::endl;
    
    return 0;
}
```

**Ứng dụng:**
- Generic programming với type traits
- Optimization tại compile-time
- Template specialization đơn giản hóa
- Embedded systems programming

### 3. Class Template Argument Deduction (CTAD)

**Khái niệm:** Compiler tự động suy luận template arguments cho class templates.

**Ví dụ:**
```cpp
#include <iostream>
#include <vector>
#include <pair>
#include <memory>

template<typename T>
class Container {
    T data;
public:
    Container(T val) : data(val) {}
    void print() { std::cout << data << std::endl; }
};

// Custom deduction guide
template<typename T>
Container(T) -> Container<T>;

int main() {
    // Trước C++17: std::vector<int> v = {1, 2, 3};
    std::vector v = {1, 2, 3, 4, 5}; // Tự động suy luận std::vector<int>
    
    // Trước C++17: std::pair<int, std::string> p = {42, "Hello"};
    std::pair p = {42, "Hello"}; // Tự động suy luận std::pair<int, const char*>
    
    // Custom class
    Container c(42);    // Tự động suy luận Container<int>
    Container s("Hello"); // Tự động suy luận Container<const char*>
    
    c.print();
    s.print();
    
    // Smart pointers
    auto ptr = std::make_unique<int>(42);
    std::shared_ptr sp = std::make_shared<std::string>("Hello");
    
    return 0;
}
```

### 4. Inline Variables

**Khái niệm:** Cho phép định nghĩa variables trong header files mà không gây ra multiple definition errors.

**Ví dụ:**
```cpp
// config.h
#ifndef CONFIG_H
#define CONFIG_H

// Trước C++17 - cần implementation file
// extern const int MAX_CONNECTIONS;

// C++17 - có thể định nghĩa trực tiếp trong header
inline const int MAX_CONNECTIONS = 100;
inline const double PI = 3.14159265359;

class Logger {
public:
    static inline int instance_count = 0; // Static member variable
    
    Logger() { ++instance_count; }
    ~Logger() { --instance_count; }
};

#endif
```

**Ứng dụng:**
- Configuration constants
- Static member variables
- Header-only libraries
- Avoiding ODR (One Definition Rule) violations

### 5. std::optional

**Khái niệm:** Container có thể chứa hoặc rỗng một giá trị, thay thế cho null pointers.

**Ví dụ chi tiết:**
```cpp
#include <iostream>
#include <optional>
#include <string>
#include <vector>

// Function có thể trả về hoặc không
std::optional<int> findIndex(const std::vector<int>& vec, int target) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return static_cast<int>(i);
        }
    }
    return std::nullopt; // Không tìm thấy
}

std::optional<std::string> getUserName(int id) {
    if (id == 1) return "Alice";
    if (id == 2) return "Bob";
    return std::nullopt; // User không tồn tại
}

class SafeConfig {
    std::optional<std::string> database_url;
    std::optional<int> port;
    
public:
    void setDatabaseUrl(const std::string& url) {
        database_url = url;
    }
    
    void setPort(int p) {
        if (p > 0 && p < 65536) {
            port = p;
        }
    }
    
    std::string getDatabaseUrl() const {
        return database_url.value_or("localhost");
    }
    
    int getPort() const {
        return port.value_or(8080);
    }
    
    bool isConfigured() const {
        return database_url.has_value() && port.has_value();
    }
};

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    
    // Tìm kiếm với optional
    auto index = findIndex(numbers, 30);
    if (index) {
        std::cout << "Found at index: " << *index << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
    
    // Sử dụng value_or
    auto name = getUserName(1);
    std::cout << "User name: " << name.value_or("Unknown") << std::endl;
    
    // Configuration example
    SafeConfig config;
    config.setDatabaseUrl("postgresql://localhost:5432/mydb");
    config.setPort(3000);
    
    std::cout << "Database: " << config.getDatabaseUrl() << std::endl;
    std::cout << "Port: " << config.getPort() << std::endl;
    std::cout << "Configured: " << config.isConfigured() << std::endl;
    
    return 0;
}
```

### 6. std::variant

**Khái niệm:** Type-safe union có thể chứa một trong nhiều kiểu dữ liệu.

**Ví dụ:**
```cpp
#include <iostream>
#include <variant>
#include <string>
#include <vector>

// Variant cho các kiểu dữ liệu khác nhau
using Value = std::variant<int, double, std::string, bool>;

// Visitor pattern với variant
struct ValuePrinter {
    void operator()(int i) const {
        std::cout << "Integer: " << i << std::endl;
    }
    void operator()(double d) const {
        std::cout << "Double: " << d << std::endl;
    }
    void operator()(const std::string& s) const {
        std::cout << "String: " << s << std::endl;
    }
    void operator()(bool b) const {
        std::cout << "Boolean: " << (b ? "true" : "false") << std::endl;
    }
};

// JSON-like data structure
using JsonValue = std::variant<
    std::nullptr_t,
    bool,
    int,
    double,
    std::string,
    std::vector<JsonValue>
>;

void printJsonValue(const JsonValue& value, int indent = 0) {
    std::string spaces(indent * 2, ' ');
    
    std::visit([&](const auto& v) {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, std::nullptr_t>) {
            std::cout << spaces << "null";
        } else if constexpr (std::is_same_v<T, bool>) {
            std::cout << spaces << (v ? "true" : "false");
        } else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
            std::cout << spaces << v;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << spaces << "\"" << v << "\"";
        } else if constexpr (std::is_same_v<T, std::vector<JsonValue>>) {
            std::cout << spaces << "[\n";
            for (const auto& item : v) {
                printJsonValue(item, indent + 1);
                std::cout << ",\n";
            }
            std::cout << spaces << "]";
        }
    }, value);
}

int main() {
    // Basic variant usage
    std::vector<Value> values = {42, 3.14, std::string("Hello"), true};
    
    for (const auto& value : values) {
        std::visit(ValuePrinter{}, value);
    }
    
    // Index-based access
    Value v = 42;
    if (std::holds_alternative<int>(v)) {
        std::cout << "Contains int: " << std::get<int>(v) << std::endl;
    }
    
    // JSON example
    JsonValue json = std::vector<JsonValue>{
        42,
        std::string("hello"),
        true,
        nullptr
    };
    
    printJsonValue(json);
    
    return 0;
}
```

---

## C++20 - Cuộc cách mạng lớn {#cpp20}

### 1. Concepts (Khái niệm)

**Khái niệm:** Cho phép định nghĩa constraints cho template parameters một cách rõ ràng và dễ hiểu.

**Ví dụ chi tiết:**
```cpp
#include <iostream>
#include <concepts>
#include <type_traits>
#include <vector>
#include <string>

// Định nghĩa concepts cơ bản
template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept Numeric = Integral<T> || FloatingPoint<T>;

// Concept phức tạp hơn
template<typename T>
concept Printable = requires(T t) {
    std::cout << t;
};

template<typename Container>
concept Iterable = requires(Container c) {
    c.begin();
    c.end();
    typename Container::iterator;
};

template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};

// Sử dụng concepts
template<Numeric T>
T add(T a, T b) {
    return a + b;
}

template<Integral T>
T multiply(T a, T b) {
    std::cout << "Integer multiplication: ";
    return a * b;
}

template<FloatingPoint T>
T multiply(T a, T b) {
    std::cout << "Float multiplication: ";
    return a * b;
}

template<Iterable Container>
void printContainer(const Container& container) {
    std::cout << "Container contents: ";
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

template<Comparable T>
T findMax(const std::vector<T>& vec) {
    if (vec.empty()) {
        throw std::runtime_error("Empty vector");
    }
    
    T max_val = vec[0];
    for (const auto& item : vec) {
        if (item > max_val) {
            max_val = item;
        }
    }
    return max_val;
}

// Concept với multiple parameters
template<typename T, typename U>
concept Addable = requires(T t, U u) {
    { t + u } -> std::convertible_to<T>;
};

template<typename T, typename U>
requires Addable<T, U>
T addDifferentTypes(T a, U b) {
    return a + b;
}

int main() {
    // Numeric concept
    std::cout << add(5, 3) << std::endl;        // int
    std::cout << add(2.5, 1.5) << std::endl;   // double
    
    // Overloaded functions with concepts
    std::cout << multiply(4, 3) << std::endl;    // Integer version
    std::cout << multiply(2.5, 3.0) << std::endl; // Float version
    
    // Iterable concept
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::string str = "Hello";
    
    printContainer(vec);
    printContainer(str);
    
    // Comparable concept
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "Max: " << findMax(numbers) << std::endl;
    
    // Multiple type concept
    std::cout << addDifferentTypes(5, 2.5) << std::endl;
    
    return 0;
}
```

### 2. Coroutines

**Khái niệm:** Cho phép viết asynchronous code một cách tự nhiên, có thể pause và resume execution.

**Ví dụ:**
```cpp
#include <iostream>
#include <coroutine>
#include <optional>
#include <thread>
#include <chrono>

// Generator coroutine
template<typename T>
struct Generator {
    struct promise_type {
        T value;
        
        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        std::suspend_always yield_value(T val) {
            value = val;
            return {};
        }
        
        void return_void() {}
        void unhandled_exception() {}
    };
    
    std::coroutine_handle<promise_type> h;
    
    explicit Generator(std::coroutine_handle<promise_type> handle) : h(handle) {}
    
    ~Generator() {
        if (h) h.destroy();
    }
    
    // Iterator interface
    struct iterator {
        std::coroutine_handle<promise_type> h;
        
        iterator& operator++() {
            h.resume();
            return *this;
        }
        
        T operator*() const {
            return h.promise().value;
        }
        
        bool operator!=(const iterator& other) const {
            return h != other.h;
        }
    };
    
    iterator begin() {
        h.resume();
        return iterator{h};
    }
    
    iterator end() {
        return iterator{nullptr};
    }
};

// Simple generator function
Generator<int> fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield a;
        auto temp = a;
        a = b;
        b += temp;
    }
}

Generator<int> range(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
    }
}

// Task coroutine for async operations
struct Task {
    struct promise_type {
        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        
        void return_void() {}
        void unhandled_exception() {}
    };
    
    std::coroutine_handle<promise_type> h;
    
    explicit Task(std::coroutine_handle<promise_type> handle) : h(handle) {}
    
    ~Task() {
        if (h) h.destroy();
    }
};

Task simulateAsyncWork(const std::string& name, int duration) {
    std::cout << "Starting " << name << std::endl;
    
    // Simulate async work
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    
    std::cout << "Completed " << name << std::endl;
    co_return;
}

int main() {
    // Generator example
    std::cout << "Fibonacci sequence (first 10):" << std::endl;
    int count = 0;
    for (auto fib : fibonacci()) {
        if (count >= 10) break;
        std::cout << fib << " ";
        ++count;
    }
    std::cout << std::endl;
    
    // Range generator
    std::cout << "Range 5-10:" << std::endl;
    for (auto i : range(5, 10)) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Async tasks
    auto task1 = simulateAsyncWork("Task 1", 1000);
    auto task2 = simulateAsyncWork("Task 2", 500);
    
    // Wait for completion
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    
    return 0;
}
```

### 3. Ranges

**Khái niệm:** Cung cấp functional programming approach cho việc xử lý collections.

**Ví dụ:**
```cpp
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Functional pipeline với ranges
    auto result = numbers 
        | std::views::filter([](int n) { return n % 2 == 0; })  // Lọc số chẵn
        | std::views::transform([](int n) { return n * n; })     // Bình phương
        | std::views::take(3);                                   // Lấy 3 phần tử đầu
    
    std::cout << "Even squares (first 3): ";
    for (int n : result) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // String processing với ranges
    std::vector<std::string> words = {"hello", "world", "cpp", "ranges", "awesome"};
    
    auto longWords = words
        | std::views::filter([](const std::string& s) { return s.length() > 4; })
        | std::views::transform([](const std::string& s) { 
            std::string upper = s;
            std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
            return upper;
        });
    
    std::cout << "Long words (uppercase): ";
    for (const auto& word : longWords) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    // Lazy evaluation example
    std::cout << "Infinite range (first 10): ";
    auto infiniteRange = std::views::iota(1)  // 1, 2, 3, 4, ...
        | std::views::filter([](int n) { return n % 3 == 0; })  // Chia hết cho 3
        | std::views::take(10);  // Chỉ lấy 10 phần tử
    
    for (int n : infiniteRange) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### 4. Modules

**Khái niệm:** Hệ thống module mới thay thế #include truyền thống.

**Ví dụ:**
```cpp
// math_module.cpp
export module math_utils;

import <iostream>;

export namespace math_utils {
    int add(int a, int b) {
        return a + b;
    }
    
    int multiply(int a, int b) {
        return a * b;
    }
    
    class Calculator {
    public:
        int calculate(int a, int b, char op) {
            switch(op) {
                case '+': return add(a, b);
                case '*': return multiply(a, b);
                default: return 0;
            }
        }
    };
}

// main.cpp
import math_utils;
import <iostream>;

int main() {
    std::cout << "5 + 3 = " << math_utils::add(5, 3) << std::endl;
    std::cout << "4 * 7 = " << math_utils::multiply(4, 7) << std::endl;
    
    math_utils::Calculator calc;
    std::cout << "Calculator: 6 + 4 = " << calc.calculate(6, 4, '+') << std::endl;
    
    return 0;
}
```

### 5. Spaceship Operator (<=>)

**Khái niệm:** Toán tử so sánh ba chiều tự động tạo ra tất cả các toán tử so sánh.

**Ví dụ:**
```cpp
#include <iostream>
#include <compare>
#include <string>
#include <vector>
#include <algorithm>

class Person {
private:
    std::string name;
    int age;
    
public:
    Person(std::string n, int a) : name(std::move(n)), age(a) {}
    
    // Spaceship operator tự động tạo ra ==, !=, <, <=, >, >=
    auto operator<=>(const Person& other) const {
        // So sánh theo age trước, sau đó theo name
        if (auto cmp = age <=> other.age; cmp != 0) {
            return cmp;
        }
        return name <=> other.name;
    }
    
    // Cần định nghĩa == riêng nếu muốn custom behavior
    bool operator==(const Person& other) const = default;
    
    // Getters for display
    const std::string& getName() const { return name; }
    int getAge() const { return age; }
};

// Custom comparison class
class Score {
private:
    int value;
    
public:
    Score(int v) : value(v) {}
    
    // Custom spaceship operator
    std::strong_ordering operator<=>(const Score& other) const {
        if (value < other.value) return std::strong_ordering::less;
        if (value > other.value) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }
    
    bool operator==(const Score& other) const = default;
    
    int getValue() const { return value; }
};

int main() {
    // Person comparison
    std::vector<Person> people = {
        Person("Alice", 30),
        Person("Bob", 25),
        Person("Charlie", 30),
        Person("Alice", 25)
    };
    
    std::cout << "Before sorting:" << std::endl;
    for (const auto& person : people) {
        std::cout << person.getName() << " (" << person.getAge() << ")" << std::endl;
    }
    
    // Sort using spaceship operator
    std::sort(people.begin(), people.end());
    
    std::cout << "\nAfter sorting:" << std::endl;
    for (const auto& person : people) {
        std::cout << person.getName() << " (" << person.getAge() << ")" << std::endl;
    }
    
    // Comparison operations
    Person p1("John", 30);
    Person p2("Jane", 25);
    
    std::cout << "\nComparisons:" << std::endl;
    std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
    std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
    std::cout << "p1 > p2: " << (p1 > p2) << std::endl;
    
    // Score comparison
    std::vector<Score> scores = {Score(85), Score(92), Score(78), Score(95)};
    
    std::sort(scores.begin(), scores.end());
    
    std::cout << "\nSorted scores:" << std::endl;
    for (const auto& score : scores) {
        std::cout << score.getValue() << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

---

## C++23 - Hoàn thiện và tối ưu {#cpp23}

### 1. Deducing this

**Khái niệm:** Cho phép template member functions tự động deduce kiểu của object (const, non-const, rvalue, lvalue).

**Ví dụ:**
```cpp
#include <iostream>
#include <string>
#include <utility>

class DataProcessor {
private:
    std::string data;
    
public:
    DataProcessor(std::string d) : data(std::move(d)) {}
    
    // Trước C++23 - cần 4 overloads
    // std::string& getData() &;
    // const std::string& getData() const &;
    // std::string&& getData() &&;
    // const std::string&& getData() const &&;
    
    // C++23 - chỉ cần 1 template function
    template<typename Self>
    auto&& getData(this Self&& self) {
        std::cout << "getData called on ";
        if constexpr (std::is_const_v<std::remove_reference_t<Self>>) {
            std::cout << "const ";
        }
        if constexpr (std::is_rvalue_reference_v<Self&&>) {
            std::cout << "rvalue";
        } else {
            std::cout << "lvalue";
        }
        std::cout << " object" << std::endl;
        
        return std::forward<Self>(self).data;
    }
    
    // Chaining operations với deducing this
    template<typename Self>
    auto&& process(this Self&& self) {
        std::cout << "Processing data..." << std::endl;
        // Modify data based on object type
        if constexpr (!std::is_const_v<std::remove_reference_t<Self>>) {
            self.data += " (processed)";
        }
        return std::forward<Self>(self);
    }
};

// CRTP pattern simplified với deducing this
template<typename Derived>
class Base {
public:
    template<typename Self>
    void interface(this Self&& self) {
        std::forward<Self>(self).implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        std::cout << "Derived implementation" << std::endl;
    }
};

int main() {
    // Lvalue object
    DataProcessor processor("Hello World");
    auto& data1 = processor.getData();  // Lvalue reference
    
    // Const lvalue object
    const DataProcessor constProcessor("Const Data");
    const auto& data2 = constProcessor.getData();  // Const lvalue reference
    
    // Rvalue object
    auto&& data3 = DataProcessor("Temp Data").getData();  // Rvalue reference
    
    // Chaining operations
    DataProcessor("Chain Test").process().getData();
    
    // CRTP example
    Derived d;
    d.interface();
    
    return 0;
}
```

### 2. std::expected

**Khái niệm:** Kiểu dữ liệu có thể chứa giá trị thành công hoặc error, thay thế cho exceptions trong nhiều trường hợp.

**Ví dụ:**
```cpp
#include <iostream>
#include <expected>
#include <string>
#include <fstream>

enum class FileError {
    NotFound,
    PermissionDenied,
    InvalidFormat
};

std::string errorToString(FileError error) {
    switch (error) {
        case FileError::NotFound: return "File not found";
        case FileError::PermissionDenied: return "Permission denied";
        case FileError::InvalidFormat: return "Invalid format";
        default: return "Unknown error";
    }
}

// Function returning expected
std::expected<std::string, FileError> readFile(const std::string& filename) {
    if (filename.empty()) {
        return std::unexpected(FileError::InvalidFormat);
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        return std::unexpected(FileError::NotFound);
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    
    return content;
}

std::expected<int, std::string> divide(int a, int b) {
    if (b == 0) {
        return std::unexpected("Division by zero");
    }
    return a / b;
}

// Chaining operations với expected
std::expected<int, std::string> processNumber(const std::string& str) {
    try {
        int num = std::stoi(str);
        if (num < 0) {
            return std::unexpected("Negative number not allowed");
        }
        return num * 2;
    } catch (const std::exception&) {
        return std::unexpected("Invalid number format");
    }
}

int main() {
    // File reading example
    auto result = readFile("test.txt");
    if (result) {
        std::cout << "File content: " << *result << std::endl;
    } else {
        std::cout << "Error: " << errorToString(result.error()) << std::endl;
    }
    
    // Division example
    auto divResult = divide(10, 2);
    if (divResult) {
        std::cout << "Division result: " << *divResult << std::endl;
    } else {
        std::cout << "Division error: " << divResult.error() << std::endl;
    }
    
    // Error case
    auto divError = divide(10, 0);
    if (!divError) {
        std::cout << "Expected error: " << divError.error() << std::endl;
    }
    
    // Chaining with transform
    auto processResult = processNumber("42")
        .transform([](int n) { return n + 10; })
        .transform([](int n) { return n * 2; });
    
    if (processResult) {
        std::cout << "Processed result: " << *processResult << std::endl;
    } else {
        std::cout << "Processing error: " << processResult.error() << std::endl;
    }
    
    return 0;
}
```

### 3. std::mdspan

**Khái niệm:** Multi-dimensional array view cho việc xử lý dữ liệu nhiều chiều hiệu quả.

**Ví dụ:**
```cpp
#include <iostream>
#include <mdspan>
#include <vector>
#include <numeric>

int main() {
    // 2D matrix example
    std::vector<int> data(12);
    std::iota(data.begin(), data.end(), 1);  // Fill with 1, 2, 3, ..., 12
    
    // Create 3x4 matrix view
    std::mdspan<int, std::dextents<size_t, 2>> matrix(data.data(), 3, 4);
    
    std::cout << "3x4 Matrix:" << std::endl;
    for (size_t i = 0; i < matrix.extent(0); ++i) {
        for (size_t j = 0; j < matrix.extent(1); ++j) {
            std::cout << matrix[i, j] << " ";
        }
        std::cout << std::endl;
    }
    
    // 3D tensor example
    std::vector<double> tensorData(24);
    std::iota(tensorData.begin(), tensorData.end(), 1.0);
    
    // Create 2x3x4 tensor view
    std::mdspan<double, std::dextents<size_t, 3>> tensor(tensorData.data(), 2, 3, 4);
    
    std::cout << "\n2x3x4 Tensor:" << std::endl;
    for (size_t i = 0; i < tensor.extent(0); ++i) {
        std::cout << "Layer " << i << ":" << std::endl;
        for (size_t j = 0; j < tensor.extent(1); ++j) {
            for (size_t k = 0; k < tensor.extent(2); ++k) {
                std::cout << tensor[i, j, k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    // Subspan example
    auto submatrix = std::submdspan(matrix, std::pair{1, 3}, std::pair{1, 3});
    std::cout << "Submatrix [1:3, 1:3]:" << std::endl;
    for (size_t i = 0; i < submatrix.extent(0); ++i) {
        for (size_t j = 0; j < submatrix.extent(1); ++j) {
            std::cout << submatrix[i, j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
```

### 4. std::print và std::format improvements

**Khái niệm:** Cải tiến formatting và printing với performance tốt hơn và API đơn giản hơn.

**Ví dụ:**
```cpp
#include <iostream>
#include <print>
#include <format>
#include <vector>
#include <chrono>

struct Person {
    std::string name;
    int age;
    double salary;
};

// Custom formatter cho Person
template<>
struct std::formatter<Person> {
    constexpr auto parse(format_parse_context& ctx) {
        return ctx.begin();
    }
    
    auto format(const Person& p, format_context& ctx) const {
        return std::format_to(ctx.out(), "{} (age: {}, salary: ${:.2f})", 
                             p.name, p.age, p.salary);
    }
};

int main() {
    // Basic std::print usage
    std::print("Hello, {}!\n", "World");
    std::print("Number: {}, Float: {:.2f}\n", 42, 3.14159);
    
    // Formatted output
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::print("Numbers: {}\n", numbers);
    
    // Custom formatting
    Person person{"Alice", 30, 75000.50};
    std::print("Employee: {}\n", person);
    
    // Date and time formatting
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::print("Current time: {:%Y-%m-%d %H:%M:%S}\n", 
               std::chrono::system_clock::from_time_t(time_t));
    
    // Format string to variable
    std::string formatted = std::format("Processing {} items with {:.1f}% completion", 
                                       100, 75.5);
    std::print("Status: {}\n", formatted);
    
    // Table formatting
    std::vector<Person> employees = {
        {"John", 25, 50000},
        {"Jane", 32, 65000},
        {"Bob", 28, 55000}
    };
    
    std::print("Employee List:\n");
    std::print("{:<10} {:<5} {:<10}\n", "Name", "Age", "Salary");
    std::print("{}\n", std::string(25, '-'));
    
    for (const auto& emp : employees) {
        std::print("{:<10} {:<5} ${:<9.2f}\n", emp.name, emp.age, emp.salary);
    }
    
    return 0;
}
```

### 5. Multidimensional subscript operator

**Khái niệm:** Cho phép sử dụng multiple indices trong subscript operator [].

**Ví dụ:**
```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Matrix {
private:
    std::vector<T> data;
    size_t rows, cols;
    
public:
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c) {}
    
    Matrix(size_t r, size_t c, const T& value) : rows(r), cols(c), data(r * c, value) {}
    
    // C++23 multidimensional subscript
    T& operator[](size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix index out of range");
        }
        return data[row * cols + col];
    }
    
    const T& operator[](size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix index out of range");
        }
        return data[row * cols + col];
    }
    
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    
    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << (*this)[i, j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

template<typename T>
class Tensor3D {
private:
    std::vector<T> data;
    size_t dim1, dim2, dim3;
    
public:
    Tensor3D(size_t d1, size_t d2, size_t d3) 
        : dim1(d1), dim2(d2), dim3(d3), data(d1 * d2 * d3) {}
    
    // 3D subscript operator
    T& operator[](size_t i, size_t j, size_t k) {
        return data[i * dim2 * dim3 + j * dim3 + k];
    }
    
    const T& operator[](size_t i, size_t j, size_t k) const {
        return data[i * dim2 * dim3 + j * dim3 + k];
    }
    
    void print() const {
        for (size_t i = 0; i < dim1; ++i) {
            std::cout << "Layer " << i << ":" << std::endl;
            for (size_t j = 0; j < dim2; ++j) {
                for (size_t k = 0; k < dim3; ++k) {
                    std::cout << (*this)[i, j, k] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // 2D Matrix example
    Matrix<int> matrix(3, 4);
    
    // Fill matrix
    int value = 1;
    for (size_t i = 0; i < matrix.getRows(); ++i) {
        for (size_t j = 0; j < matrix.getCols(); ++j) {
            matrix[i, j] = value++;  // C++23 multidimensional subscript
        }
    }
    
    std::cout << "3x4 Matrix:" << std::endl;
    matrix.print();
    
    // Access individual elements
    std::cout << "Element at [1,2]: " << matrix[1, 2] << std::endl;
    
    // Modify elements
    matrix[0, 0] = 100;
    std::cout << "After modification:" << std::endl;
    matrix.print();
    
    // 3D Tensor example
    Tensor3D<double> tensor(2, 3, 2);
    
    // Fill tensor
    double val = 1.0;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            for (size_t k = 0; k < 2; ++k) {
                tensor[i, j, k] = val++;
            }
        }
    }
    
    std::cout << "2x3x2 Tensor:" << std::endl;
    tensor.print();
    
    std::cout << "Element at [1,1,0]: " << tensor[1, 1, 0] << std::endl;
    
    return 0;
}
```

---

## So sánh và Migration Guide {#migration}

### Migration từ C++14/17 sang C++20

**Concepts thay thế SFINAE:**

```cpp
// C++17 - SFINAE approach
template<typename T>
typename std::enable_if_t<std::is_integral_v<T>, T>
multiply(T a, T b) {
    return a * b;
}

// C++20 - Concepts approach
template<std::integral T>
T multiply(T a, T b) {
    return a * b;
}
```

**Ranges thay thế algorithm + iterator:**

```cpp
// C++17 approach
std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
std::vector<int> result;

std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(result),
             [](int n) { return n % 2 == 0; });

std::transform(result.begin(), result.end(), result.begin(),
               [](int n) { return n * n; });

// C++20 approach
auto result = numbers 
    | std::views::filter([](int n) { return n % 2 == 0; })
    | std::views::transform([](int n) { return n * n; });
```

### Migration từ C++20 sang C++23

**std::expected thay thế exception handling:**

```cpp
// C++20 approach
std::optional<int> divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

// C++23 approach
std::expected<int, std::string> divide(int a, int b) {
    if (b == 0) return std::unexpected("Division by zero");
    return a / b;
}
```

---

## Best Practices và Performance {#best-practices}

### Performance Considerations

1. **Structured Bindings Performance:**
```cpp
// Tốt - avoid copies
const auto& [x, y] = getPoint();

// Tránh - unnecessary copy
auto [x, y] = getPoint();
```

2. **Ranges Lazy Evaluation:**
```cpp
// Efficient - lazy evaluation
auto result = data 
    | std::views::filter(predicate)
    | std::views::transform(transform_func)
    | std::views::take(10);

// Less efficient - eager evaluation
std::vector<T> temp1, temp2, temp3;
std::copy_if(data.begin(), data.end(), std::back_inserter(temp1), predicate);
// ... more steps
```

3. **Concepts Compile-time Benefits:**
```cpp
// Better error messages and compile-time optimization
template<Numeric T>
void process(T value) {
    // Compiler knows T is numeric
}
```

### Memory Management Best Practices

```cpp
// RAII với modern C++
class ResourceManager {
    std::unique_ptr<Resource> resource;
    
public:
    ResourceManager() : resource(std::make_unique<Resource>()) {}
    
    // Move semantics
    ResourceManager(ResourceManager&&) = default;
    ResourceManager& operator=(ResourceManager&&) = default;
    
    // Disable copy
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
};
```

---

## Ứng dụng thực tế {#applications}

### 1. Web Server với Coroutines

```cpp
#include <coroutine>
#include <string>
#include <unordered_map>

struct HttpRequest {
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

struct HttpResponse {
    int status_code;
    std::string body;
    std::unordered_map<std::string, std::string> headers;
};

// Async request handler
Task<HttpResponse> handleRequest(const HttpRequest& request) {
    if (request.path == "/api/users") {
        // Simulate database query
        co_await queryDatabase("SELECT * FROM users");
        co_return HttpResponse{200, R"({"users": []})", {{"Content-Type", "application/json"}}};
    }
    
    co_return HttpResponse{404, "Not Found", {}};
}
```

### 2. Data Processing Pipeline

```cpp
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

struct LogEntry {
    std::string timestamp;
    std::string level;
    std::string message;
    std::string source;
};

// Modern C++ data processing
auto processLogs(const std::vector<LogEntry>& logs) {
    return logs
        | std::views::filter([](const LogEntry& entry) {
            return entry.level == "ERROR" || entry.level == "WARN";
        })
        | std::views::transform([](const LogEntry& entry) {
            return std::format("[{}] {}: {}", entry.timestamp, entry.level, entry.message);
        })
        | std::ranges::to<std::vector>();
}
```

### 3. Mathematical Computing với mdspan

```cpp
#include <mdspan>
#include <vector>
#include <numeric>

// Matrix operations với mdspan
template<typename T>
void matrixMultiply(
    std::mdspan<const T, std::dextents<size_t, 2>> A,
    std::mdspan<const T, std::dextents<size_t, 2>> B,
    std::mdspan<T, std::dextents<size_t, 2>> C) {
    
    for (size_t i = 0; i < A.extent(0); ++i) {
        for (size_t j = 0; j < B.extent(1); ++j) {
            T sum = 0;
            for (size_t k = 0; k < A.extent(1); ++k) {
                sum += A[i, k] * B[k, j];
            }
            C[i, j] = sum;
        }
    }
}
```

### 4. Error Handling với std::expected

```cpp
#include <expected>
#include <string>
#include <fstream>

enum class DatabaseError {
    ConnectionFailed,
    QueryFailed,
    InvalidData
};

class DatabaseManager {
public:
    std::expected<std::string, DatabaseError> queryUser(int userId) {
        if (userId <= 0) {
            return std::unexpected(DatabaseError::InvalidData);
        }
        
        // Simulate database query
        if (!isConnected()) {
            return std::unexpected(DatabaseError::ConnectionFailed);
        }
        
        return std::format(R"({{"id": {}, "name": "User {}"}})", userId, userId);
    }
    
private:
    bool isConnected() const { return true; }
};
```

### 5. Real-time Game Development

```cpp
#include <concepts>
#include <ranges>
#include <chrono>

template<typename T>
concept Drawable = requires(T t) {
    t.draw();
    t.getPosition();
};

template<typename T>
concept Updatable = requires(T t, float deltaTime) {
    t.update(deltaTime);
};

template<typename T>
concept GameObject = Drawable<T> && Updatable<T>;

class GameEngine {
    std::vector<std::unique_ptr<GameObject auto>> gameObjects;
    
public:
    void gameLoop() {
        auto lastTime = std::chrono::high_resolution_clock::now();
        
        while (running) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
            lastTime = currentTime;
            
            // Update all game objects
            for (auto& obj : gameObjects) {
                obj->update(deltaTime);
            }
            
            // Render visible objects
            auto visibleObjects = gameObjects 
                | std::views::filter([](const auto& obj) { 
                    return isVisible(obj->getPosition()); 
                });
            
            for (const auto& obj : visibleObjects) {
                obj->draw();
            }
        }
    }
    
private:
    bool running = true;
    bool isVisible(const auto& position) { return true; }
};
```

---

## Kết luận

Các tính năng mới từ C++17 đến C++23 mang lại những cải tiến đáng kể:

### Tính năng nổi bật:
- **C++17**: Structured bindings, std::optional, std::variant, if constexpr
- **C++20**: Concepts, Coroutines, Ranges, Modules, Spaceship operator
- **C++23**: Deducing this, std::expected, std::mdspan, std::print

### Lợi ích chính:
1. **Code rõ ràng hơn**: Concepts thay thế SFINAE phức tạp
2. **Performance tốt hơn**: Ranges lazy evaluation, compile-time optimization
3. **Error handling tốt hơn**: std::expected, std::optional
4. **Functional programming**: Ranges và coroutines
5. **Modern syntax**: Structured bindings, deducing this

### Khuyến nghị:
- Migrate từ từ từ C++17 → C++20 → C++23
- Ưu tiên sử dụng concepts thay cho SFINAE
- Sử dụng ranges cho data processing
- Áp dụng coroutines cho async programming
- Sử dụng std::expected cho error handling

Các tính năng này không chỉ làm cho C++ hiện đại hơn mà còn an toàn và hiệu quả hơn, giúp developers viết code chất lượng cao với ít lỗi và dễ bảo trì hơn.