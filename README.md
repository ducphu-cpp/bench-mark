# BÁO CÁO ĐỒ ÁN: SORTING BENCHMARK

## 1. THÔNG TIN SINH VIÊN
* **Tên môn học:** Cấu trúc dữ liệu và Giải thuật
* **Thời gian học:** Học kỳ 2 - Năm học 2025-2026

### Danh sách thành viên nhóm nghiên cứu:
1. **Họ và tên:** Huỳnh Đức Phú — **MSSV:** 25120415
2. **Họ và tên:** Nguyễn Minh Nhật — **MSSV:** 25120403
3. **Họ và tên:** Nguyễn Hữu Thịnh — **MSSV:** 25120433

---

## 2. THUẬT TOÁN CÀI ĐẶT TỐT NHẤT Ở LẦN CHẠY ĐẦU TIÊN (PHIÊN BẢN LẦN 1)

### 2.1. Giải thuật chi tiết cho từng bài toán
* **Bài A (Integer Sort):** Nhóm em sử dụng Hybrid Sort dựa trên việc đánh giá động dải giá trị dữ liệu ($mx - mn$). Với $N \le 2000$, chương trình chạy *Insertion Sort* để tận dụng bộ nhớ đệm. Với các bộ test có khoảng giá trị nhỏ ($\le 2 \cdot 10^6$), thuật toán *Counting Sort* tĩnh được kích hoạt để đưa độ phức tạp về tuyến tính tuyệt đối $O(N)$. Với dải số lớn toàn phần, chương trình thực thi *LSD (Least Significant Digit) Radix Sort 4-pass*, phân tách số nguyên thành 4 phân đoạn byte (8-bit mỗi lượt) bằng các toán tử dịch bit `(src[i] >> shift) & 0xFF`.
* **Bài B (Lexicographic Sort):** Triển khai cấu trúc giải thuật *MSD (Most Significant Digit) Radix Sort* đệ quy. Thuật toán phân loại các chuỗi dựa trên ký tự tại vị trí index `pos` từ trái qua phải. Nhóm tích hợp một điều kiện ngắt sớm: khi kích thước mảng con thu hẹp xuống dưới ngưỡng 24 phần tử ($r - l \le 24$), hệ thống tự động chuyển sang *Insertion Sort* sử dụng hàm so sánh chuỗi tùy biến `smallerFrom` nhằm triệt tiêu overhead phân tách đệ quy. Đồng thời sử dụng bộ đọc tăng tốc `FastInput` nạp thô khối dữ liệu qua `cin.rdbuf()->sgetn`.
* **Bài C (Length-aware Lexicographic Sort):** Tận dụng tính chất độ dài chuỗi cố định từ 10 đến 100, nhóm áp dụng *Bucket Sort* tĩnh gồm 101 xô để nhóm các chuỗi có cùng độ dài lại với nhau. Tại mỗi xô độ dài, thuật toán *MSD Radix Sort* được triển khai đảo ngược, chạy từ vị trí ký tự cuối cùng (`pos = l - 1`) lùi về 0. Dữ liệu được đếm tần suất thông qua mảng `cnt[26]` đại diện cho các ký tự từ 'a' đến 'z'. Cơ chế I/O tốc độ cao được xây dựng thủ công bằng việc sử dụng bộ đệm mảng byte tĩnh `ibuf` kết hợp hàm `fread` cho đầu vào và `obuf` kết hợp `fwrite` cho đầu ra.

### 2.2. Lý giải nguyên nhân tối ưu và hạn chế của Lần 1
* **Nguyên nhân tối ưu:** Việc áp dụng các giải thuật không so sánh (Non-comparison Sort) như Radix Sort và Counting Sort giúp hạ độ phức tạp thời gian từ mức lý thuyết trung bình $O(N \log N)$ xuống mức tuyến tính $O(N \cdot L)$ (với $L$ là độ dài chuỗi). Việc bó cụm theo độ dài ở bài C giúp cô lập không gian tìm kiếm, không mất chi phí so sánh độ dài giữa các phần tử khác nhóm.
* **Hạn chế còn tồn tại:** 1. Ở bài B, việc sử dụng mảng hai chiều dạng `char s[MAXN][MAXL]` khiến dữ liệu chuỗi phân bố rời rạc trên RAM. Khi hoán vị chỉ số chuỗi qua mảng `id[MAXN]`, CPU phải liên tục nhảy vùng nhớ để đọc ký tự từ mảng `s`, dẫn đến hiện tượng **Cache Miss** nặng nề ở tầng bộ nhớ đệm L1/L2.
  2. Ở bài B, hàm `insertionSort` gọi hàm `smallerFrom` thực hiện vòng lặp kiểm tra tuần tự từ vị trí `pos`, nhưng bản chất vẫn phải duyệt lại các ký tự đã biết.
  3. Ở bài A, việc Radix Sort phải thực hiện tới 4 chu kỳ lặp (4-pass) vô hình trung làm tăng số lần truy xuất đọc ghi bộ nhớ lên gấp 4 lần dung lượng mảng dữ liệu.

---

## 3. THIẾT KẾ BỘ SINH TEST CASE CHI TIẾT (FILE TEST_GEN.CPP)

### 3.1. Phương pháp cài đặt kỹ thuật
Bộ sinh test case `test_gen.cpp` được lập trình theo tiêu chuẩn cấu trúc C++23 hiện đại. Chương trình tích hợp giao diện dòng lệnh CLI chuẩn hóa nhằm tiếp nhận chính xác hai đối số thực thi từ Trợ giảng: 
1. `argument 2`: Định danh bài toán cần sinh cấu trúc kết quả (`int`, `strlexi`, hoặc `strlenlexi`).
2. `argument 3`: Mã số định danh phân loại bộ test (từ 1 đến 5).

Để đảm bảo tính ngẫu nhiên chất lượng cao và phân phối đều, nhóm loại bỏ hoàn toàn hàm `rand()` truyền thống của C (vốn có chu kỳ ngắn và phân bố kém). Thay vào đó, nhóm áp dụng bộ sinh số giả ngẫu nhiên dòng Mersenne Twister 64-bit (`std::mt19937_64`) phối hợp cùng hạt giống thời gian hệ thống độ chính xác cao (`std::chrono::steady_clock`).

### 3.2. Thuật toán mục tiêu cấu trúc test nhắm tới và cơ chế bẻ gãy hiệu năng
Nhóm đã thiết kế cấu trúc hình học của dữ liệu trong 5 bộ test nhằm "bẻ gãy" và tối đa hóa thời gian thực thi của các thuật toán phổ thông, cụ thể như sau:

* **Đối với bài toán số nguyên (`int`):**
  * *Test 1 (Ngẫu nhiên dải rộng):* Sinh số nguyên phân bố đều trên toàn bộ không gian 32-bit có dấu [$-2^{31}, 2^{31}-1$]. Bộ test này ép các thuật toán Radix Sort phải thực hiện đầy đủ số pass hoặc làm tràn bộ nhớ nếu các thuật toán Counting Sort áp dụng sai lệch miền giá trị.
  * *Test 2 (Miền giá trị hẹp):* Khống chế giá trị trong khoảng hẹp [$-500000, 500000$]. Mục tiêu thử nghiệm khả năng tối ưu hóa của Counting Sort tĩnh.
  * *Test 3 & 4 (Dữ liệu tăng dần/giảm dần có chủ đích):* Sinh ra mảng đã được sắp xếp hoàn hảo hoặc đảo ngược hoàn hảo. Mục tiêu nhắm thẳng vào các thuật toán *Quick Sort* thông thường sử dụng chiến lược chọn phần tử chốt (pivot) là phần tử đầu mút hoặc cuối mút. Cấu trúc này đẩy độ phức tạp của Quick Sort từ $O(N \log N)$ chạm mức tệ nhất là $O(N^2)$, gây sập hệ thống do tràn ngăn xếp đệ quy (Stack Overflow) hoặc quá giới hạn thời gian (TLE).
  * *Test 5 (Trùng lặp mật độ cực cao):* Mảng chứa $10^5$ phần tử nhưng chỉ xoay quanh các giá trị từ 1 đến 10. Bộ test này phá hủy các giải thuật Quick Sort phân hoạch hai vùng (2-way partitioning) không có cơ chế thu hẹp phân đoạn trùng (3-way partitioning), khiến chốt phân hoạch bị lệch nghiêm trọng.

* **Đối với bài toán chuỗi ký tự (`strlexi` / `strlenlexi`):**
  * *Test 1 (Phân bố ngẫu nhiên tổng quát):* Chuỗi có độ dài biến thiên ngẫu nhiên từ 10 đến 100 ký tự.
  * *Test 2 (Đồng nhất độ dài):* Toàn bộ chuỗi đều có chiều dài cố định bằng 100. Test case này triệt tiêu hoàn toàn lợi thế phân loại theo chiều dài của bài C ở bước khởi đầu, bắt buộc hệ thống phải dồn toàn bộ tải xử lý vào tầng so sánh từ điển phía sau.
  * *Test 3 (Chiến lược ANTI-STRCMP - Tiền tố trùng lặp sâu):* Đây là bộ test cực kỳ khắc nghiệt được nhóm thiết kế riêng để hạ gục các thuật toán dùng hàm so sánh chuỗi tiêu chuẩn C/C++ (`strcmp` hoặc toán tử `<` của `std::string`). Chương trình sinh ra các chuỗi có **95 ký tự đầu tiên hoàn toàn giống hệt nhau**, và chỉ xuất hiện sự sai biệt ngẫu nhiên ở **5 ký tự cuối cùng**. 
    * *Cơ chế bẻ gãy hiệu năng:* Khi các thuật toán sắp xếp thông thường so sánh hai chuỗi, hàm `strcmp` bắt buộc phải quét tuyến tính duyệt qua toàn bộ 95 ký tự tiền tố lặp lại này rồi mới đưa ra được kết quả phân tách. Hệ quả là chi phí của một phép so sánh chuỗi bị đẩy từ mức hằng số $O(1)$ lên mức tuyến tính theo chiều dài chuỗi $O(L)$. Tổng chi phí thực thi bị nhân thêm một hệ số cực lớn, biến độ phức tạp tổng thể tiệm cận mức nguy hiểm $O(L \cdot N \log N)$ hoặc $O(L \cdot N^2)$, gây TLE lập tức trên hệ thống chấm điểm.
  * *Test 4 (Dữ liệu chuỗi tuần tự từ điển):* Chuỗi được sắp xếp sẵn từ trước nhằm kiểm tra khả năng tối ưu hóa phân đoạn dữ liệu đầu vào.
  * *Test 5 (Bể chuỗi trùng lặp):* Chỉ sinh dữ liệu từ một tập hợp gồm 20 chuỗi cố định. Bộ test này nhắm vào việc bẻ gãy các thuật toán MSD Radix Sort phân tách bucket bị lỗi logic tại ký tự kết thúc `\0`, dễ dẫn đến vòng lặp đệ quy vô hạn nếu không khống chế biên dịch chính xác.

---

## 4. THUẬT TOÁN CÀI ĐẶT TỐT NHẤT Ở LẦN THỨ HAI (TỐI ƯU NÂNG CAO)

Nhận diện được các điểm nghẽn về mặt kiến trúc hệ thống và sự tiêu tốn tài nguyên phần cứng ở phiên bản đầu tiên, nhóm đã tiến hành một cuộc tái cấu trúc toàn diện mã nguồn ở Lần 2. Mục tiêu cốt lõi là tối ưu hóa việc sử dụng bộ nhớ đệm CPU (CPU Cache Localization) và triệt tiêu chi phí hệ điều hành (System Overhead).

### 4.1. Các phương thức tối ưu hóa công nghệ cao đã áp dụng
* **Bài A (Tối ưu hóa số lượt quét bộ nhớ và Bit-manipulation):** Nhóm nâng cấp từ Radix Sort 4-pass xuống phiên bản **Radix Sort 2-pass (16-bit cho mỗi pass xử lý)**. Thay vì chia mảng đếm `count[256]`, hệ thống cấp phát mảng đếm kích thước $2^{16} = 65536$ phần tử. 
  * *Pass 1:* Đếm và phân loại dựa trên 16-bit thấp bằng mặt nạ bit `a[i] & 0xFFFF`.
  * *Pass 2:* Đếm và phân loại dựa trên 16-bit cao bằng toán tử dịch `(b[i] >> 16) & 0xFFFF`.
  Chương trình tối ưu phép xử lý số nguyên có dấu bằng cách thực hiện phép toán XOR trực tiếp với bit dấu: `a[i] ^= 0x80000000` ở đầu giải thuật để đưa toàn bộ dải số về dạng số nguyên không dấu đồng quy, sau đó XOR đảo ngược để trả về giá trị gốc sau khi sắp xếp xong. Đồng thời sử dụng con trỏ cấu trúc tĩnh `std::make_unique<int[]>(n)` giúp dọn dẹp bộ nhớ tự động ở mức tối ưu cao.
* **Bài B (Kiến trúc Flat-Memory Buffer & Nhảy cóc ký tự tiền tố):** Đây là bước đột phá lớn nhất của nhóm. Nhóm loại bỏ hoàn toàn mảng chuỗi 2 chiều rải rác. Toàn bộ tệp dữ liệu đầu vào khổng lồ được nạp duy nhất một lần vào một mảng byte tĩnh liên tục trên bộ nhớ segment: `char buf[MAX_FILE_SIZE]` thông qua hàm `fread`. 
  * Trong quá trình phân tách chuỗi, chương trình không sao chép chuỗi mà chỉ lưu vị trí byte bắt đầu của chuỗi vào mảng chỉ số `ptrs[MAXN]`. Ký tự khoảng trắng hoặc xuống dòng được thay thế trực tiếp bằng ký tự kết thúc chuỗi `\0`. 
  * Khi thực thi hàm `msd_radix_sort`, tham số chiều sâu dữ liệu `depth` được truyền vào liên tục. Tại tầng Insertion Sort cục bộ ($r - l \le 16$), thay vì gọi `strcmp` từ đầu chuỗi, nhóm dịch chuyển con trỏ đọc trực tiếp tới vị trí đang phân tách: `strcmp(buf + ptrs[j] + depth, buf + key + depth)`. Thao tác nhảy cóc này giúp loại bỏ toàn bộ chi phí duyệt lại các ký tự tiền tố đã được Radix Sort phân loại ở các tầng đệ quy trước, triệt tiêu hoàn toàn sức tàn phá của bộ test ANTI-STRCMP.
* **Bài C (Khử đệ quy bằng Ngăn xếp thủ công và Phân loại xô độ dài):** Nhóm kế thừa cơ chế phân phối xô theo độ dài chuỗi bằng mảng đếm tần suất cấu trúc dịch chuyển đầu mút `bucket_start` và `current_pos`. Tuy nhiên, tại phân đoạn sắp xếp từ điển phía trong, nhóm loại bỏ hoàn toàn đệ quy hệ thống của ngôn ngữ nhằm tránh overhead gọi hàm. Nhóm tự xây dựng một thuật toán *Quick Sort lặp (Iterative Quick Sort)* quản lý bằng hai mảng ngăn xếp tĩnh độc lập `stack_left[MAXN]` và `stack_right[MAXN]` phối hợp cùng biến con trỏ đỉnh `top`. Khi kích thước vùng phân hoạch nhỏ hơn hoặc bằng 15, giải thuật lập tức rẽ nhánh sang *Insertion Sort* tĩnh để tăng tốc độ xử lý cục bộ.

### 4.2. Phân tích hiệu năng chuyên sâu và So sánh thực nghiệm với Lần 1
Sự cải tiến vượt bậc về mặt thời gian chạy từ mức **375ms** xuống còn **171ms** trên hệ thống chấm trực tuyến Codeforces được lý giải một cách khoa học thông qua các nguyên lý kiến trúc máy tính sau:

1. **Tối ưu hóa bộ nhớ đệm (Cache Locality):** Ở lần 1, việc truy xuất mảng chuỗi 2 chiều hoặc `std::string` cấp phát trên vùng nhớ Heap gây ra việc CPU liên tục phải gửi tín hiệu nạp dữ liệu từ RAM vào Cache do dữ liệu nằm rải rác. Ở lần 2, nhờ thiết kế bộ đệm phẳng `buf`, các chuỗi ký tự nằm xếp chồng liên tiếp cạnh nhau trên các ô nhớ vật lý. Khi CPU nạp một dòng dữ liệu cache (Cache Line thông thường là 64 byte), nó vô tình nạp luôn toàn bộ nội dung của các chuỗi kế cận vào dòng Cache L1 tốc độ siêu cao. Tỷ lệ **Cache Hit** tăng vọt lên tiệm cận mức tuyệt đối, giúp tăng tốc độ xử lý của lõi CPU lên gấp nhiều lần.
2. **Giảm số lượt quét dữ liệu (Pass Reduction):** Việc chuyển đổi từ Radix Sort 4 lượt quét (mỗi lượt 8-bit) sang 2 lượt quét (mỗi lượt 16-bit) ở bài toán số nguyên đã cắt giảm chính xác 50% số lần đọc và ghi dữ liệu từ mảng tạm `temp` quay ngược lại mảng gốc `data`. Số lượng lệnh xử lý điều hướng vòng lặp (Loop Overhead) giảm một nửa, giải phóng chu kỳ xung nhịp CPU một cách triệt để.
3. **Loại bỏ Overhead của Hệ điều hành và Trình biên dịch:** Việc áp dụng cơ chế tự quản lý ngăn xếp lặp thay thế cho đệ quy hệ thống (ở bài C) giúp loại bỏ các hành động đẩy tham số vào Stack Frame, lưu giữ trạng thái thanh ghi, và lệnh nhảy `call/ret` liên tục của CPU. Phối hợp với việc xả bộ đệm kết quả đầu ra duy nhất một lần qua lệnh `fwrite` thô (loại bỏ cơ chế đồng bộ hóa luồng phức tạp của `std::cout`) giúp chương trình đạt tới ngưỡng tốc độ vật lý tối đa của phần cứng.

Bảng so sánh tổng hợp hiệu năng thực nghiệm:

| Tiêu chí hiệu năng | Phiên bản Lần 1 (Cơ bản) | Phiên bản Lần 2 (Tối ưu nâng cao) |
| :--- | :--- | :--- |
| **Thuật toán Bài A** | Radix Sort 4-pass (8-bit) | Radix Sort 2-pass (16-bit) |
| **Cấu trúc lưu chuỗi** | Mảng hai chiều cố định trên bộ nhớ | Flat-Memory Buffer liên tục (Fread) |
| **Xử lý so sánh ký tự** | Quét lại từ đầu chuỗi (`smallerFrom`) | Nhảy cóc chỉ mục ký tự (`buf+ptrs+depth`) |
| **Quản lý Đệ quy** | Đệ quy hệ thống tự động | Ngăn xếp tĩnh thủ công khử đệ quy |
| **Thời gian Codeforces** | **375 ms** | **171 ms** |

---
## 5. KẾT LUẬN
Đồ án đã minh chứng rõ ràng rằng: Để tối ưu hóa một hệ thống xử lý dữ liệu lớn đạt tới giới hạn hiệu năng cực đại, việc chỉ tối ưu hóa độ phức tạp toán học thuật toán $O(N)$ là chưa đủ. Lập trình viên bắt buộc phải thấu hiểu sâu sắc kiến trúc phần cứng máy tính, vận dụng linh hoạt các kỹ thuật thao tác bit, tổ chức cấu trúc dữ liệu phẳng gọn nhẹ để tối ưu bộ đệm ẩn CPU Cache, đồng thời triệt tiêu các chi phí vận hành ẩn của hệ điều hành thông qua cơ chế quản lý I/O cấp thấp.
