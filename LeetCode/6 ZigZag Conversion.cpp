//
// https://leetcode.com/problems/zigzag-conversion/
//

constexpr bool VERBOSE = false;

#define LOG_VAR(x)  { if (VERBOSE) { cout << #x << " : " << x << endl; } }

class Solution
{
public:
    string convert(string s, int num_rows)
    {
        LOG_VAR(s);

        const int s_len = (int)s.size();
        LOG_VAR(s_len);

        LOG_VAR(num_rows);

        if (s_len <= 1 || num_rows == 1)
            return s;

        const int peak_stride = 2 * num_rows - 2;
        LOG_VAR(peak_stride);

        const int num_peaks = 1 + (s_len - 1) / peak_stride;
        LOG_VAR(num_peaks);

        const int last_peak_rest = (s_len - 1) % peak_stride;
        LOG_VAR(last_peak_rest);

        const int last_peak_last_row = min((s_len - 1) % peak_stride, num_rows - 1);
        LOG_VAR(last_peak_last_row);

        const int last_diagonal_first_row = (last_peak_rest >= num_rows) ? (peak_stride - last_peak_rest) % num_rows : numeric_limits<int>::max();
        LOG_VAR(last_diagonal_first_row);

        string o;
        o.reserve(s_len);

        for (int row = 0; row < num_rows; ++row)
        {
            const int base = row;

            for (int i = 0; i < num_peaks - 1; ++i)
            {
                o.push_back(s[base + i * peak_stride]);

                if (row > 0 && row < (num_rows - 1)) {
                    o.push_back(s[base + i * peak_stride + (peak_stride - 2 * row)]);
                }
            }

            if (row <= last_peak_last_row) {
                o.push_back(s[base + (num_peaks - 1) * peak_stride]);
            }

            if (row < last_peak_last_row && row >= last_diagonal_first_row) {
                o.push_back(s[base + (num_peaks - 1) * peak_stride + (peak_stride - 2 * row)]);
            }

        }

        return o;
    }
};
