#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string calculateMedian(vector<string> &words){
    int size =words.size();
    if(size<=10){
        sort(words.begin(),words.end());
        return words[size/2];
    }
    int numberOfSublists = size/5;
    int lastIndex=-1;
    vector<string> mediany;
    for(int i=0; i<numberOfSublists; i++){
        vector <string> sublist;
        for(int j=0; j<5; j++){
            sublist.push_back(words[i*5+j]);
            lastIndex=i*5+j;
        }
        mediany.push_back(calculateMedian(sublist));
    }
    if((size%5) !=0) {
        vector <string> podlista;
        for (int i = lastIndex + 1; i < size; i++) {
            podlista.push_back(words[i]);
        }
        mediany.push_back(calculateMedian(podlista));
    }
    return calculateMedian(mediany);

}
void select(vector<string> &words, vector<int> &indexes, const string &median, string *answer, int shift){
    if(words.size()<=10){
        sort(words.begin(), words.end());
        for(int index: indexes){

            answer[index+shift] = words[index];

        }
        return;
    }
    vector <string> B;
    vector <string> C;
    vector <string> D;
    for(const string &s: words){
        if(s < median){
            B.push_back(s);
            continue;
        }
        if(s>median){
            D.push_back(s);
            continue;
        }
        C.push_back(median);
    }
    int sizeB = B.size();
    int sizeC =C.size();
    int sizeD = D.size();
    vector <int> indexes_B;
    vector <int> indexes_D;
    for (int index : indexes) {
        if(index < sizeB){
            indexes_B.push_back(index);
            continue;
        }
        if(index <sizeB+sizeC){
            answer[index+shift]=median;
            continue;
        }
        indexes_D.push_back(index -(sizeB+sizeC));
    }
    string medianB="b";
    string medianD="d";
    if(sizeB>10){
        medianB= calculateMedian(B);
    }
    if(sizeD>10){
        medianD= calculateMedian(D);
    }
    if(!indexes_B.empty()) {
        select(B, indexes_B, medianB, answer, shift);
    }
    if(!indexes_D.empty()) {
        select(D, indexes_D, medianD, answer, sizeB + sizeC + shift);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    int numberOfLines;
    cin>>numberOfLines;
    cin.ignore();

    string line;
    string word;
    stringstream ss;

    vector<string> book;
    for(int i=0; i<numberOfLines; i++){
        getline(cin, line);
        ss = stringstream(line);
        while(ss>>word){
            book.push_back(word);
        }

    }
    string mediana = calculateMedian(book);


    int numberOfIndexes;
    vector <int> indexes;
    int index;

    int max=-1;
    cin>>numberOfIndexes;
    for(int i=0; i<numberOfIndexes; i++){
        cin>>index;
        if(index>max){
            max=index;
        }
        indexes.push_back(index);


    }
    string tab[max+1];

    select(book, indexes, mediana, tab, 0);

    for (int i : indexes) {
        cout<<tab[i]<<"\n";

    }
    return 0;
}