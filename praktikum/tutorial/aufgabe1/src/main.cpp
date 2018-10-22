#include <stdio.h>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  if (argc != 2)
    {
      printf("usage: %s <image_path>\n", argv[0]);
    }
  
  cv::Mat image;
  image = cv::imread(argv[1], 1);

  if (!image.data)
    {
      printf("No image data\n");
      return -1;
    }
  cv::namedWindow("Display image", cv::WINDOW_AUTOSIZE);
  cv::imshow("Display image", image);

  cv::waitKey(0);

  return 0;
}
