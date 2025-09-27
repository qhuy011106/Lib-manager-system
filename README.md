# HỆ THỐNG QUẢN LÝ THƯ VIỆN

Phần mềm quản lý thư viện được phát triển bằng C++ giúp quản lý sách, thành viên và quá trình mượn/trả sách hiệu quả.

## 📚 Tính năng chính

### 👥 Quản lý thành viên
- Thêm, xóa, sửa thông tin thành viên
- Tìm kiếm thành viên theo ID, tên
- Xem lịch sử mượn sách của thành viên

### 📖 Quản lý sách
- Thêm, xóa, cập nhật thông tin sách
- Tìm kiếm sách theo tiêu đề, tác giả, thể loại
- Quản lý số lượng sách tồn kho
- Theo dõi tình trạng sách (có sẵn, đã mượn)
## 📦 Cài đặt và biên dịch

### Yêu cầu hệ thống
- Compiler C++ (g++, clang++, hoặc Visual Studio)
- CMake (tuỳ chọn)

### Biên dịch với g++
```bash
g++ -o library_manager main.cpp Book.cpp Member.cpp Transaction.cpp
