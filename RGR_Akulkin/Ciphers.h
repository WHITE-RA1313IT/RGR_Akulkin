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

void AtbashEnDecode(string const& file_directory);

int Euler(int const& input);
int mutuallyPrime(int const& num1, int const& num2);
int mutuallyInverse(int num, int euler_func);
int mod(int a0, int x0, int p0);

void RSA_Encode(string const& file_directory);
void RSA_Decode(string const& file_directory);

void RailFenceEncode(string const& file_directory);
void RailFenceDecode(string const& file_directory);