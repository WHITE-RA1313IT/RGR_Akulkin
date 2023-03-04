#include "Ciphers.h"
#include <random>

int ReadInt() {
    string val;
    cin.clear();
    getline(cin, val);

    if (val == "" || val.length() > 9) throw "\nERROR: Incorrect input. You entered a text, not a number. (Text is automatically detected from 10 characters)";
    for (int i = 0; i < val.length(); i++) {
        if (i == 0 && val[i] == '-') continue;
        if (val[i] < '0' || val[i] > '9') {
            throw "\nERROR: Incorrect input. You entered a text, not a number. (Text is automatically detected from 10 characters)";
            return 0;
        }
    }
    return stoi(val);
}

void FileInput(string const& file_directory, string const& input_text) {
    ofstream outf{ file_directory };
    if (!outf)
    {
        throw "\nERROR: FILE.txt could not be opened for writing!";
        return;
    }
    outf << input_text;
    outf.close();
}

string FileOutput(string const& file_directory) {
    ifstream inf{ file_directory };
    if (!inf)
    {
        throw "\nERROR: FILE.txt could not be opened for reading!";
        return "";
    }

    string output_text;
    while (inf) {
        string temp;
        getline(inf, temp);
        output_text += temp;
        if (!inf.eof()) output_text += '\n';
    }
    inf.close();
    return output_text;
}

void AtbashEnDecode(string const& input_text, string const& file_directory) {
    map <char, char> alphabet = { {'A','Z'}, {'B','Y'}, {'C','X'}, {'D','W'}, {'E','V'}, {'F','U'}, {'G','T'}, {'H','S'}, {'I','R'}, {'J','Q'}, {'K','P'}, {'L','O'}, {'M','N'}, {'a','z'}, {'b','y'}, {'c','x'}, {'d','w'}, {'e','v'}, {'f','u'}, {'g','t'}, {'h','s'}, {'i','r'}, {'j','q'}, {'k','p'}, {'l','o'}, {'m','n'} };
    string output_text = "";
    for (int i = 0; i < input_text.length(); i++) {
        bool find_letter = false;
        if (alphabet.find(input_text[i]) != alphabet.end()) {
            output_text += alphabet[input_text[i]];
        }
        else {
            for (auto x : alphabet) {
                if (x.second == input_text[i]) {
                    output_text += x.first;
                    find_letter = true;
                    break;
                }
            }
            if (find_letter == false) output_text += input_text[i];
        }
    }

    FileInput(file_directory, output_text);
    cout << "Output: " << output_text << endl;
}

bool checkPrime(int num) {
    for (int i = 2; i < num; i++) {
        if (num % i == 0)
        {
            return false;
            break;
        }
    }
    return true;
}

int mutuallyPrime(int const& num1, int const& num2) {
    int a = num1, b = num2;
    while (a > 0 && b > 0) {
        if (a > b) a %= b;
        else b %= a;
    }
    if (a + b == 1) return true;
    else return false;
}

int mutuallyInverse(int num, int euler_func) {
    int a = num, a0 = a, b = euler_func, x0 = 1, y0 = 0, x = 0, y = 1, q;
    while (a % b != 0) {
        q = a / b;
        a %= b;
        swap(a, b);

        x0 -= q * x;
        swap(x0, x);

        y0 -= q * y;
        swap(y0, y);
    }
    if (x < 0) return euler_func + x;
    else return x;
}

int mod(int a0, int x0, int p0) {
    long long int a = a0, x = x0, q = 1, p = p0;
    while (x > 0) {
        if (x % 2 == 0) {
            x /= 2;
            a = (a * a) % p; 
        }
        else {
            x--;
            q = (a * q) % p;
        }
    }
    return q;
}

void RSA_E_D(string const& input_text, string const& file_directory) {
    string encrypted_text, decrypted_text;

    cout << "Enter the public key (e, n):\n";

    cout << "Enter two prime numbers p and q (n = p * q):\n";

    cout << "p (p >= 128 & p <= 10000) << ";
    int p = ReadInt();
    if (p < 128 || p > 10000 || !checkPrime(p)) throw "\nERROR: Incorrect input. The number does not match the specified range or is not prime.";

    cout << "q (q >= 128 & q <= 10000) << ";
    int q = ReadInt();
    if (q < 128 || q > 10000 || !checkPrime(q)) throw "\nERROR: Incorrect input. The number does not match the specified range or is not prime.";

    int n = p * q;
    int f = (p - 1) * (q - 1);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<mt19937::result_type> dist(f / 2, f - 1);

    cout << "Possible values of e: ";

    int k = 0;
    while (k <= 10) {
        int temp = dist(gen);
        if (mutuallyPrime(temp, f)) {
            if (k != 10) cout << temp << " , ";
            else cout << temp << endl;
            k++;
        }
    }

    cout << "e (e < " << f << ") << ";
    int e = ReadInt();
    if (e < 0 || e >= f || !mutuallyPrime(e, f)) throw "ERROR: Incorrect input. The number does not match the specified range.";

    cout << endl;

    int d = mutuallyInverse(e, f);

    cout << "Public key (e, n): ( " << e << " , " << n << " )\n";
    cout << "Private key (d, n): ( " << d << " , " << n << " )\n\n";

    for (auto x : input_text) {
        encrypted_text += to_string(mod(x, e, n)) + ' ';
    }

    FileInput(file_directory, encrypted_text);

    int value = 0;
    bool negative = false;
    for (int i = 0; i < encrypted_text.length(); i++) {
        if (encrypted_text[i] >= '0' && encrypted_text[i] <= '9') {
            value *= 10;
            value += encrypted_text[i] - '0';
            if (i != 0) {
                if (encrypted_text[i - 1] == '-') negative = true;
            }
        }
        else if (encrypted_text[i] == ' ') {
            if (negative) value *= -1;
            negative = false;
            value = mod(value, d, n);
            decrypted_text += char(value);
            value = 0;
        }
    }

    FileInput(file_directory, decrypted_text);

    cout << "Input text: " << input_text << endl;
    cout << "Encrypted text: " << encrypted_text << endl;
    cout << "Decrypted text: " << decrypted_text << endl;
}

void RSA_Encode(string const& input_text, string const& file_directory) {
    string encrypted_text;

    cout << "Enter the public key (e, n):\n";

    cout << "Enter two prime numbers p and q (n = p * q):\n";

    cout << "p (p >= 128 & p <= 10000) << ";
    int p = ReadInt();
    if (p < 128 || p > 10000 || !checkPrime(p)) throw "\nERROR: Incorrect input. The number does not match the specified range or is not prime.";

    cout << "q (q >= 128 & q <= 10000) << ";
    int q = ReadInt();
    if (q < 128 || q > 10000 || !checkPrime(q)) throw "\nERROR: Incorrect input. The number does not match the specified range or is not prime.";

    int n = p * q;
    int f = (p - 1) * (q - 1);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<mt19937::result_type> dist(f / 2, f - 1);

    cout << "Possible values of e: ";

    int k = 0;
    while (k <= 10) {
        int temp = dist(gen);
        if (mutuallyPrime(temp, f)) {
            if (k != 10) cout << temp << " , ";
            else cout << temp << endl;
            k++;
        }
    }

    cout << "e (e < " << f << ") << ";
    int e = ReadInt();
    if (e < 0 || e >= f || !mutuallyPrime(e, f)) throw "ERROR: Incorrect input. The number does not match the specified range.";

    for (auto x : input_text) {
        encrypted_text += to_string(mod(x, e, n)) + ' ';
    }

    FileInput(file_directory, encrypted_text);

    cout << "Input text: " << input_text << endl;
    cout << "Encrypted text: " << encrypted_text << endl;
}

void RSA_Decode(string const& input_text, string const& file_directory) {
    string decrypted_text, encrypted_text = input_text;

    cout << "Enter the private key (d, n):\n";
    cout << "d << ";
    int d = ReadInt();
    if (d < 0) throw "ERROR: Incorrect input. The number does not match the specified range.";
    cout << "n (n >= 256) << ";
    int n = ReadInt();
    if (n < 256) throw "ERROR: Incorrect input. The number does not match the specified range.";

    cout << endl;

    int value = 0;
    bool negative = false;
    for (int i = 0; i < encrypted_text.length(); i++) {
        if (encrypted_text[i] >= '0' && encrypted_text[i] <= '9') {
            value *= 10;
            value += encrypted_text[i] - '0';
            if (i != 0) {
                if (encrypted_text[i - 1] == '-') negative = true;
            }
        }
        else if (encrypted_text[i] == ' ') {
            if (negative) value *= -1;
            negative = false;
            value = mod(value, d, n);
            decrypted_text += char(value);
            value = 0;
        }
    }

    FileInput(file_directory, decrypted_text);

    cout << "Input text: " << encrypted_text << endl;
    cout << "Decrypted text: " << decrypted_text << endl;
}

void RailFenceEncode(string const& input_text, string const& file_directory, int const& key) {
    vector <vector <char>> fence;
    string enc_text;
    bool direction = false;

    fence.resize(key);

    for (int i = 0; i < key; i++) {
        fence[i].resize(input_text.length());
    }

    int line = 0;
    for (int j = 0; j < input_text.length(); j++) {
        fence[line][j] = input_text[j];

        if (!direction) {
            line++;
            if (line == key - 1) direction = true;
        }
        else {
            line--;
            if (line == 0) direction = false;
        }
    }

    for (auto x : fence) {
        for (auto y : x) {
            if (y) enc_text += y;
        }
    }

    FileInput(file_directory, enc_text);

    cout << "Encrypted text: " << enc_text << endl;
}

void RailFenceDecode(string const& input_text, string const& file_directory, int const& key) {
    string encrypted_text = input_text, dec_text;

    vector <vector <char>> fence;
    bool direction = false;

    fence.resize(key);

    for (int rails = 0; rails < key; rails++) {
        fence[rails].resize(encrypted_text.length());
    }

    int line = 0;
    for (int j = 0; j < encrypted_text.length(); j++) {
        fence[line][j] = '*';

        if (!direction) {
            line++;
            if (line == key - 1) direction = true;
        }
        else {
            line--;
            if (line == 0) direction = false;
        }
    }

    int symbol_num = 0;
    for (int i = 0; i < fence.size(); i++) {
        for (int j = 0; j < fence[i].size(); j++) {
            if (fence[i][j] == '*') {
                fence[i][j] = encrypted_text[symbol_num];
                symbol_num++;
            }
        }
    }

    direction = false;

    line = 0;
    for (int j = 0; j < encrypted_text.length(); j++) {
        dec_text += fence[line][j];

        if (!direction) {
            line++;
            if (line == key - 1) direction = true;
        }
        else {
            line--;
            if (line == 0) direction = false;
        }
    }

    FileInput(file_directory, dec_text);

    cout << "Decrypted text: " << dec_text << endl;
}