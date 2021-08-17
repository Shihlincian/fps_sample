#include <stdio.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/imgproc.hpp>
#ifdef _WIN32
#include <windows.h>
#include <time.h>
#endif

using namespace cv;
using namespace std;

float fps()
{
	static bool firstCount = true;
	static bool startCount = true;
#ifdef WIN32
	static double currentTime = 0;
	static double previousTime = 0;
#elif (__linux__)
	static struct timeval previousTime, currentTime;
#endif
	static float avgDuration = 0.f;
	static float alpha = 1.f / 100.f; // sample amount = 100


	float fps = 0;

	if (firstCount)
	{
		firstCount = false;
#ifdef WIN32
		currentTime = clock();
#elif (__linux__)
		gettimeofday(&currentTime, NULL);
#endif
	}
	else
	{
		previousTime = currentTime;
#ifdef WIN32
		currentTime = clock();
		long deltaTime;
		deltaTime = ((double)1000 * ((currentTime - previousTime) / CLOCKS_PER_SEC));
#elif (__linux__)
		gettimeofday(&currentTime, NULL);
		long deltaTime, seconds, useconds;
		seconds = currentTime.tv_sec - previousTime.tv_sec;
		useconds = currentTime.tv_usec - previousTime.tv_usec;
		deltaTime = (seconds * 1000 + useconds / 1000.0) + 0.5;
#endif

		if (startCount)
		{
			avgDuration = static_cast<float>(deltaTime);
			startCount = false;
		}
		else
		{
			avgDuration = avgDuration * (1 - alpha) + deltaTime * alpha;
		}

		fps = static_cast<float>(1.f / avgDuration * 1000);
	}

	return fps;
}

int main()
{
	cv::Mat image;

	cv::VideoCapture cap;
	cap.open(0);

	while (cap.isOpened())
	{
		float _fps = fps();

		cap >> image;

		cv::putText(image, "fps = " + std::to_string(_fps), cv::Point(0, 80), 0, 2, cv::Scalar(255, 0, 0), 3);

		cv::imshow("Webcam live", image);

		if (cv::waitKey(20) == 27) break;
	}

	return 0;
}
