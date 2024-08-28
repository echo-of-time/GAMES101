#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) 
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

/**
 * Divide the segment between two points with a ratio t.
 * @param p1 The first point.
 * @param p2 The second point.
 * @param t The ratio. 
 * t is in the range of [0, 1] 
 * and when t = 0, the new point is located at p1.
 */
cv::Point2f divideSegment(cv::Point2f p1, cv::Point2f p2, float t) 
{
    return cv::Point2f(p1.x + (p2.x - p1.x) * t, p1.y + (p2.y - p1.y) * t);
}

/**
 * Use de Casteljau's algorithm to calculate the point on the Bezier curve.
 */
cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm
    /**
     * Step of de Casteljau's algorithm
     * 1. Think about the the sequence of control points p0, p1,...,pn,
     *  and connect the adjacent points to form a segment.
     * 2. Subdivide the segment with ratio t:(1-t), 
     *  and get the new points of division.
     * 3. Use the new points sequence as new control points, 
     *  the size of which decrease one.
     * 4. If the control points only contain one points, return the point
     *  or back to the step 1 and pass the new control points sequence.
     */
    if (control_points.size() == 1) 
    {
        return control_points[0];
    }

    std::vector<cv::Point2f> control_points_new;
    for(int i = 0; i < control_points.size() - 1; i++) {
        control_points_new.push_back(
            divideSegment(control_points[i], control_points[i + 1], t));
    }
    
    return recursive_bezier(control_points_new, t);

}

/**
 * antialiasing for one point in the window.
 * calculate the average color of 8 points adjacent to the point and itself.
 */
void convolve(cv::Point &point, cv::Mat &window) {
    cv::Vec3i newColor = cv::Vec3i(0, 0, 0);
    int count = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newY = point.y + i;
            int newX = point.x + j;

            // 边界检查
            if (newY >= 0 && newY < window.rows && newX >= 0 && newX < window.cols) {
                newColor += window.at<cv::Vec3b>(newY, newX);
                count++;
            }
        }
    }

    // 计算平均颜色
    newColor /= count;
    window.at<cv::Vec3b>(point.y, point.x) = cv::Vec3b(newColor[0], newColor[1], newColor[2]);
}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    for (double t = 0; t <= 1.0; t += 0.001) {
        auto point = recursive_bezier(control_points, t);
        window.at<cv::Vec3b>(point.y, point.x) = cv::Vec3b(198, 230, 80);
    }
    // anti-aliasing
    for (int row = 0; row < window.rows; row++) {
        for (int col = 0; col < window.cols; col++) {
            cv::Point point = cv::Point(col, row);
            convolve(point, window);
        }
    }
}

int main() 
{
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) 
    {
        for (auto &point : control_points) 
        {
            cv::circle(window, point, 1, {255, 255, 255}, 2);
        }

        if (control_points.size() == 4) 
        {
            // naive_bezier(control_points, window);
              bezier(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

    return 0;
}
