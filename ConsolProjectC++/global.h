#pragma once

const string ASCII_PALETTE = " .,:;+*?%S#@";

static atomic<bool> running(true);

static mutex gMutex;

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

static bool Ascii_Image(const string& _imagePath,  int _width = 100) 
{
    
    //string ASCII_PALETTE = " .'`^\",:;Il!i~+_-?][}{1)(|\\/<X7zjftLr-+=o*#MW&8%B@$";
    //string ASCII_PALETTE = "@%#&*+=-:. ";
   
    // 1. 이미지 로드
    cv::Mat src = cv::imread(_imagePath, cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cerr << "Error: Image not found at " << _imagePath << std::endl;
        return false;
    }

    // 2. ASCII 아트 생성
    std::string asciiArt;
    int height = (int)((double)src.rows / src.cols * _width * 0.5); // 세로 비율 조정
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

   
    // 3. 콘솔 출력
    std::cout << asciiArt << endl;

    

    return true;
}

static void Ascii_Movie(const string& _gifPath, int _width, short _x, short _y)
{
    cv::VideoCapture cap(_gifPath);
    if (!cap.isOpened()) {
        cerr << "GIF 로드 실패: " << _gifPath << endl;
        return;
    }
    
    while (running) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            cap.set(cv::CAP_PROP_POS_FRAMES, 0);
            continue;
        }

        // ASCII 변환
        cv::Mat gray;
        cv::resize(frame, frame, cv::Size(_width, (int)(frame.rows * _width / frame.cols * 0.4)));
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        string asciiFrame;
        for (int y = 0; y < gray.rows; y++) {
            for (int x = 0; x < gray.cols; x++) {
                int index = gray.at<uchar>(y, x) * 9 / 255;
                asciiFrame += "@%#*+=-:. "[index];
            }
            asciiFrame += "\n";
        }
        gMutex.lock();
        // 콘솔 커서를 GIF 출력 부분으로 이동
        Set_CursorPos(_x, _y);
        cout << asciiFrame << flush;
        gMutex.unlock();

        if (cv::waitKey(30) == 27) {
            running = false;
            break;
        }
    }
}








