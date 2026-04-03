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
$$
C = \frac{\varepsilon S}{d}
$$
#### c. Thực hành thí nghiệm đo dữ liệu cảm biến điện dung
- Ý tưởng: hai điện cực dẫn điện kẹp một lớp điện môi mềm ở giữa. Khi bị nhấn, cấu trúc bị biến dạng làm điện dung C thay đổi, rồi IC NE555/vi điều khiển đo sự thay đổi về tần số từ đó suy ra điện dung C và hiển thị qua UART
<div align="center">

![](2026-04-03-14-45-44.png)

</div>
<div align="center">
*Hình 1: Tổng quan mạch đo tần số sử dụng STM32 và IC NE555*
</div>
- Nguồn tham khảo : https://www.youtube.com/watch?v=ymMGEfDwxXg
<div align="center">

![](2026-04-03-14-52-56.png)

</div>
<div align="center">
*Hình 2: Sơ đồ đấu dây cho IC 555*
</div>
Công thức đo tần số:

$$
f = \frac{1.44}{(R1 + 2R2)\cdot C}
$$

từ đó suy ra điện dung C.
#### d. Thí nghiệm đo điện dung C với các vật liệu và kích thước khác nhau
- Sự thay đổi của tần số và điện dung khi có lực tác động vào cảm biến của các trường hợp khác nhau:
##### Phíp đồng kích thước 28x34(mm), lớp điện môi: miếng bọt biển có tính đàn hồi, độ dày 7mm
<div align="center">

![](2026-04-03-15-18-05.png)

</div>

##### Phíp đồng kích thước 28x34(mm), lớp điện môi: miếng bọt biển có tính đàn hồi, độ dày 4mm
<div align="center">

![](2026-04-03-15-22-51.png)

</div>

##### Phíp đồng kích thước 65x70(mm), lớp điện môi: miếng bọt biển có tính đàn hồi, độ dày 7mm

