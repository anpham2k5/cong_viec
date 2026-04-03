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

