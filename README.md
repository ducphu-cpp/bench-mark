# BÁO CÁO ĐỒ ÁN: SORT BENCHMARK

## 1. Thông tin sinh viên
* **Tên môn học:** Cấu trúc dữ liệu và Giải thuật
* **Thời gian học:** Học kỳ 2 - Năm học 2025-2026

### Giảng viên hướng dẫn:
1. **Họ và tên:** Huỳnh Lâm Hải Đăng
2. **Họ và tên:** Phạm Trọng Nghĩa
3. **Họ và tên:** Nguyễn Ngọc Đức

### Danh sách thành viên nhóm:
1. **Họ và tên:** Huỳnh Đức Phú - **MSSV:** 25120415
2. **Họ và tên:** Nguyễn Minh Nhật - **MSSV:** 25120403
3. **Họ và tên:** Nguyễn Hữu Thịnh - **MSSV:** 25120443

---

## 2. Thuật toán cài đặt tốt nhất ở lần chạy đầu tiên (Lần 1)
* **Thuật toán sử dụng:** MSD Radix Sort kết hợp Insertion Sort (ngưỡng $N \le 25$).
* **Các phương thức tối ưu hóa liên quan:**
  * Phân loại toàn bộ mảng chuỗi đầu vào theo độ dài dựa trên cơ chế Counting Sort (`len_count` và `len_offset`) trước khi áp dụng thuật toán Radix Sort ký tự. Phương pháp này thu hẹp tối đa không gian xét dữ liệu, chỉ thực hiện sắp xếp trên các nhóm chuỗi có cùng độ dài.
  * Tối ưu hóa hệ thống I/O bằng cách đọc toàn bộ luồng dữ liệu đầu vào từ `stdin` vào một mảng `in_buf` duy nhất thông qua hàm `fread`.
  * Khai báo một cấu trúc gọn nhẹ `StringRef` chứa con trỏ trỏ trực tiếp vào vùng đệm `in_buf`. Quá trình sắp xếp và hoán vị vị trí chỉ thao tác trên con trỏ và độ dài chuỗi, triệt tiêu hoàn toàn chi phí sao chép nội dung chuỗi (string copy).
* **Lý giải nguyên nhân tối ưu:** Do độ dài các chuỗi trong bài toán tương đối ngắn ($10 \le \text{length} \le 100$), việc chia nhóm theo độ dài giúp giảm thiểu tối đa số tầng đệ quy sâu không cần thiết. Đồng thời, kỹ thuật sử dụng mảng con trỏ trỏ vào bộ đệm tuần tự giúp giữ dữ liệu chuỗi luôn nằm tập trung trên Cache của CPU, hạn chế hiện tượng Cache Miss so với việc dùng `std::string` cấp phát động rải rác trên vùng nhớ Heap.

---

## 3. Cách thức sinh test case (Trong file test_gen.cpp)
* **Cách thức cài đặt:** Bộ sinh mã `test_gen.cpp` hỗ trợ giao diện dòng lệnh (CLI) nhận vào đối số cấu hình loại bài toán (`int`, `strlexi`, `strlenlexi`) và số thứ tự bộ test (từ 1 đến 5). Dữ liệu chuỗi được sinh ngẫu nhiên từ ký tự 'a' đến 'z' bằng các hàm sinh số ngẫu nhiên tiêu chuẩn trong STL C++23, cấu trúc xuất ra đảm bảo dòng đầu tiên chứa số lượng phần tử $N$ và các dòng sau là các chuỗi ký tự phân tách bằng dấu xuống dòng.
* **Thuật toán mục tiêu cấu trúc test nhắm tới:** Thuật toán Quick Sort xử lý chuỗi thông thường hoặc các thuật toán so sánh chuỗi sử dụng hàm `strcmp` quét từ vị trí ký tự đầu tiên.
* **Lý do bộ test case làm tăng thời gian chạy:** Đối với các bài toán so sánh chuỗi thông thường, điểm yếu chí mạng nằm ở chi phí so sánh ký tự $O(L)$. Bộ sinh test case được thiết kế đặc biệt để sinh ra số lượng lớn các chuỗi có **cùng độ dài** và sở hữu **tiền tố trùng lặp cực kỳ dài** (ví dụ: chuỗi dài 100 ký tự nhưng có đến 90 ký tự đầu tiên giống hệt nhau, chỉ khác biệt ở vài ký tự cuối). Khi các thuật toán sắp xếp thông thường gọi `strcmp`, chúng bắt buộc phải duyệt đi duyệt lại chuỗi tiền tố lặp này rất nhiều lần, khiến độ phức tạp thuật toán bị đẩy từ $O(L \cdot N \log N)$ tiệm cận mức tệ nhất là $O(L \cdot N^2)$, dễ dàng gây vượt quá giới hạn thời gian (TLE).

---

## 4. Thuật toán cài đặt tốt nhất ở lần thứ hai (Tối ưu nâng cao)
* **Các phương thức tối ưu hóa nâng cao:**
  * **Triệt tiêu hàm `strcmp` tiêu chuẩn của C:** Thay thế bằng một vòng lặp kiểm tra ký tự thủ công bắt đầu trực tiếp từ vị trí chỉ mục thứ `d` (vị trí đang phân tách đệ quy hiện tại của MSD Radix Sort). Thao tác nhảy cóc này loại bỏ hoàn toàn việc duyệt lại các ký tự tiền tố chung vốn đã được phân loại chính xác ở các tầng đệ quy trước đó.
  * **Chuyển dịch hoàn toàn sang mảng tĩnh (Static Arrays):** Khai báo cố định kích thước tối đa của dữ liệu ($10^5$) và kích thước luồng đệm ngay từ khi biên dịch. Phương pháp này giúp CPU tối ưu hóa việc nạp dữ liệu trực tiếp vào phân đoạn bộ nhớ tĩnh (Static Segment), bỏ qua toàn bộ chi phí quản lý bộ nhớ (overhead) của các con trỏ thông minh hay `std::vector` động tại thời điểm thực thi.
  * **Tối ưu hóa bộ đệm xuất dữ liệu (Output Buffer):** Thay vì sử dụng `std::cout` hoặc gọi lệnh ghi đĩa rải rác, toàn bộ chuỗi kết quả sau khi sắp xếp được chuyển đổi và nối trực tiếp vào một mảng bộ đệm đầu ra `out_buf` lớn. Khi chương trình kết thúc, toàn bộ kết quả được đẩy ra màn hình một lần duy nhất bằng lệnh `fwrite`.
* **Hiệu quả tối ưu so với lần 1:** Các cải tiến nâng cao tập trung triệt để vào việc giảm thiểu chi phí truy xuất bộ nhớ thừa và tăng tốc luồng xuất dữ liệu (Output). Kết quả thực tế khi chấm trên hệ thống Codeforces cho thấy thời gian thực thi tối đa của chương trình đã giảm mạnh từ mức **375ms** (ở lần chạy đầu tiên) xuống chỉ còn **171ms** (ở lần tối ưu nâng cao).
