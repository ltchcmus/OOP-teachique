# C++ Modern Techniques Showcase

## Mục tiêu

Project này trình bày các kỹ thuật lập trình hiện đại trong C++ (từ C++17 đến C++23) thông qua menu tương tác. Khi chọn một kỹ thuật, bạn sẽ thấy mô tả và code mẫu minh họa.

## Các kỹ thuật nổi bật
- Structured Bindings
- if constexpr
- std::optional
- std::variant
- std::any
- std::filesystem
- std::string_view
- Fold Expressions
- Inline Variables
- std::shared_mutex
- Concepts
- Ranges
- Coroutines
- std::span
- Three-way comparison (spaceship operator)
- Modules
- std::format
- std::expected
- deducing this
- std::print

## Design Pattern & SOLID
- Factory Pattern cho tạo đối tượng kỹ thuật
- Interface cho mỗi kỹ thuật
- Tách riêng menu, input helper, ...
- Mỗi kỹ thuật là một class riêng biệt

## Build & Run

Yêu cầu: CMake >= 3.20, compiler hỗ trợ C++23

```sh
mkdir build && cd build
cmake .. && make
./cpp_modern_techniques
```

## Đóng góp
Bạn có thể thêm kỹ thuật mới bằng cách tạo class kế thừa ITechnique và đăng ký vào TechniqueFactory. 