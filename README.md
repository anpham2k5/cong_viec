# Báo cáo tiến độ nghiên cứu ngày 27/03/2026
## A. Công việc đã làm
- Nghiên cứu cảm biến xúc giác điện dung
- Thực hành các thí nghiệm đo dữ liệu cảm biến
- Nghiên cứu cảm biến xúc giác từ tính
## B. Khó Khăn
- Tính lực bằng neural network
## C. Báo cáo chi tiết
### 1. Nghiên cứu cảm biến xúc giác điện dung
#### a. Cấu trúc phần cứng
- 2 miếng PCB đặt song song như 2 bản tụ và 1 lớp điện môi đàn hồi.
- Lớp điện môi đàn hồi, dễ nén khi chịu lực, cho phép khoảng cách giữa hai bản cực thay đổi theo lực tác động.
#### b. Nguyên lí điện dung
- Khi có lực tác động, lớp điện môi đàn hồi sẽ biến dạng làm cho 2 bản tụ gần nhau hơn khiến điện dung tăng. 
                                    $C = \frac{\varepsilon S}{d}$
#### c. Thực hành thí nghiệm đo dữ liệu cảm biến điện dung
- Ý tưởng: hai điện cực dẫn điện kẹp một lớp điện môi mềm ở giữa. Khi bị nhấn, cấu trúc bị biến dạng làm điện dung C thay đổi, rồi IC NE555/vi điều khiển đo sự thay đổi về tần số từ đó suy ra điện dung C và hiển thị qua UART
- Hình 1: Tổng quan mạch đo tần số sử dụng STM32 và IC NE555
- Nguồn tham khảo:(https://www.youtube.com/watch?v=ymMGEfDwxXg&feature=youtu.be)
- Hình 2: Sơ đồ nối dây cho IC NE555
- $$F = 1,44 \cdot (R_1 + 2R_2) \cdot C$$
#### d. Thí nghiệm đo điện dung C với các vật liệu và kích thước khác nhau
- Sự thay đổi của tần số và điện dung khi có lực tác động vào cảm biến của các trường hợp khác nhau:
Phíp đồng kích thước 28x34(mm), lớp điện môi: miếng bọt biển có tính đàn hồi, độ dày 7mm
Phíp đồng kích thước 28x34(mm), lớp điện môi: miếng bọt biển có tính đàn hồi, độ dày 4mm
=> Thay đổi gần gấp đôi so với dày 7mm 
Phíp đồng kích thước 65x70(mm), lớp điện môi: miếng bọt biển có tính đàn hồi, độ dày 8mm
=> Thay đổi gần gấp 4 so với kích thước 28x34(mm)
#### e.Cách tính lực của cảm biến
- Thu thập dữ liệu (Data Collection)
+ Tác động các mức lực chuẩn khác nhau lên cảm biến.
+ Đo và ghi lại giá trị điện dung tương ứng của cảm biến.
+ Tạo tập dữ liệu gồm các cặp giá trị (điện dung C, lực F).
- Xây dựng dữ liệu huấn luyện
+ Điện dung đo được từ cảm biến được sử dụng làm đầu vào (input) của mạng nơ-ron.
+ Lực tác động thực tế được sử dụng làm đầu ra (output) của mạng.
- Thiết kế mô hình mạng nơ-ron
+ Sử dụng mạng nơ-ron truyền thẳng nhiều lớp (MLP).
- Cấu trúc gồm:
+ Lớp đầu vào: giá trị điện dung hoặc tần số đo được
+ Lớp ẩn: học mối quan hệ phi tuyến
+ Lớp đầu ra: giá trị lực dự đoán.
- Huấn luyện mạng nơ-ron
+ Dữ liệu thu thập được được dùng để huấn luyện mạng.
+ Mạng điều chỉnh các trọng số để giảm sai số giữa lực dự đoán và lực thực tế.
- Sử dụng mô hình để dự đoán lực
+ Khi hệ thống hoạt động, điện dung đo được từ cảm biến được đưa vào mạng nơ-ron.
+ Mạng nơ-ron sẽ tính toán và xuất ra giá trị lực tương ứng.
- Ưu điểm của phương pháp
+ Có khả năng mô tả quan hệ phi tuyến giữa điện dung và lực.
+ Tăng độ chính xác so với phương pháp nội suy tuyến tính.
### 2. Nghiên cứu cảm biến xúc giác từ tính
#### a. Cấu trúc phần cứng
- Lớp vỏ cảm nhận cơ học: Sử dụng mạng lưới vi cấu trúc (cut-cell microstructures) kết hợp công cụ mã nguồn mở, cho phép tùy biến linh hoạt kích thước ô lưới, độ dày dầm và cấu hình phân tầng độ cứng.
- Hệ thống phát tín hiệu từ tính: Gồm các nam châm được đặt trực tiếp vào các túi chứa bên trong lưới. Các nam châm này được sắp xếp phân cực xen kẽ nhằm triệt tiêu nhiễu từ trường.
- Hệ thống thu thập tín hiệu : Tích hợp bảng mạch từ kế chứa các cảm biến Hall, được đặt trong một khe cắm chuyên dụng ở phần đế để trực tiếp đo lường sự biến thiên từ trường.
### b. Cơ chế tạo và thu nhận tín hiệu từ tính
- Nguyên lý: Khi có ngoại lực làm biến dạng bề mặt cảm biến, các nam châm bên trong sẽ bị xê dịch, kéo theo sự thay đổi của từ trường xung quanh.
- Thu nhận: Sự biến thiên từ trường này được đo lường trực tiếp bởi các cảm biến hiệu ứng Hall được đặt bên trong hoặc bên dưới mạng lưới.
- Tín hiệu đầu ra: Tín hiệu này được hệ thống xuất ra dưới dạng một vector 15 chiều(do có 5 cảm biến từ kế 3 trục) đại diện cho sự thay đổi của từ trường.
### c. Cách tính toán và suy ra lực
- Vì mối quan hệ giữa từ trường và khoảng cách thường là phi tuyến tính phức tạp, việc suy ra lực thường được thực hiện bằng cách:  Sử dụng mô hình học sâu (Deep Learning) 
- Đây là phương pháp hiệu quả nhất để xử lý dữ liệu từ trường đa chiều (thường là 3 trục Bx ,By , Bz cho mỗi điểm cảm biến):
- Thu thập dữ liệu: Sử dụng một robot hoặc thiết bị chuẩn để tác động các lực đã biết lên cảm biến và ghi lại các thay đổi từ trường (B) tương ứng.
+ Huấn luyện mô hình: Sử dụng mạng nơ-ron nhân tạo (MLP - Multi-Layer Perceptron) để ánh xạ dữ liệu từ trường 15 chiều (từ các cảm biến Hall) sang giá trị lực 3 chiều (lực pháp tuyến và lực cắt).
+ Dự đoán: Khi hoạt động thực tế, mô hình sẽ nhận dữ liệu B thời gian thực và tính toán ra giá trị lực.
+ Sai số dự đoán lực pháp tuyến của eFlesh đạt khoảng 0.27 N.
+ Sai số dự đoán lực cắt đạt khoảng 0.12 N.



  



