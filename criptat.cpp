#include <bits/stdc++.h>
using namespace std;

/* Structure that stores word information */
struct Word {
    int lcnt;      // dominant letter count
    double ratio;  // lcnt / length
    int length;    // length of word
};

class Task {
 public:
    /* Function that runs the code */
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    vector<string> words;

    /* Reading function */
    void read_input() {
        ifstream fin("criptat.in");
        fin >> n;

        words.push_back("");
        for (int i = 1; i <= n; i++) {
            string word;
            fin >> word;
            words.push_back(word);
        }

        fin.close();
    }

    /* Comparator for sorting */
    struct comparator {
        inline bool operator() (const Word& obj1, const Word& obj2) {
            // Compare ratios
            if (obj1.ratio == obj2.ratio) {
                // Then lengths
                return obj2.length < obj1.length;
            }
            return obj2.ratio < obj1.ratio;
        }
    };

    /* Function that calculates the result */
    int get_result() {
        vector<vector<Word>> wordsets(26, vector<Word>(n + 1));
        /* wordsets - matrix which stores information for each word
        and dominant letter */

        // Fill wordsets with the words' data
        for (int i = 0; i < 26; i++) {
            for (int j = 1; j <= n; j++) {
                int len = words[j].length();
                int k = 0;

                for (char letter : words[j]) {
                    if (letter - 'a' == i) {
                        k++;
                    }
                }
                wordsets[i][j].lcnt = k;
                wordsets[i][j].length = len;
                wordsets[i][j].ratio = k * 1.0 / len;
            }
        }

        vector<vector<int>> dp(27, vector<int>(n + 1, 0));
        /* dp - holds the solutions for each "smaller problem" resulting
        in the final solution */

        for (int i = 0; i < 26; ++i) {
            // Sort each word set
            sort(wordsets[i].begin() + 1, wordsets[i].end(), comparator());

            if ((double) wordsets[i][1].lcnt > wordsets[i][1].length / 2.0) {
                // Initialize with length the first word
                dp[i + 1][1] = wordsets[i][1].length;
            } else {
                continue;
            }

            // For the rest of the words
            for (int j = 2; j <= n; j++) {
                int max = -1, index;

                /* Find the max value of dp[i + 1] from the first to the
                (j-1)-th that checks the condition */
                for (int k = 1; k < j; k++) {
                    if ((double) (wordsets[i][k].lcnt + wordsets[i][j].lcnt) >
                        (dp[i + 1][k] + wordsets[i][j].length) / 2.0) {
                        if (max < dp[i + 1][k]) {
                            max = dp[i + 1][k];
                            index = k;
                        }
                    }
                }
                if (max != -1) {
                    /* If there is a max we add the length of the word to it
                    and store it in dp[i + 1][j] and update the count of
                    dominant letter */
                    dp[i + 1][j] = wordsets[i][j].length + max;
                    wordsets[i][j].lcnt += wordsets[i][index].lcnt;
                } else {
                    // Else, we set it to the length of the word
                    dp[i + 1][j] = wordsets[i][j].length;
                }
            }
        }

        // The solution is the max value of dp that respect the condition
        int max = -1;
        for (int i = 1; i <= 26; ++i) {
            for (int j = 1; j <= n; j++) {
                if (dp[i][j] > max && (double) wordsets[i - 1][j].lcnt >
                    dp[i][j] / 2.0) {
                    max = dp[i][j];
                }
            }
        }
        return max;
    }

    /* Printing function */
    void print_output(int result) {
        ofstream fout("criptat.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
