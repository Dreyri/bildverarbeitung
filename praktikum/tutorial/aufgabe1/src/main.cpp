#include <array>
#include <string_view>

#include <stdio.h>
#include <opencv2/opencv.hpp>

std::array<cv::Mat, 4> bgr2cmy(const cv::Mat& img) {
  std::array<cv::Mat, 4> cmy;

  for (auto& el : cmy) {
    el = cv::Mat(img.size(), CV_8UC1);
  }

  std::array<cv::Mat, 3> bgr;
  cv::split(img, bgr.data());

  constexpr uint8_t max_u8 = std::numeric_limits<uint8_t>::max();

  for (int y = 0; y < img.rows; ++y) {
    for (int x = 0; x < img.cols; ++x) {
      uint8_t b = bgr[0].at<uint8_t>(x, y);
      uint8_t g = bgr[1].at<uint8_t>(x, y);
      uint8_t r = bgr[2].at<uint8_t>(x, y);

      cmy[1].at<uint8_t>(x, y) = max_u8 - r;
      cmy[2].at<uint8_t>(x, y) = max_u8 - g;
      cmy[3].at<uint8_t>(x, y) = max_u8 - b;
    }
  }

  cv::merge(&cmy[1], 3, cmy[0]);

  return cmy;
}

cv::Mat anaglyph(const cv::Mat& img_left, const cv::Mat& img_right) {
  std::array<cv::Mat, 3> split_left; // r 2
  std::array<cv::Mat, 3> split_right; // b g 0 1

  cv::Mat res(img_left.size(), CV_8UC3);

  cv::split(img_left, split_left.data());
  cv::split(img_right, split_right.data());

  // keep right first 2 channels
  split_right[2] = split_left[2];
  // TODO: fix this error

  cv::merge(split_right.data(), split_right.size(), res);
  return res;
}

cv::Mat bgr2yiq(const cv::Mat& img)
{
  cv::Mat converted;
  //cv::cvtColor(img, converted, CV_
}

void display_images(const cv::Mat& img, const std::string_view title)
{
  cv::namedWindow(title.data(), cv::WINDOW_AUTOSIZE);
  cv::imshow(title.data(), img);
  cv::waitKey(0);
  cv::destroyWindow(title.data());
}

template<size_t N>
void display_images(const std::array<cv::Mat, N>& images, const std::array<const std::string_view, N> titles)
{
  for (int i = 0; i < N; ++i) {
    display_images(images[i], titles[i]);
  }
}

int main(int argc, char** argv) {
  // 1. lesen sie ein beliebiges Bild ein
  cv::Mat image;
  const char* aufgabe_cstr = argv[1];
  const char* img1 = argv[2];
  const char* img2 = argv[2];

  int aufgabe = std::atoi(aufgabe_cstr);

  if (aufgabe == 1 || aufgabe == 2) {

    image = cv::imread(img1, CV_LOAD_IMAGE_COLOR);

    if (!image.data)
    {
	printf("No image data\n");
	return -1;
    }

    // 2. stellen sie das Bild in einem Fenster dar

    display_images(image, "image");
  }
  else if (aufgabe == 3) {
    // 3. zerlegen sie das Bild in 3 Kanalen

    image = cv::imread(img1, CV_LOAD_IMAGE_COLOR);

    std::array<cv::Mat, 3> bgr;
    cv::split(image, bgr.data());

    cv::imwrite("blue.png", bgr[0]);
    cv::imwrite("green.png", bgr[1]);
    cv::imwrite("red.png", bgr[2]);

    display_images(bgr, {"blue", "green", "red"});
  }

  // 4. TODO: figure out how to do anaglyphs

  else if (aufgabe == 4) {

    assert(argc >= 4 && "must pass 2 images");

    image = cv::imread(img1, CV_LOAD_IMAGE_COLOR);
    auto image2 = cv::imread(img2, CV_LOAD_IMAGE_COLOR);

    auto anaglyph_img = anaglyph(image, image2);

    display_images(anaglyph_img, "anaglyph");
  }

  else if (aufgabe == 5)
  {

    // 5. Konvertieren zu Farbraeumen und Anzeigen von Kanalen: HSV, CMY, YIQ, Lab

    // HSV
    std::array<cv::Mat, 4> hsv;
    cv::cvtColor(image, hsv[0], CV_BGR2HSV); // write hsv
    cv::split(image, &hsv[1]); // split channels in 1-3

    cv::imwrite("hsv.png", hsv[0]);
    cv::imwrite("hsv_h.png", hsv[1]);
    cv::imwrite("hsv_s.png", hsv[2]);
    cv::imwrite("hsv_v.png", hsv[3]);

    display_images(hsv, {"hsv", "h", "s", "v"});

    // CMY
    auto cmy = bgr2cmy(image);

    display_images(cmy, {"cmy", "c", "m", "y"});

    std::array<cv::Mat, 4> yiq;
  }

  return 0;
}
