#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

using TimePoint = chrono::system_clock::time_point;

chrono::system_clock::time_point makeDate(int day, int month, int year) {
    tm t = {};
    t.tm_mday = day;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;
    return chrono::system_clock::from_time_t(mktime(&t));
}

class Fanfiction {
private:
    TimePoint date_updated;
    string name;
    int words;
public:
    Fanfiction(TimePoint date_updated, string name, int words):
        date_updated(date_updated), name(name), words(words) { }
    TimePoint get_date_updated() const{
        return date_updated;
    }
    string get_name() const {
        return name;
    }
    int get_words() const{
        return words;
    }
};

int main() {

    vector<Fanfiction> fanfics{
        Fanfiction(makeDate(28, 9, 2026),"Just fanfic", 35000),
        Fanfiction(makeDate(14, 12, 2025),"Romantic", 5000),
        Fanfiction(makeDate(1, 6, 2026), "Drabble fic", 3000)
    };
    while (true) {
        
        int  min, max;; 
        cout << "\n\tFilters\n\n";
        cout << "Minimum word count\n";
        cin >> min;
        cout << "Maxmum word count\n";
        cin >> max;
        int max_words = (max > 0) ? max : numeric_limits<int>::max();
        int min_words = (min > 0) ? min : 0;
        vector<Fanfiction> filtered ;
        copy_if(fanfics.begin(), fanfics.end(), back_inserter(filtered), [min_words,max_words](const Fanfiction& fic) {
            return fic.get_words() <= max_words && fic.get_words() >= min_words;
            });
                cout << "Works from " << min << " to " << max << " words\n\n";
                sort(filtered.begin(), filtered.end(), [](const Fanfiction& fic1, const Fanfiction& fic2) {
                    return fic1.get_date_updated() > fic2.get_date_updated();
                    });
                for (const auto& elem : filtered) {
                    time_t timeT = chrono::system_clock::to_time_t(elem.get_date_updated());
                    tm localTime;
                    localtime_s(&localTime, &timeT);
                    cout << "Date updated: " << put_time(&localTime, "%d.%m.%Y")
                        << "  Title: " << elem.get_name()  << "  Words count: " << elem.get_words() << endl;
                }
    }
    return 0;
}