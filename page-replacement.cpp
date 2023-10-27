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





#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

void FIFOPageReplacement(int pages[], int n, int capacity) {
    queue<int> pageQueue;
    unordered_set<int> pageSet;

    int pageFaults = 0;
    for (int i = 0; i < n; ++i) {
        if (pageSet.size() < capacity) {
            if (pageSet.find(pages[i]) == pageSet.end()) {
                pageSet.insert(pages[i]);
                pageQueue.push(pages[i]);
                ++pageFaults;
            }
        } else {
            if (pageSet.find(pages[i]) == pageSet.end()) {
                int oldest = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(oldest);

                pageSet.insert(pages[i]);
                pageQueue.push(pages[i]);
                ++pageFaults;
            }
        }
    }

    cout << "Number of Page Faults (FIFO): " << pageFaults << endl;
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    FIFOPageReplacement(pages, n, capacity);

    return 0;
}





#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

void optimalPageReplacement(int pages[], int n, int capacity) {
    unordered_map<int, int> nextOccurrence;
    vector<int> memory;
    int pageFaults = 0;

    for (int i = 0; i < n; ++i) {
        if (memory.size() < capacity) {
            memory.push_back(pages[i]);
            nextOccurrence[pages[i]] = INT_MAX;
            ++pageFaults;
        } else {
            bool found = false;
            for (int j = 0; j < memory.size(); ++j) {
                if (memory[j] == pages[i]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                int farthest = -1, replaceIndex;
                for (int j = 0; j < memory.size(); ++j) {
                    if (nextOccurrence[memory[j]] > farthest) {
                        farthest = nextOccurrence[memory[j]];
                        replaceIndex = j;
                    }
                }

                memory[replaceIndex] = pages[i];
                nextOccurrence[pages[i]] = INT_MAX;
                ++pageFaults;
            }
        }

        // Update the next occurrence of the current page
        for (int j = i + 1; j < n; ++j) {
            if (pages[j] == pages[i]) {
                nextOccurrence[pages[i]] = j;
                break;
            }
        }
    }

    cout << "Number of Page Faults (Optimal): " << pageFaults << endl;
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    optimalPageReplacement(pages, n, capacity);

    return 0;
}

