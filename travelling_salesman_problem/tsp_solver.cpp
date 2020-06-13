//
// Travelling Salesman Problem Solver
//
#include <cmath>
#include <string>
#include <random>
#include <cassert>
#include <fstream>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr char program_title[] = "Travelling Salesman Problem Solver";

struct ProgramArgs
{
    string input_file_path;
    string output_html_path;

    friend ostream& operator<<(ostream& out, const ProgramArgs& v) {
        return out <<
            "    input_file_path  : " << v.input_file_path << '\n' <<
            "    output_html_path : " << v.output_html_path;
    }
};

ProgramArgs parse_args(int argc, char* argv[])
{
    if (argc != 3)
        throw runtime_error{"Program requires 2 argument: <input_file:path> <output_html_path:path>"};

    return { argv[1], argv[2] };
}

struct vec2
{
    int x;
    int y;

    friend vec2 operator-(vec2 a, vec2 b) noexcept { return {a.x - b.x, a.y - b.y}; }
    friend ostream& operator<<(ostream& out, vec2 v) { return out << '[' << v.x << ',' << v.y << ']'; }
    friend bool operator==(vec2 a, vec2 b) noexcept { return a.x == b.x && a.y == b.y; }

    friend int dist_sq(const vec2& a, const vec2& b) noexcept {
        const auto d = b - a;
        return d.x * d.x + d.y * d.y;
    }

    friend double dist(const vec2& a, const vec2& b) noexcept {
        return sqrt((double)dist_sq(a, b));
    }
};

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& vv)
{
    out << "[ ";
    for (const auto& v : vv) out << v << ' ';
    return out << ']';
}

vector<vec2> read_points(string input_file_path)
{
    auto in = ifstream{input_file_path};
    auto points = vector<vec2>{};

    int count {};
    in >> count;

    while (count-- > 0)
    {
        auto v = vec2{};
        in >> v.x >> v.y;
        points.push_back(v);
    }

    return points;
}

struct Slope
{
    int p;
    int q;

    explicit Slope(const vec2& v) noexcept : p{v.y}, q{v.x} { assert(v.x > 0); }
    Slope(const vec2& left, const vec2& right) noexcept : Slope{right - left} {}

    friend bool operator==(const Slope& a, const Slope& b) noexcept { return a.p * b.q == b.p * a.q; }
    friend bool operator!=(const Slope& a, const Slope& b) noexcept { return a.p * b.q != b.p * a.q; }
    friend bool operator<(const Slope& a, const Slope& b) noexcept { return a.p * b.q < b.p * a.q; }
    friend bool operator<=(const Slope& a, const Slope& b) noexcept { return a.p * b.q <= b.p * a.q; }
    friend bool operator>(const Slope& a, const Slope& b) noexcept { return a.p * b.q > b.p * a.q; }
    friend bool operator>=(const Slope& a, const Slope& b) noexcept { return a.p * b.q >= b.p * a.q; }
};

vector<int> find_convex_hull(const vector<vec2>& points)
{
    auto ordered = vector<int>(points.size());
    iota(begin(ordered), end(ordered), 0);
    sort(begin(ordered), end(ordered), [&](int a, int b) { return points[a].x < points[b].x || (points[a].x == points[b].x && points[a].y < points[b].y); });

    auto top_trail = vector<int>{};
    auto bottom_trail = vector<int>{};
    top_trail.reserve(points.size());
    bottom_trail.reserve(points.size() / 2);

    auto foreach_bar = [&](auto fn) {
        int i0 = 0;
        for (int i = 1; i < (int)ordered.size(); ++i) {
            if (points[ordered[i]].x != points[ordered[i0]].x) {
                fn(i0, i);
                i0 = i;
            }
        }
        fn(i0, (int)ordered.size());
    };

    int top_start {};

    foreach_bar([&](int i_start, int i_end) {
        if (i_start == 0) {
            bottom_trail.push_back(ordered[i_start]);

            while (i_start < i_end) {
                top_trail.push_back(ordered[i_start]);
                ++i_start;
            }
            top_start = i_end - 1;
        }
        else {
            int point_hi_index = ordered[(size_t)i_end - 1];
            const vec2& point_hi = points[point_hi_index];

            for (int i = (int)top_trail.size() - 1; true; --i) {
                if (i == top_start ||
                    Slope{points[top_trail[i]], point_hi} <= Slope{points[top_trail[(size_t)i - 1]], points[top_trail[i]]})
                {
                    top_trail.erase(begin(top_trail) + i + 1, end(top_trail));
                    break;
                }
            }

            int point_lo_index = ordered[i_start];
            const vec2& point_lo = points[point_lo_index];

            if (bottom_trail.size() > 1) {
                for (int i = (int)bottom_trail.size() - 1; true; --i) {
                    if (i == 0 ||
                        Slope{points[bottom_trail[i]], point_lo} >= Slope{points[bottom_trail[(size_t)i - 1]], points[bottom_trail[i]]})
                    {
                        bottom_trail.erase(begin(bottom_trail) + i + 1, end(bottom_trail));
                        break;
                    }
                }
            }

            if (i_end == (int)ordered.size()) {
                while (--i_end >= i_start) {
                    top_trail.push_back(ordered[i_end]);
                }
            }
            else {
                top_trail.push_back(point_hi_index);
                bottom_trail.push_back(point_lo_index);
            }
        }
    });

    top_trail.insert(end(top_trail), rbegin(bottom_trail), rend(bottom_trail) - 1);
    return top_trail;
}

/* An idea to be considered:

    struct Dist
    {
        int d_sq = 0;
        //double d = 0.0;
    };

    class DistMap
    {
        const size_t _stride;
        vector<Dist> _dist_mat;

    public:
        DistMap(const vector<vec2>& points) :
            _stride{points.size()}
        {
            _dist_mat.resize(_stride * _stride);

            for (size_t i0 = 0; i0 < _stride - 1; ++i0) {
                for (size_t i1 = i0 + 1; i1 < _stride; ++i1) {
                    int d_sq = dist_sq(points[i0], points[i1]);
                    //double d = sqrt((double)d_sq);
                    _dist_mat[i0 * _stride + i1] = _dist_mat[i1 * _stride + i0] = Dist{d_sq};
                }
            }
        }

        const Dist& operator()(int i0, int i1) const noexcept {
            assert(i0 >= 0 && i0 < _stride);
            assert(i1 >= 0 && i1 < _stride);
            return _dist_mat[i0 * _stride + i1];
        };
    };
*/

vector<int> others(size_t count, vector<int>& trail)
{
    auto present = vector<bool>(count);

    int present_count = 0;
    for (int i : trail) {
        present[i] = true;
        ++present_count;
    }

    auto others = vector<int>{};
    others.reserve(present_count);

    for (int i = 0; i < (int)present.size(); ++i) {
        if (!present[i]) {
            others.push_back(i);
        }
    }

    return others;
}

struct EdgeBestInclusion
{
    double cost;
    int index;
};

void include_to_trail_greedily(const vector<vec2>& points, vector<int>& trail)
{
    auto edges = vector<EdgeBestInclusion>(trail.size());

    auto wild = others(points.size(), trail);

    auto find_best_point_for_edge_inclusion = [&](int edge_index) {
        auto& edge = edges[edge_index];
        edge = EdgeBestInclusion{numeric_limits<double>::max(), -1};
        const vec2& p0 = points[trail[edge_index]];
        const vec2& p1 = points[trail[(edge_index + 1) % (int)trail.size()]];

        for (int candidate_index : wild) {
            const vec2& candidate_point = points[candidate_index];
            double cost = dist(p0, candidate_point) + dist(candidate_point, p1);

            if (cost < edge.cost) {
                edge.cost = cost;
                edge.index = candidate_index;
            }
        }

        assert(edge.index != -1);
        edge.cost -= dist(p0, p1);
    };

    for (int edge_index = 0; edge_index < (int)edges.size(); ++edge_index) {
        find_best_point_for_edge_inclusion(edge_index);
    }

    while (true)
    {
        auto best_iter = min_element(begin(edges), end(edges), [](const auto& e1, const auto& e2) {
            return e1.cost < e2.cost;
        });
        const int best_edge_index = (int)distance(begin(edges), best_iter);
        const int included_point_index = best_iter->index;

        trail.insert(begin(trail) + best_edge_index + 1, included_point_index);
        edges.insert(best_iter + 1, EdgeBestInclusion{{}, included_point_index});
        wild.erase(find(begin(wild), end(wild), included_point_index));

        if (wild.empty()) {
            break;
        }

        for (int edge_index = 0; edge_index < (int)edges.size(); ++edge_index) {
            if (edges[edge_index].index == included_point_index) {
                find_best_point_for_edge_inclusion(edge_index);
            }
        }
    }
}

bool optimize(const vector<vec2>& points, vector<int>& trail)
{
    assert(points.size() == trail.size());
    bool swapped = false;

    auto neightbor_indices = [&](int i) -> pair<int, int> {
        const int i0 = (i > 0) ? i - 1 : (int)trail.size() - 1;
        const int i1 = (i + 1) % (int)trail.size();
        return {trail[i0], trail[i1]};
    };

    auto try_swap = [&](int edge0, int edge1) -> bool {
        int i0_a = trail[edge0];
        int i0_b = trail[(edge0 + 1) % (int)trail.size()];
        int i1_a = trail[edge1];
        int i1_b = trail[(edge1 + 1) % (int)trail.size()];

        if (i0_b == i1_a || i0_a == i1_b) {
            return false;
        }

        double gain = 0.0;

        gain += dist(points[i0_a], points[i0_b]);
        gain += dist(points[i1_a], points[i1_b]);

        gain -= dist(points[i0_a], points[i1_a]);
        gain -= dist(points[i0_b], points[i1_b]);

        if (gain > 0.0) {
            ++edge0;
            while (edge0 < edge1) {
                swap(trail[edge0++], trail[edge1--]);
            }
            return true;
        }
        else {
            return false;
        }
    };

    for (int i0 = 0; i0 < (int)trail.size() - 1; ++i0) {
        for (int i1 = i0 + 1; i1 < (int)trail.size(); ++i1) {
            swapped |= try_swap(i0, i1);
        }
    }

    return swapped;
}

double evaluate_trail(const vector<vec2>& points, const vector<int>& trail)
{
    auto dists = vector<double>{};
    dists.reserve(trail.size());

    for (size_t i0 = 0; i0 < trail.size(); ++i0) {
        const size_t i1 = (i0 + 1) % trail.size();
        dists.push_back(dist(points[trail[i0]], points[trail[i1]]));
    }

    sort(begin(dists), end(dists));  // To improve the resulting accuracy just a little.
    return accumulate(begin(dists), end(dists), 0.0);
}

vector<int> solve_tsp(const vector<vec2>& points)
{
    cout << "Finding convex hull..." << endl;
    auto trail = find_convex_hull(points);

    cout << "Including all the nodes..." << endl;
    include_to_trail_greedily(points, trail);

    double trail_len = evaluate_trail(points, trail);
    cout << "    length : " << trail_len << endl;

    for (int i = 1; true; ++i)
    {
        cout << "Optimizing #" << i << "..." << endl;

        auto trail_copy = trail;

        bool changed = optimize(points, trail_copy);

        double trail_copy_len = evaluate_trail(points, trail_copy);

        if (trail_copy_len >= trail_len || !changed) {
            cout << "    length : " << trail_copy_len << " (discarding)" << endl;
            break;
        }
        else {
            cout << "    length : " << trail_copy_len << endl;
            trail = move(trail_copy);
            trail_len = trail_copy_len;
        }
    }

    return trail;
}

pair<vec2, vec2> minmax(const vector<vec2>& points)
{
    auto lo = vec2{numeric_limits<int>::max(), numeric_limits<int>::max()};
    auto hi = vec2{numeric_limits<int>::min(), numeric_limits<int>::min()};

    for (const auto& p : points)
    {
        lo.x = min(lo.x, p.x);
        lo.y = min(lo.y, p.y);
        hi.x = max(hi.x, p.x);
        hi.y = max(hi.y, p.y);
    }

    return {lo, hi};
}

void save_svg(string output_file_path, const vector<vec2>& points, const vector<int>& trail)
{
    const auto graph_size = (points.size() >= 4500) ? vec2{1600, 1600} : vec2{800, 800};

    auto [p_min, p_max] = minmax(points);
    const int margin = 25;
    p_min.x -= margin;
    p_min.y -= margin;
    p_max.x += margin;
    p_max.y += margin;
    const int x0 = p_min.x;
    const int y0 = p_min.y;
    const int y1 = p_max.y;
    const int dx = p_max.x - p_min.x;
    const int dy = p_max.y - p_min.y;
    const int db = max(dx, dy);

    auto out = ofstream{output_file_path};

    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "<body>\n";
    out << "<h1>Travelling Salesman Problem Solution</h1>\n";
    out << "<h2>Total length: " << to_string(evaluate_trail(points, trail)) << "</h2>\n";
    out << "<svg height='" << graph_size.x << "' width='" << graph_size.y << "'>\n";

    auto transform = [&](vec2 p) { return vec2{(p.x - x0) * graph_size.x / dx, (y1 - p.y) * graph_size.y / dy}; };

    for (int i0 = 0; i0 < (int)trail.size(); ++i0)
    {
        const int i1 = (i0 + 1) % (int)trail.size();

        const auto pt0 = transform(points[trail[i0]]);
        const auto pt1 = transform(points[trail[i1]]);

        out << "<line x1='" << pt0.x << "' y1='" << pt0.y << "' x2='" << pt1.x << "' y2='" << pt1.y << "' style='stroke:rgb(255,0,0);stroke-width:1' />\n";
    }

    for (const auto& p : points)
    {
        const auto pt = transform(p);
        out << "<circle cx='" << pt.x << "' cy='" << pt.y << "' r='1.5' stroke='black' stroke-width='1' fill='red' />\n";
    }

    out << "</svg>\n";
    out << "</body>\n";
    out << "</html>\n";
}

int main(int argc, char* argv[])
{
    try
    {
        const auto args = parse_args(argc, argv);
        cout << program_title << '\n' << args << endl;

        auto points = read_points(args.input_file_path);
        cout << "Read " << (int)points.size() << " points" << endl;

        if (points.empty())
            throw runtime_error{"Dataset empty"};

        auto trail = solve_tsp(points);

        save_svg(args.output_html_path, points, trail);

        cout << "Done." << endl;
        return 0;
    }
    catch (exception& ex)
    {
        cerr << ex.what() << endl;
        return -1;
    }
}
