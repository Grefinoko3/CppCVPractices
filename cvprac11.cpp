#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

int main()
{
	cv::Mat image;

	// �p�X�ɂ�\\�ł͂Ȃ�/���g�p���邱��!
	string filename = "baboon.jpg";
	image = cv::imread(("D:/opencv/sources/samples/data/" + filename), cv::IMREAD_GRAYSCALE);

	if (image.empty() == true) {
		return;
	}

	cv::imshow(filename, image);

	cv::waitKey(0);

	return 0;
}
