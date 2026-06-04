# BÁO CÁO ĐỒ ÁN SORT BENCHMARK

## Thông tin 

* Môn học: Cấu trúc dữ liệu và Giải thuật
* Học kỳ: 2 - Năm học 2025-2026
* Thời gian: 01/03/2026 - 30/06/2026
* Giảng viên:
    * Thầy Phạm Trọng Nghĩa
    * Thầy Huỳnh Lâm Hải Đăng
    * Thầy Nguyễn Thanh Tình
    * Thầy Nguyễn Ngọc Đức
* Thông tin sinh viên:
    * Sinh viên 1:
        * Họ và tên: Nguyễn Minh Nhật
        * MSSV: 25120403
        * Lớp: 25CTT6
    * Sinh viên 2:
        * Họ và tên: Nguyễn Hữu Thịnh
        * MSSV: 25120443
        * Lớp: 25CTT6
    * Sinh viên 3:
        * Họ và tên: Huỳnh Đức Phú
        * MSSV: 25120415
        * Lớp: 25CTT6

---

# Giới thiệu

Mục tiêu của đồ án là nghiên cứu và tối ưu các thuật toán sắp xếp trên ba bài toán khác nhau. Đối với mỗi bài, nhóm thực hiện:

1. Xây dựng phiên bản đầu tiên với thuật toán có hiệu năng tốt nhất trong quá trình thử nghiệm.
2. Thiết kế bộ sinh dữ liệu nhằm tạo các trường hợp bất lợi cho thuật toán mục tiêu.
3. Tiếp tục tối ưu ở lần nộp thứ hai và so sánh với phiên bản ban đầu.

# Cấu trúc Repository

Repository gồm:

```text
.
├── README.md
└── test_gen.cpp
```

Trong đó:

- `README.md`: báo cáo đồ án, mô tả thuật toán, cách sinh test và các phương pháp tối ưu hóa.
- `test_gen.cpp`: chương trình sinh dữ liệu benchmark cho ba bài toán Integer Sort, Lexicographic Sort và Length-aware Lexicographic String Sort.
# BÀI A – INTEGER SORT

## 1. Mô tả bài toán

Bài toán yêu cầu sắp xếp tối đa 100000 số nguyên có dấu 32-bit theo thứ tự tăng dần.

Về mặt chức năng, đây là một bài toán sắp xếp cơ bản. Tuy nhiên trong khuôn khổ benchmark, mục tiêu không chỉ là đưa ra kết quả đúng mà còn phải tối ưu thời gian thực thi trên tập dữ liệu lớn. Do số lượng phần tử có thể đạt tới 10^5 và miền giá trị trải rộng trên toàn bộ không gian số nguyên 32-bit, thuật toán cần xử lý hiệu quả cả về thời gian lẫn bộ nhớ.

---

## 2. Thuật toán tốt nhất ở lần nộp thứ nhất

### Hybrid Sort

Phiên bản đầu tiên sử dụng chiến lược kết hợp:

* Insertion Sort khi `n ≤ 2000`.
* Counting Sort khi `max - min ≤ 2.000.000`.
* Radix Sort LSD 8-bit cho các trường hợp còn lại.

Đối với Radix Sort, mỗi pass xử lý 8 bit nên cần tổng cộng 4 pass để xử lý đủ 32 bit. Ở pass cuối, các bucket chứa bit dấu được đưa lên trước nhằm đảm bảo thứ tự đúng của số nguyên có dấu.

### Lý do lựa chọn

Trong quá trình thử nghiệm không có thuật toán nào luôn tốt nhất trên mọi bộ dữ liệu.

* Insertion Sort có chi phí hằng số thấp trên dữ liệu nhỏ.
* Counting Sort rất hiệu quả khi miền giá trị hẹp.
* Radix Sort duy trì hiệu năng ổn định trên dữ liệu lớn.

Vì vậy Hybrid Sort tận dụng được ưu điểm của từng thuật toán và cho kết quả tốt nhất ở lần nộp đầu tiên.

### Độ phức tạp

| Thuật toán     | Độ phức tạp  |
| -------------- | ------------ |
| Insertion Sort | O(n²)        |
| Counting Sort  | O(n + range) |
| Radix Sort     | O(4n)        |

---

## 3. Sinh test benchmark

### Cách sinh dữ liệu

Chương trình sinh:

* n = 100000.
* Các số nguyên được sinh ngẫu nhiên trên toàn bộ miền int32.

Đối với hầu hết các test:

```cpp
[-2147483648 ; 2147483647]
```

Riêng test số 3:

```cpp
[-500000000 ; 2147483647]
```

### Thuật toán mục tiêu

* Counting Sort.
* Bucket Sort.
* Các thuật toán phụ thuộc mạnh vào miền giá trị.

### Lý do lựa chọn

Miền giá trị quá rộng làm mất lợi thế của Counting Sort và Bucket Sort. Bộ test buộc chương trình phải sử dụng Radix Sort hoặc các thuật toán tổng quát khác.

Đây là dạng dữ liệu phù hợp để đánh giá khả năng xử lý dữ liệu lớn và tối ưu truy cập bộ nhớ.

---

## 4. Tối ưu ở lần nộp thứ hai

### Radix Sort 16-bit

| Thành phần  | Lần 1          | Lần 2          |
| ----------- | -------------- | -------------- |
| Base        | 256            | 65536          |
| Số pass     | 4              | 2              |
| Xử lý số âm | Bucket reorder | XOR 0x80000000 |

### Ý tưởng tối ưu

Phiên bản thứ hai tăng số bit xử lý trong mỗi pass từ 8 lên 16.

Nhờ đó:

* Giảm số lần quét dữ liệu từ 4 xuống còn 2.
* Giảm truy cập bộ nhớ.
* Tăng hiệu quả cache.

Ngoài ra phép XOR với `0x80000000` giúp chuyển đổi thứ tự signed integer thành unsigned integer và loại bỏ bước xử lý đặc biệt ở pass cuối.

### Kết quả

Thời gian thực thi giảm đáng kể trên bộ dữ liệu lớn nhờ giảm số pass và lượng thao tác bộ nhớ.

### Độ phức tạp

| Thuật toán | Độ phức tạp |
|------------|------------|
| Radix Sort 16-bit (2 pass) | O(n) |
| Bộ nhớ phụ | O(65536) |

---

# BÀI B – LEXICOGRAPHIC SORT

## 1. Mô tả bài toán

Cho tối đa 100000 chuỗi chỉ gồm các ký tự thường từ 'a' đến 'z', mỗi chuỗi có độ dài từ 10 đến 100 ký tự. Yêu cầu sắp xếp các chuỗi theo thứ tự từ điển tăng dần.

Đây là bài toán trên dữ liệu chuỗi. Khác với bài toán sắp xếp số nguyên, chi phí xử lý không chỉ phụ thuộc vào số lượng phần tử mà còn phụ thuộc vào độ dài của từng chuỗi. Mỗi phép so sánh giữa hai chuỗi có thể phải duyệt qua nhiều ký tự trước khi xác định được thứ tự tương đối của chúng.

Với số lượng dữ liệu lớn và chiều dài chuỗi lên tới 100 ký tự, việc giảm số lần so sánh, hạn chế sao chép dữ liệu và khai thác cấu trúc ký tự của chuỗi là những yếu tố quyết định hiệu năng. Vì vậy bài toán này tập trung đánh giá khả năng tối ưu thuật toán sắp xếp chuỗi trên các bộ dữ liệu có kích thước lớn và mức độ tương đồng cao.

---

## 2. Thuật toán tốt nhất ở lần nộp thứ nhất

### Insertion Sort + MSD String Radix Sort

Thuật toán sử dụng MSD Radix Sort trên chuỗi.

Dữ liệu được lưu bằng:

* Mảng ký tự tĩnh chứa toàn bộ chuỗi.
* Mảng con trỏ dùng để sắp xếp.
* Mảng tạm dùng trong quá trình phân bucket.

Việc sắp xếp được thực hiện trên con trỏ thay vì sao chép nội dung chuỗi.

### Các tối ưu hóa

#### Insertion Sort cho bucket nhỏ

Khi số phần tử trong bucket ≤ 32, thuật toán chuyển sang Insertion Sort để giảm chi phí đệ quy.

#### Early Stop

Nếu toàn bộ chuỗi trong một đoạn có cùng ký tự tại vị trí đang xét thì thuật toán bỏ qua bước phân bucket và tiếp tục xử lý ký tự kế tiếp.

#### Bucket 256 phần tử

Sử dụng trực tiếp bảng mã ASCII 256 ký tự giúp giảm chi phí ánh xạ ký tự.

### Lý do lựa chọn

MSD Radix Sort khai thác trực tiếp cấu trúc ký tự của chuỗi thay vì dựa trên phép so sánh toàn phần. Thuật toán đặc biệt hiệu quả khi nhiều chuỗi có tiền tố giống nhau.

### Độ phức tạp

| Thuật toán | Độ phức tạp |
|------------|------------|
| MSD Radix Sort | O(n × L) |
| Insertion Sort (bucket nhỏ) | O(k²) |
| Bộ nhớ phụ | O(n) |

với:

* n: số chuỗi.
* L: độ dài trung bình.

---

## 3. Sinh test benchmark

### Cách sinh dữ liệu

Chương trình sinh:

* n = 10000.
* Mỗi chuỗi dài đúng 100 ký tự.
* 98 ký tự đầu luôn là `'a'`.
* Hai ký tự cuối được sinh ngẫu nhiên.

Ví dụ:

```text
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabx
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacy
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaazz
```

### Thuật toán mục tiêu

* MSD Radix Sort.
* Quick Sort.
* Merge Sort.

### Lý do lựa chọn

Các chuỗi có xâu tiền tố chung rất dài.

Đối với thuật toán dựa trên so sánh, mỗi phép so sánh phải duyệt gần hết chuỗi.

Đối với MSD Radix Sort, thuật toán phải đi sâu gần hết độ dài chuỗi trước khi dữ liệu bắt đầu phân nhánh thành các bucket khác nhau.

Bộ test này giúp đánh giá khả năng xử lý dữ liệu có độ tương đồng rất cao.

---

## 4. Tối ưu ở lần nộp thứ hai

### Zero-Copy MSD Radix Sort

Các thay đổi chính:

* Đọc toàn bộ dữ liệu bằng `fread`.
* Buffer dữ liệu 100MB.
* Chỉ lưu con trỏ tới chuỗi.
* Không tạo bản sao dữ liệu.
* Xuất dữ liệu bằng `fputs`.

### Ý tưởng tối ưu

Mục tiêu là giảm chi phí I/O và giảm số lần cấp phát bộ nhớ.

Việc chỉ thao tác trên con trỏ giúp loại bỏ phần lớn chi phí sao chép chuỗi.

### Kết quả

Thuật toán giữ nguyên bản chất MSD Radix Sort nhưng đạt hiệu năng tốt hơn nhờ giảm cache miss và giảm thao tác bộ nhớ.

### Độ phức tạp

| Thuật toán | Độ phức tạp |
|------------|------------|
| MSD Radix Sort | O(n × L) |
| Bộ nhớ phụ | O(n) |

---

# BÀI C – LENGTH-AWARE LEXICOGRAPHIC STRING SORT

## 1. Mô tả bài toán

Cho tập hợp tối đa 10000 chuỗi ký tự thường. Thứ tự sắp xếp được xác định bởi hai tiêu chí: chuỗi ngắn hơn đứng trước, và nếu hai chuỗi có cùng độ dài thì sắp xếp theo thứ tự từ điển tăng dần.

Đây là bài toán benchmark kết hợp giữa phân loại theo độ dài và sắp xếp chuỗi. So với bài toán sắp xếp từ điển thông thường, thuật toán phải xử lý đồng thời hai khóa sắp xếp khác nhau, trong đó độ dài là tiêu chí ưu tiên cao nhất.

Vấn đề của bài toán nằm ở việc tận dụng đặc điểm dữ liệu để giảm số phép so sánh và giảm lượng công việc cần thực hiện trong từng nhóm chuỗi. Một lời giải hiệu quả cần khai thác tốt tính chất phân bố độ dài của dữ liệu, đồng thời tối ưu quá trình sắp xếp bên trong mỗi nhóm nhằm đạt thời gian thực thi thấp nhất trên các bộ dữ liệu benchmark.

---

## 2. Thuật toán tốt nhất ở lần nộp thứ nhất

### Bucket + LSD Radix Sort

Thuật toán gồm hai bước:

1. Chia dữ liệu thành 91 bucket theo độ dài từ 10 đến 100.
2. Thực hiện LSD Radix Sort trên từng bucket.

Dữ liệu được đọc và ghi bằng `fread/fwrite` nhằm giảm chi phí I/O.

### Lý do lựa chọn

Do tiêu chí độ dài được ưu tiên trước nên việc bucket theo độ dài giúp loại bỏ hoàn toàn bước so sánh độ dài trong quá trình sắp xếp.

Sau đó LSD Radix Sort hoạt động hiệu quả trên các chuỗi có cùng độ dài.

### Độ phức tạp

| Thuật toán | Độ phức tạp |
|------------|------------|
| Bucket theo độ dài | O(n) |
| LSD Radix Sort | O(n × L) |
| Bộ nhớ phụ | O(n) |

Trong đó:

- n là số chuỗi.
- L là độ dài chuỗi.

---

## 3. Sinh test benchmark

### Cách sinh dữ liệu

Chương trình sinh:

* n = 100000.
* Mỗi chuỗi dài đúng 100 ký tự.

Mỗi chuỗi chỉ gồm một loại ký tự:

```text
aaaaaaaaaaaaaaaaaaaa...
bbbbbbbbbbbbbbbbbbbb...
cccccccccccccccccccc...
```

Ký tự được chọn ngẫu nhiên từ `'a'` đến `'z'`.

### Thuật toán mục tiêu

* LSD Radix Sort.
* Các thuật toán xử lý chuỗi theo từng ký tự.

### Lý do lựa chọn

Toàn bộ dữ liệu có cùng độ dài điều đó làm xử lí chuỗi phức tạp từ đó làm tăng thời gian thực thi chương trình.

Bộ test giúp đánh giá khả năng xử lý khối lượng lớn dữ liệu chuỗi.

---

## 4. Tối ưu ở lần nộp thứ hai

### Bucket + Randomized Quick Sort

Các thay đổi:

* Giữ nguyên bucket theo độ dài.
* Thay LSD Radix Sort bằng Quick Sort chọn pivot ngẫu nhiên.
* Sử dụng stack thủ công thay cho đệ quy.
* Chuyển sang Insertion Sort khi đoạn ≤ 15 phần tử.

### Ý tưởng tối ưu

Giảm overhead đệ quy và cải thiện hiệu năng trên các bucket nhỏ.

Quick Sort ngẫu nhiên cũng giúp hạn chế nguy cơ rơi vào trường hợp xấu.

### Kết quả

Phiên bản thứ hai cho thời gian thực thi tốt hơn trên bộ dữ liệu benchmark nhờ giảm chi phí phụ trợ và tận dụng tốt đặc điểm dữ liệu.

### Độ phức tạp

| Thuật toán | Độ phức tạp |
|------------|------------|
| Bucket theo độ dài | O(n) |
| Randomized Quick Sort | O(n log n) (trung bình) |
| Insertion Sort | O(k²) |
| Bộ nhớ phụ | O(log n) |

Trong đó:

- n là số phần tử trong một bucket.
- k là kích thước đoạn nhỏ được xử lý bằng Insertion Sort.

---

# KẾT LUẬN

Lần nộp thứ nhất tập trung lựa chọn thuật toán phù hợp cho từng dạng dữ liệu.

Lần nộp thứ hai tập trung vào tối ưu hóa cài đặt:

* Giảm số pass của Radix Sort.
* Giảm truy cập bộ nhớ.
* Tăng hiệu quả cache.
* Giảm sao chép dữ liệu.
* Tối ưu nhập xuất.

Các bộ test được thiết kế nhằm tạo ra trường hợp bất lợi cho thuật toán mục tiêu, từ đó đánh giá rõ sự khác biệt về hiệu năng giữa các phương pháp cài đặt khác nhau.
