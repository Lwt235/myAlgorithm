#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <map>
#include <memory>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <set>
#include <fstream>
#define LL long long
#define MOD 99999997
using namespace std;
inline long long read() {
    long long x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
int faultPercent = 7; // P = x/100 * 100%, x <= 50
map<pair<bool, bool>, pair<int, int>>earnings;
class player {
protected:
    int score;
    string type;
    string name;
public:
    const string getType() const { return type; }
    const string getName() const { return name; }
    void setName(string newName) { name = newName; }
    const int getScore() const { return score; }
    void setScore(int newScore) { score = newScore; }
    void addScore(int val) { score += val; }
    player() :score(0), type(""), name("") {};
    player(int score, string type) :score(score), type(type) { srand((unsigned)(time(NULL) + rand())), name = to_string(rand() % 100000001 + 1); };
    player(int score, string type, string name) :score(score), type(type), name(name) {};
    virtual const bool strategy(bool isFirst, int step, const vector<pair<bool, bool>>& Record) = 0;
    virtual unique_ptr<player> clone() const = 0;
    bool operator < (const player& a) const {
        if (score == a.score) return name < a.name;
        return score < a.score;
    }
    bool operator > (const player& a) const {
        if (score == a.score) return name < a.name;
        return score > a.score;
    }
};
class Repeater : public player {
public:
    const bool strategy(bool isFirst, int step, const vector<pair<bool, bool>>& Record) {
        if (step == 1) return true; //合作
        if (isFirst) return Record[step - 1].second;
        else return Record[step - 1].first;
    }
    unique_ptr<player> clone() const override {
        return make_unique<Repeater>();
    }
    Repeater() :player(0, "Repeater") {};
    Repeater(string name, int score = 0) :player(score, "Repeater", name) {};
};
class Cheater : public player {
public:
    const bool strategy(bool isFirst, int step, const vector<pair<bool, bool>>& Record) {
        return false;
    }
    unique_ptr<player> clone() const override {
        return make_unique<Cheater>();
    }
    Cheater() :player(0, "Cheater") {};
    Cheater(string name, int score = 0) :player(score, "Cheater", name) {};
};
class Believer :public player {
public:
    const bool strategy(bool isFirst, int step, const vector<pair<bool, bool>>& Record) {
        return true;
    }
    unique_ptr<player> clone() const override {
        return make_unique<Believer>();
    }
    Believer() :player(0, "Believer") {};
    Believer(string name, int score = 0) :player(score, "Believer", name) {};
};
class Collaborator : public player {
private:
    bool hasBeenCheate = false;
public:
    const bool strategy(bool isFirst, int step, const vector<pair<bool, bool>>& Record) {
        if (step == 1) {
            hasBeenCheate = false;
            return true;
        }
        if (hasBeenCheate) return false;
        else {
            if (isFirst) {
                if (!Record[step - 1].second) {
                    hasBeenCheate = true;
                    return false;
                }
                return true;
            }
            else {
                if (!Record[step - 1].first) {
                    hasBeenCheate = true;
                    return false;
                }
                return true;
            }
        }
    }
    unique_ptr<player> clone() const override {
        return make_unique<Collaborator>();
    }
    Collaborator() :player(0, "Collaborator") {};
    Collaborator(string name, int score = 0) :player(score, "Collaborator", name) {};
};
class logicPerson :public player {
private:
    bool beenFightBack = false;
public:
    const bool strategy(bool isFirst, int step, const vector<pair<bool, bool>>& Record) {
        if (step == 1) {
            beenFightBack = false;
            return true;
        }
        else if (step == 2) {
            if ((isFirst && !Record[1].second) || (!isFirst && !Record[1].first)) beenFightBack = true;
            return false;
        }
        else if (step == 3) {
            if ((isFirst && !Record[2].second) || (!isFirst && !Record[2].first)) beenFightBack = true;
            return true;
        }
        else if (step == 4) {
            if ((isFirst && !Record[3].second) || (!isFirst && !Record[3].first)) beenFightBack = true;
            return true;
        }
        else if (step == 5) if ((isFirst && !Record[4].second) || (!isFirst && !Record[4].first)) beenFightBack = true;
        if (beenFightBack) return isFirst ? Record[step - 1].second : Record[step - 1].first;
        else return false;
    }
    unique_ptr<player> clone() const override {
        return make_unique<logicPerson>();
    }
    logicPerson() :player(0, "logicPerson") {};
    logicPerson(string name, int score = 0) :player(score, "logicPerson", name) {};
};
class Xpeater :public player {
private:
    int beenCheateCnt;
    int repeatCnt;
public:
    int getRepeatCnt() const {
        return repeatCnt;
    }
    const bool strategy(bool isFirst, int step, const vector<pair<bool, bool>>& Record) {
        if (step == 1) { beenCheateCnt = 0; return true; } //首回合合作
        if ((isFirst && !Record[step - 1].second) || (!isFirst && !Record[step - 1].first)) beenCheateCnt++;
        else beenCheateCnt = 0;
        return beenCheateCnt < repeatCnt;
    }
    unique_ptr<player> clone() const override {
        return make_unique<Xpeater>();
    }
    Xpeater() :player(0, "Xpeater") { repeatCnt = 1; beenCheateCnt = 0; };
    Xpeater(int RepeatCnt, int score = 0) :player(score, "Xpeater") { repeatCnt = RepeatCnt; beenCheateCnt = 0; };
    Xpeater(string name, int RepeatCnt, int score = 0) :player(score, "Xpeater", name) { repeatCnt = RepeatCnt; beenCheateCnt = 0; };
};
class Pavlov :public player {
private:
    bool hasBeenCheate = false;
public:
    const bool strategy(bool isFirst, int step, const vector<pair<bool, bool>>& Record) {
        if (step == 1) { hasBeenCheate = false; return true; } //首回合合作
        if (isFirst) hasBeenCheate = !Record[step - 1].second;
        else hasBeenCheate = !Record[step - 1].first;
        if (hasBeenCheate) {
            if (isFirst) return !Record[step - 1].first;
            else return !Record[step - 1].second;
        }
        else {
            if (isFirst) return Record[step - 1].first;
            else return Record[step - 1].second;
        }
    }
    unique_ptr<player> clone() const override {
        return make_unique<Pavlov>();
    }
    Pavlov() :player(0, "Pavlov") {};
    Pavlov(string name, int score = 0) :player(score, "Pavlov", name) {};
};
class Randomer :public player {
public:
    const bool strategy(bool isFirst, int step, const vector<pair<bool, bool>>& Record) {
        srand((unsigned)time(NULL) + rand());
        return rand() & 1;
    }
    unique_ptr<player> clone() const override {
        return make_unique<Randomer>();
    }
    Randomer() :player(0, "Randomer") {};
    Randomer(string name, int ForgetPercent, int score = 0) :player(score, "Randomer", name) {};
};
unique_ptr<player> createNewPlayer(const player& obj) {
    if (dynamic_cast<const Repeater*>(&obj))
        return make_unique<Repeater>();
    else if (dynamic_cast<const Cheater*>(&obj))
        return make_unique<Cheater>();
    else if (dynamic_cast<const Believer*>(&obj))
        return make_unique<Believer>();
    else if (dynamic_cast<const Collaborator*>(&obj))
        return make_unique<Collaborator>();
    else if (dynamic_cast<const logicPerson*>(&obj))
        return make_unique<logicPerson>();
    else if (dynamic_cast<const Xpeater*>(&obj)) {
        Xpeater tmp = static_cast<const Xpeater&>(obj);
        return make_unique<Xpeater>(tmp.getRepeatCnt());
    }
    else if (dynamic_cast<const Pavlov*>(&obj))
        return make_unique<Pavlov>();
    else if (dynamic_cast<const Randomer*>(&obj))
        return make_unique<Randomer>();
    throw runtime_error("Unknow type to create a player");
}
template<typename T>
class myVector :public vector<T> {
public:
    inline void create_back(const T& item, int cnt = 1) {
        for(int i=1;i<=cnt;i++)
            this->emplace_back(move(createNewPlayer(*item)));
    }
};
template<typename TA, typename TB>
void playGames(TA& A, TB& B, int times) {
    vector<pair<bool, bool>>Record(times + 1);
    for (int index = 1; index <= times; index++) {
        Record[index] = { A.strategy(true, index, Record), B.strategy(false, index, Record) };
        srand((unsigned)time(NULL) + rand());
        Record[index].first = (rand() % 100) < faultPercent ? !Record[index].first : Record[index].first;
        srand((unsigned)time(NULL) + rand());
        Record[index].second = (rand() % 100) < faultPercent ? !Record[index].second : Record[index].second;
        pair<int, int>res = earnings[Record[index]];
        A.addScore(res.first);
        B.addScore(res.second);
    }
    /*cout <<"对局记录:" << endl;
    for (int i = 1; i <= times; i++) {
        cout << "index: " << i << " A:" << (Record[i].first ? "Coperation" : "Cheate") << " | B:" << (Record[i].second ? "Coperation" : "Cheate") << " then: " << earnings[Record[i]].first << " -- " << earnings[Record[i]].second << endl;
    }*/
}
void setEarnings() {
    earnings[{true, true}] = { 2,2 };
    earnings[{false, true}] = { 3,-1 };
    earnings[{true, false}] = { -1,3 };
    earnings[{false, false}] = { 0,0 };
}
bool Cmp(unique_ptr<player> &a, unique_ptr<player> &b) {
    return *a > *b;
}
void runOneRound(myVector<unique_ptr<player>>& Players) {
    for (int i = 0; i < Players.size(); i++) Players[i]->setScore(0);
    for (int i = 0; i < Players.size() - 1; i++) {
        for (int j = i + 1; j < Players.size(); j++) {
            //cout << "A: " << Players[i]->getType() << " B: " << Players[j]->getType() << endl;
            playGames(*Players[i], *Players[j], 10);
            //cout << "Result: A:" << Players[i]->getScore() << " B:" << Players[j]->getScore() << endl << endl;
        }
        //cout << endl;
    }
    sort(Players.begin(), Players.end(), Cmp);
    /*cout << "Result: " << endl;
    for (int i = 0; i < Players.size(); i++)
        cout << Players[i]->getName() << " -- " << Players[i]->getType() << ": " << Players[i]->getScore() << endl;
    
    cout << "popLoser:" << endl;*/
    
    /*cout << "Score: " << endl;
    for (int i = 0; i < Players.size(); i++)
        cout << Players[i]->getName() << " -- " << Players[i]->getType() << ": " << Players[i]->getScore() << endl;*/
    
    for (int i = 1; i <= 5; i++)
        Players.erase(Players.begin() + Players.size() - 1);
    
    /*cout << "Result: " << endl;
    for (int i = 0; i < Players.size(); i++)
        cout << Players[i]->getName() << " -- " << Players[i]->getType() << ": " << Players[i]->getScore() << endl;*/

    //cout << "insertWinner:" << endl;
    for (int i = 1; i <= 5; i++)
        Players.create_back(Players[i - 1]);

    sort(Players.begin(), Players.end(), Cmp);
    /*cout << "Result: " << endl;
    for (int i = 0; i < Players.size(); i++)
        cout << Players[i]->getName() << " -- " << Players[i]->getType() << ": " << Players[i]->getScore() << endl;*/
}
void runRounds(myVector<unique_ptr<player>>& Players, int cnt = 1) {
    for (int i = 1; i <= cnt; i++) runOneRound(Players);
}
map<string, double> calcRes(const myVector<unique_ptr<player>>& Players, const set<string>& exist) {
    map<string, double>Res;
    for (auto& item : exist)
        Res[item] = 0;
    for (int i = 0; i < Players.size(); i++)
        Res[Players[i]->getType()] += 1.0 / Players.size();
    return Res;
}
int main(int argc, char* argv[]) {
    srand(atoi(argv[0]));
    ofstream outFile;
    outFile.open("Database.out");
    setEarnings();
    for (int i = 1; i <= 10; i++) {
        myVector<unique_ptr<player>>Players;
        //5-15-5-5-5
        Players.create_back(make_unique<Repeater>(), 3);
        Players.create_back(make_unique<Cheater>(), 13);
        //Players.create_back(make_unique<Believer>(), 13);
        Players.create_back(make_unique<Xpeater>(2), 3);
        Players.create_back(make_unique<Pavlov>(), 3);
        Players.create_back(make_unique<Randomer>(), 3);
        runRounds(Players, 500);
        //map<string, double>Res = calcRes(Players, { "Repeater","Cheater","Believer","Collaborator","logicPerson"});
        map<string, double>Res = calcRes(Players, { "Repeater","Cheater"/*,"Believer"*/,"Xpeater","Pavlov","Randomer"});
        for (auto& item : Res) outFile << item.first << " " << item.second << endl;
        outFile << endl;
    }
    return atoi(argv[0]);
}