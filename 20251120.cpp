#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

class Card {
private:
    string studentID;
    string name;
    double balance;
    vector<string> transactionHistory;
    
public:

    Card() : balance(0.0) {}
    
    Card(string id, string name, double balance = 0.0) 
        : studentID(id), name(name), balance(balance) {
        if (balance > 0) {
            addTransaction("初始充值", balance);
        }
    }
    

    ~Card() {}
    

    void recharge(double amount) {
        if (amount > 0) {
            balance += amount;
            addTransaction("充值", amount);
            cout << "充值成功！" << endl;
            cout << "充值金额：" << fixed << setprecision(2) << amount << "元" << endl;
            cout << "当前余额：" << fixed << setprecision(2) << balance << "元" << endl;
        } else {
            cout << "充值金额必须大于0！" << endl;
        }
    }
    

    bool consume(double amount, string description) {
        if (amount <= 0) {
            cout << "消费金额必须大于0！" << endl;
            return false;
        }
        
        if (amount > balance) {
            cout << "余额不足！" << endl;
            return false;
        }
        
        balance -= amount;
        addTransaction(description, amount);
        cout << "消费成功！" << endl;
        cout << "消费金额：" << fixed << setprecision(2) << amount << "元" << endl;
        cout << "消费描述：" << description << endl;
        cout << "当前余额：" << fixed << setprecision(2) << balance << "元" << endl;
        return true;
    }
    

    double getBalance() const {
        return balance;
    }
    

    void showInfo() const {
        cout << "账户信息：" << endl;
        cout << "学号：" << studentID << endl;
        cout << "姓名：" << name << endl;
        cout << "当前余额：" << fixed << setprecision(2) << balance << "元" << endl;
    }
    

    void showTransactions() const {
        cout << "交易记录：" << endl;
        for (const auto& record : transactionHistory) {
            cout << record << endl;
        }
    }
    

    string getStudentID() const {
        return studentID;
    }
    

    string getName() const {
        return name;
    }
    
private:

    void addTransaction(string type, double amount) {
        time_t now = time(0);
        char* dt = ctime(&now);
        dt[strlen(dt) - 1] = '\0';  // 去除换行符
        
        string record = string(dt) + " " + type + " " + 
                      to_string(amount) + "元";
        transactionHistory.push_back(record);
    }
    

    friend ostream& operator<<(ostream& os, const Card& card);
};


ostream& operator<<(ostream& os, const Card& card) {
    os << "学号：" << card.studentID << endl;
    os << "姓名：" << card.name << endl;
    os << "余额：" << fixed << setprecision(2) << card.balance << "元";
    return os;
}

class CardSystem {
private:
    vector<Card*> cards;
    
public:

    ~CardSystem() {
        for (auto card : cards) {
            delete card;
        }
    }
    

    void addCard(Card* card) {
        cards.push_back(card);
        cout << "账户创建成功！" << endl;
        card->showInfo();
    }
    

    Card* findCard(string studentID) {
        for (auto card : cards) {
            if (card->getStudentID() == studentID) {
                return card;
            }
        }
        cout << "未找到该账户！" << endl;
        return nullptr;
    }
    

    void generateReport() const {
        cout << "校园一卡通账户报表" << endl;
        cout << "=======================" << endl;
        cout << "账户总数：" << cards.size() << endl;
        cout << endl;
        
        if (cards.empty()) {
            cout << "暂无账户信息" << endl;
            return;
        }
        
        cout << "账户详情：" << endl;
        for (const auto& card : cards) {
            cout << *card << endl;
            cout << endl;
        }
    }
};

int main() {
    CardSystem system;
    

    Card* card1 = new Card("202411000632", "庄政", 100.0);
    system.addCard(card1);
    cout << endl;
    

    Card* foundCard = system.findCard("202411000632");
    if (foundCard) {
        foundCard->recharge(200.0);
        cout << endl;
        

        foundCard->consume(85.5, "午餐");
        cout << endl;
        

        foundCard->showInfo();
        cout << endl;
    }
    

    system.generateReport();
    
    return 0;
}


#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Date {
private:
    int year;
    int month;
    int day;
    

    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    

    int getDaysInMonth() const {
        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear()) {
            return 29;
        }
        return days[month - 1];
    }
    

    bool isValidDate() const {
        if (year < 1 || month < 1 || month > 12 || day < 1) {
            return false;
        }
        return day <= getDaysInMonth();
    }
    
public:
 
    Date() : year(2000), month(1), day(1) {}
    
    Date(int y, int m, int d) : year(y), month(m), day(d) {
        if (!isValidDate()) {
            throw invalid_argument("无效的日期！");
        }
    }
    

    void Init(int y, int m, int d) {
        year = y;
        month = m;
        day = d;
        if (!isValidDate()) {
            throw invalid_argument("无效的日期！");
        }
    }

    int getYear() const {
        return year;
    }
    

    int getMonth() const {
        return month;
    }
    

    int getDay() const {
        return day;
    }

    void setYear(int y) {
        int oldYear = year;
        year = y;
        if (!isValidDate()) {
            year = oldYear;
            throw invalid_argument("无效的年份！");
        }
    }

    void setMonth(int m) {
        int oldMonth = month;
        month = m;
        if (!isValidDate()) {
            month = oldMonth;
            throw invalid_argument("无效的月份！");
        }
    }
    

    void setDay(int d) {
        int oldDay = day;
        day = d;
        if (!isValidDate()) {
            day = oldDay;
            throw invalid_argument("无效的日期！");
        }
    }
    

    void display() const {
        cout << "日期：" << year << "年" << month << "月" << day << "日";
    }
    
    int calWeekday() const {
        int y = year;
        int m = month;
        int d = day;
        

        if (m == 1 || m == 2) {
            y--;
            m += 12;
        }
        

        int weekday = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
        return weekday;
    }
    

    void showWeekday() const {
        int weekday = calWeekday();
        string weekdays[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
        cout << "星期：" << weekdays[weekday];
    }
};


int main() {
    try {

        Date date1(2025, 11, 20);
        date1.display();
        cout << endl;
        date1.showWeekday();
        cout << endl << endl;
        

        Date date2(2024, 2, 29);
        date2.display();
        cout << endl;
        date2.showWeekday();
        cout << endl << endl;
        
        Date date3(2025, 1, 1);
        date3.display();
        cout << endl;
        date3.showWeekday();
        cout << endl << endl;
        
        Date date4(2023, 2, 29);
    } catch (const invalid_argument& e) {
        cout << "错误：" << e.what() << endl;
    }
    
    return 0;
}


#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Triangle {
private:
    double a, b, c;
    
public:
    Triangle() : a(0), b(0), c(0) {}
    
    Triangle(double sideA, double sideB, double sideC) 
        : a(sideA), b(sideB), c(sideC) {
        if (!isTriangle()) {
            throw invalid_argument("这三条边不能构成三角形！");
        }
    }
    
    void Init(double sideA, double sideB, double sideC) {
        a = sideA;
        b = sideB;
        c = sideC;
        if (!isTriangle()) {
            throw invalid_argument("这三条边不能构成三角形！");
        }
    }
    
    bool isTriangle() const {
        return (a + b > c) && (a + c > b) && (b + c > a) && 
               a > 0 && b > 0 && c > 0;
    }
    
    double getSideA() const { return a; }
    double getSideB() const { return b; }
    double getSideC() const { return c; }
    
    void setSideA(double sideA) {
        double oldA = a;
        a = sideA;
        if (!isTriangle()) {
            a = oldA;
            throw invalid_argument("设置失败，无法构成三角形！");
        }
    }
    
    void setSideB(double sideB) {
        double oldB = b;
        b = sideB;
        if (!isTriangle()) {
            b = oldB;
            throw invalid_argument("设置失败，无法构成三角形！");
        }
    }
    
    void setSideC(double sideC) {
        double oldC = c;
        c = sideC;
        if (!isTriangle()) {
            c = oldC;
            throw invalid_argument("设置失败，无法构成三角形！");
        }
    }
    
    double perimeter() const {
        if (!isTriangle()) {
            throw logic_error("不是三角形，无法计算周长！");
        }
        return a + b + c;
    }
    
    double area() const {
        if (!isTriangle()) {
            throw logic_error("不是三角形，无法计算面积！");
        }
        double p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    
    int typeTriangle() const {
        if (!isTriangle()) {
            throw logic_error("不是三角形，无法判断类型！");
        }
        
        double maxSide = max(max(a, b), c);
        double side1, side2;
        
        if (maxSide == a) {
            side1 = b;
            side2 = c;
        } else if (maxSide == b) {
            side1 = a;
            side2 = c;
        } else {
            side1 = a;
            side2 = b;
        }
        
        double sumSquares = side1 * side1 + side2 * side2;
        double squareMax = maxSide * maxSide;
        
        if (abs(sumSquares - squareMax) < 1e-9) {
            return 0;  // 直角三角形
        } else if (sumSquares > squareMax) {
            return 1;  // 锐角三角形
        } else {
            return 2;  // 钝角三角形
        }
    }
    
    void showInfo() const {
        cout << "三角形信息：" << endl;
        cout << "边长：a=" << a << ", b=" << b << ", c=" << c << endl;
        cout << "是否为三角形：" << (isTriangle() ? "是" : "否") << endl;
        
        if (isTriangle()) {
            cout << "周长：" << fixed << setprecision(2) << perimeter() << endl;
            cout << "面积：" << fixed << setprecision(2) << area() << endl;
            
            int type = typeTriangle();
            cout << "类型：";
            switch(type) {
                case 0: cout << "直角三角形"; break;
                case 1: cout << "锐角三角形"; break;
                case 2: cout << "钝角三角形"; break;
            }
            cout << endl;
        }
    }
};

int main() {
    try {
        cout << "测试1：直角三角形" << endl;
        Triangle t1(3, 4, 5);
        t1.showInfo();
        cout << endl;
        
        cout << "测试2：锐角三角形" << endl;
        Triangle t2(5, 5, 6);
        t2.showInfo();
        cout << endl;
        
        cout << "测试3：钝角三角形" << endl;
        Triangle t3(2, 3, 4);
        t3.showInfo();
        cout << endl;
        
        cout << "测试4：非三角形" << endl;
        Triangle t4(1, 2, 4);
        t4.showInfo();
    } catch (const exception& e) {
        cout << "错误：" << e.what() << endl;
    }
    
    return 0;

}
