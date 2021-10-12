//
// https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/
//

using Real = float;

constexpr bool VERBOSE = false;
constexpr Real EPSILON = 0.00001;

#define LOG_VAR(x)      { if constexpr (VERBOSE) { cout << #x << " = " << (x) << endl; } }

template<typename T>
struct vec2
{
    T x;
    T y;

    template<typename U>
    vec2(U x_, U y_) : x{static_cast<T>(x_)}, y{static_cast<T>(y_)} {}
    template<typename U>
    vec2(const vec2<U>& v) : vec2{v.x, v.y} {}
    template<typename U>
    vec2(const vector<U>& coords) : vec2{coords[0], coords[1]} {}

    friend T len_sq(const vec2<T>& v) { return v.x * v.x + v.y * v.y; }
    friend T dist_sq(const vec2<T>& v1, const vec2<T>& v2) { return len_sq(v2 - v1); }
    vec2<T> operator-() const { return {-x, -y}; }
    friend vec2<T> operator+(const vec2<T>& v1, const vec2<T>& v2) { return {v1.x + v2.x, v1.y + v2.y}; }
    friend vec2<T> operator-(const vec2<T>& v1, const vec2<T>& v2) { return {v1.x - v2.x, v1.y - v2.y}; }
    friend vec2<T> operator*(const vec2<T>& v, T s) { return {v.x * s, v.y * s}; }
    friend vec2<T> operator*(T s, const vec2<T>& v) { return {s * v.x, s * v.y}; }
    friend ostream& operator<<(ostream& out, const vec2& v) { return out << '[' << v.x << ',' << v.y << ']'; }
    friend ostream& operator<<(ostream& out, const vector<vec2>& vv) { out << '['; for (const auto& v : vv) { out << v; }; return out << ']'; }
};

using vec2i = vec2<int>;
using vec2r = vec2<Real>;

class Solution
{
    template<typename T>
    vec2<T> perpendicular(const vec2<T>& v)
    {
        return {v.y, -v.x};
    }
    
    pair<vec2r, vec2r> findCircleCenters(const vec2i& a, const vec2i& b, int r)
    {
        const auto m = 0.5 * vec2r{a + b};
        LOG_VAR(m);
        
        const auto ab = b - a;
        
        const auto p0 = perpendicular(ab);
        LOG_VAR(p0);

        const auto ab_len_sq = len_sq(ab);
        LOG_VAR(ab_len_sq);

        Real h = sqrt(static_cast<Real>(r*r) / static_cast<Real>(ab_len_sq) - 0.25);
        
        const auto c0 = m + h * vec2r{p0};
        LOG_VAR(c0);

        const auto c1 = m - h * vec2r{p0};
        LOG_VAR(c1);

        return {c0, c1};
    }
    
public:
    int numPoints(vector<vector<int>>& points, int r)
    {
        const int vv_len = (int)points.size();
        
        if (vv_len <= 1)
            return vv_len;
        
        vector<vec2i> vv;
        vv.reserve(vv_len);

        if (vv_len >= 10)
        {
            vec2i vv_min = vec2i{numeric_limits<int>::max(), numeric_limits<int>::max()};
            vec2i vv_max = vec2i{numeric_limits<int>::min(), numeric_limits<int>::min()};

            for (const auto& point : points) {
                const auto v = vec2i{point};
                vv.push_back(v);
                vv_min.x = min(vv_min.x, v.x);
                vv_min.y = min(vv_min.y, v.y);
                vv_max.x = max(vv_max.x, v.x);
                vv_max.y = max(vv_max.y, v.y);
            }

            if (vv_max.y - vv_min.y > vv_max.x - vv_min.x) {
                for (auto& v : vv) {
                    swap(v.x, v.y);
                }
            }
        }
        else
        {
            for (const auto& point : points) {
                vv.push_back(point);
            }            
        }

        sort(begin(vv), end(vv), [](const auto& v1, const auto& v2) {
            return v1.x < v2.x;
        });

        LOG_VAR(vv);

        const int diam = 2 * r;
        const int r_sq = r * r;
        const Real r_sq_for_check = static_cast<Real>(r_sq) + EPSILON;
        int best = 1;
        
        for (int i0 = 0; i0 < vv_len - 1; ++i0)
        {
            LOG_VAR(i0);
            LOG_VAR(vv[i0]);
            
            for (int i1 = i0 + 1; i1 < vv_len; ++i1)
            {
                LOG_VAR(i1);
                LOG_VAR(vv[i1]);
                
                if (vv[i1].x - vv[i0].x > diam)
                    break;
                
                if (dist_sq(vv[i0], vv[i1]) > 4 * r_sq)
                    continue;

                auto centers = findCircleCenters(vv[i0], vv[i1], r);
                
                for (const auto& c : {centers.first, centers.second})
                {
                    int c_x1 = static_cast<int>(ceil(c.x)) - r;
                    int c_x2 = static_cast<int>(floor(c.x)) + r;
                    LOG_VAR(c_x1);
                    LOG_VAR(c_x2);

                    int point_count = 2;

                    for (int i2 = i0 - 1; i2 >= 0 && vv[i2].x >= c_x1; --i2)
                    {
                        if (dist_sq(c, vec2r{vv[i2]}) <= r_sq_for_check) {
                            ++point_count;
                        }
                    }

                    for (int i2 = i0 + 1; i2 < i1; ++i2)
                    {
                        if (dist_sq(c, vec2r{vv[i2]}) <= r_sq_for_check) {
                            ++point_count;
                        }
                    }
                    
                    for (int i2 = i1 + 1; i2 < vv_len && vv[i2].x <= c_x2; ++i2)
                    {
                        if (dist_sq(c, vec2r{vv[i2]}) <= r_sq_for_check) {
                            ++point_count;
                        }
                    }

                    LOG_VAR(point_count);
                    best = max(best, point_count);
                }
            }
        }

        return best;
    }
};
