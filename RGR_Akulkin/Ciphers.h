#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int ReadInt();

void FileInput(string const& file_directory, string const& input_text);
string FileOutput(string const& file_directory);

void AtbashEnDecode(string const& input_text, string const& file_directory);

int Euler(int const& input);
bool checkPrime(int const& num);
int mutuallyPrime(int const& num1, int const& num2);

void RSA_E_D(string const& input_text, string const& file_directory);
void RSA_Encode(string const& input_text, string const& file_directory, int const& e, int const& p, int const& q, int& d);
void RSA_Decode(string const& input_text, string const& file_directory, int const& d, int const& n);

void RailFenceEncode(string const& input_text, string const& file_directory, int const& key);
void RailFenceDecode(string const& input_text, string const& file_directory, int const& key);