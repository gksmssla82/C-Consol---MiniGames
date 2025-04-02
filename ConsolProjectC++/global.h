#pragma once


static void Set_CursorPos(int x, int y)
{
	HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hWnd, pos);
}

static void Stream_Open(const char* _path)
{
	ifstream file("../Art/Main.txt");

	if (!file.is_open())
	{
		cout << _path << " Stream Open Fail";
	}

	string line;

	while (getline(file, line))
		cout << line << '\n';

	file.close();
}

static bool Ascii_Transform(const string& _imagePath, const string& _outputTxtPath = "ascii_art.txt", int _width = 100) {
    string ASCII_PALETTE = " .,:;+*?%S#@";
    //string ASCII_PALETTE = " .'`^\",:;Il!i~+_-?][}{1)(|\\/<X7zjftLr-+=o*#MW&8%B@$";
    //string ASCII_PALETTE = "@%#&*+=-:. ";
   
    // 1. �̹��� �ε�
    cv::Mat src = cv::imread(_imagePath, cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cerr << "Error: Image not found at " << _imagePath << std::endl;
        return false;
    }

    // 2. ASCII ��Ʈ ����
    std::string asciiArt;
    int height = (int)((double)src.rows / src.cols * _width * 0.5); // ���� ���� ����
    cv::Mat resized, gray;
    cv::resize(src, resized, cv::Size(_width, height));
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);

    for (int y = 0; y < gray.rows; y++) {
        for (int x = 0; x < gray.cols; x++) {
            uchar pixel = gray.at<uchar>(y, x);
            
            int index = (pixel * (ASCII_PALETTE.size() - 1)) / 255;
            asciiArt += ASCII_PALETTE[index];
        }
        asciiArt += "\n";
    }

    // 3. �ܼ� ���
    std::cout << asciiArt << endl;

    // 4. ���� ����
    std::ofstream outFile(_outputTxtPath);

    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot save file to " << _outputTxtPath << std::endl;
        return false;
    }
    outFile << asciiArt;
    outFile.close();

    std::cout << "ASCII art saved to: " << _outputTxtPath << std::endl;
    return true;
}

//void convertToAsciiWithAlpha(const cv::Mat& img, std::string& asciiArt, int width = 100) {
//    // ���� ä�� Ȯ�� (4ä�� �̹����� ���)
//    if (img.channels() != 4) {
//        std::cerr << "Error: No alpha channel!" << std::endl;
//        return;
//    }
//
//    // �������� �� �׷��̽����� ��ȯ
//    int height = static_cast<int>((double)img.rows / img.cols * width * 0.4);
//    cv::Mat resized, gray;
//    cv::resize(img, resized, cv::Size(width, height));
//    cv::cvtColor(resized, gray, cv::COLOR_BGRA2GRAY);  // ���� ä�� ���
//
//    asciiArt.clear();
//    for (int y = 0; y < resized.rows; y++) {
//        for (int x = 0; x < resized.cols; x++) {
//            // �ȼ��� ���� �� Ȯ�� (���� üũ)
//            uchar alpha = resized.at<cv::Vec4b>(y, x)[3];
//            if (alpha < 128) {  // ������ �ȼ��� ���� ó��
//                asciiArt += " ";
//                continue;
//            }
//
//            // ������ �ȼ��� ASCII ��ȯ
//            uchar pixel = gray.at<uchar>(y, x);
//            int index = (pixel * (ASCII_PALETTE.size() - 1)) / 255;
//            asciiArt += ASCII_PALETTE[index];
//        }
//        asciiArt += "\n";
//    }
//}



