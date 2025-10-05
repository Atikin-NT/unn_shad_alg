#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

struct Point {
    double _x, _y;
};

int number, kol;
std::vector<Point> points;

// поиск по тому, сколько точек можем накрыть радиусом
bool can_cover_with_radius(double radius) {
    std::vector<double> starts; // Массив для левых концов отрезков
    std::vector<double> ends;   // Массив для правых концов отрезков

    double radius_sq = radius * radius;

    // Для каждой точки генерируем отрезок возможных центров на оси Ox
    for (int i = 0; i < number; ++i) {
        double y_sq = points[i]._y * points[i]._y;
        // Если точка по модулю y дальше от оси, чем радиус, ее накрыть невозможно
        if (y_sq > radius_sq)
            continue;
        double dx = std::sqrt(radius_sq - y_sq);
        starts.push_back(points[i]._x - dx);
        ends.push_back(points[i]._x + dx);
    }
    
    // Если мы даже теоретически не можем накрыть 'kol' точек, то радиус мал
    if (starts.size() < kol) {
        return false;
    }
    
    // Метод сканирующей прямой для поиска максимального пересечения отрезков
    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());
    
    int current_overlap = 0;
    int max_overlap = 0;
    
    size_t i_a = 0, j = 0;
    while (i_a < starts.size()) {
        if (starts[i_a] <= ends[j]) { // Если следующее событие - начало отрезка
            current_overlap++;
            if (current_overlap > max_overlap)
                max_overlap = current_overlap;
            i_a++;
        } else { // Если следующее событие - конец отрезка
            current_overlap--;
            j++;
        }
    }
    
    // Если максимальное количество пересечений >= kol, то радиус достаточен
    return max_overlap >= kol;
}



int main() {
    // Ускорение ввода-вывода
    // std::ios_base::sync_with_stdio(false);

    std::cin >> number >> kol;
    points.resize(number);
    for (int i = 0; i < number; ++i) {
        std::cin >> points[i]._x >> points[i]._y;
    }

    // границы для поиска
    double left = 0.0;
    double right = 3000.0;

    for (int iter = 0; iter < 100; ++iter) {
        double mid = left + (right - left) / 2.0;
        if (can_cover_with_radius(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    std::cout << std::fixed << std::setprecision(6) << right << std::endl;

    return 0;
}
