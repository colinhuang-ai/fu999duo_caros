# Car Head Unit Simulator (CLI)

Giả lập màn hình giải trí trên ô tô, viết bằng C++17, chạy trong terminal.

## Chức năng

- **Home**: chọn Music / Map / Settings
- **Music**: danh sách bài hát -> chọn bài -> màn hình Now Playing (play/pause, tua, chỉnh âm lượng, stop)
- **Map**: chọn vùng bản đồ -> mô phỏng tải tile -> xem bản đồ ASCII, lái xe bằng w/a/s/d, zoom +/-
- **Settings**: âm lượng, theme, đơn vị đo, ngôn ngữ, shuffle

Phím dùng ở mọi màn hình: `b` = back, `h` = home, `q` = tắt máy.

## Build

Windows / MSVC:

    build.bat

Hoặc bằng CMake (mọi nền tảng):

    cmake -B build
    cmake --build build

Chạy: `build\car_sim.exe`

`build.bat` dùng `g++` nếu có trên PATH, nếu không thì rơi về MSVC (`cl`).
MSVC cần Windows SDK — thiếu SDK sẽ báo `Cannot open include file: 'crtdbg.h'`.

## Cấu trúc

    src/main.cpp            điểm vào
    src/core/App.*          vòng lặp input + stack màn hình + trạng thái chung
    src/core/Screen.h       interface của một màn hình
    src/core/Console.*      tiện ích in/đọc terminal
    src/services/           MusicLibrary, MapService, Settings (dữ liệu & logic)
    src/screens/            Home, Music, NowPlaying, Map, MapView, Settings

Mỗi màn hình chỉ render nội dung của nó; `App` lo header, thanh trạng thái,
lệnh toàn cục và điều hướng (pop được hoãn tới cuối vòng lặp nên một màn hình
có thể tự đóng mình trong `handleInput`).

Bước tiếp theo nếu chuyển sang GUI: giữ nguyên `services/`, thay `screens/` và
`Console` bằng lớp UI thật.
