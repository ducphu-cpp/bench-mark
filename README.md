# BÁO CÁO PHÂN TÍCH HIỆU NĂNG THUẬT TOÁN SẮP XẾP HỆ THỐNG

## 1. THÔNG TIN SINH VIÊN & NHÓM THỰC HIỆN
* **Tên môn học:** Cấu trúc dữ liệu và Giải thuật
* **Thời gian học:** Học kỳ 2 - Năm học 2025-2026
* **Đề tài đồ án:** Đánh giá hiệu năng và Tối ưu hóa tiệm cận thuật toán sắp xếp (Integer & String Sort)

### Danh sách thành viên nhóm:
1. **Họ và tên:** [Tên thành viên 1] — **MSSV:** [MSSV thành viên 1]
2. **Họ và tên:** [Tên thành viên 2] — **MSSV:** [MSSV thành viên 2]
3. **Họ và tên:** [Tên thành viên 3] — **MSSV:** [MSSV thành viên 3]

---

## 2. THUẬT TOÁN CÀI ĐẶT Ở LẦN 1: CƠ SỞ PHÂN LOẠI TUYẾN TÍNH

Ở lần chạy đầu tiên, mục tiêu của nhóm là thay thế các thuật toán so sánh thông thường có độ phức tạp $O(N \log N)$ bằng các họ thuật toán phân phối (Distribution-based) nhằm đạt được độ phức tạp thời gian tiệm cận mức tuyến tính $O(N)$ dựa trên tính chất miền dữ liệu.

### 2.1. Chi tiết giải thuật từng bài toán
* **Bài A (Integer Sort):** Nhóm cài đặt thuật toán lai (Hybrid Sort). Chương trình thực hiện một lượt quét tìm giá trị nhỏ nhất ($mn$) và lớn nhất ($mx$).
  * Nếu dải giá trị cực nhỏ ($mx - mn + 1 \le 2 \cdot 10^6$), áp dụng **Counting Sort** với độ phức tạp thời gian tối ưu tuyệt đối $O(N)$.
  * Nếu dải giá trị lớn, chương trình chuyển sang **LSD (Least Significant Digit) Radix Sort**. Thuật toán chia số nguyên 32-bit thành 4 phân đoạn (mỗi phân đoạn 8-bit, cơ số 256). Tiến hành 4 lượt quét (4-pass) từ byte thấp đến byte cao để phân loại phần tử vào các xô (buckets).
* **Bài B (Lexicographic Sort):** Triển khai thuật toán **MSD (Most Significant Digit) Radix Sort** đệ quy. Thuật toán tiến hành phân loại mảng từ trái qua phải dựa trên ký tự tại vị trí index `pos`. Tại mỗi tầng đệ quy, nếu kích thước mảng con thu hẹp xuống mức $R - L \le 24$, chương trình ngắt đệ quy và chuyển sang dùng **Insertion Sort** cục bộ để sắp xếp các chuỗi con nhằm giảm bớt chi phí chia nhỏ dữ liệu.
* **Bài C (Length-aware Lexicographic Sort):** Tận dụng giới hạn độ dài chuỗi cố định từ 10 đến 100, nhóm áp dụng **Bucket Sort** chia dữ liệu thành 101 xô tương ứng với từng độ dài. Đối với các chuỗi có cùng độ dài trong một xô, nhóm áp dụng **MSD Radix Sort ngược**, thực hiện quét đếm ký tự phân phối từ vị trí cuối chuỗi (`pos = l - 1`) lùi dần về vị trí đầu chuỗi (index 0).

### 2.2. Phân tích độ phức tạp (Complexity) và Điểm nghẽn ở Lần 1
* **Độ phức tạp thời gian (Time Complexity):**
  * *Bài A:* Counting Sort đạt $O(N + \text{range})$. LSD Radix Sort đạt $O(4 \cdot (N + 256)) \approx O(N)$.
  * *Bài B & C:* MSD Radix Sort đạt $O(L \cdot (N + 26))$ với $L$ là độ dài trung bình của chuỗi ký tự.
* **Độ phức tạp không gian (Space Complexity):** Cả 3 bài toán đều đòi hỏi mảng phụ `tmp` hoặc `b` có kích thước bằng $O(N)$ để phục vụ việc phân phối lại phần tử, cùng với các mảng đếm tần suất cố định $O(\text{cơ số})$.
* **Điểm nghẽn thuật toán khiến thời gian chạy chạm mốc 375ms:**
  1. *Số lượt lặp quá nhiều (Bài A):* Việc thực hiện tới 4 pass (mỗi pass 8-bit) buộc thuật toán phải duyệt qua toàn bộ $10^5$ phần tử và sao chép qua lại giữa hai mảng đúng 4 lần liên tiếp.
  2. *Sự trùng lặp thao tác kiểm tra ký tự (Bài B):* Khi thuật toán rẽ nhánh sang *Insertion Sort* tại các mảng con, hàm so sánh chuỗi nền tảng `smallerFrom` vẫn tiến hành kiểm tra tuần tự lại từ đầu, làm xuất hiện nhiều phép so sánh thừa đối với các ký tự tiền tố chung đã được Radix Sort phân loại trước đó.

---

## 3. PHÂN TÍCH CHIẾN LƯỢC CỦA BỘ SÌNH TEST CASE (FILE TEST_GEN.CPP)

Bộ sinh mã `test_gen.cpp` được lập trình theo chuẩn C++23, tiếp nhận cấu hình đầu vào thông qua đối số dòng lệnh CLI để sinh ra 5 bộ test case đặc thù cho từng loại dữ liệu (`int`, `strlexi`, `strlenlexi`). Mục tiêu toán học của bộ sinh test là đưa các giải thuật thông thường vào trạng thái giới hạn (Worst-case complexity).

### 3.1. Cơ chế bẻ gãy hiệu năng giải thuật số nguyên (`int`)
* *Test 3 & 4 (Dữ liệu tăng dần / giảm dần tuần tự):* Nhắm trực tiếp vào cấu trúc phân hoạch của thuật toán **Quick Sort** phổ thông. Nếu Quick Sort chọn phần tử biên (đầu hoặc cuối) làm chốt (pivot), mảng dữ liệu sẽ bị phân tách lệch hoàn toàn (một bên có 0 phần tử, một bên có $N-1$ phần tử). Điều này biến đổi độ phức tạp lý thuyết từ $O(N \log N)$ thành **$O(N^2)$**, gây tràn bộ nhớ ngăn xếp đệ quy hệ thống (Stack Overflow) hoặc vượt quá thời gian chạy (TLE).
* *Test 5 (Mật độ giá trị trùng lặp cao):* Sinh ra $10^5$ số nhưng chỉ nằm trong khoảng từ 1 đến 10. Bộ test này phá hủy các giải thuật Quick Sort phân hoạch 2 vùng (2-way partition) không có cơ chế thu hẹp phân đoạn bằng nhau, khiến chốt liên tục bị chọn sai lệch vùng.

### 3.2. Cơ chế bẻ gãy hiệu năng giải thuật chuỗi (`strlexi` / `strlenlexi`)
* *Test 2 (Đồng nhất hoàn toàn độ dài chuỗi):* Triệt tiêu hoàn toàn lợi thế phân loại thô theo xô độ dài ở bước đầu tiên của bài C, ép thuật toán phải dồn toàn bộ tải xử lý vào hàm sắp xếp ký tự phía sau.
* *Test 3 (Chiến lược ANTI-STRCMP - Tiền tố trùng lặp sâu):* Nhóm thiết kế bộ test sinh ra hàng vạn chuỗi ký tự có **95 ký tự tiền tố đầu tiên giống hệt nhau**, và chỉ bắt đầu xuất hiện ký tự khác biệt ngẫu nhiên ở **5 ký tự cuối cùng**.
  * **Hệ quả bẻ gãy toán học:** Đối với các giải thuật sắp xếp chuỗi thông thường sử dụng hàm `strcmp` hoặc toán tử so sánh `<` tiêu chuẩn, mỗi phép so sánh giữa hai chuỗi không còn tốn chi phí hằng số $O(1)$ nữa. Hàm `strcmp` bắt buộc phải chạy một vòng lặp tuyến tính duyệt qua toàn bộ 95 ký tự trùng nhau để xác định điểm khác biệt. Chi phí cho một phép so sánh bị đẩy lên mức tối đa là $O(L)$ (với $L$ là độ dài chuỗi). Tổng độ phức tạp toán học của hệ thống bị phóng đại từ $O(N \log N)$ lên thành **$O(L \cdot N \log N)$**, trực tiếp làm sập hiệu năng và gây lỗi TLE trên hệ thống chấm.

---

## 4. THUẬT TOÁN TỐI ƯU Ở LẦN 2: THAY ĐỔI CẤU TRÚC VÀ GIẢM ĐỘ PHỨC TẠP TIỆM CẬN

Nhận diện được các điểm nghẽn toán học ở lần 1, nhóm đã thực hiện tái cấu trúc kịch khung giải thuật ở lần 2 nhằm tối ưu hóa số bước lặp và loại bỏ hoàn toàn các phép toán so sánh trùng lặp.

### 4.1. Các phương thức tối ưu hóa thuật toán nâng cao
* **Bài A (Nâng cấp cấu trúc số Pass của Radix Sort):** Nhóm thay thế hoàn toàn giải thuật 4-pass bằng phiên bản **Radix Sort 2-pass (16-bit cho mỗi pass xử lý)**. Cơ số đếm được mở rộng từ 256 ($2^8$) lên thành 65536 ($2^{16}$).
  * *Cơ chế hoạt động:* Sử dụng toán tử bitwise mặt nạ `a[i] & 0xFFFF` để đếm và phân loại toàn bộ mảng theo 16-bit thấp ở Pass 1, sau đó dịch bit `(b[i] >> 16) & 0xFFFF` để phân loại theo 16-bit cao ở Pass 2. Để xử lý số nguyên có dấu, nhóm thực hiện phép toán XOR bit dấu `a[i] ^= 0x80000000` ở đầu chương trình để đồng quy toàn bộ dải số về dạng không dấu, giúp thuật toán đếm vị trí chạy chính xác tuyệt đối mà không cần chia thêm nhánh điều kiện.
* **Bài B (Cơ chế nhảy cóc ký tự tiền tố chung - Prefix Skipping):** Nhóm thay đổi mô hình lưu trữ chuỗi rời rạc thành cấu trúc **Flat-Memory Buffer** (Mảng ký tự phẳng liên tục). Khi thực hiện chia nhỏ đệ quy bằng MSD Radix Sort, biến chỉ số chiều sâu `depth` (vị trí ký tự hiện tại đang xét) được truyền liên tục vào hàm.
  * *Sự tối ưu về mặt so sánh:* Tại các mảng con có kích thước nhỏ ($\le 16$), hệ thống chuyển sang dùng *Insertion Sort*. Tuy nhiên, thay vì gọi lệnh so sánh từ ký tự đầu tiên, nhóm dịch chuyển con trỏ đọc trực tiếp đến vị trí: `strcmp(buf + ptrs[j] + depth, buf + key + depth)`. Cơ chế này loại bỏ hoàn toàn việc duyệt lại đoạn tiền tố trùng nhau đã biết, giúp hạ chi phí so sánh từ mức tuyến tính $O(L)$ về mức hằng số $O(1)$, vô hiệu hóa hoàn toàn sức tàn phá của bộ test ANTI-STRCMP.
* **Bài C (Khử đệ quy bằng ngăn xếp tĩnh):** Tại phân đoạn xử lý sắp xếp từ điển phía trong các xô độ dài, nhóm loại bỏ hoàn toàn cấu trúc đệ quy hệ thống. Nhóm tự xây dựng giải thuật **Iterative Quick Sort (Quick Sort vòng lặp)**, tự quản lý vùng biên phân hoạch bằng hai mảng ngăn xếp tĩnh độc lập `stack_left` và `stack_right`. Khi vùng phân hoạch thu hẹp xuống mức $\le 15$ phần tử, giải thuật rẽ nhánh sang *Insertion Sort* để dứt điểm mảng con.

### 4.2. So sánh đối chiếu toán học về độ phức tạp giữa hai lần chạy

1. **Giảm thiểu số lượng toán tử cơ bản (Operation Reduction):** Việc chuyển đổi từ 4-pass xuống 2-pass ở bài A giúp giảm chính xác **50% số lần duyệt** qua mảng dữ liệu $10^5$ phần tử và giảm một nửa số thao tác ghi dữ liệu từ mảng tạm ngược về mảng gốc.
2. **Hạ độ phức tạp trong điều kiện tệ nhất (Worst-case Optimization):** Nhờ cơ chế cộng dồn chỉ số chiều sâu `depth` và so sánh nhảy cóc ở bài B, độ phức tạp thời gian trong kịch bản đối phó với bộ test tiền tố trùng lặp sâu giảm từ mức nguy hiểm $O(L \cdot N \log N)$ xuống mức an toàn là $O(N \cdot L)$, tiết kiệm hàng triệu phép so sánh ký tự trên toàn mạch chạy.
3. **Triệt tiêu Overhead cấp phát hệ thống:** Khử hoàn toàn cơ chế đệ quy tự động của trình biên dịch ở bài C giúp ngăn chặn việc sinh ra các khung ngăn xếp (Stack Frames) liên tục, đưa độ phức tạp không gian phụ trợ từ mức biến thiên phụ thuộc dữ liệu về mức hằng số cố định $O(1)$ trên ngăn xếp hệ thống.

Bảng tổng hợp cải tiến toán học và thời gian thực thi thực tế trên Codeforces:

| Tiêu chí phân tích | Phiên bản Lần 1 (Cơ bản) | Phiên bản Lần 2 (Tối ưu nâng cao) |
| :--- | :--- | :--- |
| **Số pass lặp (Bài A)** | 4 lượt quét (8-bit / pass) | **2 lượt quét (16-bit / pass)** |
| **Độ phức tạp so sánh (Bài B)** | Tuyến tính theo chuỗi: $O(L)$ mỗi cặp | **Hằng số tối ưu: $O(1)$ nhờ kỹ thuật nhảy cóc chỉ mục** |
| **Quản lý ngăn xếp (Bài C)** | Đệ quy hệ thống biến thiên | **Khử đệ quy hoàn toàn bằng ngăn xếp tĩnh cố định** |
| **Chi phí I/O hệ thống** | Đọc ghi phân đoạn rời rạc | **Gom cụm tuyến tính qua mảng phẳng Fread/Fwrite** |
| **Thời gian chạy lớn nhất** | **375 ms** | **171 ms (Giảm hơn 54% thời gian xử lý)** |

---
## 5. KẾT LUẬN
Kết quả thực nghiệm đã chứng minh: Đối với các bài toán xử lý chuỗi và số nguyên hiệu năng cao, việc thiết kế một thuật toán có độ phức tạp lý thuyết tốt là chưa đủ. Để tối ưu hóa thời gian chạy vượt trội, giải thuật cần có khả năng tự co giãn cấu trúc theo miền dữ liệu thực tế, triệt tiêu tối đa các phép toán so sánh trùng lặp thông qua toán tử bitwise và tổ chức lưu trữ dữ liệu dạng phẳng liên tục.
