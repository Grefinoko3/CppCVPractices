#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

int main()
{
	string srcdir = "D:/opencv/sources/samples/data/";
    string file1name = "Tram.mp4";
	string file2name = "Mobility.mp4";
	string outputdir = "D:/CppProject/cvprograms/";

	//以下演習1
    cv::VideoCapture cap1;
    cv::VideoCapture cap2;

    cap1.open((srcdir + file1name));
	cap2.open((srcdir + file2name));
    if ((cap1.isOpened() && cap2.isOpened()) == false) {
        return -1;
    }

	int width, height, fourcc;
	double fps;
	
	if ((int)cap1.get(cv::CAP_PROP_FRAME_WIDTH) != (int)cap2.get(cv::CAP_PROP_FRAME_WIDTH)) {
		return -1;
	}
	if ((int)cap1.get(cv::CAP_PROP_FRAME_HEIGHT != (int)cap2.get(cv::CAP_PROP_FRAME_HEIGHT))) {
		return -1;
	}
	width = (int)cap1.get(cv::CAP_PROP_FRAME_WIDTH);
	height = (int)cap1.get(cv::CAP_PROP_FRAME_HEIGHT);
	fps = cap1.get(cv::CAP_PROP_FPS) < cap2.get(cv::CAP_PROP_FPS) ? cap1.get(cv::CAP_PROP_FPS) : cap2.get(cv::CAP_PROP_FPS);

	// ビデオフォーマットの指定
	fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');	// Xvid  / ファイル拡張子 .avi
	// 参考：その他のフォーマット
	//	fourcc = cv::VideoWriter::fourcc('D', 'I', 'V', 'X');	// DivX  / .avi
	//	fourcc = cv::VideoWriter::fourcc('H', '2', '6', '4');	// H.264 / .wmv
	//	fourcc = cv::VideoWriter::fourcc('V', 'P', '9', '0');	// VP9   / .avi
	//	fourcc = cv::VideoWriter::fourcc('W', 'M', 'V', '2');	// WMV8  / .wmv
	//	fourcc = cv::VideoWriter::fourcc('W', 'M', 'V', '3');	// WMV9  / .wmv
	//	fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');	// ISO MPEG-4 / .mp4
	//	fourcc = cv::VideoWriter::fourcc('M', 'P', '4', '3');	// MS MPEG-4  / .avi
	//	fourcc = cv::VideoWriter::fourcc('D', 'I', 'B', ' ');	// RGB非圧縮  / .avi

	cv::VideoWriter writer;
	writer.open((outputdir + "OutVideo.avi"), fourcc, fps, cv::Size(width, height));

	cv::Mat frame, dst;
    while (1) {

		cap1 >> frame;
		if (frame.empty() == true) {
			cap2 >> frame; // cap1のフレームが終わっていればcap2からフレーム取り込み
			if (frame.empty() == true) {
				break;
			}
		}

		//cv::imshow(("Converting..." + to_string(n) + '/' + to_string(frames)), frame); 
		// 文字列の結合はできるが、ウィンドウ名が違うので毎フレーム新しいウィンドウができる
		cv::imshow("Converting...", frame);

		cv::flip(frame, dst, 1);
		writer << dst;
		cv::waitKey(1);
    }
	//演習1終わり

	//演習2
	int start_t, end_t;
	start_t = 5;
	end_t = 25;

	cap1.open((srcdir + file1name));
	if (cap1.isOpened() == false) {
		return -1;
	}

	width = (int)cap1.get(cv::CAP_PROP_FRAME_WIDTH);
	height = (int)cap1.get(cv::CAP_PROP_FRAME_HEIGHT);
	fps = cap1.get(cv::CAP_PROP_FPS);
	fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');	// Xvid  / ファイル拡張子 .avi
	writer.open((outputdir + "OutVideo_23_2.avi"), fourcc, fps, cv::Size(width, height));
	
	cap1.set(cv::CAP_PROP_POS_FRAMES, (int)((double)start_t*fps));
	int current_f;
	while (true) {

		cap1 >> frame;
		if (frame.empty() == true) {
			break;
		}

		cv::imshow("Converting2...", frame);
		current_f = (int)cap1.get(cv::CAP_PROP_POS_FRAMES);
		if (current_f == (int)((double)end_t*fps)) {
			break;
		}

		writer << frame;
		cv::waitKey(1);
	}

    return 0;
}