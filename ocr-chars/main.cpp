#include <cstdio>
#include <cstring>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

int main(int argc, char* argv[]) {
    tesseract::TessBaseAPI tessApi;
    tessApi.Init("/usr/share", "rus");// тут data каталог в котором лежат файлы *.traineddata,
    // а rus указывает какой именно из них использовать
    if(argc > 1) {
        PIX *pix = pixRead(argv[1]);// считываем картинку из файла с именем,
        // переданным первым аргументом, это функционал Leptonica
        tessApi.SetImage(pix);// говорим tesseract, что распознавать нужно эту картинку
        char *text = tessApi.GetUTF8Text();//распознаём
        //---генерируем имя файла в который будет записан распознанный текст
        char *fileName = NULL;
        long prefixLength;
        const char* lastDotPosition = strrchr(argv[1], '.');
        if(lastDotPosition != NULL) {
            prefixLength = lastDotPosition - argv[1];
            fileName = new char[prefixLength + 5];
            strncpy(fileName, argv[1], prefixLength);
            strcpy(fileName + prefixLength, ".txt\0");
        } else {
            exit(1);
        }
        //---
        FILE *outF = fopen(fileName, "w");
        fprintf(outF, "%s", text);
        fclose(outF);
        //---
        pixDestroy(&pix);
        delete [] fileName;
        delete [] text;
    }
    return 0;
}