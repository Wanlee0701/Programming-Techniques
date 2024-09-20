// Name: Le Quang Duc
// Student ID: 20227221	
// Class: 150328
// Project: 2 - Xay dung thu vien toan lam viec voi so nguyen lon
// Date: 31/05/2024	
#include <bits/stdc++.h>
using namespace std;
const int base = 1000000000; const int base_digits = 9;
struct bigint {
    vector<int> a; int sign; // Moi phan tu cua vector a se luu mot doan so nguyen lon
    bigint() : sign(1) { // sign() dung de luu dau 
    }
    
    // Khoi tao bigint tu mot so nguyen dai
    bigint(long long v) {
        *this = v;
    }
    
    // Khoi tao bigint tu mot chuoi so
    bigint(const string &s) {
        read(s);
    }
    // Kiem tra xem bigint co khac 0 
	bool isZero(const bigint &num) {
    return num == 0;
	}
    
    // Gan gia tri cua bigint khac cho bigint hien tai
    void operator=(const bigint &v) {
        sign = v.sign;
        a = v.a;
    }
    
    // Gan gia tri cua so nguyen dai cho bigint hien tai
    void operator=(long long v) {
        sign = 1;
        if (v < 0)
            sign = -1, v = -v;
        for (; v > 0; v = v / base)
            a.push_back(v % base);
    }
    
    //Kiem tra xem bigint co bang 0 
      bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }
    
    // Cong hai bigint
    bigint operator+(const bigint &v) const {
        if (sign == v.sign) {
            bigint res = v;

            for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
                if (i == (int) res.a.size())
                    res.a.push_back(0);
                res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
                carry = res.a[i] >= base;
                if (carry)
                    res.a[i] -= base;
            }
            return res;
        }
        return *this - (-v);
    }
    
    // Tru hai bigint
    bigint operator-(const bigint &v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                bigint res = *this;
                for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
                    res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry)
                        res.a[i] += base;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }
    
    // Nhan bigint voi mot so nguyen
    void operator*=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
            if (i == (int) a.size())
                a.push_back(0);
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / base);
            a[i] = (int) (cur % base);
        }
        trim();
    }
    
    // Nhan hai bigint
    bigint operator*(int v) const {
        bigint res = *this;
        res *= v;
        return res;
    }
    
    // Chia va lay phan du hai bigint
    friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
        int norm = base / (b1.a.back() + 1);
        bigint a = a1.abs() * norm;
        bigint b = b1.abs() * norm;
        bigint q, r;
        q.a.resize(a.a.size());

        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long) base * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0)
                r += b, --d;
            q.a[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }
    pair<bigint, bigint> divideBigNum(const bigint &a, const bigint &b) {
    bigint quotient = a / b;
    bigint remainder = a % b;
    return make_pair(quotient, remainder);
}
	pair<bigint, bigint> divideBigNum(const bigint &b) const {
        bigint quotient = *this / b;
        bigint remainder = *this % b;
        return make_pair(quotient, remainder);
    }

    // Chia hai bigint
    bigint operator/(const bigint &v) const {
        return divmod(*this, v).first;
    }

    // Lay phan du giua hai bigint
    bigint operator%(const bigint &v) const {
        return divmod(*this, v).second;
    }

    // Chia bigint hien tai cho mot so nguyen
    void operator/=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
            long long cur = a[i] + rem * (long long) base;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }

    // Chia bigint hien tai cho mot so nguyen va tra ve ket qua
    bigint operator/(int v) const {
        bigint res = *this;
        res /= v;
        return res;
    }

    // Lay phan du cua bigint chia cho mot so nguyen
    int operator%(int v) const {
        if (v < 0)
            v = -v;
        int m = 0;
        for (int i = a.size() - 1; i >= 0; --i)
            m = (a[i] + m * (long long) base) % v;
        return m * sign;
    }

    // Cong bigint khac vao bigint hien tai
    void operator+=(const bigint &v) {
        *this = *this + v;
    }
    
    // Tru bigint khac tu bigint hien tai
    void operator-=(const bigint &v) {
        *this = *this - v;
    }
    
    // Nhan bigint hien tai voi bigint khac
    void operator*=(const bigint &v) {
        *this = *this * v;
    }
    
    // Chia bigint hien tai cho bigint khac
    void operator/=(const bigint &v) {
        *this = *this / v;
    }

    // So sanh nho hon giua hai bigint
    bool operator<(const bigint &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
            return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }

    // So sanh lon hon giua hai bigint
    bool operator>(const bigint &v) const {
        return v < *this;
    }
    
    // So sanh nho hon hoac bang giua hai bigint
    bool operator<=(const bigint &v) const {
        return !(v < *this);
    }
    
    // So sanh lon hon hoac bang giua hai bigint
    bool operator>=(const bigint &v) const {
        return !(*this < v);
    }
    
    // So sanh bang nhau giua hai bigint
    bool operator==(const bigint &v) const {
        return !(*this < v) && !(v < *this);
    }
    
    // So sanh khac nhau giua hai bigint
    bool operator!=(const bigint &v) const {
        return *this < v || v < *this;
    }

    // Loai bo cac phan tu 0 thua
    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
    }
    // Tra ve gia tri tuyet doi cua bigint
    bigint operator-() const {
        bigint res = *this;
        res.sign = -sign;
        return res;
    }

    // Tra ve gia tri tuyet doi cua bigint
    bigint abs() const {
        bigint res = *this;
        res.sign *= res.sign;
        return res;
    }
	// Ham tim UCLN
    friend bigint gcd(const bigint &a, const bigint &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
    
    //Ham tim BCNN
    friend bigint lcm(const bigint &a, const bigint &b) {
        return a / gcd(a, b) * b;
    }

    // Tra ve gia tri long long cua bigint
    long long longValue() const {
        long long res = 0;
        for (int i = a.size() - 1; i >= 0; i--)
            res = res * base + a[i];
        return res * sign;
    }


    // Doc gia tri cua bigint tu mot chuoi
    void read(const string &s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }

    // Doc gia tri cua bigint tu input stream
    friend istream& operator>>(istream &stream, bigint &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    // Xuat gia tri cua bigint ra output stream
    friend ostream& operator<<(ostream &stream, const bigint &v) {
        if (v.sign == -1)
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i];
        return stream;
    }

    // Chuyen doi co so cua vector so
    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vector<long long> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int) p.size(); i++)
            p[i] = p[i - 1] * 10;
        vector<int> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int) a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back(int(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int) cur);
        while (!res.empty() && !res.back())
            res.pop_back();
        return res;
    }

    typedef vector<long long> vll;

    // Thuat toan nhan Karatsuba
    static vll karatsubaMultiply(const vll &a, const vll &b) {
        int n = a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += a[i] * b[j];
            return res;
        }

        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());

        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);

        for (int i = 0; i < k; i++)
            a2[i] += a1[i];
        for (int i = 0; i < k; i++)
            b2[i] += b1[i];

        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int) a1b1.size(); i++)
            r[i] -= a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            r[i] -= a2b2[i];

        for (int i = 0; i < (int) r.size(); i++)
            res[i + k] += r[i];
        for (int i = 0; i < (int) a1b1.size(); i++)
            res[i] += a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            res[i + n] += a2b2[i];
        return res;
    }

    // Nhan hai bigint
    bigint operator*(const bigint &v) const {
        vector<int> a6 = convert_base(this->a, base_digits, 6);
        vector<int> b6 = convert_base(v.a, base_digits, 6);
        vll a(a6.begin(), a6.end());
        vll b(b6.begin(), b6.end());
        while (a.size() < b.size())
            a.push_back(0);
        while (b.size() < a.size())
            b.push_back(0);
        while (a.size() & (a.size() - 1))
            a.push_back(0), b.push_back(0);
        vll c = karatsubaMultiply(a, b);
        bigint res;
        res.sign = sign * v.sign;
        for (int i = 0, carry = 0; i < (int) c.size(); i++) {
            long long cur = c[i] + carry;
            res.a.push_back((int) (cur % 1000000));
            carry = (int) (cur / 1000000);
        }
        res.a = convert_base(res.a, 6, base_digits);
        res.trim();
        return res;
    }
    

};
    
//Ham in so nguyen lon ra bang co gioi han ki tu trong mot dong
void printBigintToBoard(const bigint& num) {
    stringstream ss;
    if (num.sign == -1)
        ss << '-';
    ss << (num.a.empty() ? 0 : num.a.back());
    
    // Them cac phan tu con lai cua mang so vao chuoi,dam bao moi phan tu co dung so chu so
    for (int i = (int) num.a.size() - 2; i >= 0; --i)
        ss << setw(base_digits) << setfill('0') << num.a[i];

    string result = ss.str();
    int count = 0;
    bool firstLine = true;
    
    //Duyet qua tung ky tu trong chuoi ket qua va in
    for (char c : result) {
        if (count == 0) {
            if (!firstLine) {
                cout << endl;
            }
            cout << "|                             |";
            firstLine = false;
        }
        cout << c;
        count++;
        
        //Neu dat den gioi han 50 ki tu thi dat len bien
        if (count >= 140) {
            count = 0;
        }
    }
    
    //Neu con lai ky tu chua in thi in ra dong moi
    if (count > 0) {
        cout << endl;
    }
}

//Ham in so nguyen ra file co gioi han ki tu trong 1 dong
void writeBigintToStream(ostream &stream, const bigint &num) {
    stringstream ss;
    if (num.sign == -1)
        ss << '-';
    ss << (num.a.empty() ? 0 : num.a.back());
    for (int i = (int) num.a.size() - 2; i >= 0; --i)
        ss << setw(base_digits) << setfill('0') << num.a[i];

    string result = ss.str();
    int count = 0;
    bool firstLine = true;
    for (char c : result) {
        if (count == 0) {
            if (!firstLine) {
                stream << endl;
            }
            stream << "|                             |";
            firstLine = false;
        }
        stream << c;
        count++;
        if (count >= 140) {
            count = 0;
        }
    }
    if (count > 0) {
        stream << endl;
    }
}
//Ham doc du lieu trong file    
void inputFromFile(bigint &a, bigint &b, const string &filename) {
    ifstream infile(filename);
    if (infile.is_open()) {
        infile >> a;
        infile >> b;
        infile.close();
    } else {
        cerr << "KHONG MO DUOC FILE:  " << filename << endl;
        exit(1);
    }
}
//Ham doc du lieu tu ban phim
void inputFromKeyBoard(bigint &num) {
    cin >> num;
}
// Ham in ket qua ra man hinh
void writeResultToBoard(const bigint &a, const bigint &b, char operattion, const bigint &result, const bigint *remainder) {
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" <<  endl;
    cout << "|                               KET QUA                                                                                                                                   |" <<  endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" <<  endl;
    cout << "|   PHEP TOAN THUC HIEN       | " << operattion <<  endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" <<  endl;
    cout << "|   TOAN HANG THU NHAT        | "; cout << endl;
   	printBigintToBoard(a); cout<<endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" <<  endl;
    cout << "|   TOAN HANG THU HAI         | "; cout << endl;
    printBigintToBoard(b);cout<<endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" <<  endl;
    cout << "|   KET QUA                   | "; cout << endl;
    printBigintToBoard(result); cout<< endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" <<  endl;
    if (remainder != nullptr) {
        cout << "|   SO DU                     | "; cout << endl;
        printBigintToBoard(*remainder); 
        cout << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" <<  endl;
    }
}
//Ham ghi ket qua vao file
void writeResultToFile(const bigint &a, const bigint &b, char operation, const bigint &result, const bigint *remainder, const string &filename) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "KHONG MO DUOC FILE " << filename << endl;
        exit(1); 
    }
    outfile << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    outfile << "|                           KET QUA                                                                                                                                       |" << endl;
    outfile << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    outfile << "|   PHEP TOAN THUC HIEN       | " << operation << endl;
    outfile << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    outfile << "|   TOAN HANG THU NHAT        | " << endl;
    writeBigintToStream(outfile, a);cout<<endl;
    outfile << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    outfile << "|   TOAN HANG THU HAI         | " << endl;
    writeBigintToStream(outfile, b);cout<<endl;
    outfile << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    outfile << "|   KET QUA                   | " << endl;
    writeBigintToStream(outfile, result);cout<<endl;
    outfile << endl;
    outfile << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    if (remainder != nullptr) {
        outfile << "|   SO DU                     | " << endl;
        writeBigintToStream(outfile, *remainder);
        outfile << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    outfile.close();
}


int main() {
    int choice;
    char choice2;
    std::cout << "------------------ NHAP LUA CHON DAU VAO ---------------------" << std::endl;
    std::cout << "|                                                            |" << std::endl;
    std::cout << "|   1. NHAP TU FILE                                          |" << std::endl;
    std::cout << "|   2. NHAP TU BAN PHIM                                      |" << std::endl;
    std::cout << "|                                                            |" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    cout << "NHAP LUA CHON CUA BAN : ";
    cin >> choice;

    bigint a, b, result, *remainder = nullptr;
    char operattion;
    string filenamein;
    string filenameout;
    switch (choice) {
        case 1:
            cout << "NHAP TEN FILE: ";
            cin >> filenamein;
            inputFromFile(a, b, filenamein);
            break;
        case 2:
            cout << "NHAP SO THU NHAT : ";
            inputFromKeyBoard(a);
            cout << "NHAP SO THU HAI  : ";
            inputFromKeyBoard(b);
            break;
        default:
            cout << "LUA CHON KHONG HOP LE!" << endl;
            return 0;
    }
    
    std::cout << "------------------ NHAP LUA CHON CHUC NANG -------------------" << std::endl;
    std::cout << "|                                                            |" << std::endl;
    std::cout << "|   1. CONG                                                  |" << std::endl;
    std::cout << "|   2. TRU                                                   |" << std::endl;
    std::cout << "|   3. NHAN                                                  |" << std::endl;
    std::cout << "|   4. CHIA                                                  |" << std::endl;
    std::cout << "|                                                            |" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    cout << "NHAP LUA CHON CUA BAN : ";
    cin >> choice;

    switch (choice) {
        case 1:
            operattion = '+';
            result = a + b;
            break;
        case 2:
            operattion = '-';
            result = a - b;
            break;
        case 3:
            operattion = '*';
            result = a * b;
            break;
        case 4: {
            operattion = '/';
            if (b.isZero(b)) {
                cout << "SO CHIA KHONG HOP LE!(SO CHIA PHAI KHAC '0')";
                return 0;
            }
            bigint divResult, divRemainder;
            tie(divResult, divRemainder) = a.divideBigNum(b); 
            result = divResult;
            remainder = &divRemainder;
            break;
        }
        default:
            cout << "LUA CHON KHONG HOP LE!" << endl;
            return 0;
    }
    
    writeResultToBoard(a, b, operattion, result, remainder);
    cout << endl << "BAN CO MUON IN KET QUA RA FILE KHONG(Y/N) : ";
    cin >> choice2;
    if (choice2 == 'Y' || choice2 == 'y'){
        cout << "NHAP TEN FILE DE LUU KET QUA : ";
        cin >> filenameout;
        writeResultToFile(a, b, operattion, result, remainder, filenameout);
        cout << "DA NHAP VAO FILE THANH CONG! ";
    }
    
    return 0;
}



//C:\\Users\\ADMIN\\Documents\\KTLT\\BaiTapLon\\Final\\Kiem_thu\\2_so_nguyen_am.txt
//C:\\Users\\ADMIN\\Documents\\KTLT\\BaiTapLon\\Final\\Kiem_thu\\2_so_nguyen_duong.txt
//C:\\Users\\ADMIN\\Documents\\KTLT\\BaiTapLon\\Final\\Kiem_thu\\2_so_nguyen_trai_dau.txt
//C:\\Users\\ADMIN\\Documents\\KTLT\\BaiTapLon\\Final\\Kiem_thu\\Ket_Qua.txt
