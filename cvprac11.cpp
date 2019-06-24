#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

int main()
{
	cv::Mat image;

	// パスには\\ではなく/を使用すること!
	string filename = "baboon.jpg";
	image = cv::imread(("D:/opencv/sources/samples/data/" + filename), cv::IMREAD_GRAYSCALE);

	if (image.empty() == true) {
		return;
	}

	cv::imshow(filename, image);

	cv::waitKey(0);

	return 0;
}
