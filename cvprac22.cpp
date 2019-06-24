#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

int main()
{
    string filename = "vtest.avi";
    /* TODO: filenameを.でsplitしてファイル名だけを取り出す
    */
    string outputdir = "D:/CppProject/cvprograms/";
    cv::VideoCapture cap;

    cap.open(("D:/opencv/sources/samples/data/" + filename));
    if (cap.isOpened() == false) {
        return 0;
    }

    int total_frames = (int)cap.get(cv::CAP_PROP_FRAME_COUNT);

    double fps = cap.get(cv::CAP_PROP_FPS);
    int period = (int)(1000 / fps);
    int savenum = 0;
    bool backflug = false;

    cv::Mat frame;

    while (1) {
        cap >> frame;

        if (frame.empty() == true) {
            break;
        }

        cv::imshow("Video", frame);

        int n = (int)cap.get(cv::CAP_PROP_POS_FRAMES);
        cout << "\rFrame:" << setw(4) << n << '/' << total_frames << flush;
        if (backflug) {
            cap.set(cv::CAP_PROP_POS_FRAMES, n-2);
            n -= 2;
        }

        int key = cv::waitKey(period);

        switch (key)
        {
        case ' ':
            cout << "\nPause" << endl;
            cv::waitKey(0);
            break;
        case 'r':
            cout << "\nRestart" << endl;
            cap.set(cv::CAP_PROP_POS_FRAMES, 0);
            break;
        case 's':
            cout << "\nSkip" << endl;
            cap.set(cv::CAP_PROP_POS_FRAMES, n + 30);
            break;
        case 'w':
            cv::imwrite((outputdir + "vtest_" + to_string(savenum) + ".bmp"), frame);
            // cv::imwrite(("vtest_" + to_string(savenum) + ".bmp"), frame); slnディレクトリに保存される
            ++savenum;
            break;
        case 'p':
            cout << "\nBack" << endl;
            cap.set(cv::CAP_PROP_POS_FRAMES, n - 30);
            break;
        case 'b':
            cout << "\nReverse" << endl;
            backflug = !backflug;
            break;
        default:
            break;
        }
        if (key == 0x1b) {
            break;
        }
        

    }

    return 0;
}