#include <iostream>
#include <string>
#include <vector>

using namespace std;


string toLowerCase(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}


void searchWebsite(const vector<string>& websites, const string& keyword) {
    string lowerKeyword = toLowerCase(keyword);
    bool found = false;

    cout << "Ket qua tim kiem cho tu khoa \"" << keyword << "\":\n";
    for (const string& site : websites) {
        string lowerSite = toLowerCase(site);
        if (lowerSite.find(lowerKeyword) != string::npos) {
            cout << "- " << site << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Khong tim thay ket qua phu hop cho tu khoa \"" << keyword << "\".\n";
    }
}

int main() {
    
    vector<string> websites = {
        "Google.com - Cong cu tim kiem lon nhat the gioi",
        "Facebook.com - Mang xa hoi lon nhat",
        "Amazon.com - Cua hang truc tuyen lon nhat",
        "YouTube.com - Nen tang chia se video lon nhat",
        "Wikipedia.org - Tu dien mo lon nhat",
        "StackOverflow.com - Dien dan lap trinh vien"
    };

    string keyword;

    cout << "Chao mung den voi cong cu tim kiem.\n";
    cout << "Nhap tu khoa ban muon tim kiem: ";
    getline(cin, keyword);

    searchWebsite(websites, keyword);

    return 0;
}

