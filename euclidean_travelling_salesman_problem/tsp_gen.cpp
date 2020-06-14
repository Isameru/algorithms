//
// Input Data Generator for the Travelling Salesman Problem
//
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr char program_title[] = "Input Data Generator for the Travelling Salesman Problem";

struct ProgramArgs
{
    string output_file_path;
    int point_count;
    int range;

    friend ostream& operator<<(ostream& out, const ProgramArgs& v) {
        return out <<
            "    output_file_path : " << v.output_file_path << '\n' <<
            "    point_count      : " << v.point_count << '\n' <<
            "    range            : " << v.range;
    }
};

ProgramArgs parse_args(int argc, char* argv[])
{
    if (argc != 4)
        throw runtime_error{"Program requires 3 arguments: <output_file:path> <point_count:int> <range:int>"};

    return { argv[1], atoi(argv[2]), atoi(argv[3]) };
}

class RandGen
{
    default_random_engine _engine;
    uniform_int_distribution<int> _distrib;
public:
    RandGen(int range) : _engine{random_device{}()}, _distrib{-range, range} {}
    auto& engine() { return _engine; }
    int operator()() { return _distrib(_engine); }
};

struct vec2
{
    int x;
    int y;

    friend bool operator==(vec2 a, vec2 b) { return a.x == b.x && a.y == b.y; }
};

int main(int argc, char* argv[])
{
    try
    {
        const auto args = parse_args(argc, argv);
        cout << program_title << '\n' << args << endl;

        // Generate unique points.
        auto points = [&](){
            auto points = vector<vec2>{};
            points.reserve(args.point_count);
            auto rand_gen = RandGen{args.range};

            while ((int)points.size() < args.point_count)
            {
                points.push_back({rand_gen(), rand_gen()});
            }

            sort(begin(points), end(points), [](const auto& a, const auto& b) {
                if (a.x < b.x) return true;
                if (a.x > b.x) return false;
                if (a.y < b.y) return true;
                return false;
            });

            auto nend = unique(begin(points), end(points));
            points.erase(nend, end(points));

            shuffle(begin(points), end(points), rand_gen.engine());

            return points;
        }();

        // Write all the generated point to the output file.
        {
            auto out = ofstream{args.output_file_path};
            out << (int)points.size();
            for (const auto p : points)
                out << '\n' << p.x << ' ' << p.y;
        }

        cout << "Done." << endl;
        return 0;
    }
    catch (exception& ex)
    {
        cerr << ex.what() << endl;
        return -1;
    }
}
