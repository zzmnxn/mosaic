#include <iostream>
#include <cstdlib>
#include <ctime>
#include <png.h>
#include <cmath>

// 간단한 픽셀 구조체 정의
struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};


// 픽셀 배열의 크기
const int numRows = 112;
const int numCols = 112;

// 픽셀 배열
Pixel pixels[numRows][numCols];

void setPixelColor(int row, int col, unsigned char red, unsigned char green, unsigned char blue) {
    pixels[row][col].red = red;
    pixels[row][col].green = green;
    pixels[row][col].blue = blue;
}
// 랜덤으로 선택할 픽셀 개수
const int numRandomPixels = (numRows)*(numCols);


// RGB 값의 평균을 계산하는 함수
Pixel calculateAverage(int row, int col) {
    int totalRed = 0, totalGreen = 0, totalBlue = 0;
    int count = 0;

    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int colOffset = -1; colOffset <= 1; ++colOffset) {
            int currentRow = row + rowOffset;
            int currentCol = col + colOffset;

            // 주변 8개 픽셀이 이미지 범위 내에 있는지 확인
            if (currentRow >= 0 && currentRow < numRows && currentCol >= 0 && currentCol < numCols) {
                // Black이 아닌 경우에만 평균값 계산에 포함
                if (!(rowOffset == 0 && colOffset == 0) && (pixels[currentRow][currentCol].red != 0 || pixels[currentRow][currentCol].green != 0 || pixels[currentRow][currentCol].blue != 0)) {
                    totalRed += pixels[currentRow][currentCol].red;
                    totalGreen += pixels[currentRow][currentCol].green;
                    totalBlue += pixels[currentRow][currentCol].blue;
                    count++;
                }
            }
        }
    }

    // 총합을 픽셀 수로 나누어 평균값 계산
    Pixel average;
    average.red =  count > 0 ? totalRed / count : 0;
    average.green = count > 0 ? totalGreen / count : 0;
    average.blue = count > 0 ? totalBlue / count : 0;

    return average;
}

// 랜덤으로 픽셀 선택 후 주변 8개 픽셀의 RGB 값을 평균값으로 변경하는 함수
void randomizePixels() {
    // 랜덤 시드 초기화
    std::srand(std::time(0));

    // 41개의 랜덤 픽셀 선택
    for (int i = 0; i < numRandomPixels; ++i) {
        int randomRow = std::rand() % numRows;
        int randomCol = std::rand() % numCols;

        // RGB 평균값 계산
        Pixel average = calculateAverage(randomRow, randomCol);

        // 선택된 픽셀을 중심으로 주변 8개 픽셀의 RGB 값을 평균값으로 변경
        for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
            for (int colOffset = -1; colOffset <= 1; ++colOffset) {
                int currentRow = randomRow + rowOffset;
                int currentCol = randomCol + colOffset;

                // 주변 8개 픽셀이 이미지 범위 내에 있는지 확인
                if (currentRow >= 0 && currentRow < numRows && currentCol >= 0 && currentCol < numCols) {
                    // 선택된 픽셀을 중심으로 주변 8개 픽셀의 RGB 값을 평균값으로 변경
                    pixels[currentRow][currentCol] = average;
                }
                
            }
        }
    }
}

// PNG 파일 쓰기 함수
void writePNG(const char* filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) abort();

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();

    png_infop info = png_create_info_struct(png);
    if (!info) abort();

    if (setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    // 이미지 속성 설정
    png_set_IHDR(
        png,
        info,
        numCols, numRows,
        8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    // 픽셀 데이터 쓰기
    for (int y = 0; y < numRows; y++) {
        png_byte row[numCols * 3];  // RGB 값만 사용
        for (int x = 0; x < numCols; x++) {
            row[x * 3] = pixels[y][x].red;
            row[x * 3 + 1] = pixels[y][x].green;
            row[x * 3 + 2] = pixels[y][x].blue;
        }
        png_write_row(png, row);
    }

    png_write_end(png, NULL);
    fclose(fp);

    // libpng 구조체 메모리 해제
    if (png && info)
        png_destroy_write_struct(&png, &info);

}

int main() {
    // Initialize the random seed
    std::srand(std::time(0));
    
    // Initialize with white background
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            pixels[i][j].red = 255;
            pixels[i][j].green = 255;
            pixels[i][j].blue = 255;
        }
    }
   
   
        // 무지개 스트라이프의 색상
    int rainbowColors[7][4] = {
        {255, 0, 0, 255},     // 빨강
        {255, 127, 0, 255},   // 주황
        {255, 255, 0, 255},   // 노랑
        {0, 255, 0, 255},     // 초록
        {0, 0, 255, 255},     // 파랑
        {75, 0, 130, 255},    // 남색
        {148, 0, 211, 255}    // 보라
    };
    int height=numRows/7;
    for(int i=0;i<7;++i){
        for(int y=i*height;y<(i+1)*height;++y){
            for(int x=0;x<numRows;++x){
                setPixelColor(y,x,rainbowColors[i][0], rainbowColors[i][1], rainbowColors[i][2]);
            }

        }
    }
    // Write the initial image to a PNG file
    const char* initialFileName = "initial_image.png";
    writePNG(initialFileName);
