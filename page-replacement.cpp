#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

int pageFaults(vector<int> pages, int capacity) {
    int pageFaults = 0;
    unordered_map<int, int> indexes;

    vector<int> frame;
    for (int i = 0; i < pages.size(); ++i) {
        if (indexes.find(pages[i]) == indexes.end()) {
            if (frame.size() < capacity) {
                frame.push_back(pages[i]);
            } else {
                int farthest = -1, replace;
                for (int j = 0; j < frame.size(); ++j) {
                    int idx = INT_MAX;
                    if (indexes.find(frame[j]) != indexes.end()) {
                        idx = indexes[frame[j]];
                    }
                    if (idx > farthest) {
                        farthest = idx;
                        replace = j;
                    }
                }
                frame[replace] = pages[i];
            }
            indexes[pages[i]] = i;
            ++pageFaults;
        } else {
            indexes[pages[i]] = i;
        }
    }
    return pageFaults;
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0};
    int capacity = 3;
    int faults = pageFaults(pages, capacity);
    cout << "Number of Page Faults: " << faults << endl;
    return 0;
}



// hit ratio== total number of successfull hits found/total no. of pages


#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <iterator>

class PageReplacementAlgo {
private:
    void lru() {
        int fsize = 0, page_fault = 0, page_hit = 0, nop = 15;
        std::unordered_set<int> s;
        std::unordered_map<int, int> indexes;
        int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0};

        std::cout << "Enter Frame Size: ";
        std::cin >> fsize;

        for (int i = 0; i < nop; i++) {
            if (s.size() < fsize) {
                if (s.find(pages[i]) == s.end()) {
                    s.insert(pages[i]);
                    page_fault++;
                } else {
                    page_hit++;
                }
                indexes[pages[i]] = i;
            } else {
                int lru = INT_MAX, val = INT_MIN;
                for (const auto& temp : s) {
                    if (indexes[temp] < lru) {
                        lru = indexes[temp];
                        val = temp;
                    }
                }
                if (s.find(pages[i]) == s.end()) {
                    s.insert(pages[i]);
                    page_fault++;
                } else {
                    page_hit++;
                }

                s.erase(val);
                s.insert(pages[i]);
                indexes[pages[i]] = i;
            }
            std::cout << " ";
            for (const auto& num : s) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Faults " << page_fault << std::endl;
        std::cout << "Hits " << page_hit << std::endl;
    }

public:
    void runLRU() {
        lru();
    }
};

int main() {
    PageReplacementAlgo P;
    P.runLRU();
    return 0;
}
