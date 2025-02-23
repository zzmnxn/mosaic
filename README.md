# 랜덤 픽셀 변환 및 PNG 생성 프로그램

## 개요
이 프로그램은 112x112 크기의 픽셀 배열을 생성하고, 무작위로 선택된 픽셀의 주변 8개 픽셀을 평균 RGB 값으로 변환한 후, 결과를 PNG 이미지 파일로 저장하는 기능을 수행한다.

## 주요 기능
- **무지개 배경 생성**: 7개의 색상(빨강, 주황, 노랑, 초록, 파랑, 남색, 보라)으로 구성된 스트라이프 무지개 배경을 생성한다.
- **랜덤 픽셀 변환**: 랜덤하게 선택된 픽셀의 주변 8개 픽셀을 포함하여 RGB 값을 평균값으로 변경한다.
- **PNG 이미지 저장**: 처리된 픽셀 데이터를 PNG 파일로 저장한다.

## 코드 구조
- `Pixel` 구조체: 각 픽셀의 RGB 값을 저장하는 구조체
- `setPixelColor(int row, int col, unsigned char red, unsigned char green, unsigned char blue)`: 특정 좌표의 픽셀 색상을 설정
- `calculateAverage(int row, int col)`: 지정된 픽셀 주변의 평균 RGB 값을 계산
- `randomizePixels()`: 무작위로 선택된 픽셀의 주변 픽셀 값을 평균값으로 변환
- `writePNG(const char* filename)`: 픽셀 데이터를 PNG 파일로 저장
- `main()`: 프로그램의 실행 흐름을 관리

## 실행 방법
1. 프로그램을 컴파일
    ```sh
    g++ -o pixel_image pixel_image.cpp -lpng
    ```
2. 실행하여 `initial_image.png` 파일을 생성
    ```sh
    ./pixel_image
    ```

## 결과
프로그램 실행 후, `initial_image.png` 파일이 생성되며, 무지개 배경 및 랜덤 픽셀 변환이 적용된 이미지를 확인할 수 있다.

## 사용 라이브러리
- `<iostream>`: 표준 입출력 지원
- `<cstdlib>`: 랜덤 함수 지원
- `<ctime>`: 랜덤 시드 초기화
- `<png.h>`: PNG 파일 저장을 위한 libpng 라이브러리
- `<cmath>`: 수학 연산 지원

## 참고 사항
- `randomizePixels()` 함수에서 전체 픽셀을 대상으로 랜덤 변환이 이루어지므로 실행할 때마다 다른 결과가 생성된다.
- `writePNG()` 함수에서 `libpng` 라이브러리를 사용하므로, 실행 환경에 `libpng`가 설치되어 있어야 한다.
- 이미지 크기(112x112)는 `numRows` 및 `numCols` 값을 수정하여 조정할 수 있다.

![image](https://github.com/user-attachments/assets/55653cb9-d95e-4820-bcb8-9959e3d347f0)
